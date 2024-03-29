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
    \file sort.cpp
    Sorting functions for Huffman coding class definition .
*/
/*******************************************************************/

#include <fstream>  //  ostream
#include <vector>
#include <climits>  //  UINT_MAX
#include <algorithm>  //  sort
#include <iostream>
#include <cassert>

using namespace std;

#include "common.hpp"
#include "bitbuffer.hpp"
#include "huffman.hpp"
#include "sort.hpp"


//  -----------------------------------------------------------------
//  Public functions
//  -----------------------------------------------------------------


//  -----------------------------------------------------------------
//  Private functions
//  -----------------------------------------------------------------



/*!
     Non-class comparison function used to sort m_SymsUsed by value in increasing order

     \param[in] lhs The left-hand entry
     \param[in] rhs The right-hand entry     
*/
bool SortByValue (const unsigned int& lhs, const unsigned int& rhs) {
  return (lhs < rhs);
}



/*!
     Sort the symbols used by frequency in decreasing order, excluding the sentinel in position 1.
*/
void Huffman::SortSymsUsed_Frequency () {
  sort (m_SymsUsed.begin() + 1, m_SymsUsed.end(), SortByFrequency (this));
  
  return;
}


/*!
     Sort the symbols used by value in increasing order, excluding the sentinel in position 1.
*/
void Huffman::SortSymsUsed_Value () {
  sort (m_SymsUsed.begin() + 1, m_SymsUsed.end(), SortByValue);

  return;
}

