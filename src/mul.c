int main() {
  long long int a = -6;
  long long int b = 7;
  long long int c = -15;
  long long int d = 17;
  short         e = 3;
  unsigned int  f = 4;

  asm("li t1,42\n"
      "li t2,47\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-13\n"
      "li t2,412\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,7373\n"
      "li t2,-222\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-46\n"
      "li t2,312\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-13\n"
      "li t2,-17\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-347\n"
      "li t2,7127\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-465\n"
      "li t2,74613\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-46165\n"
      "li t2,-4153\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-546\n"
      "li t2,789\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-165\n"
      "li t2,-1745\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,566\n"
      "li t2,-48\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,0\n"
      "li t2,-222\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,0\n"
      "li t2,-17\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,489\n"
      "li t2,7145\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-4065\n"
      "li t2,743\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,165\n"
      "li t2,-415\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,0\n"
      "li t2,-423\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-184\n"
      "li t2,-15\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,0\n"
      "li t2,-1\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-1\n"
      "li t2,-1\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-1\n"
      "li t2,12\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  asm("li t1,-3\n"
      "li t2,-1\n"
      "mul    a0,t1,t2\n"
      "mulh   a0,t1,t2\n"
      "mulhsu a0,t1,t2\n"
      "mulhu  a0,t1,t2\n"
      "div    a0,t1,t2\n"
      "divu   a0,t1,t2\n"
      "rem    a0,t1,t2\n"
      "remu   a0,t1,t2\n");

  return (a*b>>7) & (c*d>>6) | (c*a<<3) ^ ((long long int)e*(long long int)f)>>4;
}
