#include <immintrin.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BUFFER_LEN 64 
#define BUFFER_SIZE_OFFSET 56

#define LANES 8


size_t pad(const char * message, uint32_t buffer[]) {
   size_t buffer_size = strnlen(message,BUFFER_LEN);
   uint8_t * buffer_8 = (uint8_t *) buffer;
   memset(buffer_8,0,BUFFER_LEN );
   memcpy(buffer_8,message,buffer_size);
   buffer_8[buffer_size] = 0x80;
   size_t newLen = buffer_size * 8;
//   buffer_8[BUFFER_SIZE_OFFSET]= buffer_size * 8;
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

   
   uint32_t M[LANES][BUFFER_LEN];

   int mIndex;

   for (mIndex = 0 ; mIndex < LANES; ++mIndex) {

      pad(argv[mIndex + 1], M[mIndex]);
   //   hexdump("full buffer M", M[mIndex], BUFFER_LEN);
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
   __m256i F;

   

       /************************** 0 *******************************/   
//0 0
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       __m256i Kline = _mm256_set1_epi32( 0xd76aa478 );
       __m256i Mline = _mm256_set_epi32( M[0][0], M[1][0], M[2][0], M[3][0], M[4][0], M[5][0], M[6][0], M[7][0]  );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) );
       A = D;
       D = C;
       C = B;

       __m256i count_left  = _mm256_set1_epi32(7);
       __m256i rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*************************** 1 ******************************/   
//0 1

       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0xe8c7b756);
       Mline = _mm256_set_epi32( M[0][1], M[1][1], M[2][1], M[3][1], M[4][1], M[5][1], M[6][1], M[7][1]  );

       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) );
 
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(12);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /************************** 2 *******************************/   
//0 2
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0x242070db );

 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(17);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*************************** 3 ******************************/   
//0 3
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0xc1bdceee );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(22);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*************************** 4 *****************************/   
//0 4
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0xf57c0faf );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(7);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//0 5
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0x4787c62a );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(12);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//0 6
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0xa8304613 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(17);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//0 7
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0xfd469501 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(22);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//0 8
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0x698098d8 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(7);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//0 9
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0x8b44f7af );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(12);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//0 A
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0xffff5bb1 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(17);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//0 B
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0x895cd7be );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(22);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//0 C
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0x6b901122 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(7);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//0 D
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0xfd987193 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(12);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /****************************************************** M 14 ***/   
//0 E
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

//       Kline = _mm256_set1_epi32( 0xa67943ae );
       Kline = _mm256_set1_epi32( 0xa679438e );
       Mline = _mm256_set_epi32( M[0][14], M[1][14], M[2][14], M[3][14], M[4][14], M[5][14], M[6][14], M[7][14]  );

       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) ) ;

       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(17);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//0 F
       F = _mm256_or_si256( _mm256_and_si256(B,C), _mm256_and_si256(D,_mm256_andnot_si256(B,_mm256_set1_epi32(0xffffffff))) );

       Kline = _mm256_set1_epi32( 0x49b40821 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(22);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

/******************************************************************************************************/   

                       

       /*********************************************************/   

//1 0
       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0xf61e2562 );
 
       Mline = _mm256_set_epi32( M[0][1], M[1][1], M[2][1], M[3][1], M[4][1], M[5][1], M[6][1], M[7][1]  );

       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(5);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//1 1
       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0xc040b340 );


       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
 
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(9);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//1 2

       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0x265e5a51 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(14);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//1 3
       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0xe9b6c7aa );
       Mline = _mm256_set_epi32( M[0][0], M[1][0], M[2][0], M[3][0], M[4][0], M[5][0], M[6][0], M[7][0]  );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) );

       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(20);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//1 4

       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0xd62f105d );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(5);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//1 5

       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0x2441453 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(9);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//1 6

       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0xd8a1e681 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(14);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//1 7
       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0xe7d3fbc8 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(20);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//1 8
       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0x21e1cde6 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(5);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /***************************************************** M 14****/   

//1 9
       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0xc33707d6 );

       Mline = _mm256_set_epi32( M[0][14], M[1][14], M[2][14], M[3][14], M[4][14], M[5][14], M[6][14], M[7][14]  );

       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) ) ;


 
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(9);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//1 A

       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0xf4d50d87 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(14);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//1 B
       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0x455a14ed );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(20);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//1 C
       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0xa9e3e905 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(5);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//1 D
       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0xfcefa3f8 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(9);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//1 E

       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0x676f02d9 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(14);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//1 F
       F =  _mm256_or_si256( _mm256_and_si256(D,B), _mm256_and_si256(_mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff)),C) );
       Kline = _mm256_set1_epi32( 0x8d2a4c8a );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(20);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

/******************************************************************************************************/   


       /*********************************************************/   
//2 0
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0xfffa3942 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(4);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 1
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0x8771f681 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(11);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 2
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0x6d9d6122 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(16);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*****************************************************M 14****/   
//2 3
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0xfde5380c );

       Mline = _mm256_set_epi32( M[0][14], M[1][14], M[2][14], M[3][14], M[4][14], M[5][14], M[6][14], M[7][14]  );

       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) ) ;


 
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(23);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 4
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0xa4beea44 );
       Mline = _mm256_set_epi32( M[0][1], M[1][1], M[2][1], M[3][1], M[4][1], M[5][1], M[6][1], M[7][1]  );

       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) );
 
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(4);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 5
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0x4bdecfa9 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(11);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 6
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0xf6bb4b60 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(16);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 7
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0xbebfbc70 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(23);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 8
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0x289b7ec6 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(4);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 9
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0xeaa127fa );
 
       Mline = _mm256_set_epi32( M[0][0], M[1][0], M[2][0], M[3][0], M[4][0], M[5][0], M[6][0], M[7][0]  );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(11);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 A
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0xd4ef3085 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(16);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 B
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0x4881d05 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(23);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 C
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0xd9d4d039 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(4);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 D
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0xe6db99e5 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(11);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 E
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0x1fa27cf8 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(16);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//2 F
       F = _mm256_xor_si256(B,_mm256_xor_si256(C,D));

       Kline = _mm256_set1_epi32( 0xc4ac5665 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(23);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);


/******************************************************************************************************/   


       /*********************************************************/   

//3 0
       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0xf4292244 );
       Mline = _mm256_set_epi32( M[0][0], M[1][0], M[2][0], M[3][0], M[4][0], M[5][0], M[6][0], M[7][0]  );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(6);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//3 1

       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0x432aff97 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(10);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /************************************************M 14*********/   
//3 2

       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0xab9423a7 );

       Mline = _mm256_set_epi32( M[0][14], M[1][14], M[2][14], M[3][14], M[4][14], M[5][14], M[6][14], M[7][14]  );

       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) ) ;
 
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(15);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//3 3

       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0xfc93a039 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(21);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//3 4

       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0x655b59c3 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(6);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//3 5

       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0x8f0ccc92 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(10);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//3 6

       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0xffeff47d );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(15);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//3 7

       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0x85845dd1 );
       Mline = _mm256_set_epi32( M[0][1], M[1][1], M[2][1], M[3][1], M[4][1], M[5][1], M[6][1], M[7][1]  );

       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  _mm256_add_epi32(Kline,Mline) );
 
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(21);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//3 8
       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0x6fa87e4f );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(6);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//3 9
       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0xfe2ce6e0 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(10);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//3 A
       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0xa3014314 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(15);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//3 B

       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0x4e0811a1 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(21);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//3 C

       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0xf7537e82 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(6);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//3 D

       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0xbd3af235 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(10);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   

//3 E
       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0x2ad7d2bb );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(15);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);

       /*********************************************************/   
//3 F

       F = _mm256_xor_si256(C, _mm256_or_si256(B, _mm256_andnot_si256(D,_mm256_set1_epi32(0xffffffff))));
 
       Kline = _mm256_set1_epi32( 0xeb86d391 );
 
       F = _mm256_add_epi32(_mm256_add_epi32(F, A),  Kline );
       A = D;
       D = C;
       C = B;

       count_left  = _mm256_set1_epi32(21);
       rotated = _mm256_or_si256(_mm256_sllv_epi32(F, count_left), _mm256_srlv_epi32(F, _mm256_sub_epi32(right_base, count_left)));

       B = _mm256_add_epi32(B, rotated);
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



