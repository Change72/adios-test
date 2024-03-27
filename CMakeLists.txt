cmake_minimum_required(VERSION 3.12)
project(adios_test)

set(CMAKE_CXX_STANDARD 11)

set(ADIOS_DIR "/data/gc/rocksdb-index/ADIOS2")
include_directories(${ADIOS_DIR}/include)
set(ADIOS2_LIBRARY ${ADIOS_DIR}/adios2-build/lib/libadios2_core.so)

add_executable(adios_test
        TestNdCopy.cpp ${ADIOS2_LIBRARY})

target_link_libraries(adios_test ${ADIOS2_LIBRARY})
