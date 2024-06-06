#include <string>
#ifndef rainbow_builder_h

#include "includes_ext.h"

class rainbow_builder 
{
  private:

    u32 rb_rows;
    u32 rb_cols;
    
    std::string rb_alphabet, rb_delimiter;

    s_string rb_table_row;

    int gen_table_row(u32 seed, std::fstream* table_file);

    int (*hash_func)(std::string*, s_byte_array*); //Gryab: FIRST is plain text input string, SECOND is array for hash output 

    int (*reduction_func)(s_byte_array*, std::string*, std::string*); //Gryab: FIRST is hash input array, THIRD is alphabet for valid password, SECOND is string for plain text output

    int (*password_gen)(u32, std::string*, std::string*); //Gryab: FIRST is a u32 seed, SECOND is alphabet string, THIRD is output string 

  public:
    
    rainbow_builder(u32 rows, u32 rounds, std::string alphabet, std::string delimiter, \
                    int (*hash_function)(std::string* /*plain text input*/, s_byte_array* /*for hash output*/), \
                    int (*reduction_function)(s_byte_array* /*hash input*/, std::string* /*alphabet*/, std::string* /*for plain text output*/), \
                    int (*password_generator)(u32 /*seed*/, std::string* /*alphabet*/, std::string* /*output*/));

    int build_table(std::string filename);

};

#define rainbow_builder_h
#endif
