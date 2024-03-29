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
##  Define the project name and C++ standard

set (CURR_PROJECT_NAME "QScores-Archiver")

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD_REQUIRED ON)


########################################
##  Set the main source path to the very top

##  Set the main path and where additional CMake modules are
IF (NOT DEFINED MAIN_SRC_PATH)
  SET (MAIN_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

  ##  Locate where the shared CMake modules are
  SET (CMAKE_MODULE_PATH "${MAIN_SRC_PATH}/cmake")
ENDIF (NOT DEFINED MAIN_SRC_PATH)

##  Include externally defined functions
INCLUDE (global)
INCLUDE (add_subdirectory_once)


########################################
##  Set up the software
project (${CURR_PROJECT_NAME} VERSION 1.0 DESCRIPTION "QScores-Archiver" LANGUAGES CXX)
message (STATUS "Setting up ${CMAKE_PROJECT_NAME}...")

include (initial-msg)


########################################
##  Create the targets

##  Set the output directory of the libraries to the top-level binary directory
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


########################################
##  Add dependencies and directories

##  Location of configuration files
INCLUDE_DIRECTORIES (${TARGET_NAME_EXEC} PUBLIC "${PROJECT_BINARY_DIR}")

##  Location of additional header files
INCLUDE_DIRECTORIES (${MAIN_SRC_PATH}/qscores)

##  Location of module dependencies
ADD_SUBDIRECTORY_ONCE (${MAIN_SRC_PATH}/qscores ${CMAKE_BINARY_DIR}/qscores)


########################################
##  Set initial compilation flags

##  Set compiler flags based on global variable
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_CXX_FLAGS}")


########################################
##  Show final message
include (final-msg)


############################################################
##  CTest
############################################################

ENABLE_TESTING ()

