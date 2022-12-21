int* MSG_ADDR = (int *)0x003fff0;
int* HEX_ADDR = (int *)0x003fff4;
int* MSR_ADDR = (int *)0x003fff8;

int print_MSG(char c) {
  *MSG_ADDR = (int)c;
  return c;
}

int print_HEX(int c) {
  *HEX_ADDR = c;
  return c;
}

int print_MSR(char c) {
  *MSR_ADDR = (int)c;
  return c;
}
