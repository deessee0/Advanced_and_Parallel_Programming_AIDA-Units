#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

struct node {
  int32_t key;
  struct node * next;
};

struct foo {
  int8_t a;
  int64_t b;
  int8_t c;
  int64_t d;
  int16_t e;
};


struct bar {
  int8_t a;
  int8_t c;
  int16_t e;
  int64_t b;
  int64_t d;
};

struct __attribute__ ((packed)) baz {
  int8_t a;
  int64_t b;
  int8_t c;
  int64_t d;
  int16_t e;
};

void print_bytes(char * x, int len)
{
  printf("Dimensione: %d bytes\n", len);
  for (int i = 0; i < len; i++) {
    printf("byte %d: %x\n", i, x[i]);    
  }
}

int main(int argc, char * argv[])
{
  struct node n;
  n.key = 0xffffffff;
  n.next = (struct node *) 0xffffffffffffffff;
  print_bytes((char*)&n, sizeof(struct node));

  struct foo f;
  f.a = 0xff;
  f.b = 0xffffffffffffffff;
  f.c = 0xff;
  f.d = 0xffffffffffffffff;
  f.e = 0xffff;
  print_bytes((char *)&f, sizeof(struct foo));

  struct bar g;
  g.a = 0xff;
  g.b = 0xffffffffffffffff;
  g.c = 0xff;
  g.d = 0xffffffffffffffff;
  g.e = 0xffff;
  print_bytes((char *)&g, sizeof(struct bar));

  struct baz h;
  h.a = 0xff;
  h.b = 0xffffffffffffffff;
  h.c = 0xff;
  h.d = 0xffffffffffffffff;
  h.e = 0xffff;
  print_bytes((char *)&h, sizeof(struct baz));

  return 0;
}
