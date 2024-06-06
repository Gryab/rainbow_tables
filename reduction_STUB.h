#ifndef reduction_STUB_h
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
 @ Gryab: HEADER FOR DEBUGGING AND TROUBLESHOOTING ONLY 
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#include "includes_ext.h"

int my_reduction_function(s_byte_array* hash_input, std::string* alphabet, std::string* plain_text_output)
{
  
  std::size_t hash_value = *(std::size_t*)hash_input->value;
  
  plain_text_output->clear();
  
  while ((bool)hash_value)
  {

    plain_text_output->operator+=(alphabet->at((hash_value >>= 1) % alphabet->size()));
  
  }

  return 0;
}

#define reduction_STUB_h
#endif
