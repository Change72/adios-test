cmake_minimum_required(VERSION 3.12)
project(adios_test)

set(CMAKE_CXX_STANDARD 11)

set(SW_DIR "/home/4cv/project/ADIOS2-Cache/build-cache/sw")

set(ADIOS_DIR ${SW_DIR}/adios2)
include_directories(${ADIOS_DIR}/include)
set(ADIOS2_LIBRARY ${ADIOS_DIR}/lib/libadios2_core.so)

add_subdirectory(KWSys)

add_executable(adios_ndcopy TestNdCopy.cpp)
target_link_libraries(adios_ndcopy ${ADIOS2_LIBRARY})

add_executable(adios_contained_cache TestContainedCache.cpp QueryBox.h TestInteractionCut.cpp)
target_link_libraries(adios_contained_cache ${ADIOS2_LIBRARY})

add_executable(adios_ndcut TestInteractionCut.cpp)
target_link_libraries(adios_ndcut ${ADIOS2_LIBRARY})

add_executable(adios_query_box TestQueryBox.cpp)
target_link_libraries(adios_query_box ${ADIOS2_LIBRARY})

add_executable(adios_base64 TestKWSysBase64.cpp)
target_link_libraries(adios_base64 adios2sys_interface)

set(HIREDIS ${SW_DIR}/hiredis)
include_directories(${HIREDIS}/include)
set(HIREDIS_LIBRARY ${HIREDIS}/lib/libhiredis.so)

add_executable(adios_redis TestHiRedis.cpp KVCacheCommon.h KVCacheCommon.cpp)
target_link_libraries(adios_redis ${HIREDIS_LIBRARY} adios2sys_interface)

add_subdirectory(atl)
add_subdirectory(dill)
add_subdirectory(ffs)
add_subdirectory(EVPath)

find_package(atl REQUIRED)
find_package(dill REQUIRED)
find_package(ffs REQUIRED)
find_package(EVPath REQUIRED)


set(SW_DIR "/home/4cv/project/ADIOS2-Original/build/sw")
set(ADIOS_DIR ${SW_DIR}/adios2)
include_directories(${ADIOS_DIR}/include)
# Link all required ADIOS2 libraries
set(ADIOS2_LIBRARIES
        ${ADIOS_DIR}/lib/libadios2_core.so
        ${ADIOS_DIR}/lib/libadios2_c.so
        ${ADIOS_DIR}/lib/libadios2_cxx11.so # required by #include <adios2.h> in TestRemote.cpp
)

add_executable(adios_remote TestRemote.cpp)
target_link_libraries(adios_remote ${ADIOS2_LIBRARIES} EVPath::EVPath ffs::ffs dill::dill atl::atl)