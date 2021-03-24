module driver(
  input        CLK,
  input        CPU_RESETN,
  input        enable_switch,
  input  [127:0] target_selected,  
  output [31:0] target,
  output reg status_paused,
  output reg status_running,
  output reg status_warming,
  output reg status_found,
  output reg status_done
  
);


wire  [28:0] counter_out;
assign target = {counter_out,3'b000};

wire found0, found1, found2, found3, found4, found5, found6, found7;
wire found;
assign found = ( found0 | found1 | found2 | found3 | found4 | found5 | found6 | found7 );


wire warming_up_done;

wire reset;
assign reset = !CPU_RESETN;


parameter state_start          = 7'b00000001;
parameter state_warm_up        = 7'b00000010;
parameter state_warm_up_paused = 7'b00000100;
parameter state_running        = 7'b00001000;
parameter state_running_paused = 7'b00010000;
parameter state_found          = 7'b00100000;
parameter state_not_found      = 7'b01000000;

reg [6:0] state = state_start;

//always @(posedge CLK) begin
//  if (reset) begin
//    target = 31'h00000000;
//  end else 
//    target = {counter_out,3'b000};
//end


always @(posedge CLK) begin
  if (reset) begin
     state           <= state_start;
     status_paused   <= 1'b1;
     status_running  <= 1'b0; 
     status_warming  <= 1'b0;
     status_found    <= 1'b0;
     status_done     <= 1'b0;     
     
  end
  else begin
     case (state)
        state_start : begin
           if (enable_switch)
              state <= state_warm_up;
           status_paused   <= 1'b1;
           status_running  <= 1'b0; 
           status_warming  <= 1'b0;
           status_found    <= 1'b0;
           status_done     <= 1'b0;                   
        end
        
        state_warm_up : begin
           if (warming_up_done)
              state <= state_running;
           else if (!enable_switch)
              state <= state_warm_up_paused;
           status_paused   <= 1'b0;
           status_running  <= 1'b1; 
           status_warming  <= 1'b1;
           status_found    <= 1'b0;
           status_done     <= 1'b0;     
        end
        
        state_warm_up_paused : begin
           if (enable_switch )
              state <= state_warm_up;
           status_paused   <= 1'b1;
           status_running  <= 1'b1; 
           status_warming  <= 1'b1;
           status_found    <= 1'b0;
           status_done     <= 1'b0;     
        end
        
        state_running : begin
           if (found)
              state <= state_found;
           else if (counter_done)
              state <= state_not_found;
           else if (!enable_switch)
              state <= state_running_paused;
           status_paused   <= 1'b0;
           status_running  <= 1'b1; 
           status_warming  <= 1'b0;
           status_found    <= 1'b0;
           status_done     <= 1'b0;
        end
        
        state_running_paused : begin
           if (enable_switch)
              state <= state_running;
           status_paused   <= 1'b1;
           status_running  <= 1'b1; 
           status_warming  <= 1'b0;
           status_found    <= 1'b0;
           status_done     <= 1'b0;
        end
        
        state_found : begin
           status_paused   <= 1'b0;
           status_running  <= 1'b0; 
           status_warming  <= 1'b0;
           status_found    <= 1'b1;
           status_done     <= 1'b1;
        end
        
        state_not_found : begin
           status_paused   <= 1'b0;
           status_running  <= 1'b0; 
           status_warming  <= 1'b0;
           status_found    <= 1'b0;
           status_done     <= 1'b1;
        end
        
     endcase
  end							
end							

warmup_counter u_warm_upcounter(
   .CLK(CLK),
   .reset(reset),
   .enable(status_warming),
   .done(warming_up_done)
);

counter counter(.CLK(CLK),
  .reset(reset),
  .step(0),
  .enable(status_running),
  .counter_out(counter_out),
  .running(running_led),
  .done(counter_done)
);

pipeline pipeline0(.CLK(CLK),
  .counter_in({counter_out,3'b000}),
  .target_hash(target_selected),
  .reset(reset),
  .found(found0)
);

pipeline pipeline1(.CLK(CLK),
  .counter_in({counter_out,3'b001}),
  .target_hash(target_selected),
  .reset(reset),
  .found(found1)
);

pipeline pipeline2(.CLK(CLK),
  .counter_in({counter_out,3'b010}),
  .target_hash(target_selected),
  .reset(reset),
  .found(found2)
);

pipeline pipeline3(.CLK(CLK),
  .counter_in({counter_out,3'b011}),
  .target_hash(target_selected),
  .reset(reset),
  .found(found3)
);

pipeline pipeline4(.CLK(CLK),
  .counter_in({counter_out,3'b100}),
  .target_hash(target_selected),
  .reset(reset),
  .found(found4)
);

pipeline pipeline5(.CLK(CLK),
  .counter_in({counter_out,3'b101}),
  .target_hash(target_selected),
  .reset(reset),
  .found(found5)
);

pipeline pipeline6(.CLK(CLK),
  .counter_in({counter_out,3'b110}),
  .target_hash(target_selected),
  .reset(reset),
  .found(found6)
);

pipeline pipeline7(.CLK(CLK),
  .counter_in({counter_out,3'b111}),
  .target_hash(target_selected),
  .reset(reset),
  .found(found7)
);


endmodule