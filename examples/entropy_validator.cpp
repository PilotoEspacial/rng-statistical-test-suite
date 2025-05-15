/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests.hpp>

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string_view>
#include <vector>

void
print_help ( std::string_view program_name )
{
   std::cerr << "Usage: " << program_name << " <binary_file>" << std::endl;
}

std::vector < uint8_t >
read_binary_file ( std::string file_path )
{
   auto length = std::filesystem::file_size ( file_path );

   std::vector < uint8_t > buffer ( length );
   std::ifstream file ( file_path, std::ios_base::binary );
   file.read ( reinterpret_cast < char* >( buffer.data () ), length );

   return buffer;
}

struct Test
{
   std::string name;
   bool (*run)(const uint8_t [], size_t);
};

void
check_entropy ( std::vector < uint8_t > test_vector )
{
   using namespace nist::statistical::tests;
   const std::vector < Test > sp_800_2_test_suite
   {
      { "Frequency (Monobit) Test", frequency_test }
   };

   std::cout << "Entropy Validation Result\n"
                "-------------------------";

   for ( auto& test : sp_800_2_test_suite )
   {
      bool test_result = test.run ( test_vector.data (), test_vector.size () );
      std::cout << "\n   - " << test.name << ":\t" << std::boolalpha << test_result;
   }

   std::cout << std::endl;
}

int
main ( int argc, char** argv )
{
   if ( argc != 2 )
   {
      print_help ( argv [ 0 ] );

      return EXIT_FAILURE;
   }

   check_entropy ( read_binary_file ( argv [ 1 ] ) );

   return EXIT_SUCCESS;
}