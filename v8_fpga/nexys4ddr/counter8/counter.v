module counter(
   input CLK,
   input reset,
   input enable,
   input step,
   output [28:0] counter_out,
   output reg running,
   output reg done
);

reg [29:0] count;
assign counter_out = count[28:0];
initial count   = 0;
initial running = 0;
initial done    = 0;

always @(posedge CLK) 
begin
  if (reset) 
  begin
    count   <= 0;
    running <= 0;
    done    <= 0;
  end 
  else if (count == 29'h1fffffff)
  begin
    running <= 0;
    done    <= 1;
  end
  else if (enable) 
  begin
    count   <= count + 1;
    running <= 1;
    done    <= 0;
  end
  else if (step) 
  begin
    count   <= count + 1;
    running <= 0;
    done    <= 0;
  end
end
endmodule
