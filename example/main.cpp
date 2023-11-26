#include "src/util.h"

void my_count() {
  volatile int value = 0;
  {
    for (int i = 0; i < 10000000; i++)
      value += 2;
  }
}

int main() {
  time_function(my_count);
  return 0;
}
