file(GLOB FMOD_DIR "${global_engine_SOURCE_DIR}/deps/fmod")
file(GLOB_RECURSE FMOD_LIBRARIES "${FMOD_DIR}/lib/*.lib")
set(FMOD_INCLUDE_DIR "${FMOD_DIR}/include")
include_directories(${FMOD_INCLUDE_DIR})

message("FMOD_DIR = ${FMOD_DIR}")
message("FMOD_INCLUDE_DIR = ${FMOD_INCLUDE_DIR}")
message("FMOD_LIBRARIES = ${FMOD_LIBRARIES}")

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(FMOD
                                  REQUIRED_VARS FMOD_DIR FMOD_LIBRARIES FMOD_INCLUDE_DIR
                                  VERSION_VAR "2.0.8")
