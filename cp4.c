#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cputils.h"
#include <limits.h>

int main() {
  char * file4 = "src/4.txt";
  FILE * f = fopen(file4, "rb");
  char lnbuf[SIZE];
  unsigned char binbuf[SIZE];
  char result[SIZE];
  char resultchar;
  int resultscore;
  int i = 1;

  int bestscore = INT_MIN;
  int bestline;
  char bestchar;
  char bestmsg[SIZE];

  while(fgets(lnbuf, SIZE, f)) {
    lnbuf[strlen(lnbuf)-1] = 0;
    int binlen = (strlen(lnbuf) - 1)/2;
    hex_to_binary(binbuf, lnbuf);
    resultchar = singlechar_xor(result, binbuf, binlen+1);
    result[binlen] = 0;
    resultscore = caesar_score((unsigned char *)result, binlen);
    if (resultscore > bestscore) {
      bestscore = resultscore;
      bestline = i;
      bestchar = resultchar;
      memcpy(bestmsg, result, binlen);
    }
    i++;
  }
  printf("line: %d\nkey: %c\nmessage: %s\n", bestline, bestchar, bestmsg);
}


