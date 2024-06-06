#ifndef rainbow_reader_h 

#include "includes_ext.h"

class rainbow_reader
{
  private:

    bool is_found = false;
    std::string plain_text_found;

    u32 rb_cols;
    
    std::string rb_alphabet, rb_delimiter, table_row;

    std::string* computed_plain_text;

    int (*hash_func)(std::string*, s_byte_array*); //Gryab: FIRST is plain text input, SECOND is array for hash output 

    int (*reduction_func)(s_byte_array*, std::string*, std::string*); //Gryab: FIRST is hash input array, SECOND is alphabet, THIRD is for plain text output

    int find_plain_text_in_row(u32 round_found);

    int compute_plain_text(s_byte_array* hash_to_search);

    int search_row(s_byte_array* hash);
  
  public:

    rainbow_reader(u32 rounds, std::string alphabet, std::string delimiter, \
        int (*hash_function)(std::string* /*plain text input*/, s_byte_array* /*for hash output*/), \
        int (*reduction_function)(s_byte_array* /*hash input*/, std::string* /*alphabet*/, std::string* /*for plain text output*/));

    int search_table(s_byte_array* hash_to_search, std::string file_name);

};

#define rainbow_reader_h
#endif
