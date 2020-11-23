module counter(
   input CLK,
   input reset,
   input enable,
   input step,
   output reg [28:0] count,  // 8 => [28:0] , 16 => [27:0]
   output reg [28:0] count19,
   output reg [28:0] count41,
   output reg [28:0] count48, 
   output reg running,
   output reg done
);

initial count   = 0;
initial count19 = 29'h1FFFFFEC; // 8 => 1fffffff - 13 (19)
initial count41 = 29'h1FFFFFD6; // 8 => 1fffffff - 29 (41)
initial count48 = 29'h1FFFFFCF; // 8 => 1fffffff - 30 (48)
initial running = 0;
initial done    = 0;

always @(posedge CLK) 
begin
  if (reset) 
  begin
    count   <= 0;
    count19 <= 29'h1FFFFFEC;
    count41 <= 29'h1FFFFFD6;
    count48 <= 29'h1FFFFFCF;
    
    running <= 0;
    done    <= 0;
  end 
  else if (count == 29'h1fffffff)   // 8 => 29'h1fffffff, 16 => 28'h0fffffff
  begin
    running <= 0;
    done    <= 1;
  end
  else if (enable) 
  begin
    count   <= count   + 1;
    count19 <= count19 + 1;
    count41 <= count41 + 1;
    count48 <= count48 + 1;
    running <= 1;
    done    <= 0;
  end
  else if (step) 
  begin
    count   <= count + 1;
    count19 <= count19 + 1;
    count41 <= count41 + 1;
    count48 <= count48 + 1;
    running <= 0;
    done    <= 0;
  end
end
endmodule
