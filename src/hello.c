#include"../MMIO/mmio.h"

int main() {
  char *s = "Hello, world!";
  char *p;
  for (p = s; p < s + 13; p++) print_MSG(*p);
  return 0;
}
