#ifndef rainbow_reader_h 

#include "includes_ext.h"

class rainbow_reader
{
  private:

    bool is_found = false;
    std::string plain_text_found;

    u32 rb_cols;
    
    std::string rb_alphabet;

    int (*hash_func)(std::string*, s_byte_array*); //Gryab: FIRST parameter is plain text input string, SECOND parameter is array for hash output 

    int (*reduction_func)(s_byte_array*, std::string*); //Gryab: FIRST parameter is hash input array, SECOND parameter is string for plain text output

    std::string table_row;
    std::string table_row_plain_text;
    s_byte_array* table_row_hash;

    int search_row(s_byte_array* hash);
  
  public:

    rainbow_reader(u32 rounds, std::string alphabet, \
        int (*hash_function)(std::string* /*plain text input*/, s_byte_array* /*for hash output*/), \
        int (*reduction_function)(s_byte_array* /*hash input*/, std::string* /*for plain text output*/));

    int search_table(s_byte_array* hash_to_search, std::string file_name);

};

#define rainbow_reader_h
#endif
