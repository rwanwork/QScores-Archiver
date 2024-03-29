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
    \file rice.cpp
    File for encoding and decoding Rice codes.
*/
/*******************************************************************/


#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>  //  exit
#include <climits>

using namespace std;

#include "common.hpp"
#include "bitbuffer.hpp"
#include "math_utils.hpp"
#include "unary.hpp"
#include "binary.hpp"
#include "rice.hpp"


//  -----------------------------------------------------------------
//  Encoding functions
//  -----------------------------------------------------------------

/*!
     Encode a value using Rice coding

     \param bitbuffer BitBuffer object where the bits are sent
     \param value Number to encode
     \param k Parameter to Rice coding
     \return The number of bits written
*/
unsigned int Rice_Encode (BitBuffer &bitbuffer, unsigned int value, unsigned int k) {
  unsigned int x = value;
  unsigned int bits_written = 0;
  
  if (k >= g_UINT_SIZE_BITS) {
    cerr << "EE\tRice coding does not work if k >= " << g_UINT_SIZE_BITS << endl;
    exit (EXIT_FAILURE);
  }

  //  We add 1 to the unary coding in case we end up encoding a 0.
  bits_written = Unary_Encode (bitbuffer, (x >> k) + 1);
  bitbuffer.WriteBits (x & ((1 << k) - 1), k);
  bits_written += k;

  return (bits_written);
}


//  -----------------------------------------------------------------
//  Decoding functions
//  -----------------------------------------------------------------


/*!
     Decode a value using Rice coding

     \param bitbuffer BitBuffer object where the bits are from
     \param k Parameter to Rice coding
     \return decoded value
*/
unsigned int Rice_Decode (BitBuffer &bitbuffer, unsigned int k) {
  unsigned int value = Unary_Decode (bitbuffer);
  unsigned int low_order = bitbuffer.ReadBits (k);

  value--;
  value = value << k;
  value = value | low_order;
//   value++;
  
  return (value);
}

