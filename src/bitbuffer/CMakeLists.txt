###########################################################################
##  Copyright 2011-2015, 2024-2025 by Raymond Wan (rwan.work@gmail.com)
##    https://github.com/rwanwork/QScores-Archiver
##
##  This file is part of QScores-Archiver.
##
##  QScores-Archiver is free software; you can redistribute it and/or
##  modify it under the terms of the GNU Lesser General Public License
##  as published by the Free Software Foundation; either version
##  3 of the License, or (at your option) any later version.
##
##  QScores-Archiver is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU Lesser General Public License for more details.
##
##  You should have received a copy of the GNU Lesser General Public
##  License along with QScores-Archiver; if not, see
##  <http://www.gnu.org/licenses/>.
###########################################################################


##  Set the minimum required CMake version
##    3.13 required to support target_sources ()
##    3.30 required for the latest behaviour with BOOST (CMP0167)
cmake_minimum_required (VERSION 3.30 FATAL_ERROR)

##  Set policy CMP0144 to "new" (Run "cmake --help-policy CMP0144" for details.)
cmake_policy (SET CMP0144 NEW)


########################################
##  Define the project name and target(s)

set (CURR_PROJECT_NAME "BitBuffer")
set (TARGET_NAME_LIB "bitbuffer")
set (TARGET_NAME_EXEC "bitbuffer_exe")

add_library (${TARGET_NAME_LIB} "")
add_executable (${TARGET_NAME_EXEC} "")


########################################
##  Set up the software

project (${CURR_PROJECT_NAME} VERSION 1.0 DESCRIPTION "BitBuffer" LANGUAGES CXX)
message (STATUS "Setting up ${CURR_PROJECT_NAME}...")


########################################
##  Define the source files

##  Source files for both the test executable and library
set (CPP_FILES
  bitbuffer.cpp
  finish.cpp
  io.cpp
)

##  Source files for just the text executable
set (EXE_CPP_FILES
  main.cpp
  testing.cpp
)

##  Header files for the main program and library
set (HPP_FILES
)

##  Header files for just the main program
set (EXE_HPP_FILES
)


########################################
##  Set the global path

##  If the MAIN_SRC_PATH has not been defined yet
if (NOT DEFINED MAIN_SRC_PATH)
  ##  Set the main source path to the very top
  set (MAIN_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/..")

  ##  Locate where the shared CMake modules are
  list (APPEND CMAKE_MODULE_PATH "${MAIN_SRC_PATH}/cmake")
endif ()


########################################
##  Include modules

##  Include CMake provided modules
##    Provides install variables defined by the GNU Coding Standards
include (GNUInstallDirs)
##    Add FetchContent
include (FetchContent)

##  Include modules provided in this repository

##    Initial message
if (PROJECT_IS_TOP_LEVEL)
  include (initial-msg)
endif ()

##    Set initial compilation flags
include (compile-flags)

##    Obtain the Git hash
include (git-hash)

##    Obtain the version
include (version)

##    Add subdirectories onced
include (add_subdirectory_once)

##  Set up for Boost
include (boost)

##  Set up for documentation
include (doxygen)


########################################
##  Create configuration file

##  Configure a header file to pass some of the CMake settings
##  to the source code.
##
##  The output header file is placed at the top-level binary directory.
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/${CURR_PROJECT_NAME}_Config.hpp.in"
  "${CMAKE_BINARY_DIR}/generated/${CURR_PROJECT_NAME}_Config.hpp"
  @ONLY
)

##  Include the generated/ directory so that the created configuration
##    file can be located
include_directories (${CMAKE_BINARY_DIR}/generated)


########################################
##  Update the targets

##  Update an executable
if (TARGET ${TARGET_NAME_EXEC})
  ##  Add sources to the target
  target_sources (${TARGET_NAME_EXEC} PRIVATE ${CPP_FILES})
  target_sources (${TARGET_NAME_EXEC} PRIVATE ${EXE_CPP_FILES})
  target_sources (${TARGET_NAME_EXEC} PRIVATE ${HPP_FILES})
  target_sources (${TARGET_NAME_EXEC} PRIVATE ${EXE_HPP_FILES})

  ##  Rename the executable
  set_property (TARGET bitbuffer_exe PROPERTY OUTPUT_NAME bitbuffer)

  install (TARGETS ${TARGET_NAME_EXEC} DESTINATION bin)
endif ()


##  Update a library
if (TARGET ${TARGET_NAME_LIB})
  ##  Add sources to the target
  target_sources (${TARGET_NAME_LIB} PRIVATE ${CPP_FILES})
  target_sources (${TARGET_NAME_LIB} PRIVATE ${HPP_FILES})

  install (TARGETS ${TARGET_NAME_LIB} DESTINATION lib)
endif ()

##  Set the output directory of the libraries to the top-level binary directory
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


########################################
##  Add dependencies and directories

##  Location of additional header files
target_include_directories (${TARGET_NAME_EXEC} PUBLIC ${MAIN_SRC_PATH}/common)

target_include_directories (${TARGET_NAME_LIB} PUBLIC ${MAIN_SRC_PATH}/common)


########################################
##  Show final message

if (PROJECT_IS_TOP_LEVEL)
  include (final-msg)
endif ()


########################################
##  Testing

enable_testing ()
add_test (NAME BitBuffer-ShowInfo COMMAND ${TARGET_NAME_EXEC} 1)
add_test (NAME BitBuffer-Power2Limit COMMAND ${TARGET_NAME_EXEC} 2)
add_test (NAME BitBuffer-Power2 COMMAND ${TARGET_NAME_EXEC} 3)
add_test (NAME BitBuffer-FixedLength COMMAND ${TARGET_NAME_EXEC} 4)
add_test (NAME BitBuffer-Variable_Length COMMAND ${TARGET_NAME_EXEC} 5)
add_test (NAME BitBuffer-TestUnsignedInts COMMAND ${TARGET_NAME_EXEC} 6)
add_test (NAME BitBuffer-TestUnsignedChars COMMAND ${TARGET_NAME_EXEC} 7)

