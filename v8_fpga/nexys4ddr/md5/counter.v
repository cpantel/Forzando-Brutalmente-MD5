module counter(
   input CLK,
   input reset,
   input enable,
   input step,
   output reg [31:0] count,
   output reg running,
   output reg done
);

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
  else if (count == 32'hffffffff)
  begin
    running <= 0;
    done    <= 1;
  end
  else if (enable & ^ done) 
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
