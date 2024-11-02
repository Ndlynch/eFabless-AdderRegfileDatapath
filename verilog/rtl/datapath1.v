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

module datapath1(
    input i_CLK, i_ALUSrc, i_AddSub, i_RST,
    input[4:0] i_RA0, i_RA1, i_WA, 
    input[15:0] i_Im,
    output o_Cout, o_Overflow,
    output[31:0] o_ALUout
    );
    
    wire[31:0] q_ALUout, q_Q0, q_Q1, q_MUXout;

    regfile regs(
        .i_CLK(i_CLK),
        .i_WE(1'b1),
        .i_RST(i_RST),
	    .i_D(q_ALUout),
	    .i_S(i_WA),
        .i_R0(i_RA0),
        .i_R1(i_RA1),
	    .o_Q0(q_Q0),
        .o_Q1(q_Q1)
    );

    mux32bit_1bitselect mux(
	    .i_A(q_Q1),
        .i_B({{16{i_Im[15]}}, i_Im}),
	    .i_select(i_ALUSrc),
	    .o_Out(q_MUXout)
	);

    add_sub as(
		.i_A(q_Q0),
        .i_B(q_MUXout),
		.i_Select(i_AddSub),
		.o_Out(q_ALUout),
		.o_Cout(o_Cout),
        .o_Overflow(o_Overflow)
		);

        assign o_ALUout = q_ALUout;

endmodule
