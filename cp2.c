#include "cputils.h"
#include <stdio.h>
#include <string.h>

int main() {
  char buf[SIZE];
  char * i1 = "1c0111001f010100061a024b53535009181c";
  char * i2 = "686974207468652062756c6c277320657965";
  printf("input 1: %s\n", i1);
  printf("input 2: %s\n", i2);
  xor_hex(buf, i1, i2);
  printf("output: %s\n", buf);
}
