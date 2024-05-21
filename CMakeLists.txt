cmake_minimum_required(VERSION 3.12)
project(adios_test)

set(CMAKE_CXX_STANDARD 11)

set(ADIOS_DIR "/data/gc/rocksdb-index/ADIOS2")
include_directories(${ADIOS_DIR}/include)
set(ADIOS2_LIBRARY ${ADIOS_DIR}/build/lib/libadios2_core.so)

add_executable(adios_ndcopy TestNdCopy.cpp ${ADIOS2_LIBRARY})
target_link_libraries(adios_ndcopy ${ADIOS2_LIBRARY})

add_executable(adios_contained_cache TestContainedCache.cpp ${ADIOS2_LIBRARY} QueryBox.h TestInteractionCut.cpp)
target_link_libraries(adios_contained_cache ${ADIOS2_LIBRARY})

add_executable(adios_ndcut TestInteractionCut.cpp ${ADIOS2_LIBRARY})
target_link_libraries(adios_ndcut ${ADIOS2_LIBRARY})

add_executable(adios_query_box TestQueryBox.cpp ${ADIOS2_LIBRARY})
target_link_libraries(adios_query_box ${ADIOS2_LIBRARY})
