#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cputils.h"

int main(void) {
  char * file = "src/6.txt";
  FILE * fp = fopen(file, "rb");
  char msgbuf[BIGSIZE];
  char keybuf[SIZE];
  int pos = 0;
  while (fgets(&msgbuf[pos], 62, fp)) {
    pos += 60;
  }
  unsigned char b1[BIGSIZE];
  char b2[BIGSIZE];
  int binlen = (strlen(msgbuf)-1)*3/4;
  if (b64_to_binary(b1, msgbuf, binlen) >= 0) {
    break_vignere(b2, keybuf, b1, binlen, 2, 40);
    printf("key: %s\ndecrypted: %s\n", keybuf, b2);
  }
}
