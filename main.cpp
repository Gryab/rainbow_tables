#include "includes_ext.h"
#include "includes_inter.h"
#include "rainbow_builder.h"
#include "rainbow_reader.h"

#include <chrono>
#include <cstdio>

#include "user_inputs.txt"

int main(void)
{

#ifdef USER_INPUTS

  u64 rows = ROWS, rounds /*columns*/ = ROUNDS;

  std::string Alphabet(ALPHABET), delimiter(DELIMITER), file_name = std::string(FILENAME);
  #if BUILD

  rainbow_builder Rainbow_builder(rows, rounds, Alphabet, delimiter, &my_hash_function, &my_reduction_function, &my_password_generator);
  
  //auto start = std::chrono::high_resolution_clock::now();

  Rainbow_builder.build_table(file_name);

  //std::printf("%f", std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count());
  #endif
  #if READ
  rainbow_reader Rainbow_reader(rounds, Alphabet, delimiter, &my_hash_function, &my_reduction_function);
  
  s_byte_array hash = {0};

  hash.size = HASH_SIZE;
  hash.value = (u8*)malloc(HASH_SIZE);
  if(hash.value == nullptr) return 1;

  sscanf_s(HASH, "%llx", (u64*)(hash.value));

  Rainbow_reader.search_table(&hash, file_name);

  std::string result;

  if(Rainbow_reader.get_found_plain_text(&result) == 0){
    printf("%s", result.c_str());
  }else {
    printf("No suitable plain text found!");
  }
  #endif
#endif
  return 0;

}
