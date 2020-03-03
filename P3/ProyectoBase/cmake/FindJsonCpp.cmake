file(GLOB JSON_CPP_DIR "${global_engine_SOURCE_DIR}/deps/jsoncpp")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
	file(GLOB_RECURSE JSON_CPP_LIBRARIES "${JSON_CPP_DIR}/lib/release/*.lib")
else ()
	file(GLOB_RECURSE JSON_CPP_LIBRARIES "${JSON_CPP_DIR}/lib/debug/*.lib")
endif ()

set(JSON_CPP_INCLUDE_DIR "${JSON_CPP_DIR}/include")
include_directories(${JSON_CPP_INCLUDE_DIR})

message("JSON_CPP_DIR = ${JSON_CPP_DIR}")
message("JSON_CPP_INCLUDE_DIR = ${JSON_CPP_INCLUDE_DIR}")
message("JSON_CPP_LIBRARIES = ${JSON_CPP_LIBRARIES}")

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(JsonCpp
                                  REQUIRED_VARS JSON_CPP_DIR JSON_CPP_LIBRARIES JSON_CPP_INCLUDE_DIR
                                  VERSION_VAR "1.9.2")
