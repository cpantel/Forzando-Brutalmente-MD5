module counter_pipeline (
  input  CLK,
  input  [31:0]counter_in,
  output reg [31:0]counter19,
  output reg [31:0]counter41,
  output reg [31:0]counter48
);

reg [31:0] counter00;
reg [31:0] counter01;
reg [31:0] counter02;
reg [31:0] counter03;
reg [31:0] counter04;
reg [31:0] counter05;
reg [31:0] counter06;
reg [31:0] counter07;
reg [31:0] counter08;
reg [31:0] counter09;
reg [31:0] counter10;
reg [31:0] counter11;
reg [31:0] counter12;
reg [31:0] counter13;
reg [31:0] counter14;
reg [31:0] counter15;
reg [31:0] counter16;
reg [31:0] counter17;
reg [31:0] counter18;
reg [31:0] counter20;
reg [31:0] counter21;
reg [31:0] counter22;
reg [31:0] counter23;
reg [31:0] counter24;
reg [31:0] counter25;
reg [31:0] counter26;
reg [31:0] counter27;
reg [31:0] counter28;
reg [31:0] counter29;
reg [31:0] counter30;
reg [31:0] counter31;
reg [31:0] counter32;
reg [31:0] counter33;
reg [31:0] counter34;
reg [31:0] counter35;
reg [31:0] counter36;
reg [31:0] counter37;
reg [31:0] counter38;
reg [31:0] counter39;
reg [31:0] counter40;
reg [31:0] counter42;
reg [31:0] counter43;
reg [31:0] counter44;
reg [31:0] counter45;
reg [31:0] counter46;
reg [31:0] counter47;
reg [31:0] counter49;
reg [31:0] counter50;
reg [31:0] counter51;
reg [31:0] counter52;
reg [31:0] counter53;
reg [31:0] counter54;
reg [31:0] counter55;
reg [31:0] counter56;
reg [31:0] counter57;
reg [31:0] counter58;
reg [31:0] counter59;
reg [31:0] counter60;
reg [31:0] counter61;
reg [31:0] counter62;
reg [31:0] counter63;
// stage 00
always @(posedge CLK)
begin
  counter00[ 7: 0] = counter_in[31:24];
  counter00[15: 8] = counter_in[23:16];
  counter00[23:16] = counter_in[15: 8];
  counter00[31:24] = counter_in[ 7: 0];
end

// stage 01
always @(posedge CLK)
begin
  counter01 <= counter00;
end


// stage 02
always @(posedge CLK)
begin
  counter02 <= counter01;
end


// stage 03
always @(posedge CLK)
begin
  counter03 <= counter02;
end


// stage 04
always @(posedge CLK)
begin
  counter04 <= counter03;
end


// stage 05
always @(posedge CLK)
begin
  counter05 <= counter04;
end


// stage 06
always @(posedge CLK)
begin
  counter06 <= counter05;
end


// stage 07
always @(posedge CLK)
begin
  counter07 <= counter06;
end


// stage 08
always @(posedge CLK)
begin
  counter08 <= counter07;
end


// stage 09
always @(posedge CLK)
begin
  counter09 <= counter08;
end


// stage 10
always @(posedge CLK)
begin
  counter10 <= counter09;
end


// stage 11
always @(posedge CLK)
begin
  counter11 <= counter10;
end


// stage 12
always @(posedge CLK)
begin
  counter12 <= counter11;
end


// stage 13
always @(posedge CLK)
begin
  counter13 <= counter12;
end


// stage 14
always @(posedge CLK)
begin
  counter14 <= counter13;
end


// stage 15
always @(posedge CLK)
begin
  counter15 <= counter14;
end


// stage 16
always @(posedge CLK)
begin
  counter16 <= counter15;
end


// stage 17
always @(posedge CLK)
begin
  counter17 <= counter16;
end


// stage 18
always @(posedge CLK)
begin
  counter18 <= counter17;
end


// stage 19
always @(posedge CLK)
begin
  counter19 <= counter18;
end


// stage 20
always @(posedge CLK)
begin
  counter20 <= counter19;
end


// stage 21
always @(posedge CLK)
begin
  counter21 <= counter20;
end


// stage 22
always @(posedge CLK)
begin
  counter22 <= counter21;
end


// stage 23
always @(posedge CLK)
begin
  counter23 <= counter22;
end


// stage 24
always @(posedge CLK)
begin
  counter24 <= counter23;
end


// stage 25
always @(posedge CLK)
begin
  counter25 <= counter24;
end


// stage 26
always @(posedge CLK)
begin
  counter26 <= counter25;
end


// stage 27
always @(posedge CLK)
begin
  counter27 <= counter26;
end


// stage 28
always @(posedge CLK)
begin
  counter28 <= counter27;
end


// stage 29
always @(posedge CLK)
begin
  counter29 <= counter28;
end


// stage 30
always @(posedge CLK)
begin
  counter30 <= counter29;
end


// stage 31
always @(posedge CLK)
begin
  counter31 <= counter30;
end


// stage 32
always @(posedge CLK)
begin
  counter32 <= counter31;
end


// stage 33
always @(posedge CLK)
begin
  counter33 <= counter32;
end


// stage 34
always @(posedge CLK)
begin
  counter34 <= counter33;
end


// stage 35
always @(posedge CLK)
begin
  counter35 <= counter34;
end


// stage 36
always @(posedge CLK)
begin
  counter36 <= counter35;
end


// stage 37
always @(posedge CLK)
begin
  counter37 <= counter36;
end


// stage 38
always @(posedge CLK)
begin
  counter38 <= counter37;
end


// stage 39
always @(posedge CLK)
begin
  counter39 <= counter38;
end


// stage 40
always @(posedge CLK)
begin
  counter40 <= counter39;
end


// stage 41
always @(posedge CLK)
begin
  counter41 <= counter40;
end


// stage 42
always @(posedge CLK)
begin
  counter42 <= counter41;
end


// stage 43
always @(posedge CLK)
begin
  counter43 <= counter42;
end


// stage 44
always @(posedge CLK)
begin
  counter44 <= counter43;
end


// stage 45
always @(posedge CLK)
begin
  counter45 <= counter44;
end


// stage 46
always @(posedge CLK)
begin
  counter46 <= counter45;
end


// stage 47
always @(posedge CLK)
begin
  counter47 <= counter46;
end


// stage 48
always @(posedge CLK)
begin
  counter48 <= counter47;
end


// stage 49
always @(posedge CLK)
begin
  counter49 <= counter48;
end


// stage 50
always @(posedge CLK)
begin
  counter50 <= counter49;
end


// stage 51
always @(posedge CLK)
begin
  counter51 <= counter50;
end


// stage 52
always @(posedge CLK)
begin
  counter52 <= counter51;
end


// stage 53
always @(posedge CLK)
begin
  counter53 <= counter52;
end


// stage 54
always @(posedge CLK)
begin
  counter54 <= counter53;
end


// stage 55
always @(posedge CLK)
begin
  counter55 <= counter54;
end


// stage 56
always @(posedge CLK)
begin
  counter56 <= counter55;
end


// stage 57
always @(posedge CLK)
begin
  counter57 <= counter56;
end


// stage 58
always @(posedge CLK)
begin
  counter58 <= counter57;
end


// stage 59
always @(posedge CLK)
begin
  counter59 <= counter58;
end


// stage 60
always @(posedge CLK)
begin
  counter60 <= counter59;
end


// stage 61
always @(posedge CLK)
begin
  counter61 <= counter60;
end


// stage 62
always @(posedge CLK)
begin
  counter62 <= counter61;
end


// stage 63
always @(posedge CLK)
begin
  counter63 <= counter62;
end




endmodule
