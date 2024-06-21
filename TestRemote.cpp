#include <iostream>
#include <vector>
#include <adios2.h>
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

int main(int argc, char **argv) {
    std::string bpFileName = "/home/4cv/project/ADIOS2-Original/build/tmp_file";

    int i = 1;
    while (i < argc)
    {
        if (std::string(argv[i]) == "-f") {
            bpFileName = std::string(argv[i + 1]);
            i++;
        }
        else if (std::string(argv[i]) == "-h" or std::string(argv[i]) == "--help") {
            std::cout << "Usage: " << argv[0] << " [-f bpFileName]" << std::endl;
            return 0;
        }
        i++;
    }

    adios2::ADIOS adios;
    adios2::IO bpIO = adios.DeclareIO("input");
    adios2::Engine bpReader = bpIO.Open(bpFileName, adios2::Mode::Read);

    bpReader.BeginStep();
    const std::map<std::string, adios2::Params> variables = bpIO.AvailableVariables();

    int rank = 0;

    for (const auto &variablePair : variables)
    {
        std::cout << "Name: " << variablePair.first;

        for (const auto &parameter : variablePair.second)
        {
            std::cout << "\t" << parameter.first << ": " << parameter.second << "\n";
        }
    }

    /** Write variable for buffering */
    adios2::Variable<int> bpInts = bpIO.InquireVariable<int>("i32");

    const std::size_t Nx = 10;

    if (bpInts) // means not found
    {
        std::vector<int> myInts;
        // read only the chunk corresponding to our rank
        bpInts.SetSelection({{Nx * rank}, {Nx}});

        bpReader.Get(bpInts, myInts, adios2::Mode::Sync);

        std::cout << "myInts: \n";
        for (const auto number : myInts)
        {
            std::cout << number << " ";
        }
        std::cout << "\n";
    }
    // bpReader.PerformGets();

    bool RowMajorOrdering = true;


    BP5ArrayRequest Req;
    Req.VarName = "i32";
    Req.RelStep = 0;
    Req.BlockID = -1;
    Req.Count = {Nx};
    Req.Start = {Nx * rank};

    // [verified] method 1: use new
//    Req.Data = new int32_t [Nx];

    // [verified] method 2: use std::vector
//    std::vector<int> srcData;
//    srcData.resize(Nx);
//    Req.Data = srcData.data();

    // [verified] method 3: use std::unique_ptr for a different pointer variable
//    std::unique_ptr<int32_t[]> srcData(new int32_t[Nx]);

    // [verified] method 4: use malloc
//    Req.Data = malloc(Nx * sizeof(int32_t));

    // [verified] method 5: use Req.Data and convert std::unique_ptr to void*
//    std::unique_ptr<int32_t[]> srcData(new int32_t[Nx]);
//    Req.Data = srcData.get();

    // [verified] method 6: use auto and std::unique_ptr, new
    auto srcData = std::unique_ptr<int32_t[]>(new int32_t[Nx]);
    Req.Data = srcData.get();

    // method 7: use Template T to replace int32_t



    PendingGetRequests.push_back(Req);


    if (getenv("DoRemote"))
    {
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
//                std::cout << " cc " << srcData[i] << " ";

                 std::cout << ((int32_t *) Req.Data)[i] << " ";
                 std::cout << " zz ";
//                std::cout << srcData[i] << " ";

//                std::cout << srcData[i] << " ";

            }
            std::cout << std::endl;

        }


    }


    /** Close bp file, engine becomes unreachable after this*/
    bpReader.Close();

    return 0;
  
};