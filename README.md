# Caravel User Project

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0) [![UPRJ_CI](https://github.com/efabless/caravel_project_example/actions/workflows/user_project_ci.yml/badge.svg)](https://github.com/efabless/caravel_project_example/actions/workflows/user_project_ci.yml) [![Caravel Build](https://github.com/efabless/caravel_project_example/actions/workflows/caravel_build.yml/badge.svg)](https://github.com/efabless/caravel_project_example/actions/workflows/caravel_build.yml)

This is a recreation of a simple Register File and Adder datapath to get a farmiliarity with the eFabless process for more advanced projects down the line. This is equivalent to a datapath in CprE 3810's lab 2 at Iowa State University.

Clock is controlled by la_data_in[64] when la_oenb[64] = 1
Clock is controlled by la_data_in[65] when la_oenb[65] = 1

Inputs:
ALUSrc Select = la_data_in[32]
AddSub Select = la_data_in[31]
RAO = la_data_in[30:26]
RA1 = la_data_in[25:21]
WA = la_data_in[20:16]
Immediate = la_data_in[15:0]

Outputs:
io_out[37:6] = la_data_out[127:96] = ALUout
la_data_out[95] = Cout
la_data_out[94] = Overflow

Test is modified la_test2 from sample project.