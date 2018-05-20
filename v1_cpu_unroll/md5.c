#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//#define INT_BITS 32

#define BUFFER_LEN 64 
#define BUFFER_SIZE_OFFSET 56

//#define LEFTROTATE(V, B)  ( (V << B) | (V >> (32-B) ) );
#define LEFTROTATE(x, c)  (((x) << (c)) | ((x) >> (32 - (c))))

// thanks to https://cse.unl.edu/~ssamal/crypto/genhash.php

/*
   //Pre-processing: adding a single 1 bit
   append "1" bit to message    
   // Notice: the input bytes are considered as bits strings,
   //  where the first bit is the most significant bit of the byte.[48]
   
   //Pre-processing: padding with zeros
   append "0" bit until message length in bits ≡ 448 (mod 512)
   append original length in bits mod 264 to message

*/
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

void hexdump(const char * label, const uint32_t * buffer, size_t len) {
   int i;
   printf("%s: ", label);
   for (i=0; i<len; ++i) {
      printf("%02x", 0xFF & ((char*)buffer)[i]);
   }
   printf("\n");
}

int main(int argc, char * argv[]) {   

   
   uint32_t M[BUFFER_LEN];
   size_t buffer_size = pad(argv[1], M);

   printf( "buffer size: %lu\n", buffer_size);
//   hexdump("argv1      ", argv[1], strnlen(argv[1],BUFFER_LEN));
//   hexdump("buffer     ", argv[1], buffer_size);
   hexdump("full buffer", M, BUFFER_LEN);

 
   //Process the message in successive 512-bit chunks:
   //  for each 512-bit chunk of padded message
   //       break chunk into sixteen 32-bit words M[j], 0 ≤ j ≤ 15


   //Initialize hash value for this chunk:
       uint32_t A = 0x67452301;
       uint32_t B = 0xefcdab89;
       uint32_t C = 0x98badcfe;
       uint32_t D = 0x10325476;
   //Main loop:                                                 
       uint32_t F;                          //   var int F, g

       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0xd76aa478 + M[0];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 7);            //    B := B + leftrotate(F, s[i])


       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0xe8c7b7d6 ;// 0xe8c7b756 + 0x00000080;// M[1];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 12);            //    B := B + leftrotate(F, s[i])


       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0x242070db ;//+ M[2];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 17);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0xc1bdceee ;//+ M[3];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 22);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0xf57c0faf ;//+ M[4];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 7);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0x4787c62a ;//+ M[5];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 12);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0xa8304613 ;//+ M[6];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 17);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0xfd469501 ;//+ M[7];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 22);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0x698098d8 ;//+ M[8];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 7);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0x8b44f7af ;//+ M[9];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 12);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0xffff5bb1  ;//+ M[10];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 17);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0x895cd7be ;//+ M[11];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 22);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0x6b901122 ;//+ M[12];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 7);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0xfd987193 ;//+ M[13];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 12);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0xa67943ae ; //0xa679438e + 0x00000020;// M[14];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 17);            //    B := B + leftrotate(F, s[i])

 
       F = (B & C) | (( ~ B) & D);         //       F := (B and C) or ((not B) and D)
       F = F + A + 0x49b40821 ;//+ M[15];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 22);            //    B := B + leftrotate(F, s[i])

 
/********************************************************************************************/

       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0xf61e25e2; // 0xf61e2562 + 0x00000080;// M[1];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 5);            //    B := B + leftrotate(F, s[i])
 

       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0xc040b340 ;//+ M[6];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 9);            //    B := B + leftrotate(F, s[i])

       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0x265e5a51 ;//+ M[11];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 14);            //    B := B + leftrotate(F, s[i])

       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A +0xe9b6c7aa  + M[0];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 20);            //    B := B + leftrotate(F, s[i])
 
       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0xd62f105d ;//+ M[5];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 5);            //    B := B + leftrotate(F, s[i])
 
       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0x2441453 ;//+ M[10];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 9);            //    B := B + leftrotate(F, s[i])

       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0xd8a1e681 ;//+ M[15];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 14);            //    B := B + leftrotate(F, s[i])

       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0xe7d3fbc8 ;//+ M[4];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 20);            //    B := B + leftrotate(F, s[i])
 
       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0x21e1cde6 ;//+ M[9];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 5);            //    B := B + leftrotate(F, s[i])
 
       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0xc33707f6 ;//0xc33707d6 + 0x00000020;//+ M[14];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 9);            //    B := B + leftrotate(F, s[i])

       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0xf4d50d87 ;//+ M[3];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 14);            //    B := B + leftrotate(F, s[i])

       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0x455a14ed ;//+ M[8];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 20);            //    B := B + leftrotate(F, s[i])
 
       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0xa9e3e905 ;//+ M[13];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 5);            //    B := B + leftrotate(F, s[i])
 
       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0xfcefa3f8 ;//+ M[2];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 9);            //    B := B + leftrotate(F, s[i])

       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0x676f02d9 ;//+ M[7];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 14);            //    B := B + leftrotate(F, s[i])

       F = (D & B) | (( ~ D) & C);         //       F := (D and B) or ((not D) and C)
       F = F + A + 0x8d2a4c8a ;//+ M[12];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = C + LEFTROTATE(F, 20);            //    B := B + leftrotate(F, s[i])
 
/***************************************************************************************************/

       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0xfffa3942 ;//+ M[5];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 4);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0x8771f681 ;//+ M[8];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 11);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A +  0x6d9d6122 ;//+ M[11];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 16);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0xfde5382c ;//0xfde5380c + 0x00000020;//M[14];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 23);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0xa4beeac4 ;// 0xa4beea44 + 0x00000080;//M[1];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 4);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0x4bdecfa9 ;//+ M[4];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 11);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A +0xf6bb4b60 ;// + M[7];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 16);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0xbebfbc70 ;//+ M[10];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 23);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0x289b7ec6 ;//+ M[13];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 4);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0xeaa127fa + M[0];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 11);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A +  0xd4ef3085;//+ M[3];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 16);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0x4881d05 ;//+ M[6];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 23);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0xd9d4d039 ;//+ M[9];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 4);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0xe6db99e5 ;//+ M[12];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 11);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0x1fa27cf8 ;//+ M[15];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 16);            //    B := B + leftrotate(F, s[i])
 
       F = B ^ C ^ D;                      //       F := B xor C xor D
       F = F + A + 0xc4ac5665 ;//+ M[2];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 23);            //    B := B + leftrotate(F, s[i])

/**********************************************************************************************/

       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0xf4292244 + M[0];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 6);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0x432aff97 ;//+ M[7];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 10);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0xab9423c7 ;//0xab9423a7 + 0x00000020;//M[14];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 15);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0xfc93a039 ;//+ M[5];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 21);            //    B := B + leftrotate(F, s[i])
 
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0x655b59c3 ;//+ M[12];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 6);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0x8f0ccc92 ;//+ M[3];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 10);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0xffeff47d ;//+ M[10];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 15);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0x85845e51; // 0x85845dd1 + 0x00000080; //M[1];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 21);            //    B := B + leftrotate(F, s[i])
 

       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0x6fa87e4f ;//+ M[8];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 6);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0xfe2ce6e0 ;//+ M[15];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 10);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0xa3014314 ;//+ M[6];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 15);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0x4e0811a1 ;//+ M[13];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 21);            //    B := B + leftrotate(F, s[i])
 

       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0xf7537e82 ;//+ M[4];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 6);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0xbd3af235 ;//+ M[11];  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 10);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0x2ad7d2bb ;//+ M[2];
  
       A = D;                                  //    A := D
       D = C;                                  //    D := C
       C = B;                                  //    C := B
       B = B + LEFTROTATE(F, 15);            //    B := B + leftrotate(F, s[i])
    
       F = C ^ (B | (~  D));               //       F := C xor (B or (not D))
       F = F + A + 0xeb86d391 ;//+ M[9];  

       D = 0x67452301 + D;                                  //    A := D
       A = 0x10325476 + C;                                  //    D := C
       C = 0x98badcfe + B;                                  //    C := B
       B = 0xefcdab89 + B + LEFTROTATE(F, 21);            //    B := B + leftrotate(F, s[i])

           
  
   //(Output is in little-endian)
   printf("%X %X %X %X\n", D, B, C, A);
   uint32_t digest[4];
   digest[0] = D;
   digest[1] = B;
   digest[2] = C;
   digest[3] = A;

   printf("input %s\n", argv[1]);
   hexdump("digest     ", digest, 16);

   printf("expected   : 74b87337454200d4d33f80c4663dc5e5\n");

}



