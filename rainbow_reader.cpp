#include "rainbow_reader.h"

rainbow_reader::rainbow_reader(u32 rounds, std::string alphabet, \
                                  int (*hash_function)(std::string*, s_byte_array*), \
                                  int (*reduction_function)(s_byte_array*, std::string*)) \
                                  : rb_cols(rounds), rb_alphabet(alphabet), \
                                  hash_func(hash_function), reduction_func(reduction_function) { return; }

int rainbow_reader::search_row(s_byte_array* hash_to_search){
  
  this->table_row_plain_text.operator=(this->table_row.substr(this->table_row.find("@@@") + 3, this->table_row.size()));

  for(u32 i = 0; i < this->rb_cols; ++i){

    if(memcmp(this->table_row_hash->value, hash_to_search->value, std::max(this->table_row_hash->size, hash_to_search->size)) == 0){
      
      this->plain_text_found.operator=(this->table_row_plain_text);
      this->is_found = true;
      
      break;
    };
     
  }

  return 0;
}

int rainbow_reader::search_table(s_byte_array* hash_to_search, std::string file_name){
  
  std::fstream table_file;
  table_file.open(file_name, std::ios::in | std::ios::binary);
  if(!table_file.is_open()) return 1;

  while(getline(table_file, this->table_row).eofbit){

    this->search_row(hash_to_search);
    
    if(this->is_found) break;

  }
  
  do{ table_file.close(); } while(table_file.is_open());

  return 0;
}
