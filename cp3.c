#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cputils.h"

int main() {
  char* input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393"
                "b3736";
  unsigned char bin[SIZE];
  printf("input: %s\n", input);
  int binlen = strlen(input)/2;
  hex_to_binary(bin, input);
  char result[SIZE];
  result[binlen+1] = 0;
  singlechar_xor(result, bin, binlen);
  printf("result: %s\n", result);
}
