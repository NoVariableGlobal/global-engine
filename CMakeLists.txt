cmake_minimum_required(VERSION 3.6)
project(global_engine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB OGRE_DIR "${global_engine_SOURCE_DIR}/deps/ogre-*")
message("OGRE_DIR = ${OGRE_DIR}")

# Append _d for debug builds
set(CMAKE_DEBUG_POSTFIX "_d")

file(GLOB_RECURSE OGRE_LIBRARIES "{OGRE_DIR}/*.lib")
set(OGRE_INCLUDE_DIR "${OGRE_DIR}/include/OGRE")
include_directories(${OGRE_INCLUDE_DIR})

file(GLOB_RECURSE global_engine_SOURCES "src/*.cpp")
add_executable(global_engine ${global_engine_SOURCES})

set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")
file (GLOB_RECURSE DEPENDENCY_DLLS "${OGRE_DIR}/*.dll")
file(COPY ${DEPENDENCY_DLLS} DESTINATION "${BIN_DIR}")
target_link_libraries(global_engine ${OGRE_LIBRARIES})
