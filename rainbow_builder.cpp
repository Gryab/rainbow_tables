#include "rainbow_builder.h"

rainbow_builder::rainbow_builder(u32 rows, u32 rounds, std::string alphabet, std::string delimiter, \
                                  int (*hash_function)(std::string*, s_byte_array*), \
                                  int (*reduction_function)(s_byte_array*, std::string*, std::string*), \
                                  int (*password_generator)(u32, std::string*, std::string*)) \
                                  : rb_rows(rows), rb_cols(rounds), rb_alphabet(alphabet), rb_delimiter(delimiter), \
                                  hash_func(hash_function), reduction_func(reduction_function), password_gen(password_generator) { return; }

int rainbow_builder::gen_table_row(u32 seed, std::fstream* table_file)
{
  std::string row;
  std::string plain_text;
  this->password_gen(seed, &this->rb_alphabet, &plain_text);

  row.operator+=(plain_text.c_str());
  row.operator+=(this->rb_delimiter);

  s_byte_array hash_part = {0};
  
  for(u32 i = 0; i < this->rb_cols; ++i)
  { 
    this->hash_func(&plain_text, &hash_part);
    this->reduction_func(&hash_part, &(this->rb_alphabet), &plain_text);

  };

  row.operator+=(plain_text.c_str());
  row.operator+=('\n');
  table_file->write(row.c_str(), row.size());

  return 0;

};

int rainbow_builder::build_table(std::string filename)
{
  
  std::fstream table_file;
  table_file.open(filename.c_str(), std::ios::out);
  if(!table_file.is_open()) return 1;

  for(u32 i = 0; i < this->rb_rows; i++)
  {
    this->gen_table_row(i, &table_file);
  }

  do{ table_file.close(); } while(table_file.is_open());

  return 0;

};
