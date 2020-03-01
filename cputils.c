#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cputils.h"
#include <float.h>
#define MAX_SIZE 1024

static const char base64_table[65] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const char best_letters[10] = "eEtTaAoOiI";
static const char good_letters[14] = "nNsSrRhHdD";
static const char ok_letters[16] = "lLuUcCmMfFyYwWgG";

char hexchar_to_int (char hex) {
  if (hex >= '0' && hex <= '9')
    return hex - '0';

  else if (hex >= 'A' && hex <= 'F')
    return (hex - 'A') + 10;

  else if (hex >= 'a' && hex <= 'f')
      return (hex - 'a') + 10;

  else return -1;
}


void hex_to_binary (unsigned char* buf, const char* hex) {
  char n1;
  char n2;
  while (*hex != '\0') {
    n1 = hexchar_to_int(hex[0]);
    n2 = hexchar_to_int(hex[1]);
    *buf = (n1<<4)+n2;
    buf += 1;
    hex += 2;
  }
}

int b64_char_val (char c) {
  char * x = index(base64_table, c);
  if (x) return x - base64_table;
  else return -1;
}


int b64_to_binary (unsigned char* buf, const char* b64, int len) {
  unsigned char c1; unsigned char c2; unsigned char c3; unsigned char c4;
  int b64i = 0;
  for (int i = 0; i < (len - 2); i+= 3) {
    c1 = b64_char_val(b64[b64i]);
    c2 = b64_char_val(b64[b64i + 1]);
    c3 = b64_char_val(b64[b64i + 2]);
    c4 = b64_char_val(b64[b64i + 3]);
    if (c1 >= 0 && c2 >= 0 && c3 >= 0 && c4 >= 0) {
      buf[i] = (c1 << 2) | (c2 >> 4);
      buf[i+1] = ((c2 << 4)&0xFF) | (c3 >> 2);
      buf[i+2] = ((c3 << 6)&0xFF) | c4;
      b64i += 4;
    }
    else return -1;
  }
  return 0;
}


void binary_to_64 (char* buf, const unsigned char* bin, int n) {
  for (int i = 0; i < n; i+=4) {
    buf[i] = base64_table[(*bin >> 2)];
    buf[i+1] = base64_table[((*bin << 4)&0x3F) | (*(bin+1) >> 4)];
    buf[i+2] = base64_table[((*(bin+1) << 2)&0x3F) | (*(bin+2) >> 6)];
    buf[i+3] = base64_table[(*(bin+2))&0x3F];
    bin += 3;
    }
  //null terminate buf
  buf[n] = 0;
  }


int hex_to_64 (char* buf, const char* hex) {
  const int hexlen = strlen(hex);
  if (hexlen % 6 != 0) return -1;
  unsigned char bin_buf[hexlen / 2];
  hex_to_binary(bin_buf, hex);
  int b64strlen = (hexlen / 3) * 2;
  binary_to_64 (buf, bin_buf, b64strlen);
  buf[b64strlen+1] = '\0';
  return 0;
}


int xor_hex (char* buf, const char* h1, const char* h2) {
  size_t len = strlen(h1);
  if (len != strlen(h2) || len & 1) return -1;
  unsigned char* b1 = malloc(len / 2);
  unsigned char* b2 = malloc(len / 2);
  hex_to_binary(b1, h1);
  hex_to_binary(b2, h2);
  for (size_t i = 0; i < strlen(h1)/2; i++) {
    sprintf(&buf[2*i], "%x", b1[i] ^ b2[i]);
  }
  free(b1); free(b2);
  return 0;
}


void fill_buf_hex (char* buf, const char x, int len) {
  for (int i = 0; i < len/2; i++) {
    sprintf(&buf[2*i], "%x", x);
  }
}


int caesar_score (const binarray_t msg) {
  int score = 0;
  for (int i = 0; i < msg.len; i++) {
    if (index(best_letters, msg.bin[i])) score += 4;
    if (index(good_letters, msg.bin[i])) score += 2;
    if (index(ok_letters, msg.bin[i])) score += 1;
    if (msg.bin[i] < 'A' && msg.bin[i] != ' ' && msg.bin[i] != '\'') score -= 10;
    if (msg.bin[i] > 'Z' && msg.bin[i] < 'a') score -= 40;
    if (msg.bin[i] > 'z') score -= 100;
  }
  return score;
}

int caesar_compare (const void * a1, const void * a2) {
  return caesar_score( *(binarray_t *)a2) - caesar_score(*(binarray_t *)a1);
}

void bin_xor (binarray_t buf, const unsigned char* a1, const unsigned char* a2,
              const int n) {
  for (int i = 0; i < n; i++) {
    buf.bin[i] = a1[i] ^ a2[i];
  }
}

void fill_buf(unsigned char* buf, const int n, const unsigned char c) {
  for (int i = 0; i < n; i++) {
    buf[i] = c;
  }
}

int singlechar_xor (char* buf, const unsigned char* msg, const int len) {
  unsigned char charbuf[MAX_SIZE];
  charbuf[len] = 0;
  binarray_t asciiresults[256];
  for (int i = 0; i < 256; i++) {
    asciiresults[i].bin = malloc(len+1);
    asciiresults[i].len = len;
    (asciiresults[i]).bin[len] = 0;
    fill_buf(charbuf, len, (char)i);
    bin_xor(asciiresults[i], msg, charbuf, len);
  }
  mergesort(asciiresults, 256, sizeof(binarray_t), *caesar_compare);
  memcpy(buf, asciiresults[0].bin, len);
  for (int j = 0; j < 255; j++) {
    free(asciiresults[j].bin);
  }
  return 0;
}

void repeating_key_xor (unsigned char* buf, const char* msg,
                        const char* key,
                        int keylen, int msglen) {
  for (int i = 0; i < msglen; i++) {
    buf[i] = msg[i] ^ key[i%keylen];
  }
}

void bin_to_hex (char* buf, const unsigned char* bin, int len) {
  buf[0] = '0';
  for (int i = 0; i < len; i++) {
    sprintf(&buf[2*i], "%02x", bin[i]);
  }
  buf[len*2] =  0;
}

int hamming_distance(const unsigned char* c1, const unsigned char* c2, int len) {
  char xorchar;
  int count = 0;
  for (int i = 0; i < len; i++) {
    xorchar = c1[i] ^ c2[i];
    for (int j = 0; j < 8; j++) {
      if (xorchar % 2 == 1) count++;
      xorchar = xorchar >> 1;
    }
  }
  return count;
}


double block_compare (const unsigned  char* msg, const int keysize, const int len) {
  int pos1 = 0;
  int pos2 = keysize;
  double avg_dist = 0;
  double final_dist;
  int count = 0;
  double newblock_dist = 0;
  while (pos2+keysize < len && count < 3) {
    newblock_dist = (hamming_distance(&msg[pos1], &msg[pos2], keysize));
    avg_dist = (avg_dist + newblock_dist);
    count ++;
    pos1 = pos2 + keysize;
    pos2 = pos1 + keysize;
  }
  if (count == 0) return MAX_SIZE;
  final_dist = avg_dist / (count*keysize);
  return final_dist;
}

int find_keysize(const unsigned char* msg, int len) {
  double dist = 0;
  double min = DBL_MAX;
  int keysize = 0;
  for (int i = 2; i < 41; i++) {
    dist = block_compare (msg, i, len);
    if (dist < min) {
      keysize = i;
      min = dist;
    }
  }
  return keysize;
}


int break_vignere(char * buf, const unsigned char* msg, int len) {
  int keysize = find_keysize(msg, len);
  int xorlen;
  for (int i = 0; i < keysize; i++) {
    unsigned char tblock[MAX_SIZE];
    char xblock[MAX_SIZE];
    xorlen = 0;
    for (int j = i; j < len; j+= keysize) {
      tblock[j / keysize] = msg[j];
      xorlen++;
    }
   singlechar_xor(xblock, tblock, xorlen);
   for (int j = i; j < len; j+= keysize) {
     buf[j] = xblock[j / keysize];
   }
   //null terminate buf
   buf[len] = 0;
  }
  return 0;
}
