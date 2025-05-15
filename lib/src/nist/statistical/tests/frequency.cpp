/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests/frequency.hpp>

#include <cmath>
#include <limits>
#include <vector>

#include <nist/statistical/tests/utilities.hpp>

namespace nist {
namespace statistical {
namespace tests {

   namespace {

      double 
      log_gamma ( double x )
      {
         static const double coeffs [] = 
         {
            76.18009172947146,     -86.50532032941677,
            24.01409824083091,     -1.231739572450155,
            0.1208650973866179e-2, -0.5395239384953e-5
         };

         double y = x;
         double tmp = x + 5.5;
         tmp -= ( x + 0.5 ) * std::log ( tmp );
         double ser = 1.000000000190015;

         for ( int j = 0; j < 6; j++ )
         {
            ser += coeffs[j] / ++y;
         }

         return -tmp + std::log ( 2.5066282746310005 * ser / x );
      }

      double
      gamma_q ( double a, double x )
      {
         if ( x < 0.0 || a <= 0.0 )
         {
            return std::numeric_limits < double >::quiet_NaN ();
         }

         if ( x == 0.0 ) return 1.0;

         if ( x < a + 1.0 )
         {
            // Series expansion
            double ap = a;
            double sum = 1.0 / a;
            double del = sum;

            for ( int n = 1; n <= 100; n++)
            {
               ++ap;
               del *= x / ap;
               sum += del;
               if ( std::fabs ( del ) < std::fabs ( sum ) * 1e-14 ) break;
            }

            return 1.0 - sum * std::exp ( -x + a * std::log ( x ) - log_gamma ( a ) );
         }
         else
         {
            // Continued fraction
            double b = x + 1.0 - a;
            double c = 1.0 / 1e-30;
            double d = 1.0 / b;
            double h = d;

            for ( int i = 1; i <= 100; i++ )
            {
               double an = -i * (i - a);
               b += 2.0;
               d = an * d + b;
               if ( std::fabs ( d ) < 1e-30 ) d = 1e-30;
               c = b + an / c;
               if ( std::fabs ( c ) < 1e-30 ) c = 1e-30;
               d = 1.0 / d;
               double delta = d * c;
               h *= delta;
               if ( std::fabs ( delta - 1.0 ) < 1e-14 ) break;
            }

            return std::exp ( -x + a * std::log ( x ) - log_gamma ( a ) ) * h;
         }
      }

   } // namespace

   bool
   frequency ( const uint8_t input [], size_t input_length )
   {
      // n >= 100
      size_t total_bits = input_length * 8;
      if ( total_bits < 100 ) return false;

      int64_t ones = utilities::count_ones ( input, input_length );
      int64_t zeros = total_bits - ones;

      size_t s_n = std::abs ( ones - zeros );
      double s_obs = s_n / std::sqrt ( (double) total_bits );
      double p_value = std::erfc ( s_obs / std::sqrt ( 2.0 ) );

      return p_value >= 0.01;
   }

   bool
   frequency_within_a_block ( const uint8_t input [], 
                              size_t        input_length, 
                              size_t        block_size )
   {
      // n >= 100
      size_t total_bits = input_length * 8;
      if ( total_bits < 100 ) return false;

      // M >= 20 & M > (0.01 * n)
      if ( block_size < 20 || block_size <= ( total_bits * 0.01 ) ) return false;

      // N < 100
      size_t num_blocks = std::floor ( (double) total_bits / block_size );
      if ( num_blocks >= 100 ) return false;

      double chi_squared = 0.0;
      for ( size_t block = 0; block < num_blocks; block++ )
      {
         size_t ones = 0;
         size_t start_bit = block * block_size;

         for ( size_t i = 0; i < block_size; i++ )
         {
            size_t bit_index = start_bit + i;
            size_t byte_index = bit_index / 8;
            size_t bit_pos = 7 - (bit_index % 8);
            bool bit = ( input [ byte_index ] >> bit_pos ) & 0x01;
            ones += bit;
         }

         double pi = static_cast < double > ( ones ) / block_size;
         chi_squared += ( pi - 0.5 ) * ( pi - 0.5 );
      }

      chi_squared *= 4.0 * block_size;

      double p_value = gamma_q ( static_cast < double > ( num_blocks ) / 2.0, chi_squared / 2.0 );
      return p_value >= 0.01;
   }

} // tests
} // statistical
} // nist