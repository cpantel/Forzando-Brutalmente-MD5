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

wire [27:0]  counter_out;
wire [31:0]  pipeline_counter;

wire step_debounced;
wire enabled;
wire found0, found1, found2, found3, found4, found5, found6, found7, found8, found9, foundA, foundB, foundC, foundD, foundE, foundF;

assign enabled = enable_switch & ~ (found0 | found1 | found2 | found3 | found4 | found5 | found6 | found7 |
                                    found8 | found9 | foundA | foundB | foundC | foundD | foundE | foundF);
assign found_led = found0 | found1 | found2 | found3 | found4 |found5 | found6 | found7 |
                   found8 | found9 | foundA | foundB | foundC | foundD | foundE | foundF;

counter counter(.CLK(CLK),
  .reset(reset_button),
  .step(step_debounced),
  .enable(enabled),
  .count(counter_out),
  .running(running_led),
  .done(done_led)
);

pipeline pipeline0(.CLK(CLK),
  .counter_in({counter_out,4'b0000}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(found0)
);

pipeline pipeline1(.CLK(CLK),
  .counter_in({counter_out,4'b0001}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(found1)
);

pipeline pipeline2(.CLK(CLK),
  .counter_in({counter_out,4'b0010}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(found2)
);

pipeline pipeline3(.CLK(CLK),
  .counter_in({counter_out,4'b0011}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(found3)
);

pipeline pipeline4(.CLK(CLK),
  .counter_in({counter_out,4'b0100}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(found4)
);

pipeline pipeline5(.CLK(CLK),
  .counter_in({counter_out,4'b0101}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(found5)
);

pipeline pipeline6(.CLK(CLK),
  .counter_in({counter_out,4'b0110}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(found6)
);

pipeline pipeline7(.CLK(CLK),
  .counter_in({counter_out,4'b0111}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(found7)
);

pipeline pipeline8(.CLK(CLK),
  .counter_in({counter_out,4'b1000}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(found8)
);

pipeline pipeline9(.CLK(CLK),
  .counter_in({counter_out,4'b1001}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(found9)
);

pipeline pipelineA(.CLK(CLK),
  .counter_in({counter_out,4'b1010}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(foundA)
);

pipeline pipelineB(.CLK(CLK),
  .counter_in({counter_out,4'b1011}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(foundB)
);

pipeline pipelineC(.CLK(CLK),
  .counter_in({counter_out,4'b1100}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(foundC)
);

pipeline pipelineD(.CLK(CLK),
  .counter_in({counter_out,4'b1101}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(foundD)
);

pipeline pipelineE(.CLK(CLK),
  .counter_in({counter_out,4'b1110}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(foundE)
);

pipeline pipelineF(.CLK(CLK),
  .counter_in({counter_out,4'b1111}),
  .target_hash(target_selected),
  .reset(reset_button),
  //.counter_out(pipeline_counter),
  .found(foundF)
);


debouncer step_debouncer(.CLK(CLK),
  .switch_input(step_button),
  .trans_up(step_debounced)
);

display_7_seg display(.CLK (CLK), 
  .number_in({counter_out,4'b0000}),
  .SEG (SEG),
  .DIGIT (DIGIT)
);



data_selector data_selector(.CLK(CLK),
  .reset(reset_button),
  .selector(target_switch),
  .dataOut(target_selected)
);

endmodule
