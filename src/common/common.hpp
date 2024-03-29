//  ###########################################################################
//  Copyright 2011-2015, 2024 by Raymond Wan (rwan.work@gmail.com)
//    https://github.com/rwanwork/QScores-Archiver
//
//  This file is part of QScores-Archiver.
//
//  QScores-Archiver is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public License
//  as published by the Free Software Foundation; either version
//  3 of the License, or (at your option) any later version.
//
//  QScores-Archiver is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with QScores-Archiver; if not, see
//  <http://www.gnu.org/licenses/>.
//  ###########################################################################


#ifndef COMMON_HPP
#define COMMON_HPP

//!  Spacing for aligning the verbose output (in characters).
const unsigned int g_VERBOSE_WIDTH = 40;


//!  Number of bits per [un]signed integer
const unsigned int g_UINT_SIZE_BITS = 32;


//!  Number of bytes per [un]signed integer
const unsigned int g_UINT_SIZE_BYTES = 4;


//!  Number of bits per [un]signed character (byte)
const unsigned int g_CHAR_SIZE_BITS = 8;


//!  Number of bytes per [un]signed character
const unsigned int g_CHAR_SIZE_BYTES = 1;


//!  Maximum range of ASCII character set
const unsigned int g_MAX_ASCII = 0xFF;

#endif

