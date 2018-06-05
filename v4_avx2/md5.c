#include <immintrin.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BUFFER_LEN 64 
#define BUFFER_SIZE_OFFSET 56

#define LANES 8


/*
   //Pre-processing: adding a single 1 bit
   append "1" bit to message    
   // Notice: the input bytes are considered as bits strings,
   //  where the first bit is the most significant bit of the byte.[48]
   
   //Pre-processing: padding with zeros
   append "0" bit until message length in bits ≡ 448 (mod 512)
   append original length in bits mod 264 to message

_*/
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


void EXshowm256i(const char* label, const __m256i * value) {
   uint32_t* f = (uint32_t *) value;
   printf("%s:  %08x %08x %08x %08x %08x %08x %08x %08x\n", label,
    f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);
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

   int i;
   
   //s specifies the per-round shift amounts

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

      pad(argv[mIndex + 1], M[mIndex]);
      hexdump("full buffer M", M[mIndex], BUFFER_LEN);
   }

   //Initialize variables:

   __m256i a0  = _mm256_set1_epi32(0x67452301);
   __m256i b0  = _mm256_set1_epi32(0xefcdab89);
   __m256i c0  = _mm256_set1_epi32(0x98badcfe);
   __m256i d0  = _mm256_set1_epi32(0x10325476);


   __m256i A = a0;
   __m256i B = b0;
   __m256i C = c0;
   __m256i D = d0;


   __m256i right_base = _mm256_set1_epi32(32);

   //Main loop:                                                 
       for (i=0; i<64; ++i){                       
           __m256i F;
           int g;                          

          if ( i < 16 ) {                         //   if 0 ≤ i ≤ 15 then
//               F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
               __m256i NotB = _mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff));

               F = _mm256_or_si256(
                    _mm256_and_si256(B,C),
                    _mm256_and_si256(D,NotB)
                   );
 
               g = i;                              //       g := i
           } else if ( i < 32) {                   //   else if 16 ≤ i ≤ 31
//               F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
               __m256i NotD = _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff));

               F =  _mm256_or_si256(
                     _mm256_and_si256(D,B),
                    _mm256_and_si256(NotD,C)
                  );
               g = (5 * i + 1) % 16;               //       g := (5×i + 1) mod 16
           } else if ( i < 48 ) {                  //   else if 32 ≤ i ≤ 47
//               F = B ^ C ^ D;                      //       F := B xor C xor D
               F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

               g = (3 * i + 5) % 16;               //       g := (3×i + 5) mod 16
           } else  {                               //   else if 48 ≤ i ≤ 63
//               F = C ^ (B | (~  D));               //       F := C xor (B or (not D))

               __m256i NotD = _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff));

               F = _mm256_xor_si256(C, _mm256_or_si256(B, NotD));
 
               g = (7 * i) % 16;                   //       g := (7×i) mod 16
           }                                       // 



 //          F = F + A + K[i] + M[g];                //    F := F + A + K[i] + M[g]
             __m256i Kline = _mm256_set1_epi32( K[i] );
             __m256i Mline = _mm256_set_epi32( M[0][g], M[1][g], M[2][g], M[3][g], M[4][g], M[5][g], M[6][g], M[7][g]  );
 
             F = _mm256_add_epi32(
                   _mm256_add_epi32(F, A),
                   _mm256_add_epi32(Kline,Mline)
                 );

           A = D;                                  //    A := D
           D = C;                                  //    D := C
           C = B;                                  //    C := B

 //          B = B + LEFTROTATE(F, s[i]);            //    B := B + leftrotate(F, s[i])
           __m256i count_left  = _mm256_set1_epi32(s[i]);
           __m256i rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)) );


           B = _mm256_add_epi32(B, rotated);

       }

   //Add this chunk's hash to result so far:
       //a0 = a0 + A;
       //b0 = b0 + B;
       //c0 = c0 + C;
       //d0 = d0 + D;

       a0 = _mm256_add_epi32(a0, A);
       b0 = _mm256_add_epi32(b0, B);
       c0 = _mm256_add_epi32(c0, C);
       d0 = _mm256_add_epi32(d0, D);



   //(Output is in little-endian)
   //printf("%X %X %X %X\n", a0, b0, c0, d0);
   uint32_t digest[LANES][4];
   uint32_t* x0_32[] = {
       (uint32_t*) &a0,
       (uint32_t*) &b0,
       (uint32_t*) &c0,
       (uint32_t*) &d0
   };

   int col;
   for (col = 0; col < 4; ++col) {
      for (mIndex=0; mIndex < LANES; ++mIndex) { 
         digest[mIndex][col] = x0_32[col][mIndex];
      }
   }

//   digest[mIndex][0] = a0;
//   digest[mIndex][1] = b0;
//   digest[mIndex][2] = c0;
//   digest[mIndex][3] = d0;
   for ( mIndex = 0; mIndex < LANES; ++mIndex){
      
      hexdump("digest   ", digest[mIndex], 16);


   }

}



