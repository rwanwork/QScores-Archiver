///////////////////////////////////////////////////////////////////////////
//  QScores-Archiver
//  Software and library for transforming and compressing next generation
//    sequencing data in FASTQ format.
//  
//  Version 1.00 -- November 6, 2011
//  
//  Copyright (C) 2011 by Raymond Wan, All rights reserved.
//  Contact:  rwan@cuhk.edu.hk
//  Organization:  Department of Computational Biology, Graduate School of
//                 Frontier Science, University of Tokyo and
//                 Computational Biology Research Center, AIST,
//                 Japan
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
///////////////////////////////////////////////////////////////////////////


/*******************************************************************/
/*!
    \file main.cpp
    Main function for validating the computer architecture
    \author Raymond Wan (r-wan@cb.k.u-tokyo.ac.jp)
    \par Organizations
          - Department of Computational Biology, Graduate School of
            Frontier Science, University of Tokyo
          - Computational Biology Research Center, AIST, Japan
    $Id: main.cpp 224 2011-11-06 15:32:09Z rwan $

*/
/*******************************************************************/

#include <iostream>
#include <cstdlib>  //  EXIT_SUCCESS, EXIT_FAILURE

#include "systemcfg.hpp"

using namespace std;


/*!
     Main driver that checks the architecture of the machine

     \param[in] argc Number of arguments
     \param[in] argv Arguments to program
     \return Returns 0 on success, 1 otherwise.
*/
int main(int argc, char **argv) {
  bool result = true;

  //  Perform two checks -- basically unnecessary since either both are true or both are false...
  if (sizeof (unsigned int) != g_UINT_SIZE_BYTES) {
    cerr << "WW\tMismatch in size of an unsigned integer:  " << sizeof (unsigned int) << " : " << g_UINT_SIZE_BYTES << endl;
    result = false;
  }

  if (sizeof (unsigned int) * g_CHAR_SIZE_BITS != g_UINT_SIZE_BITS) {
    cerr << "WW\tMismatch in number if bits per unsigned integer:  " << sizeof (unsigned int) * g_CHAR_SIZE_BITS << " : " << g_UINT_SIZE_BITS << endl;
    result = false;
  }

  if (result) {
    cerr << "II\tComputer architecture passes all tests!" << endl;
    return (EXIT_SUCCESS);
  }

  cerr << "EE\tComputer architecture has failed some tests!" << endl;
  return (EXIT_FAILURE);
}
