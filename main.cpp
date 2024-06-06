#include "includes_ext.h"
#include "includes_inter.h"
#include "rainbow_builder.h"
#include "rainbow_reader.h"

int main(void)
{

  std::string Alphabet("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"), delimiter("|||");

  rainbow_builder Rainbow_builder(10000, 3, Alphabet, delimiter, &my_hash_function, &my_reduction_function, &my_password_generator);
  
  rainbow_reader Rainbow_reader(3, Alphabet, delimiter, &my_hash_function, &my_reduction_function);

  Rainbow_builder.build_table(std::string("table.txt"));

  return 0;

}
