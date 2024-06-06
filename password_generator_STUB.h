#include "hash_STUB.h"
#include "reduction_STUB.h"
#include <cstdlib>
#ifndef password_generator_STUB_h
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
 @ Gryab: HEADER FOR DEBUGGING AND TROUBLESHOOTING ONLY 
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#include "includes_ext.h"

int my_password_generator(u32 seed, std::string* alphabet, std::string* output)
{
  
  std::string input(seed, alphabet->at((seed << 2) % alphabet->size()));

  s_byte_array hash_input = {sizeof(std::size_t), (u8*)malloc(sizeof(std::size_t))};

  my_hash_function(&input, &hash_input);

  my_reduction_function(&hash_input, alphabet, output);

  return 0;
}

#define password_generator_STUB_h
#endif
