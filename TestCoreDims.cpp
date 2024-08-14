#include <iostream>
#include <vector>
#include <algorithm>
//#include <adios2/helper/adiosType.h>
const size_t MAX_DIMS = 32;

// Assuming CoreDims and DimsArray definitions are included here
//using namespace adios2::helper;

class CoreDims
{
private:
    const size_t DimCount;
    size_t *const DimensSpan = NULL;

public:
    // Overloading [] operator to access elements in array style
    const size_t &operator[](size_t index) const { return DimensSpan[index]; }
    size_t &operator[](size_t index) { return DimensSpan[index]; }
    CoreDims() : DimCount(0), DimensSpan(NULL) {}

    // Warning!!! CoreDims is essentially a Span.  It does not own the
    // memory that its [] operators access.  Users must ensure that
    // memory remains valid as long as it is necessary.  If you don't
    // know the memory will be valid the entire time, use the
    // DimsArray class which copies the dimension data.
    CoreDims(const std::vector<size_t> &vec) : DimCount(vec.size()), DimensSpan((size_t*)vec.data()) {}
    CoreDims(size_t count, size_t *span_val) : DimCount(count), DimensSpan(span_val) {}

    size_t size() const { return DimCount; }
    bool empty() const { return DimCount == 0; }
    // iterator
    typedef const size_t *const_iterator;
    const_iterator begin() const { return &DimensSpan[0]; }
    const_iterator end() const { return &DimensSpan[DimCount]; }
    typedef size_t *iterator;
    iterator begin() { return &DimensSpan[0]; }
    iterator end() { return &DimensSpan[DimCount]; }
    friend std::ostream &operator<<(std::ostream &os, const CoreDims &m)
    {
        os << "{";
        for (size_t i = 0; i < m.size(); i++)
        {
            os << m[i];
            if (i < m.size() - 1)
                os << ", ";
        }
        return os << "}";
    }
};

class DimsArray : public CoreDims
{
private:
    size_t Dimensions[MAX_DIMS];

public:
    //  constructor with no init of values
    DimsArray(const size_t count) : CoreDims(count, &Dimensions[0]) {}

    //  constructor with single init value
    DimsArray(const size_t count, const size_t init) : CoreDims(count, &Dimensions[0])
    {
        for (size_t i = 0; i < count; i++)
        {
            Dimensions[i] = init;
        }
    }
    //  constructor from vector
    DimsArray(const std::vector<size_t> vec) : CoreDims(vec.size(), &Dimensions[0])
    {
        for (size_t i = 0; i < vec.size(); i++)
        {
            Dimensions[i] = vec[i];
        }
    }
    //  constructor from address
    DimsArray(const size_t count, const size_t *arr) : CoreDims(count, &Dimensions[0])
    {
        for (size_t i = 0; i < count; i++)
        {
            Dimensions[i] = arr[i];
        }
    }
    DimsArray(const CoreDims &d1) : CoreDims(d1.size(), &Dimensions[0])
    {
        std::copy(d1.begin(), d1.end(), &Dimensions[0]);
    }

};

int main() {
    /*
    // Using CoreDims with a vector
    std::vector<size_t> vec = {1, 2, 3, 4, 5};
    CoreDims coreDims(vec);
    std::cout << "CoreDims from vector: " << coreDims << std::endl;

    // Using DimsArray with different constructors
    DimsArray dims1(5);  // Initialize with no values
    std::cout << "DimsArray with no values: " << dims1 << std::endl;

    DimsArray dims2(5, 42);  // Initialize with a single value
    std::cout << "DimsArray with single value: " << dims2 << std::endl;

    DimsArray dims3(vec);  // Initialize from vector
    std::cout << "DimsArray from vector: " << dims3 << std::endl;

    size_t arr[] = {10, 20, 30, 40, 50};
    DimsArray dims4(5, arr);  // Initialize from array
    std::cout << "DimsArray from array: " << dims4 << std::endl;

    // Copying from CoreDims
    DimsArray dims5(coreDims);
    std::cout << "DimsArray copied from CoreDims: " << dims5 << std::endl;

    // Declare a pointer to DimsArray
    DimsArray* dimsPointer = nullptr;

    // Later, you can decide the count
    size_t count = 5; // Example count
    dimsPointer = new DimsArray(count);

    // Now you can initialize the array with values
    for (size_t i = 0; i < count; ++i) {
        (*dimsPointer)[i] = i + 1;
    }

    CoreDims& d1 = *dimsPointer;
    DimsArray dimsPointer4(d1);

    // dimsPointer2 by copy constructor
    DimsArray dimsPointer2(reinterpret_cast<CoreDims&>(*dimsPointer));

    // only copy the pointer, and will change the original value
//    DimsArray dimsPointer2(*dimsPointer);


    // dimsPoint3 by std::copy
//    DimsArray dimsPointer3(count, &(*dimsPointer)[0]);

//    DimsArray dimsPointer3(reinterpret_cast<CoreDims&>(dimsPointer2));
    DimsArray dimsPointer3(dimsPointer2);

//    DimsArray dimsPointer3 = dimsPointer2;

    // Use the DimsArray pointer
    std::cout << "DimsArray initialized via pointer: " << *dimsPointer << std::endl;
    std::cout << "DimsArray copied from pointer: " << dimsPointer2 << std::endl;

    dimsPointer2[1] = 100;
    dimsPointer3[1] = 50;
    std::cout << "dimsPointer: " << *dimsPointer << std::endl;
    std::cout << "dimsPointer2: " << dimsPointer2 << std::endl;
    std::cout << "dimsPointer3: " << dimsPointer3 << std::endl;

    // Clean up and deallocate memory
    delete dimsPointer;
*/
    DimsArray dims1(5, 42);  // Initialize with a single value
    std::cout << "DimsArray with single value: " << dims1 << std::endl;

    DimsArray dims2(dims1);
    std::cout << "DimsArray copied from dims1: " << dims2 << std::endl;

    std::cout << "-------------------" << std::endl;

    dims2[1] = 100;
    std::cout << "dims1: " << dims1 << std::endl;
    std::cout << "dims2: " << dims2 << std::endl;
    std::cout << "-------------------" << std::endl;

    DimsArray dims3 = dims1;
    dims3[1] = 50;
    std::cout << "dims1: " << dims1 << std::endl;
    std::cout << "dims2: " << dims2 << std::endl;
    std::cout << "dims3: " << dims3 << std::endl;

    return 0;
}