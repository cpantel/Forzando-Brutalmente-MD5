`timescale 1ns/100ps

module tb_driver();
   reg  CLK;
   reg  reset_button;
   reg  enable_switch;
   reg  [3:0]target_switch;
   wire [31:0] target;
   wire status_paused;
   wire status_running;
   wire status_warming;
   wire status_found;
   wire status_done;

always 
  #5 CLK = ~CLK;
  
initial begin
  CLK  = 1'b0;
  reset_button  = 1'b0;
  enable_switch = 1'b0;
//  target_switch = 4'b0000;
//  target_switch = 4'b0001;  // 0000 0001
//  target_switch = 4'b0010;  // 0000 0002
//  target_switch = 4'b0011;  // 0000 0010
//  target_switch = 4'b0100;  // 0000 0100
//  target_switch = 4'b0101;  // 0000 1000
  target_switch = 4'b0110;  // 0001 0000

  # 400 reset_button = 1'b1;
  # 400 enable_switch = 1'b1;
  # 1200;
    # 2000;
  $finish;
end

driver u_driver(
  .CLK            (CLK),       
  .CPU_RESETN     (reset_button),      
  .enable_switch  (enable_switch),      
  .target_switch  (target_switch),
  .target         (target),
  .status_paused  (status_paused),
  .status_running (status_running),
  .status_warming (status_warming),
  .status_found   (status_found),
  .status_done    (status_done)     
  );

endmodule