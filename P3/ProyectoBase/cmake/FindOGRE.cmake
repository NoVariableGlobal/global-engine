file(GLOB OGRE_DIR "${global_engine_SOURCE_DIR}/deps/ogre")

message("OGRE_DIR = ${OGRE_DIR}")
message("OGRE_INCLUDE_DIR = ${OGRE_INCLUDE_DIR}")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
	set(OGRE_BIN_DIR "${OGRE_DIR}/bin/release")
	file(GLOB_RECURSE OGRE_LIBRARIES "${OGRE_DIR}/lib/release/*.lib")
else ()
	set(OGRE_BIN_DIR "${OGRE_DIR}/bin/debug")
	file(GLOB_RECURSE OGRE_LIBRARIES "${OGRE_DIR}/lib/debug/*.lib")
endif ()

set(OGRE_INCLUDE_DIR "${OGRE_DIR}/include")
include_directories(${OGRE_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(OGRE
                                  REQUIRED_VARS OGRE_DIR OGRE_LIBRARIES OGRE_INCLUDE_DIR OGRE_BIN_DIR
                                  VERSION_VAR "1.12.5")
