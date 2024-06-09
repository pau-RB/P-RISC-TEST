#define MSG_ADDR 0x60000000
#define HEX_ADDR 0x60000004
#define MSR_ADDR 0x60000008
#define CTR_ADDR 0x6000000c

void print_MSG(char c)
  {*(int*)MSG_ADDR = (int)c;}

void print_HEX(int c)  
  {*(int*)HEX_ADDR = c;}

void print_MSR(char c)
  {*(int*)MSR_ADDR = (int)c;}

void print_CTR(char c)
  {*(int*)CTR_ADDR = (int)c;}
