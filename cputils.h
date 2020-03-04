#define SIZE 1024
#define BIGSIZE 8192

/**
 * Returns the value represented by hexadecimal character hex,
 * (upper or lowercase), or -1 if hex is not a valid hexadecimal character.
 */
char hexchar_to_int (char hex);

/**
 * Stores the binary representation of the hexadecimal string hex in buf.
 * Requires: hex is a null-terminated string.
 */
void hex_to_binary (unsigned char* buf, const char* hex);

/**
 * Convert the base-64 encoded array in b64 to a binary array of size len
 * in buf.
 * Returns: 0 if conversion was successful, -1 otherwise.
 */
int b64_to_binary (unsigned char* buf, const char* b64, int len);

/**
 * Converts the binary array in bin to a null-terminated n-character base64
 * string in buf.
 */
void binary_to_64 (char* buf, const unsigned char* bin, int n);

/**
 * Converts a null-terminated hex string in hex to a null-terminated base64.
 * string in buf
 * Returns: 0 if successful, -1 if failed
 * Requires: the number of characters in hex is a multiple of 6.
 */
int hex_to_64 (char* buf, const char* hex);

/**
 * Stores the results of xoring the characters in h1 and h2 in buf.
 * Requires h1 and h2 have the same length
 * Returns: 0 if successful, -1 if failed
 */
int xor_hex (char* buf, const char* h1, const char* h2);

/**
 * Fill a buf with the hex representation of x up to position len.
 * Requires: len is a multiple of 2
 */
void fill_buf(unsigned char* buf, const int n, const unsigned char c);

/**
 * Returns average edit distance between blocks of length keysize for the first
 * len bytes of msg.
 */
int hamming_distance(const unsigned char* c1, const unsigned char* c2, int len);

/**
 * Returns the estimated size of the Vignere cypher key (between min and max
 * characters in length) used to encrypt the first len bytes of msg.
 */
int find_keysize (const unsigned char* c1, int len, int min, int max);

/**
 * Stores the Vignere cyphere decoding of the first len characters of
 * the binary data in msg as a null-terminated string in buf, and the key
 * as a null-terminagted string in keybuf.
 * Requires: the size of the key used in Vignere encoding is between min and max
 * characters in length.
 */
int break_vignere(char * buf, char* keybuf,  const unsigned char* msg,
                  int len, int min, int max);

/**
 * Returns the value represented by the base 64 character c, or -1
 * if c is not a valid base-64 character.
 */
int b64_char_val (char c);

/**
 *  xors the first n characters of a1 and a2 and stores results in buf
 */
void bin_xor (unsigned char* buf, const unsigned char* a1, const unsigned char* a2,
              const int n);

/**
 * Fills buf with n repetititons of c.
 */
void fill_buf(unsigned char* buf, const int n, const unsigned char c);

/**
 * xors the first len characters in msg against all 256 ascii characters,
 * then stores whatever resulting array has the highest caesar score in buf
 * Returns: the character that produces the highest caesar score
 */
char singlechar_xor (char* buf, const unsigned char* msg, const int len);

/**
 * xors the first len characters of msg with (len / keylen)
 * repetitions of the first keylen characters of key, then stores the results
 * in buf.
 */
void repeating_key_xor (unsigned char* buf, const char* msg,
                        const char* key,
                        int keylen, int len);
/**
 * Stores the hex representation of the first len/2 bytes of bin in buf,
 * followed by a null character.
 */
void bin_to_hex (char* buf, const unsigned char* bin, int len);

/**
 * Returns the hamming distance between the first len characters of c1 and c2.
 */
int hamming_distance(const unsigned char* c1, const unsigned char* c2, int len);

/**
 * Returns the caesar score of the first len characters of msg, where a
 * higher score means more resemblance to an english string.
 */
int caesar_score (const unsigned char * msg, int len );
