#
# MIT License
#
# Copyright (c) 2017-2018 Thibault Martinez and Simon Ninon
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#

########## GLOBAL CONFIGURATION ##########

cmake_minimum_required(VERSION 3.1.0)

project(iota VERSION "1.2.1")
enable_language(C CXX)

option(BUILD_TESTING "" OFF)
include(CTest)

#########################################################
# GIT
#########################################################
find_package(Git QUIET)
#####
# Check submodules
#####
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  # This is a .git repo -> nice
  # Update submodules as needed
  option(GIT_SUBMODULE "Check submodules during build" ON)
  if(GIT_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
  endif()
endif()
#####
# Check, if all folders for the submodules are present
#####
set(PROJECT_EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/external")
set(EXTERNAL_DIR_NAME "cpr;json;keccak")

FOREACH(LOCAL_DIR_NAME ${EXTERNAL_DIR_NAME})
    if(NOT EXISTS "${PROJECT_EXTERNAL_DIR}/${LOCAL_DIR_NAME}")
        message(FATAL_ERROR "The submodule ${PROJECT_EXTERNAL_DIR}/${LOCAL_DIR_NAME} was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
    endif()
ENDFOREACH()

# okay all submodules exist
# lets load them and make our dependencies clear

########## MISC CONFIG ##########
set(CUSTOM_CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include("${CUSTOM_CMAKE_MODULE_PATH}/misc.cmake")
set(CUSTOM_PROJECT_SOURCE_DIR  ${PROJECT_SOURCE_DIR}/source/)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CMAKE_MACOSX_RPATH 1)

#set(CMAKE_VERBOSE_MAKEFILE OFF)

########## DEFAULT FOLDERS ##########
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/include)


######### VERSION INCLUDE ##########
string(TOUPPER ${PROJECT_NAME} DUP_PROJECT_NAME)
configure_file(${CUSTOM_CMAKE_MODULE_PATH}/version.hpp.in
               ${PROJECT_INCLUDE_DIR}/${DUP_PROJECT_NAME}/version.hpp)

########## PROJECT FILES ##########
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${CUSTOM_PROJECT_SOURCE_DIR}/*.cpp)

########## LIBRARY ##########
add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES})

# add the submodules dependency options
include(${CUSTOM_CMAKE_MODULE_PATH}/dependency_settings.cmake)
# make the submodules
add_subdirectory("${CUSTOM_CMAKE_MODULE_PATH}")
add_subdirectory("${PROJECT_EXTERNAL_DIR}/cpr")
add_subdirectory("${PROJECT_EXTERNAL_DIR}/json")

########## DEPENDENCIES ##########
add_dependencies(${PROJECT_NAME} cpr nlohmann_json keccak)

########## INCLUDES #############
target_include_directories(${PROJECT_NAME} PUBLIC $<TARGET_PROPERTY:keccak,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(${PROJECT_NAME} PUBLIC $<TARGET_PROPERTY:nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(${PROJECT_NAME} PUBLIC $<TARGET_PROPERTY:cpr,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_INCLUDE_DIR}")

########## COMPILATION SETTINGS ##########
include("${CUSTOM_CMAKE_MODULE_PATH}/compilation_settings.cmake")

########## LINK #############
# we put all needed sources into one library...
target_link_libraries(${PROJECT_NAME} keccak nlohmann_json cpr)

########## install ##########
# ensure lib and bin directories exist
install(CODE "FILE(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})")
install(CODE "FILE(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})")

# install iota.lib.cpp
install(DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ DESTINATION lib USE_SOURCE_PERMISSIONS)
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ DESTINATION bin USE_SOURCE_PERMISSIONS)
install(DIRECTORY ${PROJECT_INCLUDE_DIR}/ DESTINATION include USE_SOURCE_PERMISSIONS)

########## TEST SETTINGS ##########

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
ENDIF()

if (BUILD_TESTS)
  enable_testing()

  # silence gtest compilation warnings..
  add_definitions(-D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
  add_subdirectory("${PROJECT_SOURCE_DIR}/test")
ENDIF()
