#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cputils.h"

int main() {
  char * file4 = "src/4.txt";
  FILE * f = fopen(file4, "rb");
  char lnbuf[SIZE];
  unsigned char binbuf[SIZE];
  char result[SIZE];
  int i = 1;
  while(fgets(lnbuf, SIZE, f)) {
    printf("Line %d:\n", i);
    printf("%s", lnbuf);
    lnbuf[strlen(lnbuf)-1] = 0;
    int binlen = (strlen(lnbuf) - 1)/2;
    hex_to_binary(binbuf, lnbuf);
    singlechar_xor(result, binbuf, binlen+1);
    result[binlen] = 0;
    printf("%s\n", result);
    i++;
  }
}


