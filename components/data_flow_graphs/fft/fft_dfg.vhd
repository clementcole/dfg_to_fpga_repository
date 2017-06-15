library ieee;
library work;
use ieee.std_logic_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;
use IEEE.STD_LOGIC_TEXTIO.all;
use STD.TEXTIO.all;
use work.opcodes.all;
--use work.Components.all;


entity fft_dfg is
		generic(ROWS  : 	integer := 15;
				COLUMNS :   integer := 3);
		port(	
			
			clk 					: in std_logic;
			rst 					: in std_logic;
			rdy_config 				: out std_logic;
			select_line_config      : out std_logic;
			func_config             : out std_logic;
			data_input_rdy          : out std_logic;
			input_bus               : in std_logic_vector(131 downto 0);

			in_rdy_00 : out std_logic;	in_rdy_01 : out std_logic;	in_rdy_02 : out std_logic;	in_rdy_03 : out std_logic;
			in_rdy_10 : out std_logic;	in_rdy_11 : out std_logic;  in_rdy_12 : out std_logic;	in_rdy_13 : out std_logic;
			in_rdy_20 : out std_logic;	in_rdy_21 : out std_logic;  in_rdy_22 : out std_logic;	in_rdy_23 : out std_logic;
			in_rdy_30 : out std_logic;	in_rdy_31 : out std_logic;  in_rdy_32 : out std_logic;	in_rdy_33 : out std_logic;
			
			out_rdy_00 : out std_logic;	out_rdy_01 : out std_logic;	out_rdy_02 : out std_logic;	out_rdy_03 : out std_logic;
			out_rdy_10 : out std_logic;	out_rdy_11 : out std_logic;	out_rdy_12 : out std_logic;	out_rdy_13 : out std_logic;
			out_rdy_20 : out std_logic;	out_rdy_21 : out std_logic;	out_rdy_22 : out std_logic;	out_rdy_23 : out std_logic;
			out_rdy_30 : out std_logic;	out_rdy_31 : out std_logic;	out_rdy_32 : out std_logic;	out_rdy_33 : out std_logic;

			data_ALU_A00 : out std_logic_vector(31 downto 0); 
			data_ALU_A01 : out std_logic_vector(31 downto 0);
			data_ALU_A02 : out std_logic_vector(31 downto 0); 
			data_ALU_A03 : out std_logic_vector(31 downto 0); 
			data_ALU_A10 : out std_logic_vector(31 downto 0);
			data_ALU_A11 : out std_logic_vector(31 downto 0);
			data_ALU_A12 : out std_logic_vector(31 downto 0);
			data_ALU_A13 : out std_logic_vector(31 downto 0); 
			data_ALU_A20 : out std_logic_vector(31 downto 0); 
			data_ALU_A21 : out std_logic_vector(31 downto 0);
			data_ALU_A22 : out std_logic_vector(31 downto 0);
			data_ALU_A23 : out std_logic_vector(31 downto 0); 
			data_ALU_A30 : out std_logic_vector(31 downto 0); 
			data_ALU_A31 : out std_logic_vector(31 downto 0); 
			data_ALU_A32 : out std_logic_vector(31 downto 0); 
			data_ALU_A33 : out std_logic_vector(31 downto 0); 

			data_ALU_B00 : out std_logic_vector(31 downto 0); 
			data_ALU_B01 : out std_logic_vector(31 downto 0); 
			data_ALU_B02 : out std_logic_vector(31 downto 0); 
			data_ALU_B03 : out std_logic_vector(31 downto 0); 
			data_ALU_B10 : out std_logic_vector(31 downto 0);
			data_ALU_B11 : out std_logic_vector(31 downto 0);
			data_ALU_B12 : out std_logic_vector(31 downto 0);
			data_ALU_B13 : out std_logic_vector(31 downto 0); 
			data_ALU_B20 : out std_logic_vector(31 downto 0);
			data_ALU_B21 : out std_logic_vector(31 downto 0);
			data_ALU_B22 : out std_logic_vector(31 downto 0);
			data_ALU_B23 : out std_logic_vector(31 downto 0); 
			data_ALU_B30 : out std_logic_vector(31 downto 0); 
			data_ALU_B31 : out std_logic_vector(31 downto 0); 
			data_ALU_B32 : out std_logic_vector(31 downto 0); 
			data_ALU_B33 : out std_logic_vector(31 downto 0); 

			result_ALU00 : out std_logic_vector(63 downto 0);	result_ALU01 : out std_logic_vector(63 downto 0);	result_ALU02 : out std_logic_vector(63 downto 0);	result_ALU03 : out std_logic_vector(63 downto 0);	
			result_ALU10 : out std_logic_vector(63 downto 0);	result_ALU11 : out std_logic_vector(63 downto 0);	result_ALU12 : out std_logic_vector(63 downto 0);	result_ALU13 : out std_logic_vector(63 downto 0);
			result_ALU20 : out std_logic_vector(63 downto 0); 	result_ALU21 : out std_logic_vector(63 downto 0);	result_ALU22 : out std_logic_vector(63 downto 0);	result_ALU23 : out std_logic_vector(63 downto 0);
			result_ALU30 : out std_logic_vector(63 downto 0); 	result_ALU31 : out std_logic_vector(63 downto 0);	result_ALU32 : out std_logic_vector(63 downto 0);	result_ALU33 : out std_logic_vector(63 downto 0);
			result_Real_out_k : out std_logic_vector(63 downto 0);	result_Real_out_j : out std_logic_vector(63 downto 0);
			result_Img_out_k  : out std_logic_vector(63 downto 0);	result_Img_out_j  : out std_logic_vector(63 downto 0);

			FUNC_CODE_00 : in std_logic_vector(7 downto 0); -- Add 0000
			FUNC_CODE_01 : in std_logic_vector(7 downto 0); -- mult fp
			FUNC_CODE_02 : in std_logic_vector(7 downto 0); -- mult fp
			FUNC_CODE_03 : in std_logic_vector(7 downto 0); -- add 00000
			FUNC_CODE_10 : in std_logic_vector(7 downto 0); -- sub
			FUNC_CODE_11 : in std_logic_vector(7 downto 0); -- sub
			FUNC_CODE_12 : in std_logic_vector(7 downto 0); -- mult fp
			FUNC_CODE_13 : in std_logic_vector(7 downto 0); -- mult fp
			FUNC_CODE_20 : in std_logic_vector(7 downto 0); -- mult fp
			FUNC_CODE_21 : in std_logic_vector(7 downto 0); -- mult fp
			FUNC_CODE_22 : in std_logic_vector(7 downto 0); -- sub
			FUNC_CODE_23 : in std_logic_vector(7 downto 0); -- add
			FUNC_CODE_30 : in std_logic_vector(7 downto 0); -- sub
			FUNC_CODE_31 : in std_logic_vector(7 downto 0); -- add
			FUNC_CODE_32 : in std_logic_vector(7 downto 0);
			FUNC_CODE_33 : in std_logic_vector(7 downto 0);
			MUX_CONFIG_CODE 		: in std_logic_vector(63 downto 0));
end fft_dfg;

architecture arch of fft_dfg is

	type ALU_DATA_TYPE   is array(0 to ROWS) of std_logic_vector(31 downto 0);
	type ALU_RDY_TYPE					is  array(0 to ROWS) of std_logic;
	type ALU_OP_TYPE  					is  array(0 to ROWS) of std_logic_vector(7 downto 0);
	type ALU_OUTPUT_TYPE		 		is 	array(0 to ROWS) of std_logic_vector(63 downto 0);
	type mux_sel_typeA            		is  array(0 to ROWS) of std_logic_vector(1 downto 0); --Need to know if inputA or inputB so an extra bit
	type mux_sel_typeB            		is  array(0 to ROWS) of std_logic_vector(1 downto 0);
	type mux_data_flow_out_type       	is  array(0 to ROWS) of std_logic_vector(31 downto 0); --ACTUAL DATA FROM PREVIOUS ALU TO NEXT
	type mux_data_flow_in_type			is  array(0 to ROWS) of std_logic_vector(63 downto 0);

	--Modififications
	signal   in_A, in_B 									: ALU_DATA_TYPE;
	signal   in_rdy_sig, out_rdy_sig                        : ALU_RDY_TYPE;
	signal   in_rdy_sig_demux, out_rdy_sig_demux            : ALU_RDY_TYPE;
	signal 	 a_ready, b_ready								: ALU_RDY_TYPE;
	signal   alu_op 										: ALU_OP_TYPE;
	signal   alu_output 									: ALU_OUTPUT_TYPE;
	signal   in_A64, in_B64, in_X64, in_Y64, out_Z64        : std_logic_vector(63 downto 0);
	signal   zeros  										: std_logic_vector(63 downto 0);

	signal   in_baseX, in_baseY, in_baseZ					: std_logic_vector(63 downto 0);
	signal   config_sig, in_rdy_sigs : std_logic;


	--MUXES
	signal select_linesA 						: mux_sel_typeA;
	signal select_linesB 						: mux_sel_typeB;
	signal flow_AX0_out, flow_AX1_out       	: mux_data_flow_out_type;
	signal flow_BX0_out, flow_BX1_out       	: mux_data_flow_out_type;
	signal data_flow_out						: mux_data_flow_in_type;
	signal data_rdy								: std_logic_vector(1 downto 0);


	signal INTER_RDY_CONFIG			   :  std_logic;
	signal INTER_SELECT_LINE_CONFIG      :  std_logic;
	signal INTER_FUNC_CONFIG             :  std_logic;
	signal INTER_DATA_INPUT_RDY          :  std_logic;


	signal config_go 				:  std_logic;
	signal in_rdy_sigs_config 		:  std_logic;
	signal op_code_config_go       :  std_logic;
	signal input_data_go 			:  std_logic; --input_data_en <= not(config_go)
	signal instr 	:  std_logic_vector(131 downto 0);
	begin
	instr <= input_bus; -- (others => '0');

	config_sig <= input_bus(0);
	in_rdy_sigs_config <= config_sig;
	INTER_SELECT_LINE_CONFIG <= input_bus(1);
	INTER_FUNC_CONFIG <= input_bus(2);
	INTER_DATA_INPUT_RDY <= input_bus(3);

	rdy_config <= input_bus(0);
	select_line_config <= INTER_SELECT_LINE_CONFIG;
	func_config <= INTER_FUNC_CONFIG;
	data_input_rdy <= INTER_DATA_INPUT_RDY;


	alu_0 : entity work.ALU_EXPERIMENT_32
		port map(in_A(0), in_B(0), clk, rst, in_rdy_sig(0), out_rdy_sig(0), alu_op(0), data_flow_out(0));

	alu_1 : entity work.ALU_EXPERIMENT_32 
		port map(in_A(1), in_B(1), clk, rst, in_rdy_sig(1), out_rdy_sig(1), alu_op(1), data_flow_out(1));

	alu_2 : entity work.ALU_EXPERIMENT_32
		port map(in_A(2), in_B(2), clk, rst, in_rdy_sig(2), out_rdy_sig(2), alu_op(2), data_flow_out(2));

	alu_3 : entity work.ALU_EXPERIMENT_32
		port map(in_A(3), in_B(3), clk, rst, in_rdy_sig(3), out_rdy_sig(3), alu_op(3), data_flow_out(3));


	alu_4 : entity work.ALU_EXPERIMENT_32
		port map(in_A(4), in_B(4), clk, rst, in_rdy_sig(4), out_rdy_sig(4), alu_op(4), data_flow_out(4));


	alu_5 : entity work.ALU_EXPERIMENT_32
		port map(in_A(5), in_B(5), clk, rst, in_rdy_sig(5), out_rdy_sig(5), alu_op(5), data_flow_out(5));
		

	alu_6 : entity work.ALU_EXPERIMENT_32
		port map(in_A(6), in_B(6), clk, rst, in_rdy_sig(6), out_rdy_sig(6), alu_op(6), data_flow_out(6));
		

	alu_7 : entity work.ALU_EXPERIMENT_32
		port map(in_A(7), in_B(7), clk, rst, in_rdy_sig(7), out_rdy_sig(7), alu_op(7), data_flow_out(7));			
	

	alu_8 : entity work.ALU_EXPERIMENT_32
		port map(in_A(8), in_B(8), clk, rst, in_rdy_sig(8), out_rdy_sig(8), alu_op(8), data_flow_out(8));


	alu_9 : entity work.ALU_EXPERIMENT_32 
		port map(in_A(9), in_B(9), clk, rst, in_rdy_sig(9), out_rdy_sig(9), alu_op(9), data_flow_out(9));


	alu_10 : entity work.ALU_EXPERIMENT_32 
		port map(in_A(10), in_B(10), clk, rst, in_rdy_sig(10), out_rdy_sig(10), alu_op(10), data_flow_out(10));


	alu_11 : entity work.ALU_EXPERIMENT_32 
		port map(in_A(11), in_B(11), clk, rst, in_rdy_sig(11), out_rdy_sig(11), alu_op(11), data_flow_out(11));

	alu_12 : entity work.ALU_EXPERIMENT_32 
		port map(in_A(12), in_B(12), clk, rst, in_rdy_sig(12), out_rdy_sig(12), alu_op(12), data_flow_out(12));

	alu_13 : entity work.ALU_EXPERIMENT_32 
		port map(in_A(13), in_B(13), clk, rst, in_rdy_sig(13), out_rdy_sig(13), alu_op(13), data_flow_out(13));

	alu_14 : entity work.ALU_EXPERIMENT_32 
		port map(in_A(14), in_B(14), clk, rst, in_rdy_sig(14), out_rdy_sig(14), alu_op(14), data_flow_out(14));

	alu_15 : entity work.ALU_EXPERIMENT_32 
		port map(in_A(15), in_B(15), clk, rst, in_rdy_sig(15), out_rdy_sig(15), alu_op(15), data_flow_out(15));

	--alu_14 : entity work.ALU_EXPERIMENT_32 
	--	port map(in_A(14), in_B(14), clk, rst, in_rdy_sig(14), out_rdy_sig(14), alu_op(14), data_flow_out(14));



		----------------------------------------
	--ALU_0
	----------------------------------------
	muxes_A0 : entity work.mux_4_to_1 
						port map(clk,  input_bus(131 downto 68), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesA(0), in_A(0)); --sel 00
	muxes_B0 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesB(0), in_B(0));--sel 00

	----------------------------------------
	--ALU_1
	----------------------------------------
	muxes_A1 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesA(1), in_A(1));--sel 01
	muxes_B1 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesB(1), in_B(1));--sel 01

	----------------------------------------
	--ALU_2
	----------------------------------------
	muxes_A2 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesA(2), in_A(2));--sel 02
	muxes_B2 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesB(2), in_B(2));--sel 02



	----------------------------------------
	--ALU_3
	----------------------------------------
	muxes_A3 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesA(3), in_A(3)); --sel 03
	muxes_B3 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesB(3), in_B(3));  --sel 03


	----------------------------------------
	--ALU_4
	----------------------------------------
	muxes_A4 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesA(4), in_A(4)); --sel 10
	muxes_B4 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesB(4), in_B(4));  --sel 10


	----------------------------------------
	--ALU_5
	----------------------------------------
	muxes_A5 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesA(5), in_A(5)); --sel 11
	muxes_B5 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesB(5), in_B(5));	--sel 11


	----------------------------------------
	--ALU_6
	----------------------------------------
	muxes_A6 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(6), in_A(6));	--sel 12
	muxes_B6 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(1), data_flow_out(5), data_flow_out(6), select_linesB(6), in_B(6));	--sel 12

	----------------------------------------
	--ALU_7
	----------------------------------------
	muxes_A7 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(7), in_A(7)); --sel 13
	muxes_B7 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(1), data_flow_out(5), data_flow_out(6), select_linesB(7), in_B(7));	--sel 13

	----------------------------------------
	--ALU_8
	----------------------------------------
	muxes_A8 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(8), in_A(8));	--sel 20
	muxes_B8 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(1), data_flow_out(5), data_flow_out(6), select_linesB(8), in_B(8));	--sel 20


	----------------------------------------
	--ALU_9
	----------------------------------------
	muxes_A9 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(9), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(8), in_A(8));	--sel 21
	muxes_B9 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(9), data_flow_out(1), data_flow_out(5), data_flow_out(6), select_linesB(8), in_B(8));	--sel 21


	----------------------------------------
	--ALU_10
	----------------------------------------
	muxes_A10 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(8), in_A(8));	--sel 22
	muxes_B10 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(1), data_flow_out(5), data_flow_out(6), select_linesB(8), in_B(8));	--sel 22



	----------------------------------------
	--ALU_11
	----------------------------------------
	muxes_A11 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(8), in_A(8));	--sel 23
	muxes_B11 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(1), data_flow_out(5), data_flow_out(6), select_linesB(8), in_B(8));	--sel 23


	----------------------------------------
	--ALU_12
	----------------------------------------
	muxes_A12 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(8), in_A(8));	--sel 30
	muxes_B12 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(1), data_flow_out(5), data_flow_out(6), select_linesB(8), in_B(8));	--sel 30


	----------------------------------------
	--ALU_13
	----------------------------------------
	muxes_A13 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(8), in_A(8));	--sel 31
	muxes_B13 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(1), data_flow_out(5), data_flow_out(6), select_linesB(8), in_B(8));	--sel 31



	----------------------------------------
	--ALU_14
	----------------------------------------
	muxes_A14 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(8), in_A(8));	--sel 32
	muxes_B14 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(1), data_flow_out(5), data_flow_out(6), select_linesB(8), in_B(8));	--sel 32



	----------------------------------------
	--ALU_15
	----------------------------------------
	muxes_A15 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(8), in_A(8));	--sel 33
	muxes_B15 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(1), data_flow_out(5), data_flow_out(6), select_linesB(8), in_B(8));	--sel 33




	in_rdy_sig(0) <= out_rdy_sig(4); 	in_rdy_sig(1) <= out_rdy_sig(4);	
	in_rdy_sig(2) <= out_rdy_sig(5);	in_rdy_sig(3) <= out_rdy_sig(5);

	
	in_rdy_sig(4) <= out_rdy_sig(0) and out_rdy_sig(1);		in_rdy_sig(5) <= out_rdy_sig(2) and out_rdy_sig(3);
	in_rdy_sig(6) <= out_rdy_sig(8) and out_rdy_sig(9);		in_rdy_sig(7) <= out_rdy_sig(10) and out_rdy_sig(11);
	
	in_rdy_sig(8) <= out_rdy_sig(4); -- and Fifo real
	in_rdy_sig(9) <= out_rdy_sig(5); -- and Fifo Image
	in_rdy_sig(10) <= out_rdy_sig(5); --and Fifo Image
	in_rdy_sig(11) 	<= out_rdy_sig(5); --and real Fifo


	in_rdy_sig(12) 	<= out_rdy_sig(6); -- and Fifo Real;
	in_rdy_sig(13) 	<= out_rdy_sig(6); -- and Fifo Real
	in_rdy_sig(14) 	<= out_rdy_sig(7); -- and Fifo Image
	in_rdy_sig(15) 	<= out_rdy_sig(7); --  and Fifo Image 




	alu_op(0) <= FUNC_CODE_00; --add "0000000"
	alu_op(1) <= FUNC_CODE_01; --mult fp
	alu_op(2) <= FUNC_CODE_02; --mult fp
	alu_op(3) <= FUNC_CODE_03; --add "0000000"
	alu_op(4) <= FUNC_CODE_10; --sub fp
	alu_op(5) <= FUNC_CODE_11; --sub fp
	alu_op(6) <= FUNC_CODE_12; -- mult fp
	alu_op(7) <= FUNC_CODE_13;  -- mult fp
	alu_op(8) <= FUNC_CODE_20;  -- mult fp
	alu_op(9) <= FUNC_CODE_21;  -- mult fp
	alu_op(10) <= FUNC_CODE_22; -- sub fp
	alu_op(11) <= FUNC_CODE_23; -- sub fp
	alu_op(12) <= FUNC_CODE_30; -- sub
	alu_op(13) <= FUNC_CODE_31; -- add 
	alu_op(14) <= FUNC_CODE_32; -- sub
	alu_op(15) <= FUNC_CODE_33; -- add




			select_linesA(0) <= MUX_CONFIG_CODE(63 downto 62); --"01"
			select_linesB(0) <= MUX_CONFIG_CODE(61 downto 60); --"01";

			select_linesA(1) <= MUX_CONFIG_CODE(59 downto 58); --"01";
			select_linesB(1) <= MUX_CONFIG_CODE(57 downto 56); --"01";

			select_linesA(2) <= MUX_CONFIG_CODE(55 downto 54); --"01";
			select_linesB(2) <= MUX_CONFIG_CODE(53 downto 52); --"01";
 				
					
					
					
			--Second row ALU3, ALU4, ALU5
			select_linesA(3) <= MUX_CONFIG_CODE(51 downto 50); --"00"; --00
			select_linesB(3) <= MUX_CONFIG_CODE(49 downto 48); --"01"; --01


			select_linesA(4) <= MUX_CONFIG_CODE(47 downto 46); --"01"; --01
			select_linesB(4) <= MUX_CONFIG_CODE(45 downto 44); --"01"; --01

			select_linesA(5) <= MUX_CONFIG_CODE(43 downto 42); --"10"; --10
			select_linesB(5) <= MUX_CONFIG_CODE(41 downto 40); --"01"; --01

			--Third row ALU6, ALU7, ALU8
			select_linesA(6) <= MUX_CONFIG_CODE(39 downto 38); --"00"; --00
			select_linesB(6) <= MUX_CONFIG_CODE(37 downto 36); --"01"; --01

			select_linesA(7) <= MUX_CONFIG_CODE(35 downto 34); --"01"; --01
			select_linesB(7) <= MUX_CONFIG_CODE(33 downto 32); --"01"; --01

			select_linesA(8) <= MUX_CONFIG_CODE(31 downto 30); --"10"; --10
			select_linesB(8) <= MUX_CONFIG_CODE(29 downto 28); --"01"; --01

			select_linesA(9) <= MUX_CONFIG_CODE(27 downto 26); --"10"; --10
			select_linesB(9) <= MUX_CONFIG_CODE(25 downto 24); --"01"; --01


			select_linesA(10) <= MUX_CONFIG_CODE(23 downto 22); --"10"; --10
			select_linesB(10) <= MUX_CONFIG_CODE(21 downto 20); --"01"; --01


			select_linesA(11) <= MUX_CONFIG_CODE(19 downto 18); --"10"; --10
			select_linesB(11) <= MUX_CONFIG_CODE(17 downto 16); --"01"; --01

			select_linesA(12) <= MUX_CONFIG_CODE(15 downto 14); --"10"; --10
			select_linesB(12) <= MUX_CONFIG_CODE(13 downto 12); --"01"; --01

			select_linesA(13) <= MUX_CONFIG_CODE(11 downto 10); --"10"; --10
			select_linesB(13) <= MUX_CONFIG_CODE(9 downto 8); --"01"; --01


			select_linesA(14) <= MUX_CONFIG_CODE(7 downto 6); --"10"; --10
			select_linesB(14) <= MUX_CONFIG_CODE(5 downto 4); --"01"; --01
					

			select_linesA(15) <= MUX_CONFIG_CODE(3 downto 2); --"10"; --10
			select_linesB(15) <= MUX_CONFIG_CODE(1 downto 0); --"01"; --01
				
					
				
				
			data_ALU_A00 <= in_A(0);  	data_ALU_A01 <= in_A(1);  	data_ALU_A02 <= in_A(2);  data_ALU_A03 <= in_A(3); 
			data_ALU_A10 <= in_A(4);  	data_ALU_A11 <= in_A(5);  	data_ALU_A12 <= in_A(6);  data_ALU_A13 <= in_A(7);
			data_ALU_A20 <= in_A(8);  	data_ALU_A21 <= in_A(9);  	data_ALU_A22 <= in_A(10); data_ALU_A23 <= in_A(11);
			data_ALU_A30 <= in_A(12); 	data_ALU_A31 <= in_A(13); 	data_ALU_A32 <= in_A(14); data_ALU_A33 <= in_A(15);

			data_ALU_B00 <= in_B(0); 	data_ALU_B01 <= in_B(1); 	data_ALU_B02 <= in_B(2);  data_ALU_B03 <= in_B(3); 
			data_ALU_B10 <= in_B(4); 	data_ALU_B11 <= in_B(5); 	data_ALU_B12 <= in_B(6);  data_ALU_B13 <= in_B(7);
			data_ALU_B20 <= in_B(8); 	data_ALU_B21 <= in_B(9); 	data_ALU_B22 <= in_B(10); data_ALU_B23 <= in_B(11);
			data_ALU_B30 <= in_B(12); 	data_ALU_B31 <= in_B(13); 	data_ALU_B32 <= in_B(14); data_ALU_B33 <= in_B(15); 
				

			result_ALU00 <= data_flow_out(0); 	result_ALU01 <= data_flow_out(1); 	result_ALU02 <= data_flow_out(2); 	result_ALU03 <= data_flow_out(3); 
			result_ALU10 <= data_flow_out(4);	result_ALU11 <= data_flow_out(5);	result_ALU12 <= data_flow_out(6);	result_ALU13 <= data_flow_out(7);
			result_ALU20 <= data_flow_out(8);	result_ALU21 <= data_flow_out(9);	result_ALU22 <= data_flow_out(10);	result_ALU23 <= data_flow_out(11);
			result_ALU30 <= data_flow_out(12);	result_ALU31 <= data_flow_out(13);	result_ALU32 <= data_flow_out(14);	result_ALU33 <= data_flow_out(15);
			result_Real_out_k <= data_flow_out(12);		result_Real_out_j <= data_flow_out(13);
			result_Img_out_k  <= data_flow_out(14);		result_Img_out_j  <= data_flow_out(15);

end arch;