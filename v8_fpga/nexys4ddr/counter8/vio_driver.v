module vio_driver(
  input        CLK
);

// virtual outputs
   wire        status_paused;
   wire        status_running;
   wire        status_warming;
   wire        status_found;
   wire        status_done;
   wire [31:0] target;

// virtual inputs
   wire           enable_switch;
   wire           reset_switch;   
   wire [  4 : 0] probe_in0;
   wire [ 31 : 0] probe_in1;
   wire [  1 : 0] probe_out0;
   wire [ 31 : 0] probe_out1;
   wire [ 31 : 0] probe_out2;
   wire [ 31 : 0] probe_out3;
   wire [ 31 : 0] probe_out4;
   
// VIO patching
   assign probe_in0  = { status_paused,
                         status_running,
                         status_warming,
                         status_found,
                         status_done
                       };
   assign probe_out0 = { reset_switch,
                         enable_switch
                       };
   assign probe_in1  = target;
   

vio_0 vio_driver (
  .clk(CLK),                // input wire clk
  .probe_in0(probe_in0),    // input wire [4 : 0] probe_in0
  .probe_in1(probe_in1),    // input wire [31 : 0] probe_in1
  .probe_out0(probe_out0),  // output wire [0 : 0] probe_out0
  .probe_out1(probe_out1),  // output wire [31 : 0] probe_out1
  .probe_out2(probe_out2),  // output wire [31 : 0] probe_out2
  .probe_out3(probe_out3),  // output wire [31 : 0] probe_out3
  .probe_out4(probe_out4)   // output wire [31 : 0] probe_out4  
);

driver u_driver(
  .CLK            (CLK),       
  .CPU_RESETN     (reset_switch),      
  .enable_switch  (enable_switch),      
  .target_selected({probe_out1,probe_out2,probe_out3,probe_out4}),
  .target         (target),
  .status_paused  (status_paused),
  .status_running (status_running),
  .status_warming (status_warming),
  .status_found   (status_found),
  .status_done    (status_done)     
  );

endmodule