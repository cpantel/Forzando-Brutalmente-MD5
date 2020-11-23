#include <stdio.h>

int main(int argc, char* argv[]) {

  printf("module counter_pipeline (\n");
  printf("  input  CLK,\n");
  printf("  input  [31:0]counter_in,\n");
  printf("  output reg [31:0]counter19,\n");
  printf("  output reg [31:0]counter41,\n");
  printf("  output reg [31:0]counter48\n");
  printf(");\n");
  printf("\n");

 for (int i =0; i<64; ++i) {
  if (i != 19 & i != 41 & i != 48) 
    printf("reg [31:0] counter%02d;\n", i);
}

 printf("// stage 00\n");
  printf("always @(posedge CLK)\n");
  printf("begin\n");
  printf("  counter00[ 7: 0] = counter_in[31:24];\n");
  printf("  counter00[15: 8] = counter_in[23:16];\n");
  printf("  counter00[23:16] = counter_in[15: 8];\n");
  printf("  counter00[31:24] = counter_in[ 7: 0];\n");
  printf("end\n");


  for (int x=1; x<64; ++x) {


  printf("\n// stage %02d\n",x);
  printf("always @(posedge CLK)\n");
  printf("begin\n");
  printf("  counter%02d = counter%02d;\n",x,x-1);
  printf("end\n\n");
  }

     printf("\n");
  printf("\n");
  printf("\nendmodule\n");
}

