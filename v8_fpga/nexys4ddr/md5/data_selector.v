module data_selector(
    input CLK,
    input [31:0] data0,
    input [31:0] data1,
    input [31:0] data2,
    input [31:0] data3,
    input [31:0] data4,
    input [31:0] data5,
    input select0,
    input select1,
    input select2,
    input select3,
    input select4,
    input select5,
    output reg [31:0] dataOut
    );
    
always @(posedge CLK) 
    begin
      case ({select0, select1, select2, select3, select4, select5 })
      6'b100000 : dataOut = data0;
      6'b010000 : dataOut = data1;
      6'b001000 : dataOut = data2;
      6'b000100 : dataOut = data3;
      6'b000010 : dataOut = data4;
      6'b000001 : dataOut = data5;
      default  : dataOut = 32'hfefefefe; 
      endcase    
    end
endmodule
