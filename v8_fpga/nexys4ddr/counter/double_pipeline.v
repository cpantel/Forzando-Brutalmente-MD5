module double_pipeline (
  input  CLK,
  input  [31:0]counter_in,
  input  [127:0]target_hash,
  input  reset,
  //output [127:0]hash,
  output reg [31:0]counter_out,
  output found
);
reg [127:0] hash;
wire hash_equal;
reg hash_equal_pos = 0;
reg hash_equal_neg = 0;

// someday I will learn to be more veriloger
reg [31:0] counter00, A00, B00, C00, D00, F00;
reg [31:0] counter01, counter01neg, A01, B01, C01, D01, F01, B01neg, C01neg, D01neg;
reg [31:0] counter02, counter02neg, A02, B02, C02, D02, F02, B02neg, C02neg, D02neg;
reg [31:0] counter03, counter03neg, A03, B03, C03, D03, F03, B03neg, C03neg, D03neg;
reg [31:0] counter04, counter04neg, A04, B04, C04, D04, F04, B04neg, C04neg, D04neg;
reg [31:0] counter05, counter05neg, A05, B05, C05, D05, F05, B05neg, C05neg, D05neg;
reg [31:0] counter06, counter06neg, A06, B06, C06, D06, F06, B06neg, C06neg, D06neg;
reg [31:0] counter07, counter07neg, A07, B07, C07, D07, F07, B07neg, C07neg, D07neg;
reg [31:0] counter08, counter08neg, A08, B08, C08, D08, F08, B08neg, C08neg, D08neg;
reg [31:0] counter09, counter09neg, A09, B09, C09, D09, F09, B09neg, C09neg, D09neg;
reg [31:0] counter10, counter10neg, A10, B10, C10, D10, F10, B10neg, C10neg, D10neg;
reg [31:0] counter11, counter11neg, A11, B11, C11, D11, F11, B11neg, C11neg, D11neg;
reg [31:0] counter12, counter12neg, A12, B12, C12, D12, F12, B12neg, C12neg, D12neg;
reg [31:0] counter13, counter13neg, A13, B13, C13, D13, F13, B13neg, C13neg, D13neg;
reg [31:0] counter14, counter14neg, A14, B14, C14, D14, F14, B14neg, C14neg, D14neg;
reg [31:0] counter15, counter15neg, A15, B15, C15, D15, F15, B15neg, C15neg, D15neg;
reg [31:0] counter16, counter16neg, A16, B16, C16, D16, F16, B16neg, C16neg, D16neg;
reg [31:0] counter17, counter17neg, A17, B17, C17, D17, F17, B17neg, C17neg, D17neg;
reg [31:0] counter18, counter18neg, A18, B18, C18, D18, F18, B18neg, C18neg, D18neg;
reg [31:0] counter19, counter19neg, A19, B19, C19, D19, F19, B19neg, C19neg, D19neg;
reg [31:0] counter20, counter20neg, A20, B20, C20, D20, F20, B20neg, C20neg, D20neg;
reg [31:0] counter21, counter21neg, A21, B21, C21, D21, F21, B21neg, C21neg, D21neg;
reg [31:0] counter22, counter22neg, A22, B22, C22, D22, F22, B22neg, C22neg, D22neg;
reg [31:0] counter23, counter23neg, A23, B23, C23, D23, F23, B23neg, C23neg, D23neg;
reg [31:0] counter24, counter24neg, A24, B24, C24, D24, F24, B24neg, C24neg, D24neg;
reg [31:0] counter25, counter25neg, A25, B25, C25, D25, F25, B25neg, C25neg, D25neg;
reg [31:0] counter26, counter26neg, A26, B26, C26, D26, F26, B26neg, C26neg, D26neg;
reg [31:0] counter27, counter27neg, A27, B27, C27, D27, F27, B27neg, C27neg, D27neg;
reg [31:0] counter28, counter28neg, A28, B28, C28, D28, F28, B28neg, C28neg, D28neg;
reg [31:0] counter29, counter29neg, A29, B29, C29, D29, F29, B29neg, C29neg, D29neg;
reg [31:0] counter30, counter30neg, A30, B30, C30, D30, F30, B30neg, C30neg, D30neg;
reg [31:0] counter31, counter31neg, A31, B31, C31, D31, F31, B31neg, C31neg, D31neg;
reg [31:0] counter32, counter32neg, A32, B32, C32, D32, F32, B32neg, C32neg, D32neg;
reg [31:0] counter33, counter33neg, A33, B33, C33, D33, F33, B33neg, C33neg, D33neg;
reg [31:0] counter34, counter34neg, A34, B34, C34, D34, F34, B34neg, C34neg, D34neg;
reg [31:0] counter35, counter35neg, A35, B35, C35, D35, F35, B35neg, C35neg, D35neg;
reg [31:0] counter36, counter36neg, A36, B36, C36, D36, F36, B36neg, C36neg, D36neg;
reg [31:0] counter37, counter37neg, A37, B37, C37, D37, F37, B37neg, C37neg, D37neg;
reg [31:0] counter38, counter38neg, A38, B38, C38, D38, F38, B38neg, C38neg, D38neg;
reg [31:0] counter39, counter39neg, A39, B39, C39, D39, F39, B39neg, C39neg, D39neg;
reg [31:0] counter40, counter40neg, A40, B40, C40, D40, F40, B40neg, C40neg, D40neg;
reg [31:0] counter41, counter41neg, A41, B41, C41, D41, F41, B41neg, C41neg, D41neg;
reg [31:0] counter42, counter42neg, A42, B42, C42, D42, F42, B42neg, C42neg, D42neg;
reg [31:0] counter43, counter43neg, A43, B43, C43, D43, F43, B43neg, C43neg, D43neg;
reg [31:0] counter44, counter44neg, A44, B44, C44, D44, F44, B44neg, C44neg, D44neg;
reg [31:0] counter45, counter45neg, A45, B45, C45, D45, F45, B45neg, C45neg, D45neg;
reg [31:0] counter46, counter46neg, A46, B46, C46, D46, F46, B46neg, C46neg, D46neg;
reg [31:0] counter47, counter47neg, A47, B47, C47, D47, F47, B47neg, C47neg, D47neg;
reg [31:0] counter48, counter48neg, A48, B48, C48, D48, F48, B48neg, C48neg, D48neg;
reg [31:0] counter49, counter49neg, A49, B49, C49, D49, F49, B49neg, C49neg, D49neg;
reg [31:0] counter50, counter50neg, A50, B50, C50, D50, F50, B50neg, C50neg, D50neg;
reg [31:0] counter51, counter51neg, A51, B51, C51, D51, F51, B51neg, C51neg, D51neg;
reg [31:0] counter52, counter52neg, A52, B52, C52, D52, F52, B52neg, C52neg, D52neg;
reg [31:0] counter53, counter53neg, A53, B53, C53, D53, F53, B53neg, C53neg, D53neg;
reg [31:0] counter54, counter54neg, A54, B54, C54, D54, F54, B54neg, C54neg, D54neg;
reg [31:0] counter55, counter55neg, A55, B55, C55, D55, F55, B55neg, C55neg, D55neg;
reg [31:0] counter56, counter56neg, A56, B56, C56, D56, F56, B56neg, C56neg, D56neg;
reg [31:0] counter57, counter57neg, A57, B57, C57, D57, F57, B57neg, C57neg, D57neg;
reg [31:0] counter58, counter58neg, A58, B58, C58, D58, F58, B58neg, C58neg, D58neg;
reg [31:0] counter59, counter59neg, A59, B59, C59, D59, F59, B59neg, C59neg, D59neg;
reg [31:0] counter60, counter60neg, A60, B60, C60, D60, F60, B60neg, C60neg, D60neg;
reg [31:0] counter61, counter61neg, A61, B61, C61, D61, F61, B61neg, C61neg, D61neg;
reg [31:0] counter62, counter62neg, A62, B62, C62, D62, F62, B62neg, C62neg, D62neg;
reg [31:0] counter63, counter63neg, A63, B63, C63, D63, F63, B63neg, C63neg, D63neg;
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
localparam Stage21Value = 32'h02441453;
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
localparam Stage43Value = 32'h04881d05;
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
end

// stage 00neg
always @(negedge CLK)
begin
  B00 = BValue + ( (F00 << 7) | (F00 >> ( 32 - 7 ) ) );
end


// stage 01pos
always @(posedge CLK)
begin
  counter01neg = counter00;
  F01 = ( ( B00 & C00) | (( ~ B00) & D00) ) + A00 + Stage01Value;
  D01neg = D00;
  C01neg = C00;
  B01neg = B00;
end


// stage 01neg
always @(negedge CLK)
begin
  counter01 = counter01neg;
  A01 = D01neg;
  D01 = C01neg;
  C01 = B01neg;
  B01 = B01neg + ( (F01 << 12) | (F01 >> ( 32 - 12 ) ) );
end


// stage 02pos
always @(posedge CLK)
begin
  counter02neg = counter01;
  F02 = ( ( B01 & C01) | (( ~ B01) & D01) ) + A01 + Stage02Value;
  D02neg = D01;
  C02neg = C01;
  B02neg = B01;
end


// stage 02neg
always @(negedge CLK)
begin
  counter02 = counter02neg;
  A02 = D02neg;
  D02 = C02neg;
  C02 = B02neg;
  B02 = B02neg + ( (F02 << 17) | (F02 >> ( 32 - 17 ) ) );
end


// stage 03pos
always @(posedge CLK)
begin
  counter03neg = counter02;
  F03 = ( ( B02 & C02) | (( ~ B02) & D02) ) + A02 + Stage03Value;
  D03neg = D02;
  C03neg = C02;
  B03neg = B02;
end


// stage 03neg
always @(negedge CLK)
begin
  counter03 = counter03neg;
  A03 = D03neg;
  D03 = C03neg;
  C03 = B03neg;
  B03 = B03neg + ( (F03 << 22) | (F03 >> ( 32 - 22 ) ) );
end


// stage 04pos
always @(posedge CLK)
begin
  counter04neg = counter03;
  F04 = ( ( B03 & C03) | (( ~ B03) & D03) ) + A03 + Stage04Value;
  D04neg = D03;
  C04neg = C03;
  B04neg = B03;
end


// stage 04neg
always @(negedge CLK)
begin
  counter04 = counter04neg;
  A04 = D04neg;
  D04 = C04neg;
  C04 = B04neg;
  B04 = B04neg + ( (F04 << 7) | (F04 >> ( 32 - 7 ) ) );
end


// stage 05pos
always @(posedge CLK)
begin
  counter05neg = counter04;
  F05 = ( ( B04 & C04) | (( ~ B04) & D04) ) + A04 + Stage05Value;
  D05neg = D04;
  C05neg = C04;
  B05neg = B04;
end


// stage 05neg
always @(negedge CLK)
begin
  counter05 = counter05neg;
  A05 = D05neg;
  D05 = C05neg;
  C05 = B05neg;
  B05 = B05neg + ( (F05 << 12) | (F05 >> ( 32 - 12 ) ) );
end


// stage 06pos
always @(posedge CLK)
begin
  counter06neg = counter05;
  F06 = ( ( B05 & C05) | (( ~ B05) & D05) ) + A05 + Stage06Value;
  D06neg = D05;
  C06neg = C05;
  B06neg = B05;
end


// stage 06neg
always @(negedge CLK)
begin
  counter06 = counter06neg;
  A06 = D06neg;
  D06 = C06neg;
  C06 = B06neg;
  B06 = B06neg + ( (F06 << 17) | (F06 >> ( 32 - 17 ) ) );
end


// stage 07pos
always @(posedge CLK)
begin
  counter07neg = counter06;
  F07 = ( ( B06 & C06) | (( ~ B06) & D06) ) + A06 + Stage07Value;
  D07neg = D06;
  C07neg = C06;
  B07neg = B06;
end


// stage 07neg
always @(negedge CLK)
begin
  counter07 = counter07neg;
  A07 = D07neg;
  D07 = C07neg;
  C07 = B07neg;
  B07 = B07neg + ( (F07 << 22) | (F07 >> ( 32 - 22 ) ) );
end


// stage 08pos
always @(posedge CLK)
begin
  counter08neg = counter07;
  F08 = ( ( B07 & C07) | (( ~ B07) & D07) ) + A07 + Stage08Value;
  D08neg = D07;
  C08neg = C07;
  B08neg = B07;
end


// stage 08neg
always @(negedge CLK)
begin
  counter08 = counter08neg;
  A08 = D08neg;
  D08 = C08neg;
  C08 = B08neg;
  B08 = B08neg + ( (F08 << 7) | (F08 >> ( 32 - 7 ) ) );
end


// stage 09pos
always @(posedge CLK)
begin
  counter09neg = counter08;
  F09 = ( ( B08 & C08) | (( ~ B08) & D08) ) + A08 + Stage09Value;
  D09neg = D08;
  C09neg = C08;
  B09neg = B08;
end


// stage 09neg
always @(negedge CLK)
begin
  counter09 = counter09neg;
  A09 = D09neg;
  D09 = C09neg;
  C09 = B09neg;
  B09 = B09neg + ( (F09 << 12) | (F09 >> ( 32 - 12 ) ) );
end


// stage 10pos
always @(posedge CLK)
begin
  counter10neg = counter09;
  F10 = ( ( B09 & C09) | (( ~ B09) & D09) ) + A09 + Stage10Value;
  D10neg = D09;
  C10neg = C09;
  B10neg = B09;
end


// stage 10neg
always @(negedge CLK)
begin
  counter10 = counter10neg;
  A10 = D10neg;
  D10 = C10neg;
  C10 = B10neg;
  B10 = B10neg + ( (F10 << 17) | (F10 >> ( 32 - 17 ) ) );
end


// stage 11pos
always @(posedge CLK)
begin
  counter11neg = counter10;
  F11 = ( ( B10 & C10) | (( ~ B10) & D10) ) + A10 + Stage11Value;
  D11neg = D10;
  C11neg = C10;
  B11neg = B10;
end


// stage 11neg
always @(negedge CLK)
begin
  counter11 = counter11neg;
  A11 = D11neg;
  D11 = C11neg;
  C11 = B11neg;
  B11 = B11neg + ( (F11 << 22) | (F11 >> ( 32 - 22 ) ) );
end


// stage 12pos
always @(posedge CLK)
begin
  counter12neg = counter11;
  F12 = ( ( B11 & C11) | (( ~ B11) & D11) ) + A11 + Stage12Value;
  D12neg = D11;
  C12neg = C11;
  B12neg = B11;
end


// stage 12neg
always @(negedge CLK)
begin
  counter12 = counter12neg;
  A12 = D12neg;
  D12 = C12neg;
  C12 = B12neg;
  B12 = B12neg + ( (F12 << 7) | (F12 >> ( 32 - 7 ) ) );
end


// stage 13pos
always @(posedge CLK)
begin
  counter13neg = counter12;
  F13 = ( ( B12 & C12) | (( ~ B12) & D12) ) + A12 + Stage13Value;
  D13neg = D12;
  C13neg = C12;
  B13neg = B12;
end


// stage 13neg
always @(negedge CLK)
begin
  counter13 = counter13neg;
  A13 = D13neg;
  D13 = C13neg;
  C13 = B13neg;
  B13 = B13neg + ( (F13 << 12) | (F13 >> ( 32 - 12 ) ) );
end


// stage 14pos
always @(posedge CLK)
begin
  counter14neg = counter13;
  F14 = ( ( B13 & C13) | (( ~ B13) & D13) ) + A13 + Stage14Value;
  D14neg = D13;
  C14neg = C13;
  B14neg = B13;
end


// stage 14neg
always @(negedge CLK)
begin
  counter14 = counter14neg;
  A14 = D14neg;
  D14 = C14neg;
  C14 = B14neg;
  B14 = B14neg + ( (F14 << 17) | (F14 >> ( 32 - 17 ) ) );
end


// stage 15pos
always @(posedge CLK)
begin
  counter15neg = counter14;
  F15 = ( ( B14 & C14) | (( ~ B14) & D14) ) + A14 + Stage15Value;
  D15neg = D14;
  C15neg = C14;
  B15neg = B14;
end


// stage 15neg
always @(negedge CLK)
begin
  counter15 = counter15neg;
  A15 = D15neg;
  D15 = C15neg;
  C15 = B15neg;
  B15 = B15neg + ( (F15 << 22) | (F15 >> ( 32 - 22 ) ) );
end

//**********************************************************************
//                             round 01
//**********************************************************************


// stage 16pos
always @(posedge CLK)
begin
  counter16neg = counter15;
  F16 = ( ( D15 & B15) | (( ~ D15) & C15) ) + A15 + Stage16Value;
  D16neg = D15;
  C16neg = C15;
  B16neg = B15;
end


// stage 16neg
always @(negedge CLK)
begin
  counter16 = counter16neg;
  A16 = D16neg;
  D16 = C16neg;
  C16 = B16neg;
  B16 = B16neg + ( (F16 << 5) | (F16 >> ( 32 - 5 ) ) );
end


// stage 17pos
always @(posedge CLK)
begin
  counter17neg = counter16;
  F17 = ( ( D16 & B16) | (( ~ D16) & C16) ) + A16 + Stage17Value;
  D17neg = D16;
  C17neg = C16;
  B17neg = B16;
end


// stage 17neg
always @(negedge CLK)
begin
  counter17 = counter17neg;
  A17 = D17neg;
  D17 = C17neg;
  C17 = B17neg;
  B17 = B17neg + ( (F17 << 9) | (F17 >> ( 32 - 9 ) ) );
end


// stage 18pos
always @(posedge CLK)
begin
  counter18neg = counter17;
  F18 = ( ( D17 & B17) | (( ~ D17) & C17) ) + A17 + Stage18Value;
  D18neg = D17;
  C18neg = C17;
  B18neg = B17;
end


// stage 18neg
always @(negedge CLK)
begin
  counter18 = counter18neg;
  A18 = D18neg;
  D18 = C18neg;
  C18 = B18neg;
  B18 = B18neg + ( (F18 << 14) | (F18 >> ( 32 - 14 ) ) );
end


// stage 19pos
always @(posedge CLK)
begin
  counter19neg = counter18;
  F19 = ( ( D18 & B18) | (( ~ D18) & C18) ) + A18 + Stage19Value + counter19;
  D19neg = D18;
  C19neg = C18;
  B19neg = B18;
end


// stage 19neg
always @(negedge CLK)
begin
  counter19 = counter19neg;
  A19 = D19neg;
  D19 = C19neg;
  C19 = B19neg;
  B19 = B19neg + ( (F19 << 20) | (F19 >> ( 32 - 20 ) ) );
end


// stage 20pos
always @(posedge CLK)
begin
  counter20neg = counter19;
  F20 = ( ( D19 & B19) | (( ~ D19) & C19) ) + A19 + Stage20Value;
  D20neg = D19;
  C20neg = C19;
  B20neg = B19;
end


// stage 20neg
always @(negedge CLK)
begin
  counter20 = counter20neg;
  A20 = D20neg;
  D20 = C20neg;
  C20 = B20neg;
  B20 = B20neg + ( (F20 << 5) | (F20 >> ( 32 - 5 ) ) );
end


// stage 21pos
always @(posedge CLK)
begin
  counter21neg = counter20;
  F21 = ( ( D20 & B20) | (( ~ D20) & C20) ) + A20 + Stage21Value;
  D21neg = D20;
  C21neg = C20;
  B21neg = B20;
end


// stage 21neg
always @(negedge CLK)
begin
  counter21 = counter21neg;
  A21 = D21neg;
  D21 = C21neg;
  C21 = B21neg;
  B21 = B21neg + ( (F21 << 9) | (F21 >> ( 32 - 9 ) ) );
end


// stage 22pos
always @(posedge CLK)
begin
  counter22neg = counter21;
  F22 = ( ( D21 & B21) | (( ~ D21) & C21) ) + A21 + Stage22Value;
  D22neg = D21;
  C22neg = C21;
  B22neg = B21;
end


// stage 22neg
always @(negedge CLK)
begin
  counter22 = counter22neg;
  A22 = D22neg;
  D22 = C22neg;
  C22 = B22neg;
  B22 = B22neg + ( (F22 << 14) | (F22 >> ( 32 - 14 ) ) );
end


// stage 23pos
always @(posedge CLK)
begin
  counter23neg = counter22;
  F23 = ( ( D22 & B22) | (( ~ D22) & C22) ) + A22 + Stage23Value;
  D23neg = D22;
  C23neg = C22;
  B23neg = B22;
end


// stage 23neg
always @(negedge CLK)
begin
  counter23 = counter23neg;
  A23 = D23neg;
  D23 = C23neg;
  C23 = B23neg;
  B23 = B23neg + ( (F23 << 20) | (F23 >> ( 32 - 20 ) ) );
end


// stage 24pos
always @(posedge CLK)
begin
  counter24neg = counter23;
  F24 = ( ( D23 & B23) | (( ~ D23) & C23) ) + A23 + Stage24Value;
  D24neg = D23;
  C24neg = C23;
  B24neg = B23;
end


// stage 24neg
always @(negedge CLK)
begin
  counter24 = counter24neg;
  A24 = D24neg;
  D24 = C24neg;
  C24 = B24neg;
  B24 = B24neg + ( (F24 << 5) | (F24 >> ( 32 - 5 ) ) );
end


// stage 25pos
always @(posedge CLK)
begin
  counter25neg = counter24;
  F25 = ( ( D24 & B24) | (( ~ D24) & C24) ) + A24 + Stage25Value;
  D25neg = D24;
  C25neg = C24;
  B25neg = B24;
end


// stage 25neg
always @(negedge CLK)
begin
  counter25 = counter25neg;
  A25 = D25neg;
  D25 = C25neg;
  C25 = B25neg;
  B25 = B25neg + ( (F25 << 9) | (F25 >> ( 32 - 9 ) ) );
end


// stage 26pos
always @(posedge CLK)
begin
  counter26neg = counter25;
  F26 = ( ( D25 & B25) | (( ~ D25) & C25) ) + A25 + Stage26Value;
  D26neg = D25;
  C26neg = C25;
  B26neg = B25;
end


// stage 26neg
always @(negedge CLK)
begin
  counter26 = counter26neg;
  A26 = D26neg;
  D26 = C26neg;
  C26 = B26neg;
  B26 = B26neg + ( (F26 << 14) | (F26 >> ( 32 - 14 ) ) );
end


// stage 27pos
always @(posedge CLK)
begin
  counter27neg = counter26;
  F27 = ( ( D26 & B26) | (( ~ D26) & C26) ) + A26 + Stage27Value;
  D27neg = D26;
  C27neg = C26;
  B27neg = B26;
end


// stage 27neg
always @(negedge CLK)
begin
  counter27 = counter27neg;
  A27 = D27neg;
  D27 = C27neg;
  C27 = B27neg;
  B27 = B27neg + ( (F27 << 20) | (F27 >> ( 32 - 20 ) ) );
end


// stage 28pos
always @(posedge CLK)
begin
  counter28neg = counter27;
  F28 = ( ( D27 & B27) | (( ~ D27) & C27) ) + A27 + Stage28Value;
  D28neg = D27;
  C28neg = C27;
  B28neg = B27;
end


// stage 28neg
always @(negedge CLK)
begin
  counter28 = counter28neg;
  A28 = D28neg;
  D28 = C28neg;
  C28 = B28neg;
  B28 = B28neg + ( (F28 << 5) | (F28 >> ( 32 - 5 ) ) );
end


// stage 29pos
always @(posedge CLK)
begin
  counter29neg = counter28;
  F29 = ( ( D28 & B28) | (( ~ D28) & C28) ) + A28 + Stage29Value;
  D29neg = D28;
  C29neg = C28;
  B29neg = B28;
end


// stage 29neg
always @(negedge CLK)
begin
  counter29 = counter29neg;
  A29 = D29neg;
  D29 = C29neg;
  C29 = B29neg;
  B29 = B29neg + ( (F29 << 9) | (F29 >> ( 32 - 9 ) ) );
end


// stage 30pos
always @(posedge CLK)
begin
  counter30neg = counter29;
  F30 = ( ( D29 & B29) | (( ~ D29) & C29) ) + A29 + Stage30Value;
  D30neg = D29;
  C30neg = C29;
  B30neg = B29;
end


// stage 30neg
always @(negedge CLK)
begin
  counter30 = counter30neg;
  A30 = D30neg;
  D30 = C30neg;
  C30 = B30neg;
  B30 = B30neg + ( (F30 << 14) | (F30 >> ( 32 - 14 ) ) );
end


// stage 31pos
always @(posedge CLK)
begin
  counter31neg = counter30;
  F31 = ( ( D30 & B30) | (( ~ D30) & C30) ) + A30 + Stage31Value;
  D31neg = D30;
  C31neg = C30;
  B31neg = B30;
end


// stage 31neg
always @(negedge CLK)
begin
  counter31 = counter31neg;
  A31 = D31neg;
  D31 = C31neg;
  C31 = B31neg;
  B31 = B31neg + ( (F31 << 20) | (F31 >> ( 32 - 20 ) ) );
end

//**********************************************************************
//                             round 02
//**********************************************************************


// stage 32pos
always @(posedge CLK)
begin
  counter32neg = counter31;
  F32 = ( ( B31 ^ C31) ^ D31 ) +  A31 + Stage32Value;
  D32neg = D31;
  C32neg = C31;
  B32neg = B31;
end


// stage 32neg
always @(negedge CLK)
begin
  counter32 = counter32neg;
  A32 = D32neg;
  D32 = C32neg;
  C32 = B32neg;
  B32 = B32neg + ( (F32 << 4) | (F32 >> ( 32 - 4 ) ) );
end


// stage 33pos
always @(posedge CLK)
begin
  counter33neg = counter32;
  F33 = ( ( B32 ^ C32) ^ D32 ) +  A32 + Stage33Value;
  D33neg = D32;
  C33neg = C32;
  B33neg = B32;
end


// stage 33neg
always @(negedge CLK)
begin
  counter33 = counter33neg;
  A33 = D33neg;
  D33 = C33neg;
  C33 = B33neg;
  B33 = B33neg + ( (F33 << 11) | (F33 >> ( 32 - 11 ) ) );
end


// stage 34pos
always @(posedge CLK)
begin
  counter34neg = counter33;
  F34 = ( ( B33 ^ C33) ^ D33 ) +  A33 + Stage34Value;
  D34neg = D33;
  C34neg = C33;
  B34neg = B33;
end


// stage 34neg
always @(negedge CLK)
begin
  counter34 = counter34neg;
  A34 = D34neg;
  D34 = C34neg;
  C34 = B34neg;
  B34 = B34neg + ( (F34 << 16) | (F34 >> ( 32 - 16 ) ) );
end


// stage 35pos
always @(posedge CLK)
begin
  counter35neg = counter34;
  F35 = ( ( B34 ^ C34) ^ D34 ) +  A34 + Stage35Value;
  D35neg = D34;
  C35neg = C34;
  B35neg = B34;
end


// stage 35neg
always @(negedge CLK)
begin
  counter35 = counter35neg;
  A35 = D35neg;
  D35 = C35neg;
  C35 = B35neg;
  B35 = B35neg + ( (F35 << 23) | (F35 >> ( 32 - 23 ) ) );
end


// stage 36pos
always @(posedge CLK)
begin
  counter36neg = counter35;
  F36 = ( ( B35 ^ C35) ^ D35 ) +  A35 + Stage36Value;
  D36neg = D35;
  C36neg = C35;
  B36neg = B35;
end


// stage 36neg
always @(negedge CLK)
begin
  counter36 = counter36neg;
  A36 = D36neg;
  D36 = C36neg;
  C36 = B36neg;
  B36 = B36neg + ( (F36 << 4) | (F36 >> ( 32 - 4 ) ) );
end


// stage 37pos
always @(posedge CLK)
begin
  counter37neg = counter36;
  F37 = ( ( B36 ^ C36) ^ D36 ) +  A36 + Stage37Value;
  D37neg = D36;
  C37neg = C36;
  B37neg = B36;
end


// stage 37neg
always @(negedge CLK)
begin
  counter37 = counter37neg;
  A37 = D37neg;
  D37 = C37neg;
  C37 = B37neg;
  B37 = B37neg + ( (F37 << 11) | (F37 >> ( 32 - 11 ) ) );
end


// stage 38pos
always @(posedge CLK)
begin
  counter38neg = counter37;
  F38 = ( ( B37 ^ C37) ^ D37 ) +  A37 + Stage38Value;
  D38neg = D37;
  C38neg = C37;
  B38neg = B37;
end


// stage 38neg
always @(negedge CLK)
begin
  counter38 = counter38neg;
  A38 = D38neg;
  D38 = C38neg;
  C38 = B38neg;
  B38 = B38neg + ( (F38 << 16) | (F38 >> ( 32 - 16 ) ) );
end


// stage 39pos
always @(posedge CLK)
begin
  counter39neg = counter38;
  F39 = ( ( B38 ^ C38) ^ D38 ) +  A38 + Stage39Value;
  D39neg = D38;
  C39neg = C38;
  B39neg = B38;
end


// stage 39neg
always @(negedge CLK)
begin
  counter39 = counter39neg;
  A39 = D39neg;
  D39 = C39neg;
  C39 = B39neg;
  B39 = B39neg + ( (F39 << 23) | (F39 >> ( 32 - 23 ) ) );
end


// stage 40pos
always @(posedge CLK)
begin
  counter40neg = counter39;
  F40 = ( ( B39 ^ C39) ^ D39 ) +  A39 + Stage40Value;
  D40neg = D39;
  C40neg = C39;
  B40neg = B39;
end


// stage 40neg
always @(negedge CLK)
begin
  counter40 = counter40neg;
  A40 = D40neg;
  D40 = C40neg;
  C40 = B40neg;
  B40 = B40neg + ( (F40 << 4) | (F40 >> ( 32 - 4 ) ) );
end


// stage 41pos
always @(posedge CLK)
begin
  counter41neg = counter40;
  F41 = ( ( B40 ^ C40) ^ D40 ) +  A40 + Stage41Value + counter41;
  D41neg = D40;
  C41neg = C40;
  B41neg = B40;
end


// stage 41neg
always @(negedge CLK)
begin
  counter41 = counter41neg;
  A41 = D41neg;
  D41 = C41neg;
  C41 = B41neg;
  B41 = B41neg + ( (F41 << 11) | (F41 >> ( 32 - 11 ) ) );
end


// stage 42pos
always @(posedge CLK)
begin
  counter42neg = counter41;
  F42 = ( ( B41 ^ C41) ^ D41 ) +  A41 + Stage42Value;
  D42neg = D41;
  C42neg = C41;
  B42neg = B41;
end


// stage 42neg
always @(negedge CLK)
begin
  counter42 = counter42neg;
  A42 = D42neg;
  D42 = C42neg;
  C42 = B42neg;
  B42 = B42neg + ( (F42 << 16) | (F42 >> ( 32 - 16 ) ) );
end


// stage 43pos
always @(posedge CLK)
begin
  counter43neg = counter42;
  F43 = ( ( B42 ^ C42) ^ D42 ) +  A42 + Stage43Value;
  D43neg = D42;
  C43neg = C42;
  B43neg = B42;
end


// stage 43neg
always @(negedge CLK)
begin
  counter43 = counter43neg;
  A43 = D43neg;
  D43 = C43neg;
  C43 = B43neg;
  B43 = B43neg + ( (F43 << 23) | (F43 >> ( 32 - 23 ) ) );
end


// stage 44pos
always @(posedge CLK)
begin
  counter44neg = counter43;
  F44 = ( ( B43 ^ C43) ^ D43 ) +  A43 + Stage44Value;
  D44neg = D43;
  C44neg = C43;
  B44neg = B43;
end


// stage 44neg
always @(negedge CLK)
begin
  counter44 = counter44neg;
  A44 = D44neg;
  D44 = C44neg;
  C44 = B44neg;
  B44 = B44neg + ( (F44 << 4) | (F44 >> ( 32 - 4 ) ) );
end


// stage 45pos
always @(posedge CLK)
begin
  counter45neg = counter44;
  F45 = ( ( B44 ^ C44) ^ D44 ) +  A44 + Stage45Value;
  D45neg = D44;
  C45neg = C44;
  B45neg = B44;
end


// stage 45neg
always @(negedge CLK)
begin
  counter45 = counter45neg;
  A45 = D45neg;
  D45 = C45neg;
  C45 = B45neg;
  B45 = B45neg + ( (F45 << 11) | (F45 >> ( 32 - 11 ) ) );
end


// stage 46pos
always @(posedge CLK)
begin
  counter46neg = counter45;
  F46 = ( ( B45 ^ C45) ^ D45 ) +  A45 + Stage46Value;
  D46neg = D45;
  C46neg = C45;
  B46neg = B45;
end


// stage 46neg
always @(negedge CLK)
begin
  counter46 = counter46neg;
  A46 = D46neg;
  D46 = C46neg;
  C46 = B46neg;
  B46 = B46neg + ( (F46 << 16) | (F46 >> ( 32 - 16 ) ) );
end


// stage 47pos
always @(posedge CLK)
begin
  counter47neg = counter46;
  F47 = ( ( B46 ^ C46) ^ D46 ) +  A46 + Stage47Value;
  D47neg = D46;
  C47neg = C46;
  B47neg = B46;
end


// stage 47neg
always @(negedge CLK)
begin
  counter47 = counter47neg;
  A47 = D47neg;
  D47 = C47neg;
  C47 = B47neg;
  B47 = B47neg + ( (F47 << 23) | (F47 >> ( 32 - 23 ) ) );
end

//**********************************************************************
//                             round 03
//**********************************************************************


// stage 48pos
always @(posedge CLK)
begin
  counter48neg = counter47;
  F48 = ( C47 ^ (  B47 | ~ D47 ) ) +  A47 + Stage48Value + counter48;
  D48neg = D47;
  C48neg = C47;
  B48neg = B47;
end


// stage 48neg
always @(negedge CLK)
begin
  counter48 = counter48neg;
  A48 = D48neg;
  D48 = C48neg;
  C48 = B48neg;
  B48 = B48neg + ( (F48 << 6) | (F48 >> ( 32 - 6 ) ) );
end


// stage 49pos
always @(posedge CLK)
begin
  counter49neg = counter48;
  F49 = ( C48 ^ (  B48 | ~ D48 ) ) +  A48 + Stage49Value;
  D49neg = D48;
  C49neg = C48;
  B49neg = B48;
end


// stage 49neg
always @(negedge CLK)
begin
  counter49 = counter49neg;
  A49 = D49neg;
  D49 = C49neg;
  C49 = B49neg;
  B49 = B49neg + ( (F49 << 10) | (F49 >> ( 32 - 10 ) ) );
end


// stage 50pos
always @(posedge CLK)
begin
  counter50neg = counter49;
  F50 = ( C49 ^ (  B49 | ~ D49 ) ) +  A49 + Stage50Value;
  D50neg = D49;
  C50neg = C49;
  B50neg = B49;
end


// stage 50neg
always @(negedge CLK)
begin
  counter50 = counter50neg;
  A50 = D50neg;
  D50 = C50neg;
  C50 = B50neg;
  B50 = B50neg + ( (F50 << 15) | (F50 >> ( 32 - 15 ) ) );
end


// stage 51pos
always @(posedge CLK)
begin
  counter51neg = counter50;
  F51 = ( C50 ^ (  B50 | ~ D50 ) ) +  A50 + Stage51Value;
  D51neg = D50;
  C51neg = C50;
  B51neg = B50;
end


// stage 51neg
always @(negedge CLK)
begin
  counter51 = counter51neg;
  A51 = D51neg;
  D51 = C51neg;
  C51 = B51neg;
  B51 = B51neg + ( (F51 << 21) | (F51 >> ( 32 - 21 ) ) );
end


// stage 52pos
always @(posedge CLK)
begin
  counter52neg = counter51;
  F52 = ( C51 ^ (  B51 | ~ D51 ) ) +  A51 + Stage52Value;
  D52neg = D51;
  C52neg = C51;
  B52neg = B51;
end


// stage 52neg
always @(negedge CLK)
begin
  counter52 = counter52neg;
  A52 = D52neg;
  D52 = C52neg;
  C52 = B52neg;
  B52 = B52neg + ( (F52 << 6) | (F52 >> ( 32 - 6 ) ) );
end


// stage 53pos
always @(posedge CLK)
begin
  counter53neg = counter52;
  F53 = ( C52 ^ (  B52 | ~ D52 ) ) +  A52 + Stage53Value;
  D53neg = D52;
  C53neg = C52;
  B53neg = B52;
end


// stage 53neg
always @(negedge CLK)
begin
  counter53 = counter53neg;
  A53 = D53neg;
  D53 = C53neg;
  C53 = B53neg;
  B53 = B53neg + ( (F53 << 10) | (F53 >> ( 32 - 10 ) ) );
end


// stage 54pos
always @(posedge CLK)
begin
  counter54neg = counter53;
  F54 = ( C53 ^ (  B53 | ~ D53 ) ) +  A53 + Stage54Value;
  D54neg = D53;
  C54neg = C53;
  B54neg = B53;
end


// stage 54neg
always @(negedge CLK)
begin
  counter54 = counter54neg;
  A54 = D54neg;
  D54 = C54neg;
  C54 = B54neg;
  B54 = B54neg + ( (F54 << 15) | (F54 >> ( 32 - 15 ) ) );
end


// stage 55pos
always @(posedge CLK)
begin
  counter55neg = counter54;
  F55 = ( C54 ^ (  B54 | ~ D54 ) ) +  A54 + Stage55Value;
  D55neg = D54;
  C55neg = C54;
  B55neg = B54;
end


// stage 55neg
always @(negedge CLK)
begin
  counter55 = counter55neg;
  A55 = D55neg;
  D55 = C55neg;
  C55 = B55neg;
  B55 = B55neg + ( (F55 << 21) | (F55 >> ( 32 - 21 ) ) );
end


// stage 56pos
always @(posedge CLK)
begin
  counter56neg = counter55;
  F56 = ( C55 ^ (  B55 | ~ D55 ) ) +  A55 + Stage56Value;
  D56neg = D55;
  C56neg = C55;
  B56neg = B55;
end


// stage 56neg
always @(negedge CLK)
begin
  counter56 = counter56neg;
  A56 = D56neg;
  D56 = C56neg;
  C56 = B56neg;
  B56 = B56neg + ( (F56 << 6) | (F56 >> ( 32 - 6 ) ) );
end


// stage 57pos
always @(posedge CLK)
begin
  counter57neg = counter56;
  F57 = ( C56 ^ (  B56 | ~ D56 ) ) +  A56 + Stage57Value;
  D57neg = D56;
  C57neg = C56;
  B57neg = B56;
end


// stage 57neg
always @(negedge CLK)
begin
  counter57 = counter57neg;
  A57 = D57neg;
  D57 = C57neg;
  C57 = B57neg;
  B57 = B57neg + ( (F57 << 10) | (F57 >> ( 32 - 10 ) ) );
end


// stage 58pos
always @(posedge CLK)
begin
  counter58neg = counter57;
  F58 = ( C57 ^ (  B57 | ~ D57 ) ) +  A57 + Stage58Value;
  D58neg = D57;
  C58neg = C57;
  B58neg = B57;
end


// stage 58neg
always @(negedge CLK)
begin
  counter58 = counter58neg;
  A58 = D58neg;
  D58 = C58neg;
  C58 = B58neg;
  B58 = B58neg + ( (F58 << 15) | (F58 >> ( 32 - 15 ) ) );
end


// stage 59pos
always @(posedge CLK)
begin
  counter59neg = counter58;
  F59 = ( C58 ^ (  B58 | ~ D58 ) ) +  A58 + Stage59Value;
  D59neg = D58;
  C59neg = C58;
  B59neg = B58;
end


// stage 59neg
always @(negedge CLK)
begin
  counter59 = counter59neg;
  A59 = D59neg;
  D59 = C59neg;
  C59 = B59neg;
  B59 = B59neg + ( (F59 << 21) | (F59 >> ( 32 - 21 ) ) );
end


// stage 60pos
always @(posedge CLK)
begin
  counter60neg = counter59;
  F60 = ( C59 ^ (  B59 | ~ D59 ) ) +  A59 + Stage60Value;
  D60neg = D59;
  C60neg = C59;
  B60neg = B59;
end


// stage 60neg
always @(negedge CLK)
begin
  counter60 = counter60neg;
  A60 = D60neg;
  D60 = C60neg;
  C60 = B60neg;
  B60 = B60neg + ( (F60 << 6) | (F60 >> ( 32 - 6 ) ) );
end


// stage 61pos
always @(posedge CLK)
begin
  counter61neg = counter60;
  F61 = ( C60 ^ (  B60 | ~ D60 ) ) +  A60 + Stage61Value;
  D61neg = D60;
  C61neg = C60;
  B61neg = B60;
end


// stage 61neg
always @(negedge CLK)
begin
  counter61 = counter61neg;
  A61 = D61neg;
  D61 = C61neg;
  C61 = B61neg;
  B61 = B61neg + ( (F61 << 10) | (F61 >> ( 32 - 10 ) ) );
end


// stage 62pos
always @(posedge CLK)
begin
  counter62neg = counter61;
  F62 = ( C61 ^ (  B61 | ~ D61 ) ) +  A61 + Stage62Value;
  D62neg = D61;
  C62neg = C61;
  B62neg = B61;
end


// stage 62neg
always @(negedge CLK)
begin
  counter62 = counter62neg;
  A62 = D62neg;
  D62 = C62neg;
  C62 = B62neg;
  B62 = B62neg + ( (F62 << 15) | (F62 >> ( 32 - 15 ) ) );
end

// stage 63pos
always @(posedge CLK)
begin
  counter63 = counter62;
  F63 = ( C62 ^ (  B62 | ~ D62 ) ) +  A62 + Stage63Value;
  D63neg = D62;
  C63neg = C62;
  B63neg = B62;
end
// stage 63neg
always @(negedge CLK)
begin
  A63 = D63neg + AValue;
  D63 = C63neg + DValue;
  C63 = B63neg + CValue;
  B63 = B63neg + BValue + ( (F63 << 21) | (F63 >> ( 32 - 21 ) ) );
end

// stage64pos
always @(posedge CLK)
begin
  if (reset)
    hash <= 128'h00000000000000000000000000000000;
  else
  begin  
    hash[127:120] <= A63[ 7: 0];
    hash[119:112] <= A63[15: 8];
    hash[111:104] <= A63[23:16];
    hash[103: 96] <= A63[31:24];
    
    hash[ 95: 88] <= B63[ 7: 0];
    hash[ 87: 80] <= B63[15: 8];
    hash[ 79: 72] <= B63[23:16];
    hash[ 71: 64] <= B63[31:24];
    
    hash[ 63: 56] <= C63[ 7: 0];
    hash[ 55: 48] <= C63[15: 8];
    hash[ 47: 40] <= C63[23:16];
    hash[ 39: 32] <= C63[31:24];
    
    hash[ 31: 24] <= D63[ 7: 0];
    hash[ 23: 16] <= D63[15: 8];
    hash[ 15:  8] <= D63[23:16];
    hash[  7:  0] <= D63[31:24];
    counter_out <= counter63;
  end
end

// stage 64neg
always @(negedge CLK)
begin
  if (hash == target_hash)
    hash_equal_neg <= 1'h1;
end

// stage 64pos
always @(posedge CLK)
begin
  if (hash == target_hash)
    hash_equal_pos <= 1'h1;
end

assign hash_equal = hash_equal_pos | hash_equal_neg;

sr_ff ff(.CLK(CLK),
  .set(hash_equal),
  .reset(reset),
  .Q(found)
);

//assign counter_out = counter63;

//assign hash[127:120] = A63[ 7: 0];
//assign hash[119:112] = A63[15: 8];
//assign hash[111:104] = A63[23:16];
//assign hash[103: 96] = A63[31:24];

//assign hash[ 95: 88] = B63[ 7: 0];
//assign hash[ 87: 80] = B63[15: 8];
//assign hash[ 79: 72] = B63[23:16];
//assign hash[ 71: 64] = B63[31:24];

//assign hash[ 63: 56] = C63[ 7: 0];
//assign hash[ 55: 48] = C63[15: 8];
//assign hash[ 47: 40] = C63[23:16];
//assign hash[ 39: 32] = C63[31:24];

//assign hash[ 31: 24] = D63[ 7: 0];
//assign hash[ 23: 16] = D63[15: 8];
//assign hash[ 15:  8] = D63[23:16];
//assign hash[  7:  0] = D63[31:24];

endmodule
