module ft245_comm(
    input clk,        // clock from the FT232H/FT2232h board
    input rxf,        // rxf pin input from FT board
	 input [7:0] data, // parallel data bus from FT board
 
    output [7:0] led, // output to leds for debugging
	 output rd,			 // rd pin output to FT board
	 output oe			 // oe pin output to FT board
  );
// declare IO wire/registers   
wire clk;
wire rxf;
wire [7:0] data;

wire [7:0] led;
wire rd;
wire oe;

// declare internal variable registers
reg rd_r = 1'b1;
reg oe_r = 1'b1;
reg [1:0] cnt= 2'b0;
reg [7:0] data_r = 0;
   
always @(negedge clk) begin  	// process begins at FT clock negative edge
	if (rxf == 0 ) begin			// rxf engages following patterns with precise timings
		if(cnt != 3)begin      
		cnt <= cnt + 1;			// running a counter for time mangagements
		end
		if(cnt == 2) begin
			oe_r <= 1'b0;			// set oe_r register to Low once rxf was low and one neg clock time
		end
		if(cnt == 3) begin
			rd_r <= 1'b0;			// set rd_r register to Low at cnt == 3
		end
	end else begin					// reset rd_r, oe_r and cnt to default value and waits for rxf to go low
	 	rd_r <= 1'b1;
		oe_r <= 1'b1;
		cnt <= 0;
   end
end

always @(posedge clk)begin		// synchronizes data transfer with positive edge of FT clock
	if(rd_r == 0)begin			// once rd_r is low, which happens at cnt = 3
		data_r <= data;			// writes 8 bit data to data register
	end
end

assign led = data_r;				// outputs the data resigter to led pins for visualization
assign rd = rd_r;					// assign register value to output
assign oe = oe_r;					// assign register value to output
   
endmodule