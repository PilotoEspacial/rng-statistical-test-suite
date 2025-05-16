#ifndef __NIST_TEST_VECTORS_HPP_
#define __NIST_TEST_VECTORS_HPP_

#include <cinttypes>
#include <vector>

const std::vector < uint8_t > valid_test_vector =
{
   0b11001001, 0b00001111, 0b11011010, 0b10100010, 
   0b00100001, 0b01101000, 0b11000010, 0b00110100, 
   0b11000100, 0b11000110, 0b01100010, 0b10001011,
   0b1000
};

const std::vector < uint8_t > invalid_test_vector =
{
   0b00000000, 0b00000000, 0b00000000, 0b00000000,
   0b00000000, 0b00000000, 0b00000000, 0b11111111,
   0b11000100, 0b11000110, 0b01100010, 0b10001011,
   0b1000
};

#endif // __NIST_TEST_VECTORS_HPP_