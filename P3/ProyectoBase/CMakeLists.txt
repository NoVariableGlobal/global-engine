cmake_minimum_required(VERSION 3.6)
project(global_engine)

set(CMAKE_CXX_STANDARD 14)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# Print the compiler flags for debugging purposes.
message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG = ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE = ${CMAKE_CXX_FLAGS_RELEASE}")

# Set the cmake module path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${global_engine_SOURCE_DIR}/cmake/")
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

# Append _d for debug builds.
set(CMAKE_DEBUG_POSTFIX "_d")

# Find all libraries.
find_package(FMOD REQUIRED)
find_package(OGRE REQUIRED)
find_package(JsonCpp REQUIRED)

# Copy all assets.
include_directories(Src)

# Add all .cpp source files to the global-engine executable.
file(GLOB_RECURSE global_engine_SOURCES "Src/*.cpp")
add_executable(global_engine ${global_engine_SOURCES})

# Copy all the DLLs from OGRE to the BIN_DIR destination.
file(GLOB_RECURSE DEPENDENCY_DLLS "${OGRE_BIN_DIR}/*.dll")
file(COPY ${DEPENDENCY_DLLS} DESTINATION "${BIN_DIR}")

# Link the libraries and install them
target_link_libraries(global_engine ${OGRE_LIBRARIES} ${FMOD_LIBRARIES} ${JSON_CPP_LIBRARIES})
install(TARGETS global_engine RUNTIME DESTINATION ${BIN_DIR})
