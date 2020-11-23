module MD5(
    input CLK,
    input reset_button,
    input step_button,
    input enable_switch,
    input selectA_switch,
    input selectB_switch,
    input selectC_switch,
    input selectD_switch,
    input selectPipeline_switch,
    input selectCounter_switch,
    input [5:0] stagesel_switch,
    output [7:0] SEG,
    output [7:0] DIGIT,
    output running_led,
    output running_pin,
    output done_led,
    output done_pin,
    output found_led,
    output found_pin
    );

 
wire reset_debounced;
wire running;
wire done;
reg found = 0;

wire step_debounced;
wire enable_debounced;

wire done_output;



wire [31:0]  counter_out;
wire [31:0]  pipeline_counter_out;
wire [127:0] pipeline_hash;
wire [31:0]  data_selector_2_display;

//reg [127:0] target_hash = 127'hf1d3ff8443297732862df21dc4e57262;  //  ./4bytes/00000000.bin
//reg [127:0] target_hash = 127'hf1450306517624a57eafbbf8ed995985;  //  ./4bytes/00000001.bin
reg [127:0] target_hash = 127'hf11177d2ec63d995fb4ac628e0d782df;  //  ./4bytes/00000002.bin
//reg [127:0] target_hash = 127'h08d6c05a21512a79a1dfeb9d2a8f262f;  //  ./4bytes/01020304.bin
//  reg [127:0] target_hash = 127'h8e2b74ecfe5d826692b79830932f2165;  //  ./4bytes/01234567.bin
//reg [127:0] target_hash = 127'h19308bf325717913757f1584fae31c4a;  //  ./4bytes/01ed6e54.bin
//reg [127:0] target_hash = 127'hc6f00988430dbc8e83a7bc7ab5256346;  //  ./4bytes/484f4c41_HOLA.bin
//reg [127:0] target_hash = 127'hf1b8fe6435ac5a4b3c5dc461f7e9bcfe;  //  ./4bytes/bebafeca.bin
//reg [127:0] target_hash = 127'h2d1bbde2acac0afd07646d98154f402e;  //  ./4bytes/cafebabe.bin
//reg [127:0] target = 127'h0290a09d67739bb3a69914532acfaf2d;  //  ./4bytes/f0000000.bin
//reg [127:0] target_hash = 127'ha54f0041a9e15b050f25c463f1db7449;  //  ./4bytes/ffffffff.bin

always @(posedge CLK)
begin
  if ( target_hash == pipeline_hash ) 
    found = 1'b1;
end


//sr_ff found_ff(.CLK (CLK),
//  .reset(reset_debounced),
//  .set(found),
//  .Q(found_output)
//);

//sr_ff done_ff(.CLK (CLK),
//  .reset(reset_debounced),
//  .set(done),
//  .Q(done_output)
//);

debouncer debouncer_enable(.CLK (CLK),
  .switch_input(enable_switch),
  .state (enable_debounced)
);

debouncer debouncer_reset(.CLK (CLK),
  .switch_input(reset_button),
  .trans_up (reset_debounced)
);

debouncer debouncer_step(.CLK (CLK),
  .switch_input(step_button),
  .trans_up (step_debounced)
);

assign running_led = running;
assign running_pin = running;
assign done_led    = done;
assign done_pin    = done;
assign found_led   = found;
assign found_pin   = found;

data_selector data_selector(.CLK(CLK),
  .data0(counter_out),
  .data1(pipeline_counter_out), 
  .data2(pipeline_hash[127:96]),
  .data3(pipeline_hash[95:64]),
  .data4(pipeline_hash[63:32]),
  .data5(pipeline_hash[31:0]),
  .select0(selectCounter_switch),
  .select1(selectPipeline_switch),
  .select2(selectA_switch),
  .select3(selectB_switch),
  .select4(selectC_switch),
  .select5(selectD_switch),
  .dataOut(data_selector_2_display)
);

display_7_seg display(.CLK (CLK), 
  .number_in(data_selector_2_display),
  .SEG (SEG), .DIGIT (DIGIT)
);

counter counter(.CLK (CLK ),
   .reset(reset_debounced),
   .enable(enable_debounced),
   .step(step_debounced),   
   .count(counter_out),
   .running(running),
   .done(done) 
);

//double_pipeline pipeline(.CLK (CLK & enable_debounced | step_debounced),
double_pipeline pipeline(.CLK (CLK),
  .counter_in(counter_out),
  .counter_out(pipeline_counter_out),
  .hash(pipeline_hash)
);	

endmodule

//alarm alarm_running(.CLK (CLK),
//  .BUZZER (running_led),
//  .enable (running)
//);

//alarm alarm_done(.CLK (CLK),
//  .BUZZER (done_led),
//  .enable (done_output)
//);

//alarm alarm_found(.CLK (CLK),
//  .BUZZER (found_led),
//  .enable (found_output)
//);
