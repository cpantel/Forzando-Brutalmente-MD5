#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

#define BUFFER_LEN 64 
#define BUFFER_SIZE_OFFSET 56

#define LEFTROTATE(x, c)  (((x) << (c)) | ((x) >> (32 - (c))))

void loadHash(char* argv[], uint32_t* a, uint32_t* b, uint32_t* c, uint32_t* d) {
   char tmp[8];

   strncpy(tmp,&argv[1][0],8);
   *a = htonl(strtoul(tmp,0,16));

   strncpy(tmp,&argv[1][8],8);
   *b = htonl(strtoul(tmp,0,16));

   strncpy(tmp,&argv[1][16],8);
   *c = htonl(strtoul(tmp,0,16));

   strncpy(tmp,&argv[1][24],8);
   *d = htonl(strtoul(tmp,0,16));
}

size_t pad(const char * message, uint32_t buffer[]) {
   size_t buffer_size = strnlen(message,BUFFER_LEN);
   uint8_t * buffer_8 = (uint8_t *) buffer;
   memset(buffer_8,0,BUFFER_LEN );
   memcpy(buffer_8,message,buffer_size);
   buffer_8[buffer_size] = 0x80;
   size_t newLen = buffer_size * 8;
   uint8_t * offset = &buffer_8[BUFFER_SIZE_OFFSET];
   memcpy(offset, &newLen, 4);
   return buffer_size;
}

void hexdump(const char * label, const uint32_t * buffer, size_t len) {
   int i;
   printf("%s: ", label);
   for (i=0; i<len; ++i) {
      printf("%02x", 0xFF & ((char*)buffer)[i]);
   }
   printf("\n");
}

int main(int argc, char * argv[]) {   
   uint32_t targetA;
   uint32_t targetB;
   uint32_t targetC;
   uint32_t targetD;

   int i;

   loadHash(argv, &targetA, &targetB, &targetC, &targetD);

   uint32_t s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                   5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                   4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                   6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

   uint32_t K[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
   
   uint32_t M[BUFFER_LEN];

   pad("    ", M);

   char char0,char1,char2,char3;
   uint64_t hashcount = 0;

   for (char0 = ';'; char0 <= 'z' ; ++char0) {
   for (char1 = ';'; char1 <= 'z' ; ++char1) {
   for (char2 = ';'; char2 <= 'z' ; ++char2) {
   for (char3 = ';'; char3 <= 'z' ; ++char3) {


      ((char*)M)[0] = char0;
      ((char*)M)[1] = char1;
      ((char*)M)[2] = char2;
      ((char*)M)[3] = char3;


      ++hashcount;

      //Initialize variables:
      uint32_t a0 = 0x67452301;   //A
      uint32_t b0 = 0xefcdab89;   //B
      uint32_t c0 = 0x98badcfe;   //C
      uint32_t d0 = 0x10325476;   //D


   //Initialize hash value for this chunk:
      uint32_t A = a0;
      uint32_t B = b0;
      uint32_t C = c0;
      uint32_t D = d0;
   //Main loop:                                                 
      for (i=0; i<64; ++i){                       // for i from 0 to 63
           uint32_t F, g;                          //   var int F, g
           if ( i < 16 ) {                         //   if 0 ≤ i ≤ 15 then
               F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
               g = i;                              //       g := i
           } else if ( i < 32) {                   //   else if 16 ≤ i ≤ 31
               F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
               g = (5 * i + 1) % 16;               //       g := (5×i + 1) mod 16
           } else if ( i < 48 ) {                  //   else if 32 ≤ i ≤ 47
               F = B ^ C ^ D;                      //       F := B xor C xor D
               g = (3 * i + 5) % 16;               //       g := (3×i + 5) mod 16
           } else  {                               //   else if 48 ≤ i ≤ 63
               F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
               g = (7 * i) % 16;                   //       g := (7×i) mod 16
           }

           F = F + A + K[i] + M[g];                //    F := F + A + K[i] + M[g]

           A = D;                                  //    A := D
           D = C;                                  //    D := C
           C = B;                                  //    C := B
           B = B + LEFTROTATE(F, s[i]);            //    B := B + leftrotate(F, s[i])
      }

      //Add this chunk's hash to result so far:
      a0 = a0 + A;
      b0 = b0 + B;
      c0 = c0 + C;
      d0 = d0 + D;
  
      if ( targetA == a0
        && targetB == b0
        && targetC == c0
        && targetD == d0) {
           printf("found key : %c%c%c%c\n", char0,char1,char2,char3);
           printf("hashcount : %lu\n", hashcount);
           return 0;
      }

   }
   }
   }
   }

   printf("key not found\n");
   printf("hashcount : %lu\n", hashcount);
   return 1;
}



