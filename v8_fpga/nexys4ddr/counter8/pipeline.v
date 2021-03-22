module pipeline (
  input  CLK,
  input  [31:0]counter_in,
  input  [127:0]target_hash,
  input  reset,
 // output reg [31:0]counter_out,
  output reg found
);
reg [127:0] hash;
reg hash_equal;

reg [31:0] counter00, A00, B00, C00, D00, F00;
reg [31:0] counter01, A01, B01, C01, D01, F01;
reg [31:0] counter02, A02, B02, C02, D02, F02;
reg [31:0] counter03, A03, B03, C03, D03, F03;
reg [31:0] counter04, A04, B04, C04, D04, F04;
reg [31:0] counter05, A05, B05, C05, D05, F05;
reg [31:0] counter06, A06, B06, C06, D06, F06;
reg [31:0] counter07, A07, B07, C07, D07, F07;
reg [31:0] counter08, A08, B08, C08, D08, F08;
reg [31:0] counter09, A09, B09, C09, D09, F09;
reg [31:0] counter10, A10, B10, C10, D10, F10;
reg [31:0] counter11, A11, B11, C11, D11, F11;
reg [31:0] counter12, A12, B12, C12, D12, F12;
reg [31:0] counter13, A13, B13, C13, D13, F13;
reg [31:0] counter14, A14, B14, C14, D14, F14;
reg [31:0] counter15, A15, B15, C15, D15, F15;
reg [31:0] counter16, A16, B16, C16, D16, F16;
reg [31:0] counter17, A17, B17, C17, D17, F17;
reg [31:0] counter18, A18, B18, C18, D18, F18;
reg [31:0] counter19, A19, B19, C19, D19, F19;
reg [31:0] counter20, A20, B20, C20, D20, F20;
reg [31:0] counter21, A21, B21, C21, D21, F21;
reg [31:0] counter22, A22, B22, C22, D22, F22;
reg [31:0] counter23, A23, B23, C23, D23, F23;
reg [31:0] counter24, A24, B24, C24, D24, F24;
reg [31:0] counter25, A25, B25, C25, D25, F25;
reg [31:0] counter26, A26, B26, C26, D26, F26;
reg [31:0] counter27, A27, B27, C27, D27, F27;
reg [31:0] counter28, A28, B28, C28, D28, F28;
reg [31:0] counter29, A29, B29, C29, D29, F29;
reg [31:0] counter30, A30, B30, C30, D30, F30;
reg [31:0] counter31, A31, B31, C31, D31, F31;
reg [31:0] counter32, A32, B32, C32, D32, F32;
reg [31:0] counter33, A33, B33, C33, D33, F33;
reg [31:0] counter34, A34, B34, C34, D34, F34;
reg [31:0] counter35, A35, B35, C35, D35, F35;
reg [31:0] counter36, A36, B36, C36, D36, F36;
reg [31:0] counter37, A37, B37, C37, D37, F37;
reg [31:0] counter38, A38, B38, C38, D38, F38;
reg [31:0] counter39, A39, B39, C39, D39, F39;
reg [31:0] counter40, A40, B40, C40, D40, F40;
reg [31:0] counter41, A41, B41, C41, D41, F41;
reg [31:0] counter42, A42, B42, C42, D42, F42;
reg [31:0] counter43, A43, B43, C43, D43, F43;
reg [31:0] counter44, A44, B44, C44, D44, F44;
reg [31:0] counter45, A45, B45, C45, D45, F45;
reg [31:0] counter46, A46, B46, C46, D46, F46;
reg [31:0] counter47, A47, B47, C47, D47, F47;
reg [31:0] counter48, A48, B48, C48, D48, F48;
reg [31:0] counter49, A49, B49, C49, D49, F49;
reg [31:0] counter50, A50, B50, C50, D50, F50;
reg [31:0] counter51, A51, B51, C51, D51, F51;
reg [31:0] counter52, A52, B52, C52, D52, F52;
reg [31:0] counter53, A53, B53, C53, D53, F53;
reg [31:0] counter54, A54, B54, C54, D54, F54;
reg [31:0] counter55, A55, B55, C55, D55, F55;
reg [31:0] counter56, A56, B56, C56, D56, F56;
reg [31:0] counter57, A57, B57, C57, D57, F57;
reg [31:0] counter58, A58, B58, C58, D58, F58;
reg [31:0] counter59, A59, B59, C59, D59, F59;
reg [31:0] counter60, A60, B60, C60, D60, F60;
reg [31:0] counter61, A61, B61, C61, D61, F61;
reg [31:0] counter62, A62, B62, C62, D62, F62;
reg [31:0] counter63, A63, B63, C63, D63, F63;

localparam AValue = 32'h67452301;
localparam BValue = 32'hefcdab89;
localparam CValue = 32'h98badcfe;
localparam DValue = 32'h10325476;

localparam Stage00Value = 32'hd76aa478;
localparam Stage01Value = 32'he8c7b7d6;
localparam Stage02Value = 32'h242070db;
localparam Stage03Value = 32'hc1bdceee;
localparam Stage04Value = 32'hf57c0faf;
localparam Stage05Value = 32'h4787c62a;
localparam Stage06Value = 32'ha8304613;
localparam Stage07Value = 32'hfd469501;
localparam Stage08Value = 32'h698098d8;
localparam Stage09Value = 32'h8b44f7af;
localparam Stage10Value = 32'hffff5bb1;
localparam Stage11Value = 32'h895cd7be;
localparam Stage12Value = 32'h6b901122;
localparam Stage13Value = 32'hfd987193;
localparam Stage14Value = 32'ha67943ae;
localparam Stage15Value = 32'h49b40821;
localparam Stage16Value = 32'hf61e25e2;
localparam Stage17Value = 32'hc040b340;
localparam Stage18Value = 32'h265e5a51;
localparam Stage19Value = 32'he9b6c7aa;
localparam Stage20Value = 32'hd62f105d;
localparam Stage21Value = 32'h2441453;
localparam Stage22Value = 32'hd8a1e681;
localparam Stage23Value = 32'he7d3fbc8;
localparam Stage24Value = 32'h21e1cde6;
localparam Stage25Value = 32'hc33707f6;
localparam Stage26Value = 32'hf4d50d87;
localparam Stage27Value = 32'h455a14ed;
localparam Stage28Value = 32'ha9e3e905;
localparam Stage29Value = 32'hfcefa3f8;
localparam Stage30Value = 32'h676f02d9;
localparam Stage31Value = 32'h8d2a4c8a;
localparam Stage32Value = 32'hfffa3942;
localparam Stage33Value = 32'h8771f681;
localparam Stage34Value = 32'h6d9d6122;
localparam Stage35Value = 32'hfde5382c;
localparam Stage36Value = 32'ha4beeac4;
localparam Stage37Value = 32'h4bdecfa9;
localparam Stage38Value = 32'hf6bb4b60;
localparam Stage39Value = 32'hbebfbc70;
localparam Stage40Value = 32'h289b7ec6;
localparam Stage41Value = 32'heaa127fa;
localparam Stage42Value = 32'hd4ef3085;
localparam Stage43Value = 32'h4881d05;
localparam Stage44Value = 32'hd9d4d039;
localparam Stage45Value = 32'he6db99e5;
localparam Stage46Value = 32'h1fa27cf8;
localparam Stage47Value = 32'hc4ac5665;
localparam Stage48Value = 32'hf4292244;
localparam Stage49Value = 32'h432aff97;
localparam Stage50Value = 32'hab9423c7;
localparam Stage51Value = 32'hfc93a039;
localparam Stage52Value = 32'h655b59c3;
localparam Stage53Value = 32'h8f0ccc92;
localparam Stage54Value = 32'hffeff47d;
localparam Stage55Value = 32'h85845e51;
localparam Stage56Value = 32'h6fa87e4f;
localparam Stage57Value = 32'hfe2ce6e0;
localparam Stage58Value = 32'ha3014314;
localparam Stage59Value = 32'h4e0811a1;
localparam Stage60Value = 32'hf7537e82;
localparam Stage61Value = 32'hbd3af235;
localparam Stage62Value = 32'h2ad7d2bb;
localparam Stage63Value = 32'heb86d391;

//**********************************************************************
//                             round 00
//**********************************************************************

//assign counter00 = {counter_in[7:0],counter_in[15:8],counter_in[23:16],counter_in[31:24]};
//assign A00 = DValue;
//assign D00 = CValue;
//assign C00 = BValue;

// stage 00
always @(posedge CLK)
begin
  counter00[ 7: 0] = counter_in[31:24];
  counter00[15: 8] = counter_in[23:16];
  counter00[23:16] = counter_in[15: 8];
  counter00[31:24] = counter_in[ 7: 0];
  F00 = ( ( BValue & CValue) | (( ~ BValue) & DValue) ) + AValue + Stage00Value + counter00;
  A00 = DValue;
  D00 = CValue;
  C00 = BValue;
  B00 = BValue + ( (F00 << 7) | (F00 >> ( 32 - 7 ) ) );
end


// stage 01
always @(posedge CLK)
begin
  counter01 = counter00;
  F01 = ( ( B00 & C00) | (( ~ B00) & D00) ) + A00 + Stage01Value;
  A01 = D00;
  D01 = C00;
  C01 = B00;
  B01 = B00 + ( (F01 << 12) | (F01 >> ( 32 - 12 ) ) );
end


// stage 02
always @(posedge CLK)
begin
  counter02 = counter01;
  F02 = ( ( B01 & C01) | (( ~ B01) & D01) ) + A01 + Stage02Value;
  A02 = D01;
  D02 = C01;
  C02 = B01;
  B02 = B01 + ( (F02 << 17) | (F02 >> ( 32 - 17 ) ) );
end


// stage 03
always @(posedge CLK)
begin
  counter03 = counter02;
  F03 = ( ( B02 & C02) | (( ~ B02) & D02) ) + A02 + Stage03Value;
  A03 = D02;
  D03 = C02;
  C03 = B02;
  B03 = B02 + ( (F03 << 22) | (F03 >> ( 32 - 22 ) ) );
end


// stage 04
always @(posedge CLK)
begin
  counter04 = counter03;
  F04 = ( ( B03 & C03) | (( ~ B03) & D03) ) + A03 + Stage04Value;
  A04 = D03;
  D04 = C03;
  C04 = B03;
  B04 = B03 + ( (F04 << 7) | (F04 >> ( 32 - 7 ) ) );
end


// stage 05
always @(posedge CLK)
begin
  counter05 = counter04;
  F05 = ( ( B04 & C04) | (( ~ B04) & D04) ) + A04 + Stage05Value;
  A05 = D04;
  D05 = C04;
  C05 = B04;
  B05 = B04 + ( (F05 << 12) | (F05 >> ( 32 - 12 ) ) );
end


// stage 06
always @(posedge CLK)
begin
  counter06 = counter05;
  F06 = ( ( B05 & C05) | (( ~ B05) & D05) ) + A05 + Stage06Value;
  A06 = D05;
  D06 = C05;
  C06 = B05;
  B06 = B05 + ( (F06 << 17) | (F06 >> ( 32 - 17 ) ) );
end


// stage 07
always @(posedge CLK)
begin
  counter07 = counter06;
  F07 = ( ( B06 & C06) | (( ~ B06) & D06) ) + A06 + Stage07Value;
  A07 = D06;
  D07 = C06;
  C07 = B06;
  B07 = B06 + ( (F07 << 22) | (F07 >> ( 32 - 22 ) ) );
end


// stage 08
always @(posedge CLK)
begin
  counter08 = counter07;
  F08 = ( ( B07 & C07) | (( ~ B07) & D07) ) + A07 + Stage08Value;
  A08 = D07;
  D08 = C07;
  C08 = B07;
  B08 = B07 + ( (F08 << 7) | (F08 >> ( 32 - 7 ) ) );
end


// stage 09
always @(posedge CLK)
begin
  counter09 = counter08;
  F09 = ( ( B08 & C08) | (( ~ B08) & D08) ) + A08 + Stage09Value;
  A09 = D08;
  D09 = C08;
  C09 = B08;
  B09 = B08 + ( (F09 << 12) | (F09 >> ( 32 - 12 ) ) );
end


// stage 10
always @(posedge CLK)
begin
  counter10 = counter09;
  F10 = ( ( B09 & C09) | (( ~ B09) & D09) ) + A09 + Stage10Value;
  A10 = D09;
  D10 = C09;
  C10 = B09;
  B10 = B09 + ( (F10 << 17) | (F10 >> ( 32 - 17 ) ) );
end


// stage 11
always @(posedge CLK)
begin
  counter11 = counter10;
  F11 = ( ( B10 & C10) | (( ~ B10) & D10) ) + A10 + Stage11Value;
  A11 = D10;
  D11 = C10;
  C11 = B10;
  B11 = B10 + ( (F11 << 22) | (F11 >> ( 32 - 22 ) ) );
end


// stage 12
always @(posedge CLK)
begin
  counter12 = counter11;
  F12 = ( ( B11 & C11) | (( ~ B11) & D11) ) + A11 + Stage12Value;
  A12 = D11;
  D12 = C11;
  C12 = B11;
  B12 = B11 + ( (F12 << 7) | (F12 >> ( 32 - 7 ) ) );
end


// stage 13
always @(posedge CLK)
begin
  counter13 = counter12;
  F13 = ( ( B12 & C12) | (( ~ B12) & D12) ) + A12 + Stage13Value;
  A13 = D12;
  D13 = C12;
  C13 = B12;
  B13 = B12 + ( (F13 << 12) | (F13 >> ( 32 - 12 ) ) );
end


// stage 14
always @(posedge CLK)
begin
  counter14 = counter13;
  F14 = ( ( B13 & C13) | (( ~ B13) & D13) ) + A13 + Stage14Value;
  A14 = D13;
  D14 = C13;
  C14 = B13;
  B14 = B13 + ( (F14 << 17) | (F14 >> ( 32 - 17 ) ) );
end


// stage 15
always @(posedge CLK)
begin
  counter15 = counter14;
  F15 = ( ( B14 & C14) | (( ~ B14) & D14) ) + A14 + Stage15Value;
  A15 = D14;
  D15 = C14;
  C15 = B14;
  B15 = B14 + ( (F15 << 22) | (F15 >> ( 32 - 22 ) ) );
end

//**********************************************************************
//                             round 01
//**********************************************************************


// stage 16
always @(posedge CLK)
begin
  counter16 = counter15;
  F16 = ( ( D15 & B15) | (( ~ D15) & C15) ) + A15 + Stage16Value;
  A16 = D15;
  D16 = C15;
  C16 = B15;
  B16 = B15 + ( (F16 << 5) | (F16 >> ( 32 - 5 ) ) );
end


// stage 17
always @(posedge CLK)
begin
  counter17 = counter16;
  F17 = ( ( D16 & B16) | (( ~ D16) & C16) ) + A16 + Stage17Value;
  A17 = D16;
  D17 = C16;
  C17 = B16;
  B17 = B16 + ( (F17 << 9) | (F17 >> ( 32 - 9 ) ) );
end


// stage 18
always @(posedge CLK)
begin
  counter18 = counter17;
  F18 = ( ( D17 & B17) | (( ~ D17) & C17) ) + A17 + Stage18Value;
  A18 = D17;
  D18 = C17;
  C18 = B17;
  B18 = B17 + ( (F18 << 14) | (F18 >> ( 32 - 14 ) ) );
end


// stage 19
always @(posedge CLK)
begin
  counter19 = counter18;
  F19 = ( ( D18 & B18) | (( ~ D18) & C18) ) + A18 + Stage19Value + counter19;
  A19 = D18;
  D19 = C18;
  C19 = B18;
  B19 = B18 + ( (F19 << 20) | (F19 >> ( 32 - 20 ) ) );
end


// stage 20
always @(posedge CLK)
begin
  counter20 = counter19;
  F20 = ( ( D19 & B19) | (( ~ D19) & C19) ) + A19 + Stage20Value;
  A20 = D19;
  D20 = C19;
  C20 = B19;
  B20 = B19 + ( (F20 << 5) | (F20 >> ( 32 - 5 ) ) );
end


// stage 21
always @(posedge CLK)
begin
  counter21 = counter20;
  F21 = ( ( D20 & B20) | (( ~ D20) & C20) ) + A20 + Stage21Value;
  A21 = D20;
  D21 = C20;
  C21 = B20;
  B21 = B20 + ( (F21 << 9) | (F21 >> ( 32 - 9 ) ) );
end


// stage 22
always @(posedge CLK)
begin
  counter22 = counter21;
  F22 = ( ( D21 & B21) | (( ~ D21) & C21) ) + A21 + Stage22Value;
  A22 = D21;
  D22 = C21;
  C22 = B21;
  B22 = B21 + ( (F22 << 14) | (F22 >> ( 32 - 14 ) ) );
end


// stage 23
always @(posedge CLK)
begin
  counter23 = counter22;
  F23 = ( ( D22 & B22) | (( ~ D22) & C22) ) + A22 + Stage23Value;
  A23 = D22;
  D23 = C22;
  C23 = B22;
  B23 = B22 + ( (F23 << 20) | (F23 >> ( 32 - 20 ) ) );
end


// stage 24
always @(posedge CLK)
begin
  counter24 = counter23;
  F24 = ( ( D23 & B23) | (( ~ D23) & C23) ) + A23 + Stage24Value;
  A24 = D23;
  D24 = C23;
  C24 = B23;
  B24 = B23 + ( (F24 << 5) | (F24 >> ( 32 - 5 ) ) );
end


// stage 25
always @(posedge CLK)
begin
  counter25 = counter24;
  F25 = ( ( D24 & B24) | (( ~ D24) & C24) ) + A24 + Stage25Value;
  A25 = D24;
  D25 = C24;
  C25 = B24;
  B25 = B24 + ( (F25 << 9) | (F25 >> ( 32 - 9 ) ) );
end


// stage 26
always @(posedge CLK)
begin
  counter26 = counter25;
  F26 = ( ( D25 & B25) | (( ~ D25) & C25) ) + A25 + Stage26Value;
  A26 = D25;
  D26 = C25;
  C26 = B25;
  B26 = B25 + ( (F26 << 14) | (F26 >> ( 32 - 14 ) ) );
end


// stage 27
always @(posedge CLK)
begin
  counter27 = counter26;
  F27 = ( ( D26 & B26) | (( ~ D26) & C26) ) + A26 + Stage27Value;
  A27 = D26;
  D27 = C26;
  C27 = B26;
  B27 = B26 + ( (F27 << 20) | (F27 >> ( 32 - 20 ) ) );
end


// stage 28
always @(posedge CLK)
begin
  counter28 = counter27;
  F28 = ( ( D27 & B27) | (( ~ D27) & C27) ) + A27 + Stage28Value;
  A28 = D27;
  D28 = C27;
  C28 = B27;
  B28 = B27 + ( (F28 << 5) | (F28 >> ( 32 - 5 ) ) );
end


// stage 29
always @(posedge CLK)
begin
  counter29 = counter28;
  F29 = ( ( D28 & B28) | (( ~ D28) & C28) ) + A28 + Stage29Value;
  A29 = D28;
  D29 = C28;
  C29 = B28;
  B29 = B28 + ( (F29 << 9) | (F29 >> ( 32 - 9 ) ) );
end


// stage 30
always @(posedge CLK)
begin
  counter30 = counter29;
  F30 = ( ( D29 & B29) | (( ~ D29) & C29) ) + A29 + Stage30Value;
  A30 = D29;
  D30 = C29;
  C30 = B29;
  B30 = B29 + ( (F30 << 14) | (F30 >> ( 32 - 14 ) ) );
end


// stage 31
always @(posedge CLK)
begin
  counter31 = counter30;
  F31 = ( ( D30 & B30) | (( ~ D30) & C30) ) + A30 + Stage31Value;
  A31 = D30;
  D31 = C30;
  C31 = B30;
  B31 = B30 + ( (F31 << 20) | (F31 >> ( 32 - 20 ) ) );
end

//**********************************************************************
//                             round 02
//**********************************************************************


// stage 32
always @(posedge CLK)
begin
  counter32 = counter31;
  F32 = ( ( B31 ^ C31) ^ D31 ) +  A31 + Stage32Value;
  A32 = D31;
  D32 = C31;
  C32 = B31;
  B32 = B31 + ( (F32 << 4) | (F32 >> ( 32 - 4 ) ) );
end


// stage 33
always @(posedge CLK)
begin
  counter33 = counter32;
  F33 = ( ( B32 ^ C32) ^ D32 ) +  A32 + Stage33Value;
  A33 = D32;
  D33 = C32;
  C33 = B32;
  B33 = B32 + ( (F33 << 11) | (F33 >> ( 32 - 11 ) ) );
end


// stage 34
always @(posedge CLK)
begin
  counter34 = counter33;
  F34 = ( ( B33 ^ C33) ^ D33 ) +  A33 + Stage34Value;
  A34 = D33;
  D34 = C33;
  C34 = B33;
  B34 = B33 + ( (F34 << 16) | (F34 >> ( 32 - 16 ) ) );
end


// stage 35
always @(posedge CLK)
begin
  counter35 = counter34;
  F35 = ( ( B34 ^ C34) ^ D34 ) +  A34 + Stage35Value;
  A35 = D34;
  D35 = C34;
  C35 = B34;
  B35 = B34 + ( (F35 << 23) | (F35 >> ( 32 - 23 ) ) );
end


// stage 36
always @(posedge CLK)
begin
  counter36 = counter35;
  F36 = ( ( B35 ^ C35) ^ D35 ) +  A35 + Stage36Value;
  A36 = D35;
  D36 = C35;
  C36 = B35;
  B36 = B35 + ( (F36 << 4) | (F36 >> ( 32 - 4 ) ) );
end


// stage 37
always @(posedge CLK)
begin
  counter37 = counter36;
  F37 = ( ( B36 ^ C36) ^ D36 ) +  A36 + Stage37Value;
  A37 = D36;
  D37 = C36;
  C37 = B36;
  B37 = B36 + ( (F37 << 11) | (F37 >> ( 32 - 11 ) ) );
end


// stage 38
always @(posedge CLK)
begin
  counter38 = counter37;
  F38 = ( ( B37 ^ C37) ^ D37 ) +  A37 + Stage38Value;
  A38 = D37;
  D38 = C37;
  C38 = B37;
  B38 = B37 + ( (F38 << 16) | (F38 >> ( 32 - 16 ) ) );
end


// stage 39
always @(posedge CLK)
begin
  counter39 = counter38;
  F39 = ( ( B38 ^ C38) ^ D38 ) +  A38 + Stage39Value;
  A39 = D38;
  D39 = C38;
  C39 = B38;
  B39 = B38 + ( (F39 << 23) | (F39 >> ( 32 - 23 ) ) );
end


// stage 40
always @(posedge CLK)
begin
  counter40 = counter39;
  F40 = ( ( B39 ^ C39) ^ D39 ) +  A39 + Stage40Value;
  A40 = D39;
  D40 = C39;
  C40 = B39;
  B40 = B39 + ( (F40 << 4) | (F40 >> ( 32 - 4 ) ) );
end


// stage 41
always @(posedge CLK)
begin
  counter41 = counter40;
  F41 = ( ( B40 ^ C40) ^ D40 ) +  A40 + Stage41Value + counter41;
  A41 = D40;
  D41 = C40;
  C41 = B40;
  B41 = B40 + ( (F41 << 11) | (F41 >> ( 32 - 11 ) ) );
end


// stage 42
always @(posedge CLK)
begin
  counter42 = counter41;
  F42 = ( ( B41 ^ C41) ^ D41 ) +  A41 + Stage42Value;
  A42 = D41;
  D42 = C41;
  C42 = B41;
  B42 = B41 + ( (F42 << 16) | (F42 >> ( 32 - 16 ) ) );
end


// stage 43
always @(posedge CLK)
begin
  counter43 = counter42;
  F43 = ( ( B42 ^ C42) ^ D42 ) +  A42 + Stage43Value;
  A43 = D42;
  D43 = C42;
  C43 = B42;
  B43 = B42 + ( (F43 << 23) | (F43 >> ( 32 - 23 ) ) );
end


// stage 44
always @(posedge CLK)
begin
  counter44 = counter43;
  F44 = ( ( B43 ^ C43) ^ D43 ) +  A43 + Stage44Value;
  A44 = D43;
  D44 = C43;
  C44 = B43;
  B44 = B43 + ( (F44 << 4) | (F44 >> ( 32 - 4 ) ) );
end


// stage 45
always @(posedge CLK)
begin
  counter45 = counter44;
  F45 = ( ( B44 ^ C44) ^ D44 ) +  A44 + Stage45Value;
  A45 = D44;
  D45 = C44;
  C45 = B44;
  B45 = B44 + ( (F45 << 11) | (F45 >> ( 32 - 11 ) ) );
end


// stage 46
always @(posedge CLK)
begin
  counter46 = counter45;
  F46 = ( ( B45 ^ C45) ^ D45 ) +  A45 + Stage46Value;
  A46 = D45;
  D46 = C45;
  C46 = B45;
  B46 = B45 + ( (F46 << 16) | (F46 >> ( 32 - 16 ) ) );
end


// stage 47
always @(posedge CLK)
begin
  counter47 = counter46;
  F47 = ( ( B46 ^ C46) ^ D46 ) +  A46 + Stage47Value;
  A47 = D46;
  D47 = C46;
  C47 = B46;
  B47 = B46 + ( (F47 << 23) | (F47 >> ( 32 - 23 ) ) );
end

//**********************************************************************
//                             round 03
//**********************************************************************


// stage 48
always @(posedge CLK)
begin
  counter48 = counter47;
  F48 = ( C47 ^ (  B47 | ~ D47 ) ) +  A47 + Stage48Value + counter48;
  A48 = D47;
  D48 = C47;
  C48 = B47;
  B48 = B47 + ( (F48 << 6) | (F48 >> ( 32 - 6 ) ) );
end


// stage 49
always @(posedge CLK)
begin
  counter49 = counter48;
  F49 = ( C48 ^ (  B48 | ~ D48 ) ) +  A48 + Stage49Value;
  A49 = D48;
  D49 = C48;
  C49 = B48;
  B49 = B48 + ( (F49 << 10) | (F49 >> ( 32 - 10 ) ) );
end


// stage 50
always @(posedge CLK)
begin
  counter50 = counter49;
  F50 = ( C49 ^ (  B49 | ~ D49 ) ) +  A49 + Stage50Value;
  A50 = D49;
  D50 = C49;
  C50 = B49;
  B50 = B49 + ( (F50 << 15) | (F50 >> ( 32 - 15 ) ) );
end


// stage 51
always @(posedge CLK)
begin
  counter51 = counter50;
  F51 = ( C50 ^ (  B50 | ~ D50 ) ) +  A50 + Stage51Value;
  A51 = D50;
  D51 = C50;
  C51 = B50;
  B51 = B50 + ( (F51 << 21) | (F51 >> ( 32 - 21 ) ) );
end


// stage 52
always @(posedge CLK)
begin
  counter52 = counter51;
  F52 = ( C51 ^ (  B51 | ~ D51 ) ) +  A51 + Stage52Value;
  A52 = D51;
  D52 = C51;
  C52 = B51;
  B52 = B51 + ( (F52 << 6) | (F52 >> ( 32 - 6 ) ) );
end


// stage 53
always @(posedge CLK)
begin
  counter53 = counter52;
  F53 = ( C52 ^ (  B52 | ~ D52 ) ) +  A52 + Stage53Value;
  A53 = D52;
  D53 = C52;
  C53 = B52;
  B53 = B52 + ( (F53 << 10) | (F53 >> ( 32 - 10 ) ) );
end


// stage 54
always @(posedge CLK)
begin
  counter54 = counter53;
  F54 = ( C53 ^ (  B53 | ~ D53 ) ) +  A53 + Stage54Value;
  A54 = D53;
  D54 = C53;
  C54 = B53;
  B54 = B53 + ( (F54 << 15) | (F54 >> ( 32 - 15 ) ) );
end


// stage 55
always @(posedge CLK)
begin
  counter55 = counter54;
  F55 = ( C54 ^ (  B54 | ~ D54 ) ) +  A54 + Stage55Value;
  A55 = D54;
  D55 = C54;
  C55 = B54;
  B55 = B54 + ( (F55 << 21) | (F55 >> ( 32 - 21 ) ) );
end


// stage 56
always @(posedge CLK)
begin
  counter56 = counter55;
  F56 = ( C55 ^ (  B55 | ~ D55 ) ) +  A55 + Stage56Value;
  A56 = D55;
  D56 = C55;
  C56 = B55;
  B56 = B55 + ( (F56 << 6) | (F56 >> ( 32 - 6 ) ) );
end


// stage 57
always @(posedge CLK)
begin
  counter57 = counter56;
  F57 = ( C56 ^ (  B56 | ~ D56 ) ) +  A56 + Stage57Value;
  A57 = D56;
  D57 = C56;
  C57 = B56;
  B57 = B56 + ( (F57 << 10) | (F57 >> ( 32 - 10 ) ) );
end


// stage 58
always @(posedge CLK)
begin
  counter58 = counter57;
  F58 = ( C57 ^ (  B57 | ~ D57 ) ) +  A57 + Stage58Value;
  A58 = D57;
  D58 = C57;
  C58 = B57;
  B58 = B57 + ( (F58 << 15) | (F58 >> ( 32 - 15 ) ) );
end


// stage 59
always @(posedge CLK)
begin
  counter59 = counter58;
  F59 = ( C58 ^ (  B58 | ~ D58 ) ) +  A58 + Stage59Value;
  A59 = D58;
  D59 = C58;
  C59 = B58;
  B59 = B58 + ( (F59 << 21) | (F59 >> ( 32 - 21 ) ) );
end


// stage 60
always @(posedge CLK)
begin
  counter60 = counter59;
  F60 = ( C59 ^ (  B59 | ~ D59 ) ) +  A59 + Stage60Value;
  A60 = D59;
  D60 = C59;
  C60 = B59;
  B60 = B59 + ( (F60 << 6) | (F60 >> ( 32 - 6 ) ) );
end


// stage 61
always @(posedge CLK)
begin
  counter61 = counter60;
  F61 = ( C60 ^ (  B60 | ~ D60 ) ) +  A60 + Stage61Value;
  A61 = D60;
  D61 = C60;
  C61 = B60;
  B61 = B60 + ( (F61 << 10) | (F61 >> ( 32 - 10 ) ) );
end


// stage 62
always @(posedge CLK)
begin
  counter62 = counter61;
  F62 = ( C61 ^ (  B61 | ~ D61 ) ) +  A61 + Stage62Value;
  A62 = D61;
  D62 = C61;
  C62 = B61;
  B62 = B61 + ( (F62 << 15) | (F62 >> ( 32 - 15 ) ) );
end

// stage 63
always @(posedge CLK)
begin
  counter63 = counter62;
  F63 = ( C62 ^ (  B62 | ~ D62 ) ) +  A62 + Stage63Value;
  A63 = D62 + AValue;
  D63 = C62 + DValue;
  C63 = B62 + CValue;
  B63 = B62 + BValue + ( (F63 << 21) | (F63 >> ( 32 - 21 ) ) );
end

// stage 64
always @(posedge CLK)
begin
  hash <= {A63[7:0],A63[15:8],A63[23:16],A63[31:24],
           B63[7:0],B63[15:8],B63[23:16],B63[31:24],
           C63[7:0],C63[15:8],C63[23:16],C63[31:24],
           D63[7:0],D63[15:8],D63[23:16],D63[31:24]
          };

//  counter_out <= {counter63[7:0],counter63[15:8],counter63[23:16],counter63[31:24]} - 32'h00000043;
end

// stage 65
always @(posedge CLK)
begin
  if (reset)
    found <= 1'h0;
  else if ( hash == target_hash)
    found <= 1'b1;
  else 
    found <= 1'b0;
end

endmodule