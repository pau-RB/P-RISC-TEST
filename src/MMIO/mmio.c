int* PUT_ADDR = (int *)0x003fff0;
int* LSR_ADDR = (int *)0x003fff4;

int putchar(int c) {
  *PUT_ADDR = c;
  return c;
}

int printLSR(int c) {
  *LSR_ADDR = c;
  return c;
}
