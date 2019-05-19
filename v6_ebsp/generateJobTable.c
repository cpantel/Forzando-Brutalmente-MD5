#include <stdio.h>

int main(int argc, char * argv[]) {
   int step = 0;
   int steps = 16;
   int delta = 64 / steps;
   printf("    Data data[] = {\n");
   for( step = 0; step < steps; ++step) {
     char comma = ',';
     if ( step == steps -1) comma = ' ';
     printf("      {%d,'%c','%c'}%c\n", step, ';'+ (delta * step), ';' + delta * (step + 1) -1, comma );
     //printf("      {%d,'%c','%c',hash}%c\n", step, ';'+ (delta * step), ';' + delta * (step + 1) -1, comma );
   }
   printf("    };\n");
   return 0;
}
