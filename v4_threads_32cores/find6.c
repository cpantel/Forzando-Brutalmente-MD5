#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

#include <pthread.h>

#define BUFFER_LEN 64 
#define BUFFER_SIZE_OFFSET 56

#define LEFTROTATE(x, c)  (((x) << (c)) | ((x) >> (32 - (c))))

void loadHash(char* argv, uint32_t* a, uint32_t* b, uint32_t* c, uint32_t* d) {
   char tmp[8];

   strncpy(tmp,&argv[0],8);
   *a = htonl(strtoul(tmp,0,16));

   strncpy(tmp,&argv[8],8);
   *b = htonl(strtoul(tmp,0,16));

   strncpy(tmp,&argv[16],8);
   *c = htonl(strtoul(tmp,0,16));

   strncpy(tmp,&argv[24],8);
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

typedef struct {
     uint64_t hashcount;
     char init;
     char stop;
     char * hash;
} Data;


void * doIt(void * data);

int main(int argc, char * argv[]) {   

   pthread_t tid[32];


   Data data[] = { {0,';','<',argv[1]},
            {1,'=','>',argv[1]},
            {2,'?','@',argv[1]},
            {3,'A','B',argv[1]},
            {4,'C','D',argv[1]},
            {5,'E','F',argv[1]},
            {6,'G','H',argv[1]},
            {7,'I','J',argv[1]},
            {8,'K','L',argv[1]},
            {9,'M','N',argv[1]},
            {10,'O','P',argv[1]},
            {11,'Q','R',argv[1]},
            {12,'S','T',argv[1]},
            {13,'U','V',argv[1]},
            {14,'W','X',argv[1]},
            {15,'Y','Z',argv[1]},
            {16,'[','\\',argv[1]},
            {17,']','^',argv[1]},
            {18,'_','`',argv[1]},
            {19,'a','b',argv[1]},
            {20,'c','d',argv[1]},
            {21,'e','f',argv[1]},
            {22,'g','h',argv[1]},
            {23,'i','j',argv[1]},
            {24,'k','l',argv[1]},
            {25,'m','n',argv[1]},
            {26,'o','p',argv[1]},
            {27,'q','r',argv[1]},
            {28,'s','t',argv[1]},
            {29,'u','v',argv[1]},
            {30,'w','x',argv[1]},
            {31,'y','z',argv[1]}
                 };
   int error;

   for (int i = 0 ; i < 32 ; ++i) { 
        error = pthread_create(&(tid[i]), NULL, &doIt, (void *) &data[i]);
        if (error != 0)
            printf("\ncan't create thread :[%s]", strerror(error));
   }

   for (int i = 0 ; i < 32 ; ++i) {
      pthread_join(tid[i], NULL);
   }
   return 0;
}



void * doIt(void * args) {
   uint64_t hashcount = ((Data *) args)->hashcount;
   char init          = ((Data *) args)->init;
   char stop          = ((Data *) args)->stop;
   char * hash          = ((Data *) args)->hash;

   printf("I am a thread and I will explore from %c;;;; to %czzzz the hash %s \n", init, stop, hash);
   
   uint32_t M[BUFFER_LEN];
   pad("01234", M);

   uint32_t targetA;
   uint32_t targetB;
   uint32_t targetC;
   uint32_t targetD;

   loadHash(hash, &targetA, &targetB, &targetC, &targetD);

   char char0,char1,char2,char3,char4; 

   for (char0 = init; char0 <= stop ; ++char0) {
   for (char1 = ';'; char1 <= 'z' ; ++char1) {
   for (char2 = ';'; char2 <= 'z' ; ++char2) {
   for (char3 = ';'; char3 <= 'z' ; ++char3) {
   for (char4 = ';'; char4 <= 'z' ; ++char4) {

      ((char *)M)[0] = char0;
      ((char *)M)[1] = char1;
      ((char *)M)[2] = char2;
      ((char *)M)[3] = char3;
      ((char *)M)[4] = char4;
      ++hashcount;

      //Initialize variables:
      uint32_t a0 = 0x67452301; 
      uint32_t b0 = 0xefcdab89;
      uint32_t c0 = 0x98badcfe;
      uint32_t d0 = 0x10325476;


       //Initialize hash value for this chunk:
       uint32_t A = a0;
       uint32_t B = b0;
       uint32_t C = c0;
       uint32_t D = d0;

       //Main loop:                                                 
       uint32_t F; 

       F = (B & C) | (( ~ B) & D);
       F = F + A + 0xd76aa478 + M[0];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 7);

       F = (B & C) | (( ~ B) & D);
       F = F + A + 0xe8c7b756 + M[1];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 12);

       F = (B & C) | (( ~ B) & D);
       F = F + A + 0x242070db + M[2];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 17);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0xc1bdceee + M[3];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 22);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0xf57c0faf + M[4];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 7);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0x4787c62a + M[6];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 12);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0xa8304613 + M[6];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 17);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0xfd469501 + M[7];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 22);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0x698098d8 + M[8];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 7);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0x8b44f7af + M[9];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 12);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0xffff5bb1  + M[10];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 17);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0x895cd7be + M[11];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 22);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0x6b901122 + M[12];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 7);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0xfd987193 + M[13];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 12);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0xa679438e + M[14];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 17);
 
       F = (B & C) | (( ~ B) & D);
       F = F + A + 0x49b40821 + M[15];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 22);
 
// ********************************************************************************************

       F = (D & B) | (( ~ D) & C);
       F = F + A + 0xf61e2562 + M[1];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 5);

       F = (D & B) | (( ~ D) & C);
       F = F + A + 0xc040b340+ M[6];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 9);

       F = (D & B) | (( ~ D) & C);
       F = F + A + 0x265e5a51 + M[11];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 14);

       F = (D & B) | (( ~ D) & C);
       F = F + A +0xe9b6c7aa  + M[0];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 20);
 
       F = (D & B) | (( ~ D) & C);
       F = F + A + 0xd62f105d + M[5];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 5);
 
       F = (D & B) | (( ~ D) & C);
       F = F + A + 0x2441453 + M[10];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 9);

       F = (D & B) | (( ~ D) & C);
       F = F + A + 0xd8a1e681 + M[15];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 14);

       F = (D & B) | (( ~ D) & C);
       F = F + A + 0xe7d3fbc8 + M[4];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 20);
 
       F = (D & B) | (( ~ D) & C);
       F = F + A + 0x21e1cde6 + M[9];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 5);
 
       F = (D & B) | (( ~ D) & C);
       F = F + A + 0xc33707d6 + M[14];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 9);

       F = (D & B) | (( ~ D) & C);
       F = F + A + 0xf4d50d87 + M[3];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 14);

       F = (D & B) | (( ~ D) & C);
       F = F + A + 0x455a14ed + M[8];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 20);
 
       F = (D & B) | (( ~ D) & C);
       F = F + A + 0xa9e3e905 + M[13];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 5);
 
       F = (D & B) | (( ~ D) & C);
       F = F + A + 0xfcefa3f8 + M[2];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 9);

       F = (D & B) | (( ~ D) & C);
       F = F + A + 0x676f02d9 + M[7];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 14);

       F = (D & B) | (( ~ D) & C);
       F = F + A + 0x8d2a4c8a + M[12];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 20);
 
// ***************************************************************************************************

       F = B ^ C ^ D;
       F = F + A + 0xfffa3942 + M[5];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 4);
 
       F = B ^ C ^ D;
       F = F + A + 0x8771f681+ M[8];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 11);
 
       F = B ^ C ^ D;
       F = F + A +  0x6d9d6122+ M[11];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 16);
 
       F = B ^ C ^ D;
       F = F + A + 0xfde5380c + M[14];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 23);
 
       F = B ^ C ^ D;
       F = F + A + 0xa4beea44 + M[1];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 4);
 
       F = B ^ C ^ D;
       F = F + A + 0x4bdecfa9 + M[4];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 11);
 
       F = B ^ C ^ D;
       F = F + A +0xf6bb4b60  + M[7];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 16);
 
       F = B ^ C ^ D;
       F = F + A + 0xbebfbc70 + M[10];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 23);
 
       F = B ^ C ^ D;
       F = F + A + 0x289b7ec6 + M[13];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 4);
 
       F = B ^ C ^ D;
       F = F + A + 0xeaa127fa + M[0];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 11);
 
       F = B ^ C ^ D;
       F = F + A +  0xd4ef3085+ M[3];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 16);
 
       F = B ^ C ^ D;
       F = F + A + 0x4881d05 + M[6];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 23);
 
       F = B ^ C ^ D;
       F = F + A + 0xd9d4d039 + M[9];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 4);
 
       F = B ^ C ^ D;
       F = F + A + 0xe6db99e5 + M[12];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 11);
 
       F = B ^ C ^ D;
       F = F + A + 0x1fa27cf8 + M[15];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 16);
 
       F = B ^ C ^ D;
       F = F + A + 0xc4ac5665 + M[2];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 23);

// **********************************************************************************************

       F = C ^ (B | (~  D));
       F = F + A + 0xf4292244 + M[0];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 6);
    
       F = C ^ (B | (~  D));
       F = F + A + 0x432aff97 + M[7];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 10);
    
       F = C ^ (B | (~  D));
       F = F + A + 0xab9423a7 + M[14];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 15);
    
       F = C ^ (B | (~  D));
       F = F + A + 0xfc93a039 + M[5];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 21);
 
       F = C ^ (B | (~  D));
       F = F + A + 0x655b59c3 + M[12];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 6);
    
       F = C ^ (B | (~  D));
       F = F + A + 0x8f0ccc92 + M[3];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 10);
    
       F = C ^ (B | (~  D));
       F = F + A + 0xffeff47d + M[10];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 15);
    
       F = C ^ (B | (~  D));
       F = F + A + 0x85845dd1 + M[1];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 21);
 

       F = C ^ (B | (~  D));
       F = F + A + 0x6fa87e4f + M[8];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 6);
    
       F = C ^ (B | (~  D));
       F = F + A + 0xfe2ce6e0 + M[15];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 10);
    
       F = C ^ (B | (~  D));
       F = F + A + 0xa3014314 + M[6];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 15);
    
       F = C ^ (B | (~  D));
       F = F + A + 0x4e0811a1 + M[13];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 21);
 

       F = C ^ (B | (~  D));
       F = F + A + 0xf7537e82 + M[4];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 6);
    
       F = C ^ (B | (~  D));
       F = F + A + 0xbd3af235 + M[11];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 10);
    
       F = C ^ (B | (~  D));
       F = F + A + 0x2ad7d2bb + M[2];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 15);
    
       F = C ^ (B | (~  D));
       F = F + A + 0xeb86d391 + M[9];  
       A = D;
       D = C;
       C = B;
       B = B + LEFTROTATE(F, 21);

       //Add this chunk's hash to result so far:
       a0 = a0 + A;
       b0 = b0 + B;
       c0 = c0 + C;
       d0 = d0 + D;
  
       if ( targetA == a0
         && targetB == b0
         && targetC == c0
         && targetD == d0) {
            printf("<<< FOUND KEY : %c%c%c%c%c >>>\n", char0,char1,char2,char3,char4);

            pthread_exit(NULL);

         }
   } 
   }
   }
   }
   }
   printf("hashcount : %lu\n", hashcount);


   pthread_exit(NULL);
}



