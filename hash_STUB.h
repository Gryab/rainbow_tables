#ifndef hash_STUB_h
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
 @ Gryab: HEADER FOR DEBUGGING AND TROUBLESHOOTING ONLY 
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#include "includes_ext.h"

int my_hash_function(std::string* plain_text_input, s_byte_array* hash_output)
{
  
  hash_output->size = (u64)sizeof(std::size_t);
  hash_output->value = (u8*)malloc(hash_output->size);

  if(hash_output->value == nullptr) return 1;

  *(std::size_t*)(hash_output->value) = std::hash<std::string>{}(*plain_text_input);

  return 0;
};

#define hash_STUB_h
#endif
