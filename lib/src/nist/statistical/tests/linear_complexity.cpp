/***************************************************
 * Copyright (c) 2025 Paulino de la Fuente
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests/linear_complexity.hpp>

#include <cmath>
#include <limits>
#include <vector>

#include <nist/statistical/tests/utilities.hpp>

namespace nist {
namespace statistical {
namespace tests {
namespace {

    /**
     * @brief Implements the Berlekamp–Massey algorithm over GF(2).
     *
     * This algorithm determines the linear complexity of a binary sequence.
     * It computes the length of the shortest LFSR (Linear Feedback Shift Register)
     * that can generate the given input sequence.
     *
     * @param s A vector of binary values (0 or 1) representing a fixed-length bit sequence.
     *          This corresponds to a block from the full sequence under analysis.
     *
     * @return The linear complexity (L) of the input sequence block.
     */

    int 
    berlekamp_massey( const std::vector < uint8_t >& bits ) 
    {
        int n = bits.size ();
        std::vector < uint8_t > c ( n, 0 ), b ( n, 0 );

        c [ 0 ] = 1;
        b [ 0 ] = 1;

        int L = 0, m = -1;
        uint8_t d;

        for ( int i = 0; i < n; ++i ) 
        {
            d = bits [ i ];
            
            for ( int j = 1; j <= L; ++j )
                d ^= c [ j ] & bits [ i - j ];

            if ( d )
            {
                std::vector < uint8_t > temp = c;
                int shift = i - m;
                for ( int j = 0; j < n - shift; ++j )
                    c [ shift + j ] ^= b [ j ];

                if ( L <= i / 2 ) 
                {
                    L = i + 1 - L;
                    m = i;
                    b = temp;
                }
            }
        }
        return L;
    }
} // namespace


    bool 
    linear_complexity_test ( const uint8_t input[], size_t input_length, size_t block_length ) 
    {
        using namespace nist::statistical::tests::utilities;

        std::vector < uint8_t > bits = extract_bits_from_bytes ( input, input_length );

        size_t M = block_length;
        size_t n = bits.size ();
        size_t N = n / M;

        if ( N == 0 ) return false; // Not enough blocks

        double mu = M / 2.0 + ( 9.0 + std::pow ( -1.0, M + 1 ) ) / 36.0;
        double sigma2 = M / 9.0 + ( 2.0 / 9.0 ) * std::pow ( -1.0, M + 1 );

        double sum = 0.0;

        for ( size_t i = 0; i < N; ++i ) 
        {
            std::vector < uint8_t > block ( bits.begin () + i * M, bits.begin () + ( i + 1 ) * M );
            
            int L = berlekamp_massey ( block );
            double T = std::pow ( -1.0, M ) * ( L - mu ) + ( 2.0 / 9.0 );
            sum += T;
        }

        double normalized = sum / std::sqrt ( 2.0 * sigma2 * N );
        double p_value = std::erfc ( std::fabs ( normalized ) );

        return p_value >= 0.01;
    }


} // tests
} // statistical
} // nist