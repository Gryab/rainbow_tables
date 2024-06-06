#include "rainbow_reader.h"

rainbow_reader::rainbow_reader(u32 rounds, std::string alphabet, std::string delimiter, \
                                  int (*hash_function)(std::string*, s_byte_array*), \
                                  int (*reduction_function)(s_byte_array*, std::string*, std::string*)) \
                                  : rb_cols(rounds), rb_alphabet(alphabet), rb_delimiter(delimiter), \
                                  hash_func(hash_function), reduction_func(reduction_function) 
{ 
  this->computed_plain_text = (std::string*)malloc(sizeof(std::string) * this->rb_cols);
  assert(this->computed_plain_text!=nullptr);
}

int rainbow_reader::find_plain_text_in_row(u32 round_found)
{

  if(round_found > 0)
  {
    this->plain_text_found.assign(this->computed_plain_text[round_found - 1]);
    return 0;
  }

  this->plain_text_found.assign(this->table_row.substr(0, this->table_row.find(this->rb_delimiter)));

  return 0;
};

int rainbow_reader::search_row(s_byte_array* hash_to_search)
{
  
  std::string row_last = this->table_row.substr(this->table_row.find(this->rb_delimiter) + this->rb_delimiter.size());

  for(u32 i = 0; i < this->rb_cols; i++)
  {
    
    if((*(this->computed_plain_text + i)).compare(row_last) == 0)
    {

      this->is_found = true;

      this->find_plain_text_in_row(this->rb_cols - i);
      
      return 0;
    };
    
  };

  return 0;
};

int rainbow_reader::compute_plain_text(s_byte_array* hash_to_search)
{
  
  s_byte_array intermediate_hash = *hash_to_search;

  for(u32 i = 0; i < this->rb_cols; i++)
  {

    this->reduction_func(&intermediate_hash, &(this->rb_alphabet), this->computed_plain_text + i);
    this->hash_func(this->computed_plain_text + i, &intermediate_hash);
  
  }

  return 0;
};

int rainbow_reader::search_table(s_byte_array* hash_to_search, std::string file_name)
{
  
  std::fstream table_file;
  table_file.open(file_name, std::ios::in | std::ios::binary);
  if(!table_file.is_open()) return 1;

  while(getline(table_file, this->table_row).eofbit)
  {

    this->search_row(hash_to_search);
    
    if(this->is_found) break;

  }
  
  do{ table_file.close(); } while(table_file.is_open());

  return 0;
}
