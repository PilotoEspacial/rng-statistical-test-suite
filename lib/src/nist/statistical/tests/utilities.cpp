/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests/utilities.hpp>

#include <bitset>

namespace nist {
namespace statistical {
namespace tests {
namespace utilities {

   size_t
   count_ones ( const uint8_t input [], size_t input_length )
   {
      size_t count = 0;
      for ( size_t idx = 0; idx < input_length; idx++ )
      {
         count += std::bitset < 8 > ( input [ idx ] ).count ();
      }

      return count;
   }

} // utilities
} // tests
} // statistical
} // nist