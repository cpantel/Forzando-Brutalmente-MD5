module vio_driver(
  input        CLK,
  input        CPU_RESETN
);
//   reg  CLK;
//   reg  reset_button;
//   reg  enable_switch;
//   reg  [3:0]target_switch;
//   wire [7:0] SEG;
//   wire [7:0] DIGIT;
//   wire status_paused;
//   wire status_running;
//   wire status_warming;
//   wire status_found;
//   wire status_done;


   wire status_paused;
   wire status_running;
   wire status_warming;
   wire status_found;
   wire status_done;
   wire [31:0] target;
   
   wire enable_switch;
   wire [3:0] target_switch;
   
   wire [ 4 : 0] probe_in0;
   wire [31 : 0] probe_in1;
   wire [ 4 : 0] probe_out0;
   
   assign probe_in0  = { status_paused, status_running, status_warming, status_found, status_done };
   assign probe_out0 = { enable_switch, target_switch };
   assign probe_in1  = target;
   

vio_0 vio_driver (
  .clk(CLK),                // input wire clk
  .probe_in0(probe_in0),    // input wire [4 : 0] probe_in0
  .probe_in1(probe_in1),    // input wire [31 : 0] probe_in1
  .probe_out0(probe_out0)   // output wire [4 : 0] probe_out0
);

driver u_driver(
  .CLK            (CLK),       
  .CPU_RESETN     (CPU_RESETN),      
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