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

wire [28:0]counter_out;
wire [28:0]counter19;
wire [28:0]counter41;
wire [28:0]counter48;

wire [31:0]  pipeline_counter;

wire step_debounced;
wire enabled;
wire found0, found1, found2, found3, found4, found5, found6, found7, found8, found9, found10, found11;

assign enabled = enable_switch & ~ (found0 | found1 | found2 | found3 | found4 |found5 | found6 | found7
                                    | found8 | found9 );
assign found_led = found0 | found1 | found2 | found3 | found4 |found5 | found6 | found7 | 
                                    found8 | found9 ;

counter counter(.CLK(CLK),
  .reset(reset_button),
  .step(step_debounced),
  .enable(enabled),
  .count(counter_out),
  .running(running_led),
  .count19(counter19),
  .count41(counter41),
  .count48(counter48),
  .done(done_led)
);

//counter_pipeline counter_pipeline (.CLK(CLK),
// .counter_in({counter_out,3'b000}),
// .counter19(counter19),
// .counter41(counter41),
// .counter48(counter48)
//);

pipeline pipeline0(.CLK(CLK),
  .counter_in({counter_out,4'b0000}),
  .target_hash(target_selected),
  .reset(reset_button),
  .counter19_in(counter19),
  .counter41_in(counter41),
  .counter48_in(counter48),
  .found(found0)
);

pipeline pipeline1(.CLK(CLK),
  .counter_in({counter_out,4'b0001}),
  .target_hash(target_selected),
  .reset(reset_button),
  .counter19_in({counter19,4'b0001}),
  .counter41_in({counter41,4'b0001}),
  .counter48_in({counter48,4'b0001}),
  .found(found1)
);

pipeline pipeline2(.CLK(CLK),
  .counter_in({counter_out,4'b0010}),
  .target_hash(target_selected),
  .reset(reset_button),
  .counter19_in({counter19,4'b0010}),
  .counter41_in({counter41,4'b0010}),
  .counter48_in({counter48,4'b0010}),
  .found(found2)
);

pipeline pipeline3(.CLK(CLK),
  .counter_in({counter_out,4'b0011}),
  .target_hash(target_selected),
  .reset(reset_button),
  .counter19_in({counter19,4'b0011}),
  .counter41_in({counter41,4'b0011}),
  .counter48_in({counter48,4'b0011}),
  .found(found3)
);

pipeline pipeline4(.CLK(CLK),
  .counter_in({counter_out,4'b0100}),
  .target_hash(target_selected),
  .reset(reset_button),
  .counter19_in({counter19,4'b0100}),
  .counter41_in({counter41,4'b0100}),
  .counter48_in({counter48,4'b0100}),
  .found(found4)
);

pipeline pipeline5(.CLK(CLK),
  .counter_in({counter_out,4'b0101}),
  .target_hash(target_selected),
  .reset(reset_button),
  .counter19_in({counter19,4'b0100}),
  .counter41_in({counter41,4'b0100}),
  .counter48_in({counter48,4'b0100}),
  .found(found5)
);

pipeline pipeline6(.CLK(CLK),
  .counter_in({counter_out,4'b0110}),
  .target_hash(target_selected),
  .reset(reset_button),
  .counter19_in({counter19,4'b0110}),
  .counter41_in({counter41,4'b0110}),
  .counter48_in({counter48,4'b0110}),
  .found(found6)
);

pipeline pipeline7(.CLK(CLK),
  .counter_in({counter_out,4'b0111}),
  .target_hash(target_selected),
  .reset(reset_button),
  .counter19_in({counter19,4'b0111}),
  .counter41_in({counter41,4'b0111}),
  .counter48_in({counter48,4'b0111}),
  .found(found7)
);


pipeline pipeline8(.CLK(CLK),
  .counter_in({counter_out,4'b1000}),
  .target_hash(target_selected),
  .reset(reset_button),
  .counter19_in({counter19,4'b1000}),
  .counter41_in({counter41,4'b1000}),
  .counter48_in({counter48,4'b1000}),
  .found(found8)
);

pipeline pipeline9(.CLK(CLK),
  .counter_in({counter_out,4'b1001}),
  .target_hash(target_selected),
  .reset(reset_button),
  .counter19_in({counter19,4'b1001}),
  .counter41_in({counter41,4'b1001}),
  .counter48_in({counter48,4'b1001}),
  .found(found9)
);


debouncer step_debouncer(.CLK(CLK),
  .switch_input(step_button),
  .trans_up(step_debounced)
);

display_7_seg display(.CLK (CLK), 
  .number_in({counter_out,3'b000}),
  .SEG (SEG),
  .DIGIT (DIGIT)
);

data_selector data_selector(.CLK(CLK),
  .reset(reset_button),
  .selector(target_switch),
  .dataOut(target_selected)
);

endmodule