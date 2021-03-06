///////////////////////////////////////////////////////////////////////////
//  QScores-Archiver
//  Software and library for transforming and compressing next generation
//    sequencing data in FASTQ format.
//  
//  Version N/A (On Github) -- November 12, 2015
//  
//  Copyright (C) 2011-2015 by Raymond Wan, All rights reserved.
//  Contact:  rwan.work@gmail.com
//  Organization:  Division of Life Science, Faculty of Science, Hong Kong
//                 University of Science and Technology, Hong Kong
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
    Test driver for BlockStatistics class.
    
    \author Raymond Wan (r-wan@cb.k.u-tokyo.ac.jp)
    \par Organizations
          - Department of Computational Biology, Graduate School of
            Frontier Science, University of Tokyo
          - Computational Biology Research Center, AIST, Japan
          
    $Id: main.cpp 224 2011-11-06 15:32:09Z rwan $

*/
/*******************************************************************/

#include <cstdlib>  //  EXIT_SUCCESS, EXIT_FAILURE, exit ()
#include <iostream>
#include <cstring>
#include <vector>
#include <climits>

using namespace std;

#include "BlockStatisticsConfig.hpp"
#include "common.hpp"
#include "block-statistics.hpp"


/*!
     Main driver

     \param[in] argc Number of arguments
     \param[in] argv Arguments to program
     \return Returns 0 on success, 1 otherwise.
*/
int main(int argc, char **argv) {
  BlockStatistics bs;
  vector<unsigned int> tmp;
  unsigned int tmp_values = 100;
  
  //  Need at least one argument
  if (argc < 2) {
    return (EXIT_FAILURE);
  }

  srand (time (NULL));

  for (unsigned int i = 0; i < tmp_values; i++) {
    unsigned int pos = rand () % g_MAX_ASCII;
    tmp.push_back (pos);
  }

  if (strcmp (argv[1], "1") == 0) {
    cout << "BlockStatistics version " << BlockStatistics_VERSION_MAJOR << "." << BlockStatistics_VERSION_MINOR << ":  " << __DATE__ <<  " (" << __TIME__ << ")" << endl;
  }
  else if (strcmp (argv[1], "2") == 0) {
    bs.UpdateFrequencyTable (tmp);
    cout << bs << endl;
  }
  else if (strcmp (argv[1], "3") == 0) {
    bs.UpdateFrequencyTable (tmp);
    vector<unsigned int> result = bs.GetQScoresToIDs ();
    cout << "Size:  " << result.size () << endl;
    for (unsigned int i = 0; i < result.size (); i++) {
      cout << result[i];
      if ((i + 1) % 5 == 0) {
        cout << endl;
      }
      else {
        cout << "\t";
      }
    }
    cout << endl;
    result = bs.GetIDsToQScores ();
    cout << "==============================" << endl;
    cout << "Size:  " << bs.GetIDsToQScoresSize () << endl;
    for (unsigned int i = 0; i < bs.GetIDsToQScoresSize (); i++) {
      cout << result[i];
      if ((i + 1) % 5 == 0) {
        cout << endl;
      }
      else {
        cout << "\t";
      }
    }
  }
  cout << endl;

  return (EXIT_SUCCESS);
}


