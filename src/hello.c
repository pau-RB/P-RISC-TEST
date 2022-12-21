#include"../MMIO/mmio.h"

int main() {
  char *s = "Hello, world!\n";
  char *p;
  for (p = s; p < s + 14; p++) print_MSG(*p);
  return 0;
}
