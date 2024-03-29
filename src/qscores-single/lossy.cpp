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
    \file lossy.cpp
    Lossy transformation functions.
*/
/*******************************************************************/

#include <vector>
#include <string>
#include <fstream>
#include <cassert>
// #include <cstdlib>
#include <iostream>
// #include <climits>

using namespace std;

#include "bitbuffer.hpp"
#include "qscores-single-defn.hpp"
#include "qscores-single.hpp"


//  -----------------------------------------------------------------
//  Transformation functions
//  -----------------------------------------------------------------

/*!
     Change all low quality score values to the given value.

     \param[in] param The value that low values are to be changed to (where "low values" refers to values below this threshold).
*/
void QScoresSingle::ApplyLossyMinTruncation (unsigned int param) {
  assert ((m_Status == e_QSCORES_SINGLE_STATUS_BOTH) || (m_Status == e_QSCORES_SINGLE_STATUS_INT));

  for (unsigned int i = 0; i < m_QScoreInt.size (); i++) {
    if (m_QScoreInt[i] < param) {
      m_QScoreInt[i] = param;
    }
  }

  m_Status = e_QSCORES_SINGLE_STATUS_INT;

  return;
}


/*!
     Change all high quality score values to the given value.

     \param[in] param The value that high values are to be changed to (where "high values" refers to values above this threshold).
*/
void QScoresSingle::ApplyLossyMaxTruncation (unsigned int param) {
  assert ((m_Status == e_QSCORES_SINGLE_STATUS_BOTH) || (m_Status == e_QSCORES_SINGLE_STATUS_INT));

  for (unsigned int i = 0; i < m_QScoreInt.size (); i++) {
    if (m_QScoreInt[i] > param) {
      m_QScoreInt[i] = param;
    }
  }

  m_Status = e_QSCORES_SINGLE_STATUS_INT;

  return;
}


/*!
     Remap quality scores using the given lookup table.

     \param[in] lookup The lookup table to remap with.  The size of the table should be equal to the size of the ASCII alphabet.
*/
void QScoresSingle::ApplyLossyRemapping (vector <unsigned int> lookup) {
  assert ((m_Status == e_QSCORES_SINGLE_STATUS_BOTH) || (m_Status == e_QSCORES_SINGLE_STATUS_INT));

  for (unsigned int i = 0; i < m_QScoreInt.size (); i++) {
    m_QScoreInt[i] = lookup[m_QScoreInt[i]];
  }

  m_Status = e_QSCORES_SINGLE_STATUS_INT;

  return;
}


/*!
     Remap the quality scores back using the given lookup table.  The function is the same as ApplyLossyRemapping () but since it is used for the reverse, we created the same function with a different name.

     \param[in] lookup The lookup table to remap with.  The size of the table should be equal to the size of the ASCII alphabet.
*/
void QScoresSingle::UnapplyLossyRemapping (vector <unsigned int> lookup) {
  assert ((m_Status == e_QSCORES_SINGLE_STATUS_BOTH) || (m_Status == e_QSCORES_SINGLE_STATUS_INT));

  for (unsigned int i = 0; i < m_QScoreInt.size (); i++) {
    m_QScoreInt[i] = lookup[m_QScoreInt[i]];
  }

  m_Status = e_QSCORES_SINGLE_STATUS_INT;

  return;
}

