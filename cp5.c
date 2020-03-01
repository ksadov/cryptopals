#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cputils.h"

#define MAX_SIZE 1024

int main() {
  char* key = "ICE";
  char* msg = "Burning 'em, if you ain't quick and nimble\n"
              "I go crazy when I hear a cymbal";
  printf("input: %s\n", msg);
  unsigned char binresult[MAX_SIZE];
  char hexresult[MAX_SIZE];
  repeating_key_xor(binresult, msg, key,
                      strlen(key), strlen(msg));
  bin_to_hex(hexresult, binresult, strlen(msg));
  printf("output: %s\n", hexresult);
}


