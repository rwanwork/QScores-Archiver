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
##  Variables specific to this project
SET (TARGET_NAME "bitio")
SET (TARGET_NAME_EXEC "bitio-test")
SET (CURR_PROJECT_NAME "BitIO")

##  Source files for both the test executable and library
SET (SRC_FILES
  binary.cpp
  bytecode.cpp
  delta.cpp
  gamma.cpp
  golomb.cpp
  math_utils.cpp
  rice.cpp
  unary.cpp
)

##  Source files for just the text executable
SET (TEST_FILES
  main-test.cpp
  parameters-test.cpp
  test_random.cpp
  test_sequential.cpp
  test_showlengths.cpp
)

##  Header files that are included by other libraries / programs
SET (HEADER_FILES
)


########################################
##  Set the main source path to the very top

##  Set the main path and where additional CMake modules are
IF (NOT DEFINED MAIN_SRC_PATH)
  SET (MAIN_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/..")

  ##  Locate where the shared CMake modules are
  SET (CMAKE_MODULE_PATH "${MAIN_SRC_PATH}/cmake")
ENDIF (NOT DEFINED MAIN_SRC_PATH)

##  Include externally defined functions
INCLUDE (global)
INCLUDE (add_subdirectory_once)


########################################
##  Set up the software

##  Project name
PROJECT (${CURR_PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)
# ENABLE_LANGUAGE (C)
MESSAGE (STATUS "Setting up ${PROJECT_NAME}, version ${PROJECT_VERSION}...")

include (initial-msg)


########################################
##  Create configuration file

##  Configure a header file to pass some of the CMake settings
##  to the source code.
##  
##  The output header file is placed at the top-level binary directory.
CONFIGURE_FILE (
  "${PROJECT_SOURCE_DIR}/${CURR_PROJECT_NAME}Config.hpp.in"
  "${CMAKE_BINARY_DIR}/${CURR_PROJECT_NAME}Config.hpp"
  @ONLY
)


########################################
##  Create the targets

##  Set the output directory of the libraries to the top-level binary directory
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

##  Create the test executable
IF (NOT TARGET ${TARGET_NAME_EXEC})
  ADD_EXECUTABLE (${TARGET_NAME_EXEC} ${TEST_FILES} ${SRC_FILES})
  TARGET_LINK_LIBRARIES (${TARGET_NAME_EXEC} bitbuffer)
  INSTALL (TARGETS ${TARGET_NAME_EXEC} DESTINATION bin)
ENDIF (NOT TARGET ${TARGET_NAME_EXEC})

##  Create a library and change its output name
IF (NOT TARGET ${TARGET_NAME})
  ADD_LIBRARY (${TARGET_NAME} SHARED ${SRC_FILES})
  INSTALL (TARGETS ${TARGET_NAME} DESTINATION lib)
ENDIF (NOT TARGET ${TARGET_NAME})


########################################
##  Add dependencies and directories

##  Location of configuration file
INCLUDE_DIRECTORIES (${TARGET_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

##  Location of additional header files
INCLUDE_DIRECTORIES (${MAIN_SRC_PATH}/common)
INCLUDE_DIRECTORIES (${MAIN_SRC_PATH}/bitbuffer)

##  Location of module dependencies
ADD_SUBDIRECTORY (${MAIN_SRC_PATH}/bitbuffer ${CMAKE_CURRENT_BINARY_DIR}/bitbuffer)


########################################
##  Set initial compilation flags

##  Set compiler flags based on global variable
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_CXX_FLAGS}")


########################################
##  Set up for Boost

INCLUDE (boost)


########################################
##  Documentation

INCLUDE (doxygen)


########################################
##  Show final message
include (final-msg)


############################################################
##  CTest
############################################################

ENABLE_TESTING ()
ADD_TEST (NAME BitIO-ShowInfo COMMAND ${TARGET_NAME_EXEC} --showinfo)
ADD_TEST (NAME BitIO-Unary-Sequential COMMAND ${TARGET_NAME_EXEC} --method unary)
ADD_TEST (NAME BitIO-Binary-Sequential COMMAND ${TARGET_NAME_EXEC} --method binary)
ADD_TEST (NAME BitIO-Gamma-Sequential COMMAND ${TARGET_NAME_EXEC} --method gamma)
ADD_TEST (NAME BitIO-Delta-Sequential COMMAND ${TARGET_NAME_EXEC} --method delta)
ADD_TEST (NAME BitIO-Golomb-Sequential COMMAND ${TARGET_NAME_EXEC} --method golomb --param 5)
ADD_TEST (NAME BitIO-Rice-Sequential COMMAND ${TARGET_NAME_EXEC} --method rice --param 2)
ADD_TEST (NAME BitIO-Unary-Random COMMAND ${TARGET_NAME_EXEC} --method unary --random)
ADD_TEST (NAME BitIO-Binary-Random COMMAND ${TARGET_NAME_EXEC} --method binary --random)
ADD_TEST (NAME BitIO-Gamma-Random COMMAND ${TARGET_NAME_EXEC} --method gamma --random)
ADD_TEST (NAME BitIO-Delta-Random COMMAND ${TARGET_NAME_EXEC} --method delta --random)
ADD_TEST (NAME BitIO-Golomb-Random COMMAND ${TARGET_NAME_EXEC} --method golomb --random --param 5)
ADD_TEST (NAME BitIO-Rice-Random COMMAND ${TARGET_NAME_EXEC} --method rice --random --param 2)
ADD_TEST (NAME BitIO-Unary-ShowLengths COMMAND ${TARGET_NAME_EXEC} --method unary --showlengths 255)
ADD_TEST (NAME BitIO-Binary-ShowLengths COMMAND ${TARGET_NAME_EXEC} --method binary --showlengths 255)
ADD_TEST (NAME BitIO-Gamma-ShowLengths COMMAND ${TARGET_NAME_EXEC} --method gamma --showlengths 255)
ADD_TEST (NAME BitIO-Delta-ShowLengths COMMAND ${TARGET_NAME_EXEC} --method delta --showlengths 255)
ADD_TEST (NAME BitIO-Golomb-ShowLengths COMMAND ${TARGET_NAME_EXEC} --method golomb --showlengths 255 --param 5)
ADD_TEST (NAME BitIO-Rice-ShowLengths COMMAND ${TARGET_NAME_EXEC} --method rice --showlengths 255 --param 2)

