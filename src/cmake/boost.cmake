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

##  Use the new policy CMP0167 for the use of find_package (Boost)
if (POLICY CMP0167)
  cmake_policy (SET CMP0167 NEW)
endif ()

##  Check if this is the top level
if (PROJECT_IS_TOP_LEVEL)
  ##  Enable verbose and debugging messages
  set (Boost_VERBOSE YES)
  set (Boost_DEBUG YES)

  ##  Set the minimum version and the required components
  set (BOOST_MIN_VERSION 1.85.0)
  set (BOOST_REQUIRED_COMPONENTS program_options filesystem headers)

  ##  Locate Boost using the Boost-provided `BoostConfig.cmake`
#  find_package (Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS ${BOOST_REQUIRED_COMPONENTS})

  ##  If it is not found, then install and compile Boost
  if (NOT Boost_FOUND)
    set (CPM_USE_LOCAL_PACKAGES YES)

    ##  Download CPM
    message (STATUS "Fetching CPM.cmake from GitHub...")
    FetchContent_Declare (
      "cpm"
      GIT_REPOSITORY "git@github.com:cpm-cmake/CPM.cmake.git"
      GIT_TAG "origin/master"
    )
    FetchContent_MakeAvailable (cpm)
    set (CPM_SOURCE_DIR "${cpm_SOURCE_DIR}")
    set (CPM_BINARY_DIR "${cpm_BINARY_DIR}")
    include (${CPM_SOURCE_DIR}/cmake/CPM.cmake)

    ##  Set the components that we need and download locally
    list (APPEND BOOST_INCLUDE_LIBRARIES ${BOOST_REQUIRED_COMPONENTS})

    ###############
    ##  There are two options to obtain Boost.  The default is to just copy from a local directory on the system.  The alternative is to clone from GitHub.
    ##    To use the alternative, swap the comments.
    ###############

    ###############
    ##  Fetch Boost from a local directory
    set (FETCHCONTENT_SOURCE_DIR_BOOST /usr/local/boost/)

    ##  Clone Boost-CMake with CPM; only works with Git Tag 85c04c6
    ##    (Need to investigate further why.)
    message (STATUS "Cloning Boost-CMake from GitHub with CPM...")
    CPMAddPackage(
      NAME boost_cmake
      GIT_REPOSITORY "https://github.com/ClausKlein/boost-cmake.git"
      GIT_TAG "85c04c6"
      DOWNLOAD_ONLY YES
    )

    ##  Configure Boost
    add_subdirectory (${boost_cmake_SOURCE_DIR} ${boost_cmake_BINARY_DIR})
    ###############

    ###############
    ##  Clone from Claus Klein's GitHub repository
    # CPMAddPackage ("gh:ClausKlein/boost-cmake#v1.87.0-rc5")
    ###############
  endif ()
endif ()

