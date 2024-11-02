// SPDX-FileCopyrightText: 2020 Efabless Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// SPDX-License-Identifier: Apache-2.0

module regfile(
		input i_CLK, i_WE, i_RST,
		input[31:0] i_D,
		input[4:0] i_S, i_R0, i_R1,
		output[31:0] o_Q0, o_Q1
);
	integer i; //Used in for loop
	reg[31:0] Regs[31:0]; //Stores internal register values.

	always @(posedge i_CLK)
	begin
    	//Resets all registers
    	if(i_RST==1'b1) begin
			for(i = 0; i < 32; i = i + 1) begin
	    		Regs[i] <= 32'b0;
			end
    	end
    //Writes i_D to register i_S.
    else if(i_WE==1'b1)
	     Regs[i_S] <= i_D;
	end

	//Assigns outputs.
	assign o_Q0 = Regs[i_R0];
	assign o_Q1 = Regs[i_R1];

endmodule
