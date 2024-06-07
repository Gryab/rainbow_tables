#include "rainbow_reader.h"

rainbow_reader::rainbow_reader(u64 rounds, std::string alphabet, std::string delimiter, \
                                  int (*hash_function)(std::string*, s_byte_array*), \
                                  int (*reduction_function)(s_byte_array*, std::string*, std::string*)) \
                                  : rb_cols(rounds), rb_alphabet(alphabet), rb_delimiter(delimiter), \
                                  hash_func(hash_function), reduction_func(reduction_function) { return;}

int rainbow_reader::find_plain_text_in_row(u64 round_found)
{

  std::string starting_plain_text(this->table_row.substr(0, this->table_row.find(this->rb_delimiter)));
  s_byte_array intermediate_hash = {0};

  if(round_found == 0)
  {
    this->plain_text_found.assign(starting_plain_text);
    return 0;
  }

  for(u64 i = 0; i < round_found; i++)
  {
    this->hash_func(&starting_plain_text, &intermediate_hash);
    this->reduction_func(&intermediate_hash, &(this->rb_alphabet), &starting_plain_text);
  }

  this->plain_text_found.assign(starting_plain_text);
  
  return 0;
};

int rainbow_reader::search_row(s_byte_array* hash_to_search)
{

  std::size_t last_plain_in_chain_pos = this->table_row.find(this->rb_delimiter) + this->rb_delimiter.size();
  std::string row_last = this->table_row.substr(last_plain_in_chain_pos, this->table_row.size() - last_plain_in_chain_pos - 1);

  for(u64 i = 0; i < this->rb_cols; i++)
  {
    
    if(this->computed_plain_text.at(i).compare(row_last) == 0)
    {

      this->is_found = true;

      this->find_plain_text_in_row(this->rb_cols - i - 1);
      
      return 0;
    };
    
  };

  return 0;
};

int rainbow_reader::compute_plain_text(s_byte_array* hash_to_search)
{
  
  s_byte_array intermediate_hash = {hash_to_search->size, hash_to_search->value};

  std::string intermediate_plain_text;

  for(u64 i = 0; i < this->rb_cols; i++)
  {

    this->reduction_func(&intermediate_hash, &(this->rb_alphabet), &intermediate_plain_text);
    this->computed_plain_text.push_back(intermediate_plain_text);
    this->hash_func(&intermediate_plain_text, &intermediate_hash);
  
  }

  return 0;
};

int rainbow_reader::search_table(s_byte_array* hash_to_search, std::string file_name)
{
 
  if((this->rb_cols * this->rb_alphabet.size() * this->rb_delimiter.size() == 0) + \
      (this->hash_func == nullptr) + (this->reduction_func == nullptr)) return 1;

  this->compute_plain_text(hash_to_search);

  std::fstream table_file;
  table_file.open(file_name, std::ios::in | std::ios::binary);
  if(!table_file.is_open()) return 1;

  while(getline(table_file, this->table_row).eofbit & (this->is_found != true) & (this->table_row.size() > 0))
  {

    this->search_row(hash_to_search);
    
  }
  
  do{ table_file.close(); } while(table_file.is_open());

  return 0;
}

int rainbow_reader::get_found_plain_text(std::string* output)
{ 
  if(!this->is_found) return 1;
  if(output != nullptr)
  {
    output->assign(this->plain_text_found);
  }
  return 0;
}
