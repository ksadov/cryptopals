#include <stdio.h>
#include "cputils.h"

int main() {
  char result[SIZE];
  char* hexstring = "49276d206b696c6c696e6720796f757220627261696e206c696b652061"
                    "20706f69736f6e6f7573206d757368726f6f6d";
  printf("input: %s\n", hexstring);
  hex_to_64(result, hexstring);
  printf("output: %s\n", result);
}
