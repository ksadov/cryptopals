#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cputils.h"
#define BIGSIZE 1000000

/*
int main(void) {
  char * msg = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
  unsigned char b1[SIZE];
  char b2[SIZE];
  // VHE VHH VHI VHJ VHK VHL VHM VHO BHK BHN good, VHF VHG VHK VHN  bad
  repeating_key_xor (b1, msg, "VHK", 3, 74);
  //repeating_key_xor ((unsigned char *) b2, (char *) b1, "VHN", 3, 74);
  //printf("message: %s\n", b1);
  break_vignere(b2, b1, 74);
  printf("decrypted: %s\n", b2);
  //printf("bad: %s\n", b2);
}
*/

int main(void) {
  char * file = "src/6.txt";
  FILE * fp = fopen(file, "rb");
  char msgbuf[BIGSIZE];
  int pos = 0;
  while (fgets(&msgbuf[pos], 62, fp)) {
    pos += 60;
  }
  unsigned char b1[SIZE];
  char b2[SIZE];
  // VHE VHH VHI VHJ VHK VHL VHM VHO BHK BHN good, VHF VHG VHK VHN  bad
  //repeating_key_xor (b1, msg, "VHK", 3, 60);
  //repeating_key_xor ((unsigned char *) b2, (char *) b1, "VHN", 3, 74);
  //printf("message: %s\n", b1);
  if (b64_to_binary(b1, msgbuf, (360*2)/3) >= 0 ) {
    break_vignere(b2, b1, (360*2)/3);
    printf("decrypted: %s\nstrlen:%lu\n", &b2[9], strlen(b2));
  }
  //printf("bad: %s\n", b2);
}
