module counter(
   input CLK,
   input reset,
   input enable,
   input step,
   output reg [31:0] count,
   output reg running,
   output reg done
);

localparam STOP = 0, RUNNING = 1, DONE = 2;

reg state       = RUNNING;
initial count   = 0;
initial running = 0;
initial done    = 0;

always @(posedge CLK)
begin
  case (state)
    STOP : begin
      running <= 0;
      if (enable)
        state <= RUNNING;
      else if (step)
        count <= count + 1;
    end
    RUNNING : begin
      running <= 1;
      count   <= count + 1;
      if (count == 0 )
        state <= DONE;
      else if (~enable )
        state <= STOP;
      else if (reset)
      begin
        state <= STOP;
        count <= 0;
      end
    end
    DONE :  begin
      running <= 0;
      done    <= 1;
      if (reset)
        state <= STOP;
    end
    default : begin
      state <= STOP;
    end
  endcase
end
endmodule
