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
    \file decode.cpp
    Decoding functions for interpolative coding.
*/
/*******************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

#include "bitbuffer.hpp"
#include "bitio-defn.hpp"
#include "decode.hpp"


//  -----------------------------------------------------------------
//  Functions for unsigned ints
//  -----------------------------------------------------------------


/*!
     Decode a vector of unsigned ints using interpolative coding

     \param bitbuffer BitBuffer object where the bits are sent
     \param v Vector of values to decode (initially empty)
     \param v_size Number of values to decode
*/
void Interpolative_Decode (BitBuffer &bitbuffer, vector <unsigned int> &v, unsigned int v_size) {
  unsigned int left_value = 0;
  unsigned int right_value = 0;
  unsigned int i = 0;
  vector <unsigned int> v_tmp;

  //  Resize the vector and initialize it to zero
  v.resize (v_size);
  v_tmp.resize (v_size);
  for (i = 0; i < v_size; i++) {
    v_tmp[i] = 0;
  }
  
  //  Decode the lower and upper bound limits
  left_value = Gamma_Decode (bitbuffer);
  right_value = Gamma_Decode (bitbuffer);

  //  Begin to recursively process list
  Recursive_Interpolative_Decode (bitbuffer, v_tmp, v_size, 0, v_size - 1, left_value, right_value);

  //  Reverse the cumulative sum process
  v[0] = v_tmp[0];
  for (unsigned int i = 1; i < v_size; i++) {
    v[i] = v_tmp[i] - v_tmp[i - 1];
  }

  return;
}



/*!
     Recursively decode a vector of unsigned ints using interpolative coding

     \param bitbuffer BitBuffer object where the bits are sent
     \param list Vector of values to encode
     \param list_size Size of the list to be coded defined by the boundary (i.e., not the entire list)
     \param left Left (lower) boundary of vector
     \param right Right (upper) boundary of vector
     \param left_value Value for the left boundary of vector
     \param right_value Value for the right boundary of vector
*/
void Recursive_Interpolative_Decode (BitBuffer &bitbuffer, vector <unsigned int> &list, unsigned int list_size, unsigned int left, unsigned int right, unsigned int left_value, unsigned int right_value) {
  unsigned int midpoint = 0;
  unsigned int first_list_size = 0;
  unsigned int second_list_size = 0;

  if (list_size == 0) {
    return;
  }

  //  0-based vector, so adjust these values accordingly
  midpoint = ((list_size + 1) >> 1) - 1;
  first_list_size = midpoint;
  second_list_size = list_size - midpoint - 1;
  midpoint += left;  //  Shift the midpoint over

  //  Decode the middle value
  list[midpoint] = BinaryLowHigh_Decode (bitbuffer, left_value + first_list_size, right_value - second_list_size);

  //  Recurse on both halves
  Recursive_Interpolative_Decode (bitbuffer, list, first_list_size, left, midpoint - 1, left_value, list[midpoint] - 1);
  Recursive_Interpolative_Decode (bitbuffer, list, second_list_size, midpoint + 1, right, list[midpoint] + 1, right_value);

  return;
}


