module warmup_counter
(
   input CLK,
   input reset,
   input enable,
   output reg done
);

reg [7:0]count;

always @(posedge CLK) 
begin
  if (reset) begin
    count      <= 8'b00000000;
    done       <= 1'b0;
  end else begin
    if (count == 8'b00010000)
      done    <= 1;
    else if (enable & ! done) 
      count   <= count + 1;
  end
end
endmodule
