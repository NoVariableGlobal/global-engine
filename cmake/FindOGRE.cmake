file(GLOB OGRE_DIR "${global_engine_SOURCE_DIR}/deps/ogre-*")
file(GLOB_RECURSE OGRE_LIBRARIES "${OGRE_DIR}/*.lib")
set(OGRE_INCLUDE_DIR "${OGRE_DIR}/include/OGRE")
include_directories(${OGRE_INCLUDE_DIR})

message("OGRE_DIR = ${OGRE_DIR}")
message("OGRE_INCLUDE_DIR = ${OGRE_INCLUDE_DIR}")

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(OGRE
                                  REQUIRED_VARS OGRE_DIR OGRE_LIBRARIES OGRE_INCLUDE_DIR
                                  VERSION_VAR "1.12.5")