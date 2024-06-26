#include <iostream>
#include <vector>
#include <adios2.h>
#include <memory>
#include <cstring>
#include <hiredis/hiredis.h>
#include "adios2/toolkit/remote/EVPathRemote.h"

enum RequestTypeEnum
{
    Global = 0,
    Local = 1
};

struct BP5ArrayRequest
{
    void *VarRec = NULL;
    char *VarName;
    enum RequestTypeEnum RequestType;
    size_t Step;    // local operations use absolute steps
    size_t RelStep; // preserve Relative Step for remote
    size_t BlockID;
    adios2::Dims Start;
    adios2::Dims Count;
    adios2::MemorySpace MemSpace;
    void *Data;
};
std::vector<BP5ArrayRequest> PendingGetRequests;

void store_to_redis(const char *key, int32_t *data, size_t length)
{
    // Connect to Redis server
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err)
    {
        if (c)
        {
            std::cerr << "Connection error: " << c->errstr << std::endl;
            redisFree(c);
        }
        else
        {
            std::cerr << "Connection error: can't allocate redis context" << std::endl;
        }
        exit(1);
    }

    // Serialize the data into a binary format
    size_t data_size = length * sizeof(int32_t);
    redisReply *reply = (redisReply *)redisCommand(c, "SET %s %b", key, data, data_size);
    if (reply == NULL)
    {
        std::cerr << "SET command failed: " << c->errstr << std::endl;
        redisFree(c);
        exit(1);
    }

    std::cout << "SET command result: " << reply->str << std::endl;
    freeReplyObject(reply);

    // Disconnect from Redis server
    redisFree(c);
}

void get_and_print_from_redis(const char *key, size_t length, void *data)
{
    // Connect to Redis server
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err)
    {
        if (c)
        {
            std::cerr << "Connection error: " << c->errstr << std::endl;
            redisFree(c);
        }
        else
        {
            std::cerr << "Connection error: can't allocate redis context" << std::endl;
        }
        exit(1);
    }

    // Retrieve the data
    redisReply *reply = (redisReply *)redisCommand(c, "GET %s", key);
    if (reply == NULL)
    {
        std::cerr << "GET command failed: " << c->errstr << std::endl;
        redisFree(c);
        exit(1);
    }

    if (reply->type != REDIS_REPLY_STRING)
    {
        std::cerr << "Unexpected data type received: " << reply->type << std::endl;
        freeReplyObject(reply);
        redisFree(c);
        exit(1);
    }

    // Deserialize the data
    int32_t *data2 = (int32_t *)reply->str;

    // Print the data
    printf("Retrieved data:\n");
    for (size_t i = 0; i < length; ++i) {
        printf("%d ", data2[i]);
    }
    printf("\n");

    memcpy(data, reply->str, length * sizeof(int32_t));
    
    freeReplyObject(reply);

    // Disconnect from Redis server
    redisFree(c);

    /*
    // return the data
    memcpy(data, reply->str, length * sizeof(int32_t));

    // Print the data
    int32_t *int_data = static_cast<int32_t *>(data);
    std::cout << "Retrieved data:\n";
    for (size_t i = 0; i < length; ++i)
    {
        std::cout << int_data[i] << " ";
    }
    std::cout << std::endl;

    freeReplyObject(reply);
    redisFree(c);
    */
}

template <typename T>
void ProcessData(const std::string &bpFileName, const std::string &varName, size_t Nx, int rank)
{
    adios2::ADIOS adios;
    adios2::IO bpIO = adios.DeclareIO("input");
    adios2::Engine bpReader = bpIO.Open(bpFileName, adios2::Mode::Read);

    bpReader.BeginStep();
    const std::map<std::string, adios2::Params> variables = bpIO.AvailableVariables();

    adios2::Variable<T> bpVar = bpIO.InquireVariable<T>(varName);

    if (bpVar) // means found
    {
        // std::vector<T> myInts;
        // read only the chunk corresponding to our rank
        bpVar.SetSelection({{Nx * rank}, {Nx}});

        // bpReader.Get(bpVar, myInts, adios2::Mode::Sync);

        // change myInts to new int32_t [Nx]
        int32_t *myInts = new int32_t[Nx];
        bpReader.Get(bpVar, myInts, adios2::Mode::Sync);

        std::cout << "myInts: \n";

        for (int i = 0; i < Nx; i++)
        {
            // std::cout << number << " ";
            std::cout << myInts[i] << " ";
        }
        
        // for (const auto number : myInts)
        // {
        //     std::cout << number << " ";
        // }
        std::cout << "\n";
        
        // Store myInts to Redis
        // store_to_redis("myInts", (int32_t *)myInts.data(), Nx);
        store_to_redis("myInts", myInts, Nx);

        free(myInts);

        BP5ArrayRequest Req;
        Req.VarName = const_cast<char *>(varName.c_str());
        Req.RelStep = 0;
        Req.BlockID = -1;
        Req.Count = {Nx};
        Req.Start = {Nx * rank};

        PendingGetRequests.push_back(Req);

        if (getenv("DoRemote"))
        {
            // Use malloc
            Req.Data = malloc(Nx * sizeof(T));
            get_and_print_from_redis("myInts", Nx, Req.Data);

            // print out the data
            std::cout << "Data: ";
            for (int i = 0; i < Nx; i++)
            {
                std::cout << ((T *)Req.Data)[i] << " ";
            }
            std::cout << std::endl;


            /*
            bool RowMajorOrdering = true;
            auto m_Remote = std::unique_ptr<adios2::EVPathRemote>(new adios2::EVPathRemote());

            m_Remote->Open("localhost", adios2::EVPathRemoteCommon::ServerPort, bpFileName, adios2::Mode::Read,
                           RowMajorOrdering);
            std::cout << "===============================================================" << std::endl;
            std::cout << "remote open done" << std::endl;
            for (auto &Req : PendingGetRequests)
            {
                auto handle = m_Remote->Get(Req.VarName, Req.RelStep, Req.BlockID, Req.Count, Req.Start, Req.Data);
                std::cout << "Requested: " << Req.VarName << " " << Req.RelStep << " " << Req.BlockID << std::endl;
                std::cout << "Requested: " << Req.Count[0] << " " << Req.Start[0] << std::endl;
                auto result = m_Remote->WaitForGet(handle);

                std::cout << "Result was " << result << std::endl;

                // print out the data
                std::cout << "Data: ";
                for (int i = 0; i < Nx; i++)
                {
                    std::cout << ((T *)Req.Data)[i] << " cg ";
                }
                std::cout << std::endl;
            }
            */
        }
    }

    bpReader.Close();
}

int main(int argc, char **argv)
{
    std::string bpFileName = "/home/4cv/project/ADIOS2-Original/build/tmp_file";

    int i = 1;
    while (i < argc)
    {
        if (std::string(argv[i]) == "-f")
        {
            bpFileName = std::string(argv[i + 1]);
            i++;
        }
        else if (std::string(argv[i]) == "-h" or std::string(argv[i]) == "--help")
        {
            std::cout << "Usage: " << argv[0] << " [-f bpFileName]" << std::endl;
            return 0;
        }
        i++;
    }

    int rank = 0;
    const std::size_t Nx = 10;

    ProcessData<int32_t>(bpFileName, "i32", Nx, rank);

    return 0;
}
