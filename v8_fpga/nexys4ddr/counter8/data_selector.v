module data_selector(
    input CLK,
    input reset,
    input [3:0] selector,
    output reg [127:0] dataOut
    );
    
always @(posedge CLK) 
    begin
    if (reset) 
      dataOut <=  128'h00000000000000000000000000000000;
    else
    case (selector)
      4'b0000 : dataOut <=  128'hf1d3ff8443297732862df21dc4e57262;   //  ./4bytes/00000000.bin     
      4'b0001 : dataOut <=  128'hf1450306517624a57eafbbf8ed995985;   //  ./4bytes/00000001.bin     
      4'b0010 : dataOut <=  128'hf11177d2ec63d995fb4ac628e0d782df;   //  ./4bytes/00000002.bin 
      4'b0011 : dataOut <=  128'ha4300bfbc02f3d4a1e47d4caf91fd29e;   //  ./4bytes/00000010.bin
      4'b0100 : dataOut <=  128'h2ab4b906fabd1c154d3d8fd77942028e;   //  ./4bytes/00000100.bin
      4'b0101 : dataOut <=  128'h7f78dc6c2d96c9312550124899899b94;   //  ./4bytes/00001000.bin
      4'b0110 : dataOut <=  128'h03bf3e510fa084f991c7a5e607d9712b;   //  ./4bytes/00010000.bin
      4'b0111 : dataOut <=  128'h08d6c05a21512a79a1dfeb9d2a8f262f;   //  ./4bytes/01020304.bin     
      4'b1000 : dataOut <=  128'h8e2b74ecfe5d826692b79830932f2165;   //  ./4bytes/01234567.bin     
      4'b1001 : dataOut <=  128'h19308bf325717913757f1584fae31c4a;   //  ./4bytes/01ed6e54.bin     
      4'b1010 : dataOut <=  128'hc6f00988430dbc8e83a7bc7ab5256346;   //  ./4bytes/484f4c41_HOLA.bin
      4'b1011 : dataOut <=  128'hd96ff7938f84d310c9d25805bfdbabb2;   //  ./4bytes/bebacafe.bin
      4'b1100 : dataOut <=  128'hf1b8fe6435ac5a4b3c5dc461f7e9bcfe;   //  ./4bytes/bebafeca.bin
      4'b1101 : dataOut <=  128'h2d1bbde2acac0afd07646d98154f402e;   //  ./4bytes/cafebabe.bin           
      4'b1110 : dataOut <=  128'h0290a09d67739bb3a69914532acfaf2d;   //  ./4bytes/f0000000.bin     
      4'b1111 : dataOut <=  128'ha54f0041a9e15b050f25c463f1db7449;   //  ./4bytes/ffffffff.bin
      default : dataOut <=  128'ha54f0041a9e15b050f25c463f1db7449;
    endcase    
  end
endmodule
