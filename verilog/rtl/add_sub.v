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
/*
Module to add and subtract 8 bit numbers.
i_Select = 0 gives the result of i_A + i_B and i_Select = 1 gives the result of i_A - i_B.
o_Out gives the result of the operation.
o_Cout gives the C out from the final adder.
o_Overflow outputs 1 if there is an arithmatic overflow.
*/
module add_sub(
		input [31:0] i_A,i_B,
		input i_Select,
		output reg[31:0] o_Out,
		output o_Cout, o_Overflow
		);
		
	integer i; //Used in for loop
	reg[32:0] carryIn; //Stores the carry outs from each adder
	always @(*) begin
		carryIn[0] = i_Select;
		//For loop computes the outputs for adder i.
		for(i = 0; i < 32; i = i + 1) begin
			o_Out[i] = carryIn[i] ^ (i_A[i] ^  (i_B[i] ^ i_Select)); //Sum
			carryIn[i+1] = (i_A[i] & (i_B[i] ^ i_Select)) + (carryIn[i] & (i_A[i] ^ (i_B[i] ^ i_Select)));  //Carry Out
		end

	end
	assign o_Overflow = carryIn[32] ^ carryIn[31];
	assign o_Cout = carryIn[32];

endmodule
