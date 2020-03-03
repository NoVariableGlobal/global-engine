file(GLOB JSON_CPP_DIR "${global_engine_SOURCE_DIR}/deps/jsoncpp")
file(GLOB_RECURSE JSON_CPP_LIBRARIES "${JSON_CPP_DIR}/lib/*.lib")
set(JSON_CPP_INCLUDE_DIR "${JSON_CPP_DIR}/include")
include_directories(${JSON_CPP_INCLUDE_DIR})

message("JSON_CPP_DIR = ${JSON_CPP_DIR}")
message("JSON_CPP_INCLUDE_DIR = ${JSON_CPP_INCLUDE_DIR}")

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(JsonCpp
                                  REQUIRED_VARS JSON_CPP_DIR JSON_CPP_LIBRARIES JSON_CPP_INCLUDE_DIR
                                  VERSION_VAR "1.9.2")
