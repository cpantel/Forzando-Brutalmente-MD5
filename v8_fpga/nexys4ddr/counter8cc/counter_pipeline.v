module counter_pipeline (
  input  CLK,
  input  [31:0]counter_in,
  output wire [31:0]counter19,
  output wire [31:0]counter41,
  output wire [31:0]counter48
);

reg [31:0] counter00;
reg [31:0] counter[63:0];
assign counter19 = counter[19];
assign counter41 = counter[41];
assign counter48 = counter[48];


integer p;
always @(posedge CLK)begin
  counter00[ 7: 0] = counter_in[31:24];
  counter00[15: 8] = counter_in[23:16];
  counter00[23:16] = counter_in[15: 8];
  counter00[31:24] = counter_in[ 7: 0];
  counter[0] = counter00;
  for(p = 1;p < 49;p = p+1)begin
    counter[p] = counter[p-1];
  end
end 

endmodule
