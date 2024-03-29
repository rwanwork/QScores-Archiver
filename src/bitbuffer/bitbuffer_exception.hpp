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


/*******************************************************************/
/*!
    \file bitbuffer_exception.hpp
    Exceptions for BitBuffer class.
*/
/*******************************************************************/

#ifndef BITBUFFER_EXCEPTION_HPP
#define BITBUFFER_EXCEPTION_HPP

/*!
    \class BitBuffer_Input_Exception

    \details Derived exception class for handling input exceptions.
*/
class BitBuffer_Input_Exception : public exception
{
  virtual const char* what() const throw() {
    return "EE\tNo more bits left in input file...";
  }
};

#endif

