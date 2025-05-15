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
   
   // Input test vector
   auto test_vector = read_binary_file ( argv [ 1 ] );

   // 01. Frequency (Monobit)
   using namespace nist::statistical::tests;
   print_result ( "Frequency (Monobit)", frequency ( test_vector.data (), test_vector.size () ) );

   // 02. Frequency Test within a Block
   size_t block_size = std::ceil ( test_vector.size () * 8 * 0.01 );
   if ( block_size < 20 ) block_size = 20;
   print_result ( "Frequency within a Block", frequency_within_a_block ( test_vector.data (), test_vector.size (), block_size ) );

   return EXIT_SUCCESS;
}