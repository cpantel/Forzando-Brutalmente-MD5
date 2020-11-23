module driver(
  input CLK,
  input reset_button,
  input step_button,
  input enable_switch,
  input [3:0]target_switch,
  output [7:0] SEG,
  output [7:0] DIGIT,
  output running_led,
  output done_led,
  output found_led,
  output found_pin
);
wire [127:0] target_selected;

wire [31:0]  counter_out;
wire [31:0]  pipeline_counter;
wire [127:0] pipeline_hash;

wire step_debounced;
wire enabled;
wire found;

assign enabled = enable_switch & ~found;
assign found_led = found;
assign found_pin = found;

counter counter(.CLK(CLK),
  .reset(reset_button),
  .step(step_debounced),
  .enable(enabled),
  .count(counter_out),
  .running(running_led),
  .done(done_led)
);

pipeline pipeline(.CLK(CLK),
  .counter_in(counter_out),
  .target_hash(target_selected),
  .reset(reset_button),
  .counter_out(pipeline_counter),
  .found(found)
);

debouncer step_debouncer(.CLK(CLK),
  .switch_input(step_button),
  .trans_up(step_debounced)
);

display_7_seg display(.CLK (CLK), 
  .number_in(pipeline_counter),
  .SEG (SEG),
  .DIGIT (DIGIT)
);

data_selector data_selector(.CLK(CLK),
  .reset(reset_button),
  .selector(target_switch),
  .dataOut(target_selected)
);

endmodule