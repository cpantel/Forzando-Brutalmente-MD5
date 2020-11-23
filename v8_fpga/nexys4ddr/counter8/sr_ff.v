module sr_ff (
  input CLK, 
  input set,
  input reset,
  output reg Q = 1'b0
);
always @ (posedge CLK)
begin
  if (reset)
    Q <= 1'b0;
  else if (set)
    Q <= 1'b1;
end
endmodule
