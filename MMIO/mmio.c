#define MSG_ADDR 0x7ffff000
#define HEX_ADDR 0x7ffff004
#define MSR_ADDR 0x7ffff008

void print_MSG(char c)
  {*(int*)MSG_ADDR = (int)c;}

void print_HEX(int c)  
  {*(int*)HEX_ADDR = c;}

void print_MSR(char c)
  {*(int*)MSR_ADDR = (int)c;}
