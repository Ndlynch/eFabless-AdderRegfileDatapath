/*
 * SPDX-FileCopyrightText: 2020 Efabless Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * SPDX-License-Identifier: Apache-2.0
 */

/* Runs the Following Test
addi  $1,  $0,  1 		# Place “1” in $1
addi  $2,  $0,  2		# Place “2” in $2
addi  $3,  $0,  3		# Place “3” in $3
addi  $4,  $0,  4		# Place “4” in $4
addi  $5,  $0,  5		# Place “5” in $5
addi  $6,  $0,  6		# Place “6” in $6
addi  $7,  $0,  7		# Place “7” in $7
addi  $8,  $0,  8		# Place “8” in $8
addi  $9,  $0,  9		# Place “9” in $9
addi  $10, $0,  10		# Place “10” in $10
add	  $11, $1,  $2		# $11 = $1 + $2
sub   $12, $11, $3 		# $12 = $11 - $3
add   $13, $12, $4		# $13 = $12 + $4
sub	  $14, $13, $5		# $14 = $13 - $5
add   $15, $14, $6		# $15 = $14 + $6
sub   $16, $15, $7		# $16 = $15 - $7
add   $17, $16, $8		# $17 = $16 + $8
sub   $18, $17, $9		# $18 = $17 - $9
add   $19, $18, $10 	        # $19 = $18 + $10
addi  $20, $0,  -35		# Place “-35” in $20
add   $21, $19, $20
*/

// This include is relative to $CARAVEL_PATH (see Makefile)
#include <defs.h>
#include <stub.c>

/*
	MPRJ LA Test:
		- Sets counter clk through LA[64]
		- Sets counter rst through LA[65] 
		- Observes count value for five clk cycle through LA[31:0]
*/
int clk = 0;
int i;

void main()
{
        /* Set up the housekeeping SPI to be connected internally so	*/
	/* that external pin changes don't affect it.			*/

	// reg_spimaster_config = 0xa002;	// Enable, prescaler = 2,
        reg_spi_enable = 1;
                                        // connect to housekeeping SPI

	// Connect the housekeeping SPI to the SPI master
	// so that the CSB line is not left floating.  This allows
	// all of the GPIO pins to be used for user functions.


	// All GPIO pins are configured to be output
	// Used to flad the start/end of a test 

        reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;

        reg_mprj_io_15 = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_14 = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_13 = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_12 = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_11 = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_10 = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_9  = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_8  = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_7  = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_5  = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_4  = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_3  = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_2  = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_1  = GPIO_MODE_USER_STD_OUTPUT;
        reg_mprj_io_0  = GPIO_MODE_USER_STD_OUTPUT;

        /* Apply configuration */
        reg_mprj_xfer = 1;
        while (reg_mprj_xfer == 1);

	// Configure All LA probes as inputs to the cpu 
	reg_la0_oenb = reg_la0_iena = 0x00000000;    // [31:0]
	reg_la1_oenb = reg_la1_iena = 0x00000000;    // [63:32]
	reg_la2_oenb = reg_la2_iena = 0x00000000;    // [95:64]
	reg_la3_oenb = reg_la3_iena = 0x00000000;    // [127:96]

	// Flag start of the test
	reg_mprj_datal = 0xAB600000;

        clk = !clk;
        reg_la2_data = 0x00000000 | clk;
	reg_la0_oenb = reg_la0_iena = 0xFFFFFFFF;    // [31:0]
	reg_la1_oenb = reg_la1_iena = 0x00000001;    // [63:32]
	// Configure LA[64] LA[65] as outputs from the cpu
	reg_la2_oenb = reg_la2_iena = 0x00000003; 

	// Set clk & reset to one
	reg_la2_data = 0x00000003;

        // DELAY
        for (i=0; i<5; i=i+1) {}

	// Toggle clk & de-assert reset
	for (i=0; i<12; i=i+1) {
		clk = !clk;
		reg_la2_data = 0x00000000 | clk;
	}
        
    //Instruction: 1
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0x00000000 | 1;
    reg_la0_data = 0x00000000 | 65537;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 1);

    //Instruction: 2
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0x00000000 | 1;
    reg_la0_data = 0x00000000 | 131074;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 2);

    //Instruction: 3
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0x00000000 | 1;
    reg_la0_data = 196611;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 3);

    //Instruction: 4
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 1;
    reg_la0_data = 262148;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 4);

    //Instruction: 5
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 1;
    reg_la0_data = 327685;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 5);

    //Instruction: 6
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 1;
    reg_la0_data = 393222;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 6);

    //Instruction: 7
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 1;
    reg_la0_data = 458759;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 7);

    //Instruction: 8
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 1;
    reg_la0_data = 524296;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 8);

    //Instruction: 9
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 1;
    reg_la0_data = 589833;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 9);

    //Instruction: 10
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 1;
    reg_la0_data = 655370;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 10);

    //Instruction: 11
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0;
    reg_la0_data = 72024064;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 3);

    //Instruction: 12
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0;
    reg_la0_data = 2892759040;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 0);

    //Instruction: 13
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0;
    reg_la0_data = 814546944;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 4);

    //Instruction: 14
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0;
    reg_la0_data = 3031302144;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != -1);

    //Instruction: 15
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0;
    reg_la0_data = 953090048;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 5);

    //Instruction: 16
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0;
    reg_la0_data = 3169845248;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != -2);

    //Instruction: 17
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0;
    reg_la0_data = 1091633152;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != 6);

    //Instruction: 18
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0;
    reg_la0_data = 3308388352;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != -3);

    //Instruction: 19
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0;
    reg_la0_data = 1230176256;


    clk = !clk;
    reg_la2_data = 0x00000000 | clk;
    //while(reg_la3_data != 7);

    //Instruction: 20
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 1;
    reg_la0_data = 1310685;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    //while(reg_la3_data != -35);

    //Instruction: 21
    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_la1_data = 0;
    reg_la0_data = 1318387712;

    clk = !clk;
    reg_la2_data = 0x00000000 | clk;

    reg_mprj_datal = 0xAB610000;




}
