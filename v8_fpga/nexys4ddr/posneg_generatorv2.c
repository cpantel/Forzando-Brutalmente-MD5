#include <stdio.h>

int main(int argc, char* argv[]) {

  printf("module double_pipeline (\n");
  printf("  input              CLK,\n");
  printf("  input      [ 31:0]  counter_in ,\n");
  printf("  input      [127:0] target_hash,\n");
  printf("  input              reset\n");
  printf("  output reg [ 31:0] counter_out\n");
  printf("  output reg         found = 0\n");
  printf(");\n\n");
  printf("reg [127:0] hash;\n");
  
  printf("// someday I will learn to be more veriloger\n");

  printf("reg [31:0] counter00, A00, B00, C00, D00, F00;\n");
  for (int i =1; i<64; ++i) {
    printf("reg [31:0] counter%02d, counter%02dneg, A%02d, B%02d, C%02d, D%02d, F%02d, B%02dneg, C%02dneg, D%02dneg;\n", i,i,i,i,i,i,i,i,i,i);
  }

  printf("localparam AValue = 32'h67452301;\n");
  printf("localparam BValue = 32'hefcdab89;\n");
  printf("localparam CValue = 32'h98badcfe;\n");
  printf("localparam DValue = 32'h10325476;\n");
  printf("\n");
  printf("localparam Stage00Value = 32'hd76aa478;\n");
  printf("localparam Stage01Value = 32'he8c7b7d6;\n");
  printf("localparam Stage02Value = 32'h242070db;\n");
  printf("localparam Stage03Value = 32'hc1bdceee;\n");
  printf("localparam Stage04Value = 32'hf57c0faf;\n");
  printf("localparam Stage05Value = 32'h4787c62a;\n");
  printf("localparam Stage06Value = 32'ha8304613;\n");
  printf("localparam Stage07Value = 32'hfd469501;\n");
  printf("localparam Stage08Value = 32'h698098d8;\n");
  printf("localparam Stage09Value = 32'h8b44f7af;\n");
  printf("localparam Stage10Value = 32'hffff5bb1;\n");
  printf("localparam Stage11Value = 32'h895cd7be;\n");
  printf("localparam Stage12Value = 32'h6b901122;\n");
  printf("localparam Stage13Value = 32'hfd987193;\n");
  printf("localparam Stage14Value = 32'ha67943ae;\n");
  printf("localparam Stage15Value = 32'h49b40821;\n");
  printf("localparam Stage16Value = 32'hf61e25e2;\n");
  printf("localparam Stage17Value = 32'hc040b340;\n");
  printf("localparam Stage18Value = 32'h265e5a51;\n");
  printf("localparam Stage19Value = 32'he9b6c7aa;\n");
  printf("localparam Stage20Value = 32'hd62f105d;\n");
  printf("localparam Stage21Value = 32'h02441453;\n");
  printf("localparam Stage22Value = 32'hd8a1e681;\n");
  printf("localparam Stage23Value = 32'he7d3fbc8;\n");
  printf("localparam Stage24Value = 32'h21e1cde6;\n");
  printf("localparam Stage25Value = 32'hc33707f6;\n");
  printf("localparam Stage26Value = 32'hf4d50d87;\n");
  printf("localparam Stage27Value = 32'h455a14ed;\n");
  printf("localparam Stage28Value = 32'ha9e3e905;\n");
  printf("localparam Stage29Value = 32'hfcefa3f8;\n");
  printf("localparam Stage30Value = 32'h676f02d9;\n");
  printf("localparam Stage31Value = 32'h8d2a4c8a;\n");
  printf("localparam Stage32Value = 32'hfffa3942;\n");
  printf("localparam Stage33Value = 32'h8771f681;\n");
  printf("localparam Stage34Value = 32'h6d9d6122;\n");
  printf("localparam Stage35Value = 32'hfde5382c;\n");
  printf("localparam Stage36Value = 32'ha4beeac4;\n");
  printf("localparam Stage37Value = 32'h4bdecfa9;\n");
  printf("localparam Stage38Value = 32'hf6bb4b60;\n");
  printf("localparam Stage39Value = 32'hbebfbc70;\n");
  printf("localparam Stage40Value = 32'h289b7ec6;\n");
  printf("localparam Stage41Value = 32'heaa127fa;\n");
  printf("localparam Stage42Value = 32'hd4ef3085;\n");
  printf("localparam Stage43Value = 32'h04881d05;\n");
  printf("localparam Stage44Value = 32'hd9d4d039;\n");
  printf("localparam Stage45Value = 32'he6db99e5;\n");
  printf("localparam Stage46Value = 32'h1fa27cf8;\n");
  printf("localparam Stage47Value = 32'hc4ac5665;\n");
  printf("localparam Stage48Value = 32'hf4292244;\n");
  printf("localparam Stage49Value = 32'h432aff97;\n");
  printf("localparam Stage50Value = 32'hab9423c7;\n");
  printf("localparam Stage51Value = 32'hfc93a039;\n");
  printf("localparam Stage52Value = 32'h655b59c3;\n");
  printf("localparam Stage53Value = 32'h8f0ccc92;\n");
  printf("localparam Stage54Value = 32'hffeff47d;\n");
  printf("localparam Stage55Value = 32'h85845e51;\n");
  printf("localparam Stage56Value = 32'h6fa87e4f;\n");
  printf("localparam Stage57Value = 32'hfe2ce6e0;\n");
  printf("localparam Stage58Value = 32'ha3014314;\n");
  printf("localparam Stage59Value = 32'h4e0811a1;\n");
  printf("localparam Stage60Value = 32'hf7537e82;\n");
  printf("localparam Stage61Value = 32'hbd3af235;\n");
  printf("localparam Stage62Value = 32'h2ad7d2bb;\n");
  printf("localparam Stage63Value = 32'heb86d391;\n");


  int shifts00[] = {7,12,17,22};

  printf("//**********************************************************************\n");
  printf("//                             round 00\n");
  printf("//**********************************************************************\n\n");


  printf("// stage 00\n");
  printf("always @(posedge CLK)\n");
  printf("begin\n");
//  printf("  counter00 = counter_in;\n");

   printf("  counter00[ 7: 0] = counter_in[31:24];\n");
   printf("  counter00[15: 8] = counter_in[23:16];\n");
   printf("  counter00[23:16] = counter_in[15: 8];\n");
   printf("  counter00[31:24] = counter_in[ 7: 0];\n");


  printf("  F00 = ( ( BValue & CValue) | (( ~ BValue) & DValue) ) + AValue + Stage00Value + counter00;\n");
  printf("  A00 = DValue;\n");
  printf("  D00 = CValue;\n");
  printf("  C00 = BValue;\n");
  printf("end\n\n");

  printf("// stage 00neg\n");
  printf("always @(negedge CLK)\n");
  printf("begin\n");
  printf("  B00 = BValue + ( (F00 << 7) | (F00 >> ( 32 - 7 ) ) );\n");
  printf("end\n\n");


  for (int x=0; x< 15; ++x) {
    int y=x+1;
    int z=shifts00[(x+1)%4];

    printf("\n// stage %02dpos\n",y);
    printf("always @(posedge CLK)\n");
    printf("begin\n");
    printf("  counter%02dneg = counter%02d;\n", y,x);
    printf("  F%02d = ( ( B%02d & C%02d) | (( ~ B%02d) & D%02d) ) + A%02d + Stage%02dValue;\n", y,x,x,x,x,x,y);
    printf("  D%02dneg = D%02d;\n", y,x);
    printf("  C%02dneg = C%02d;\n", y,x);
    printf("  B%02dneg = B%02d;\n", y,x);
    printf("end\n\n");


    printf("\n// stage %02dneg\n",y);
    printf("always @(negedge CLK)\n");
    printf("begin\n");
    printf("  counter%02d = counter%02dneg;\n", y,y);
    printf("  A%02d = D%02dneg;\n", y,y);
    printf("  D%02d = C%02dneg;\n", y,y);
    printf("  C%02d = B%02dneg;\n", y,y);
    printf("  B%02d = B%02dneg + ( (F%02d << %d) | (F%02d >> ( 32 - %d ) ) );\n", y,y,y,z,y,z);
    printf("end\n\n");
  }

  int shifts01[] = {5,9,14,20};

  printf("//**********************************************************************\n");
  printf("//                             round 01\n");
  printf("//**********************************************************************\n\n");



  for (int x=15; x< 31; ++x) {
    int y=x+1;
    int z=shifts01[(x+1)%4];
    char* with_counter = " + counter19";
    char* with_out_counter = "";
    char* counter;

    if ( y == 19) {
       counter = with_counter;
    } else {
       counter = with_out_counter;
    }

    printf("\n// stage %02dpos\n", y);
    printf("always @(posedge CLK)\n");
    printf("begin\n");
    printf("  counter%02dneg = counter%02d;\n", y,x);
    printf("  F%02d = ( ( D%02d & B%02d) | (( ~ D%02d) & C%02d) ) + A%02d + Stage%02dValue%s;\n", y,x,x,x,x,x,y,counter);
    printf("  D%02dneg = D%02d;\n",y,x);
    printf("  C%02dneg = C%02d;\n",y,x);
    printf("  B%02dneg = B%02d;\n",y,x);
    printf("end\n\n");

    printf("\n// stage %02dneg\n", y);
    printf("always @(negedge CLK)\n");
    printf("begin\n");
    printf("  counter%02d = counter%02dneg;\n", y,y);
    printf("  A%02d = D%02dneg;\n",y,y);
    printf("  D%02d = C%02dneg;\n",y,y);
    printf("  C%02d = B%02dneg;\n",y,y);
    printf("  B%02d = B%02dneg + ( (F%02d << %d) | (F%02d >> ( 32 - %d ) ) );\n",y,y,y,z,y,z);
    printf("end\n\n");
  }

  int shifts02[] = {4,11, 16,23};

  printf("//**********************************************************************\n");
  printf("//                             round 02\n");
  printf("//**********************************************************************\n\n");



  for (int x=31; x< 47; ++x) {
    int y=x+1;
    int z=shifts02[(x+1)%4];
    char* with_counter = " + counter41";
    char* with_out_counter = "";
    char* counter;

    if ( y == 41) {
       counter = with_counter;
    } else {
       counter = with_out_counter;
    }
    printf("\n// stage %02dpos\n",y);
    printf("always @(posedge CLK)\n");
    printf("begin\n");
    printf("  counter%02dneg = counter%02d;\n", y,x);
    printf("  F%02d = ( ( B%02d ^ C%02d) ^ D%02d ) +  A%02d + Stage%02dValue%s;\n",y,x,x,x,x,y,counter);
    printf("  D%02dneg = D%02d;\n",y,x);
    printf("  C%02dneg = C%02d;\n",y,x);
    printf("  B%02dneg = B%02d;\n",y,x);
    printf("end\n\n");

    printf("\n// stage %02dneg\n",y);
    printf("always @(negedge CLK)\n");
    printf("begin\n");
    printf("  counter%02d = counter%02dneg;\n", y,y);
    printf("  A%02d = D%02dneg;\n",y,y);
    printf("  D%02d = C%02dneg;\n",y,y);
    printf("  C%02d = B%02dneg;\n",y,y);
    printf("  B%02d = B%02dneg + ( (F%02d << %d) | (F%02d >> ( 32 - %d ) ) );\n",y,y,y,z,y,z);
    printf("end\n\n");


  }
  printf("//**********************************************************************\n");
  printf("//                             round 03\n");
  printf("//**********************************************************************\n\n");


  int shifts03[] = {6,10, 15,21};
  for (int x=47; x< 62; ++x) {
    int y=x+1;
    int z=shifts03[(x+1)%4];
    char* with_counter = " + counter48";
    char* with_out_counter = "";
    char* counter;

    if ( y == 48) {
       counter = with_counter;
    } else {
       counter = with_out_counter;
    }
    printf("\n// stage %02dpos\n",y);
    printf("always @(posedge CLK)\n");
    printf("begin\n");
    printf("  counter%02dneg = counter%02d;\n", y,x);
    printf("  F%02d = ( C%02d ^ (  B%02d | ~ D%02d ) ) +  A%02d + Stage%02dValue%s;\n",y,x,x,x,x,y,counter);
    printf("  D%02dneg = D%02d;\n",y,x);
    printf("  C%02dneg = C%02d;\n",y,x);
    printf("  B%02dneg = B%02d;\n",y,x);
    printf("end\n\n");

    printf("\n// stage %02dneg\n",y);
    printf("always @(negedge CLK)\n");
    printf("begin\n");
    printf("  counter%02d = counter%02dneg;\n", y,y);
    printf("  A%02d = D%02dneg;\n",y,y);
    printf("  D%02d = C%02dneg;\n",y,y);
    printf("  C%02d = B%02dneg;\n",y,y);
    printf("  B%02d = B%02dneg + ( (F%02d << %d) | (F%02d >> ( 32 - %d ) ) );\n",y,y,y,z,y,z);
    printf("end\n\n");
  }

  printf("// stage 63pos\n");
  printf("always @(posedge CLK)\n");
  printf("begin\n");
  printf("  counter63 = counter62;\n");
  printf("  F63 = ( C62 ^ (  B62 | ~ D62 ) ) +  A62 + Stage63Value;\n");
  printf("  D63neg = D62;\n");
  printf("  C63neg = C62;\n");
  printf("  B63neg = B62;\n");
  printf("end\n");

  printf("// stage 63neg\n");
  printf("always @(negedge CLK)\n");
  printf("begin\n");
  printf("  A63 = D63neg + AValue;\n");
  printf("  D63 = C63neg + DValue;\n");
  printf("  C63 = B63neg + CValue;\n");
  printf("  B63 = B63neg + BValue + ( (F63 << 21) | (F63 >> ( 32 - 21 ) ) );\n");
  printf("end\n");




  printf("\n");
  printf("//assign counter_out = F00;\n");
  printf("//assign hash = {A00,B00,C00,D00};\n");
  printf("\n");
  printf("//assign counter_out = F15;\n");
  printf("//assign hash = {A15,B15,C15,D15};\n");
  printf("\n");
  printf("//assign counter_out = F16;\n");
  printf("//assign hash = {A16,B16,C16,D16};\n");
  printf("\n");
  printf("//assign counter_out = F31;\n");
  printf("//assign hash = {A31,B31,C31,D31};\n");
  printf("\n");
  printf("//assign counter_out = F32;\n");
  printf("//assign hash = {A32,B32,C32,D32};\n");
  printf("\n");
  printf("//assign counter_out = F47;\n");
  printf("//assign hash = {A47,B47,C47,D47};\n");
  printf("\n");
  printf("//assign counter_out = F48;\n");
  printf("//assign hash = {A48,B48,C48,D48};\n");
  printf("\n");
  printf("//assign counter_out = F63;\n");
  printf("//assign hash = {A63,B63,C63,D63};\n");
  printf("\n");
  printf("//assign counter_out = counter63;\n");
  printf("//assign hash = {\n");
  printf("// D63[7:0],D63[15:8],D63[23:16],D63[31:24],\n");
  printf("// B63[7:0],B63[15:8],B63[23:16],B63[31:24],\n");
  printf("// C63[7:0],C63[15:8],C63[23:16],C63[31:24],\n");
  printf("// A63[7:0],A63[15:8],A63[23:16],A63[31:24]\n");
  printf("//};\n");
  printf("\n");
  printf("assign counter_out = counter63;\n");
  printf("\n");
  printf("assign hash[127:120] = A63[ 7: 0];\n");
  printf("assign hash[119:112] = A63[15: 8];\n");
  printf("assign hash[111:104] = A63[23:16];\n");
  printf("assign hash[103: 96] = A63[31:24];\n");
  printf("\n");
  printf("assign hash[ 95: 88] = B63[ 7: 0];\n");
  printf("assign hash[ 87: 80] = B63[15: 8];\n");
  printf("assign hash[ 79: 72] = B63[23:16];\n");
  printf("assign hash[ 71: 64] = B63[31:24];\n");
  printf("\n");
  printf("assign hash[ 63: 56] = C63[ 7: 0];\n");
  printf("assign hash[ 55: 48] = C63[15: 8];\n");
  printf("assign hash[ 47: 40] = C63[23:16];\n");
  printf("assign hash[ 39: 32] = C63[31:24];\n");
  printf("\n");
  printf("assign hash[ 31: 24] = D63[ 7: 0];\n");
  printf("assign hash[ 23: 16] = D63[15: 8];\n");
  printf("assign hash[ 15: 8] = D63[23:16];\n");
  printf("assign hash[ 7: 0] = D63[31:24];\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("endmodule\n");




}

