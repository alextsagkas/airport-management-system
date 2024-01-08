#include "int.h"
#include "key.h"
#include <stdio.h>

int main() {

  key_intp int_data1 = create_int_node(5);
  key_intp int_data2 = create_int_node(5);

  key_tp data1 = create_key((void *)int_data1);
  key_tp data2 = create_key((void *)int_data2);

  if (are_equal(data1, data2, int_equalizer)) {
    printf("Equal\n");
  } else {
    printf("Not equal\n");
  }

  return 0;
}