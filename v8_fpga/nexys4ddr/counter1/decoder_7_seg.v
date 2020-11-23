module decoder_7_seg(
	input CLK,
   input [3:0] D,
   output reg [7:0] SEG
   );

always @(posedge CLK) 
begin
	case(D)
    4'h0: SEG <= 8'b00000011;
    4'h1: SEG <= 8'b10011111; 
    4'h2: SEG <= 8'b00100101;
    4'h3: SEG <= 8'b00001101;
    4'h4: SEG <= 8'b10011001;
    4'h5: SEG <= 8'b01001001;
    4'h6: SEG <= 8'b01000001;
    4'h7: SEG <= 8'b00011111;
    4'h8: SEG <= 8'b00000001;
    4'h9: SEG <= 8'b00001001;
    4'ha: SEG <= 8'b00000101; // 8'b00010001;
    4'hb: SEG <= 8'b11000001;
    4'hc: SEG <= 8'b11100101; // 8'b01100011; 
    4'hd: SEG <= 8'b10000101;
    4'he: SEG <= 8'b00100001; // 8'b01100001;
    4'hf: SEG <= 8'b01110001;                    
    default: SEG <= 8'b11111110;
	endcase
end

endmodule
