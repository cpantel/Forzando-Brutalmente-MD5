#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

#include <immintrin.h>

#define BUFFER_LEN 64 
#define BUFFER_SIZE_OFFSET 56

#define LANES 8
void loadHashx(char* argv[], uint32_t* a, uint32_t* b, uint32_t* c, uint32_t* d) {
   char tmp[8];

   strncpy(tmp,&argv[1][0],8);
   *a = strtoul(tmp,0,16);

   strncpy(tmp,&argv[1][8],8);
   *b = strtoul(tmp,0,16);

   strncpy(tmp,&argv[1][16],8);
   *c = strtoul(tmp,0,16);

   strncpy(tmp,&argv[1][24],8);
   *d = strtoul(tmp,0,16);
}


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

void showm256i(const char* label, const __m256i * value) {
   uint32_t* f = (uint32_t *) value;
   printf("%s:  %08x \n", label,
    f[0]);
}


void showm256iAll(const char* label, const __m256i * value) {
   uint32_t* f = (uint32_t *) value;
   printf("%s:  %08x %08x %08x %08x %08x %08x %08x %08x\n", label,
    f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);
}


void hexdump(const char * label, const uint32_t * buffer, size_t len) {
   int i;
   printf("%s: ", label);
   for (i=0; i<len; ++i) {
      printf("%02x", 0xFF & ((char*)buffer)[i]);
      if (( i + 1 )  % 4 == 0) {
         printf(" ");
      }
   }
   printf("\n");
}

int main(int argc, char * argv[]) {   

   int i;
   

   uint32_t targetA;
   uint32_t targetB;
   uint32_t targetC;
   uint32_t targetD;

   loadHash(argv, &targetA, &targetB, &targetC, &targetD);

   __m256i mTargetA = _mm256_set1_epi32(targetA);
   __m256i mTargetB = _mm256_set1_epi32(targetB);
   __m256i mTargetC = _mm256_set1_epi32(targetC);
   __m256i mTargetD = _mm256_set1_epi32(targetD);


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
   
   uint32_t M[LANES][BUFFER_LEN];

   int mIndex;

   for (mIndex = 0 ; mIndex < LANES; ++mIndex) {
      pad(";;;a", M[mIndex]);
   }

   char char0,char1,char2,char3;
   uint64_t hashcount = 0;

//   uint32_t digest[LANES][4];

/*
   uint32_t* X0_32[] = {
       (uint32_t*) &a0,
       (uint32_t*) &b0,
       (uint32_t*) &c0,
       (uint32_t*) &d0
   };
*/

for ( char0 = ';' ; char0 <= 'z' ; ++char0) {
for ( char1 = ';' ; char1 <= 'z' ; ++char1) {
for ( char2 = ';' ; char2 <= 'z' ; ++char2) {
for ( char3 = ';' ; char3 <= 'z' ; char3 += LANES) {


   int laneIdx;

   for (laneIdx = 0; laneIdx < LANES ; ++laneIdx) {
        (( char* ) ( M[laneIdx] ))[0] = char0;
        (( char* ) ( M[laneIdx] ))[1] = char1;
        (( char* ) ( M[laneIdx] ))[2] = char2;
        (( char* ) ( M[laneIdx] ))[3] = char3 + laneIdx;
   }

   hashcount += LANES;

   __m256i a0  = _mm256_set1_epi32(0x67452301);
   __m256i b0  = _mm256_set1_epi32(0xefcdab89);
   __m256i c0  = _mm256_set1_epi32(0x98badcfe);
   __m256i d0  = _mm256_set1_epi32(0x10325476);

   __m256i A = a0;
   __m256i B = b0;
   __m256i C = c0;
   __m256i D = d0;

/*
   uint32_t* X0_32[] = {
       (uint32_t*) &a0,
       (uint32_t*) &b0,
       (uint32_t*) &c0,
       (uint32_t*) &d0
   };

*/

   __m256i right_base = _mm256_set1_epi32(32);

   //Main loop:                                                 
   for (i=0; i<64; ++i){                       
           __m256i F;
           int g;                          

          if ( i < 16 ) {
               // F = (B & C) | (( ~ B) & D);
               __m256i NotB = _mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff));

               F = _mm256_or_si256(
                    _mm256_and_si256(B,C),
                    _mm256_and_si256(D,NotB)
                   );
 
               g = i;
           } else if ( i < 32) {
              //  F = (D & B) | (( ~ D) & C);
               __m256i NotD = _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff));

               F =  _mm256_or_si256(
                     _mm256_and_si256(D,B),
                    _mm256_and_si256(NotD,C)
                  );
               g = (5 * i + 1) % 16;
           } else if ( i < 48 ) {
           //  F = B ^ C ^ D;
               F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

               g = (3 * i + 5) % 16;
           } else  {
           //  F = C ^ (B | (~  D));
               __m256i NotD = _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff));

               F = _mm256_xor_si256(C, _mm256_or_si256(B, NotD));
 
               g = (7 * i) % 16;
           }

           // F = F + A + K[i] + M[g];
           __m256i Kline = _mm256_set1_epi32( K[i] );
           __m256i Mline = _mm256_set_epi32( M[0][g], M[1][g], M[2][g], M[3][g], M[4][g], M[5][g], M[6][g], M[7][g]  );
 
           F = _mm256_add_epi32(
                 _mm256_add_epi32(F, A),
                 _mm256_add_epi32(Kline,Mline)
           );

           A = D;
           D = C;
           C = B;

           // B = B + LEFTROTATE(F, s[i]);
           __m256i count_left  = _mm256_set1_epi32(s[i]);
           __m256i rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)) );

           B = _mm256_add_epi32(B, rotated);
   }

   a0 = _mm256_add_epi32(a0, A);
   b0 = _mm256_add_epi32(b0, B);
   c0 = _mm256_add_epi32(c0, C);
   d0 = _mm256_add_epi32(d0, D);



   // comparisson and copy to buffer if equal

   __m256i cmpA = _mm256_cmpeq_epi32( mTargetA, a0);

   //showm256iAll("cmpA  ", &cmpA);

  int cmpBufferA[8];
  _mm256_maskstore_epi32(cmpBufferA,cmpA,cmpA);


  //hexdump("cmpBufferA  ", cmpBufferA, 32);

/*
  if strncmp(M,";;;;",4) {
     printf("expecting match...\n");

  }
*/

  int y;

  for (y=0; y<LANES; ++y) {
 

//    hexdump("cmpBufferA[y]  ", cmpBufferA[y], 4);
 
    if ( cmpBufferA[y] == 0xffffffff) {
        __m256i cmpB = _mm256_cmpeq_epi32( mTargetB, b0);
        int cmpBufferB[8];
        _mm256_maskstore_epi32(cmpBufferB,cmpB,cmpB);
        if (cmpBufferB[y] == 0xffffffff ) {
           __m256i cmpC = _mm256_cmpeq_epi32( mTargetC, c0);
           int cmpBufferC[8];
           _mm256_maskstore_epi32(cmpBufferC,cmpC,cmpC);
            if (cmpBufferC[y] == 0xffffffff ) {
              __m256i cmpD = _mm256_cmpeq_epi32( mTargetD, d0);
              int cmpBufferD[8];
              _mm256_maskstore_epi32(cmpBufferD,cmpD,cmpD);
              if (cmpBufferC[y] == 0xffffffff ) {
                 //showm256iAll("target A   ", &mTargetA);
                 //showm256iAll("a0         ", &a0);
                 //showm256iAll("cmpA       ", &cmpA);
                 //hexdump("cmpBufferA ", (const uint32_t * ) cmpBufferA, 32);

                 printf("found key %c%c%c%c\n", char0, char1, char2, char3 + LANES -y -1 );
                 printf("hashcount : %lu\n", hashcount);
                 return 0;
              }
           }
        }
     }
  }  
/*
   if ( hashcount > 1  16777210  ) {

      showm256iAll("mtargetA ", &mTargetA);
      showm256iAll("mtargetB ", &mTargetB);
      showm256iAll("mtargetC ", &mTargetC);
      showm256iAll("mtargetD ", &mTargetD);
      printf("\n");

      showm256iAll("a0       ", &a0);
      showm256iAll("b0       ", &b0);
      showm256iAll("c0       ", &c0);
      showm256iAll("d0       ", &d0);

      printf("\n");

     int col;
     for (col = 0; col < 4; ++col) {
         for (mIndex=0; mIndex < LANES; ++mIndex) { 
            digest[mIndex][col] = X0_32[col][mIndex];
         }
     }

     for ( mIndex = 0; mIndex < LANES; ++mIndex){
        hexdump("digest   ", digest[mIndex], 16);
     }

   return 2;
   }
*/
}
}
}
}

   printf("key not found\n");
   printf("hashcount : %lu\n", hashcount);
   return 1;
}



