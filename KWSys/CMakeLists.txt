#message_start_thirdparty()

message(STATUS "Adding adios2sys for thirdparty/KWSys")

set(KWSYS_NAMESPACE adios2sys)
set(KWSYS_USE_CommandLineArguments ON)
set(KWSYS_USE_DynamicLoader ON)
set(KWSYS_USE_RegularExpression ON)
set(KWSYS_USE_SystemTools ON)
set(KWSYS_USE_Base64 ON)
set(KWSYS_USE_MD5 ON)

if(WIN32)
  set(KWSYS_BUILD_SHARED OFF)
else()
  set(KWSYS_BUILD_SHARED ${BUILD_SHARED_LIBS})
endif()
set(KWSYS_SPLIT_OBJECTS_FROM_INTERFACE ON)
set(KWSYS_INSTALL_EXPORT_NAME adios2Exports)
set(KWSYS_INSTALL_LIB_DIR ${CMAKE_INSTALL_LIBDIR})

add_subdirectory(adios2sys)
add_library(adios2sys_interface ALIAS adios2sys_private)

#message_end_thirdparty()
