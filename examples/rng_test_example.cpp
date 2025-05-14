/***************************************************
 * Copyright (c) 2025 Jose Alberto Granados
 *
 * MIT License (See LICENSE file for more details)
 ***************************************************/

#include <nist/statistical/tests.hpp>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

std::string
hex_dump ( const std::vector < uint8_t >& buffer )
{
  std::stringstream ss;
  ss << std::hex << std::setfill ( '0' );

   for ( auto& value : buffer )
   {
      ss << std::uppercase << std::hex << std::setw ( 2 ) << (int) value;
   }

  return ss.str ();
}

std::vector < uint8_t >
generate_random ( size_t size )
{
   std::random_device rd;
   std::mt19937 gen ( rd () );
   std::uniform_int_distribution <> dist ( 0, 255 );

   std::vector < uint8_t > buffer ( size );
   std::generate( buffer.begin (), buffer.end (),
      [&]() { return dist ( gen ); } );

   return buffer;
}

void
save_file ( const std::string& file_name,
            const std::string& file_data )
{
   std::ofstream file ( file_name );

   if ( !file.is_open () )
   {
      throw std::runtime_error ( "Unable to write file \"" + file_name + "\"!" );
   }

   file << file_data << "\n";
}

void
print_test_result ( const std::string& test_name, bool test_result )
{
   std::cout << "   - " << test_name << ":\t" << std::boolalpha << test_result << std::endl;
}

struct Test
{
   std::string name;
   bool (*run)(const uint8_t [], size_t );
};

int
main ( int, char** )
{
   using namespace nist::statistical::tests;
   const std::vector < Test > tests
   {
      { "Frequency (Monobit) test", frequency_test }
   };

   auto test_vector = generate_random ( 2048 );

   const std::string test_vector_file_name = "/tmp/random.hex";
   save_file ( test_vector_file_name, hex_dump ( test_vector ) );

   std::cout << "Test results:" << std::endl;
   for ( auto& test : tests )
   {
      print_test_result ( test.name, test.run ( test_vector.data (), test_vector.size () ) );
   }

   std::cout << "\nTest vector saved in: " << test_vector_file_name << std::endl;

   return EXIT_SUCCESS;
}