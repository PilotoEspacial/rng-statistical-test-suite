/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests.hpp>

#include <cmath>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string_view>
#include <vector>

std::vector < uint8_t >
read_binary_file ( std::string file_path )
{
   auto length = std::filesystem::file_size ( file_path );

   std::vector < uint8_t > buffer ( length );
   std::ifstream file ( file_path, std::ios_base::binary );
   file.read ( reinterpret_cast < char* >( buffer.data () ), length );

   return buffer;
}

void
print_help ( std::string_view program_name )
{
   std::cerr << "Usage: " << program_name << " <binary_file>" << std::endl;
}

void
print_result ( std::string test_name, bool test_result )
{
   std::string test_result_str = ( test_result ) ? "PASS" : "FAIL";
   std::cout << "(" << test_result_str << ") " << test_name << "\n";
}

bool
valid_longest_run_of_ones_input_length ( size_t n )
{
   bool valid_input = false;

   if ( n >= 128 && n < 6272 && ( n % 8 == 0 ) ) valid_input = true;
   else if ( n >= 6272 && n < 750000 && ( n % 128 == 0) ) valid_input = true;
   else if ( n >= 750000 && ( n % 10000 == 0 ) ) valid_input = true;

   return valid_input;
}

int
main ( int argc, char** argv )
{
   if ( argc != 2 )
   {
      print_help ( argv [ 0 ] );

      return EXIT_FAILURE;
   }

   std::cout << "NIST SP 800-22 Rev. 1\n"
                "---------------------\n"
                "file: " << argv [ 1 ] <<
                "\n---------------------\n";
   
   using namespace nist::statistical::tests;

   // Input test vector
   auto test_vector = read_binary_file ( argv [ 1 ] );
   auto test_vector_bit_size = test_vector.size () * 8;

   // 01. Frequency (Monobit)
   print_result ( "Frequency (Monobit) Test", 
      frequency_test ( test_vector.data (), test_vector.size () ) );

   // 02. Frequency Test within a Block
   size_t block_size = std::ceil ( test_vector.size () * 8 * 0.01 ) + 1;
   if ( block_size < 20 ) block_size = 20;
   print_result ( "Frequency Test within a Block", 
      frequency_test_within_a_block ( test_vector.data (), test_vector.size (), block_size ) );

   // 03. Runs Test
   print_result ( "Runs Test", 
      runs_test ( test_vector.data (), test_vector.size () ) );

   // 04. Longest Run of Ones in a Block Test
   if ( valid_longest_run_of_ones_input_length ( test_vector_bit_size ) )
   {
      print_result ( "Longest Run of Ones in a Block Test",
         longest_run_of_ones_test ( test_vector.data (), test_vector.size () ) );
   }

   return EXIT_SUCCESS;
}