###########################################################################
##  Copyright 2011-2015, 2024 by Raymond Wan (rwan.work@gmail.com)
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
cmake_minimum_required (VERSION 3.5 FATAL_ERROR)

##  Set policy CMP0144 to "new" (Run "cmake --help-policy CMP0144" for details.)
cmake_policy (SET CMP0144 NEW)


########################################
##  Define the project name and target(s)

set (CURR_PROJECT_NAME "Common")
set (TARGET_NAME_LIB "common")
set (TARGET_NAME_EXEC "common_exe")

add_executable (${TARGET_NAME_EXEC} "")


########################################
##  Set the C++ standard

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

##  Use target_compile_features () for macOS
target_compile_features (${TARGET_NAME_EXEC} PUBLIC cxx_std_11)


########################################
##  Set the C++ standard

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

##  Use target_compile_features () for macOS
target_compile_features (${TARGET_NAME_EXEC} PUBLIC cxx_std_11)


########################################
##  Define the source files

##  Source files for both the test executable and library
set (CPP_FILES
)

##  Source files for just the text executable
set (EXE_CPP_FILES
  main.cpp
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

##  Include externally defined modules
include (add_subdirectory_once)


########################################
##  Set up the software

include (initial-msg)

project (${CURR_PROJECT_NAME} VERSION 1.0 DESCRIPTION "BitBuffer" LANGUAGES CXX)
message (STATUS "Setting up ${CURR_PROJECT_NAME}...")


########################################
##  Set initial compilation flags

include (compile-flags)


########################################
##  Obtain the Git hash and version

include (git-hash)
include (version)


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
  set_property (TARGET common_exe PROPERTY OUTPUT_NAME common)

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
##  Documentation

include (doxygen)


########################################
##  Show final message

include (final-msg)


########################################
##  Testing

enable_testing ()
add_test (NAME Common-Architecture COMMAND ${TARGET_NAME_EXEC})


