#include "includes_ext.h"
#include "includes_inter.h"
#include "rainbow_builder.h"
#include "rainbow_reader.h"
#include "stdio.h"

int main(void)
{

  u64 rows = 100000, rounds /*columns*/ = 3;

  std::string Alphabet("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"), delimiter("|||");

  rainbow_builder Rainbow_builder(rows, rounds, Alphabet, delimiter, &my_hash_function, &my_reduction_function, &my_password_generator);
  
  Rainbow_builder.build_table(std::string("table.txt"));


  rainbow_reader Rainbow_reader(rounds, Alphabet, delimiter, &my_hash_function, &my_reduction_function);
  
  {

    std::string __test_text = "tRDbntRD63WlswyzzUkNgLAanOCbntRDbI9ZH8ZH84XlswTEcJepuxTEcJ94210";

    std::string __test_output;

    s_byte_array __test_array;

    my_hash_function(&__test_text, &__test_array);
    
    for(u64 i = 0; i < 1; i++)
    {
      my_reduction_function(&__test_array, &Alphabet, &__test_text);

      my_hash_function(&__test_text, &__test_array);
    }

    printf("%s\n", __test_text.c_str());

    Rainbow_reader.search_table(&__test_array, std::string("table.txt"));

    printf("%i\n", Rainbow_reader.get_found_plain_text(&__test_output));

    printf("%s", __test_output.c_str());

  }

  return 0;

}
