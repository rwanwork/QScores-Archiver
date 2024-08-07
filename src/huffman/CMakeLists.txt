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

set (CURR_PROJECT_NAME "Huffman")
set (TARGET_NAME_LIB "huffman")
set (TARGET_NAME_EXEC "huffman_exe")

add_library (${TARGET_NAME_LIB} "")
add_executable (${TARGET_NAME_EXEC} "")


########################################
##  Set the C++ standard

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

##  Use target_compile_features () for macOS
target_compile_features (${TARGET_NAME_LIB} PUBLIC cxx_std_11)
target_compile_features (${TARGET_NAME_EXEC} PUBLIC cxx_std_11)


########################################
##  Define the source files

##  Source files for both the test executable and library
set (CPP_FILES
  debug.cpp
  decode.cpp
  encode.cpp
  huffman.cpp
  process.cpp
  sort.cpp
)

##  Source files for just the text executable
set (EXE_CPP_FILES
  main-test.cpp
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

##  Include externally defined modules
include (add_subdirectory_once)


########################################
##  Set up the software

include (initial-msg)

project (${CURR_PROJECT_NAME} VERSION 1.0 DESCRIPTION "Huffman Coding" LANGUAGES CXX)
message (STATUS "Setting up ${CURR_PROJECT_NAME}...")


########################################
##  Set initial compilation flags

include (compile-flags)


########################################
##  Obtain the Git hash and version

include (git-hash)
include (version)


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
  set_property (TARGET huffman_exe PROPERTY OUTPUT_NAME huffman)

  target_link_libraries (${TARGET_NAME_EXEC} bitbuffer)
  target_link_libraries (${TARGET_NAME_EXEC} bitio)
  target_link_libraries (${TARGET_NAME_EXEC} interpolative)

  install (TARGETS ${TARGET_NAME_EXEC} DESTINATION bin)
endif ()


##  Update a library
if (TARGET ${TARGET_NAME_LIB})
  ##  Add sources to the target
  target_sources (${TARGET_NAME_LIB} PRIVATE ${CPP_FILES})
  target_sources (${TARGET_NAME_LIB} PRIVATE ${HPP_FILES})

  target_link_libraries (${TARGET_NAME_LIB} bitbuffer)
  target_link_libraries (${TARGET_NAME_LIB} bitio)
  target_link_libraries (${TARGET_NAME_LIB} interpolative)

  install (TARGETS ${TARGET_NAME_LIB} DESTINATION lib)
endif ()

##  Set the output directory of the libraries to the top-level binary directory
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


########################################
##  Add dependencies and directories

##  Location of additional header files
target_include_directories (${TARGET_NAME_EXEC} PUBLIC ${MAIN_SRC_PATH}/bitbuffer)
target_include_directories (${TARGET_NAME_EXEC} PUBLIC ${MAIN_SRC_PATH}/bitio)
target_include_directories (${TARGET_NAME_EXEC} PUBLIC ${MAIN_SRC_PATH}/interpolative)

target_include_directories (${TARGET_NAME_LIB} PUBLIC ${MAIN_SRC_PATH}/bitbuffer)
target_include_directories (${TARGET_NAME_LIB} PUBLIC ${MAIN_SRC_PATH}/bitio)
target_include_directories (${TARGET_NAME_LIB} PUBLIC ${MAIN_SRC_PATH}/interpolative)

##  Location of module dependencies
add_subdirectory_once (${MAIN_SRC_PATH}/common ${CMAKE_CURRENT_BINARY_DIR}/common)
add_subdirectory_once (${MAIN_SRC_PATH}/bitbuffer ${CMAKE_CURRENT_BINARY_DIR}/bitbuffer)
add_subdirectory_once (${MAIN_SRC_PATH}/bitio ${CMAKE_CURRENT_BINARY_DIR}/bitio)
add_subdirectory_once (${MAIN_SRC_PATH}/interpolative ${CMAKE_CURRENT_BINARY_DIR}/interpolative)


########################################
##  Documentation

include (doxygen)


########################################
##  Show final message

include (final-msg)


########################################
##  Testing

enable_testing ()
add_test (NAME Huffman-ShowInfo COMMAND ${TARGET_NAME_EXEC} 1)
add_test (NAME Huffman-Simple1 COMMAND ${TARGET_NAME_EXEC} 2)
add_test (NAME Huffman-Simple2 COMMAND ${TARGET_NAME_EXEC} 3)
add_test (NAME Huffman-Simple3 COMMAND ${TARGET_NAME_EXEC} 4)
add_test (NAME Huffman-CACA COMMAND ${TARGET_NAME_EXEC} 5)
add_test (NAME Huffman-Random COMMAND ${TARGET_NAME_EXEC} 6)
