library ieee;
library work;
use ieee.std_logic_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;
use IEEE.STD_LOGIC_TEXTIO.all;
use STD.TEXTIO.all;
use work.opcodes.all;
--use work.Components.all;



entity fft_tb is
end;

architecture tb of fft_tb is
signal test_input_bus : std_logic_vector(131 downto 0);
signal test_clk, test_rst 	: std_logic;
signal test_dynamic_config_done, test_config_done 		: std_logic;
--signal test_src_alu, test_dest_alu 						: std_logic_vector(31 downto 0);
--signal test_data_a_b_x_y								: std_logic_vector(127 downto 0);


--configuration instruction format:+
--{7 downto 0 ==> OPCODE of Current ALU,  9 downto 8 => src ALU Position, 11 downto 10 => dest alu, 13 downto 12 => input a? b}
--signal 	test_instr 		: std_logic_vector(191 downto 0) := (others => '0');  
signal 	test_data_ALU_A00,		test_data_ALU_A01,  	test_data_ALU_A02,  	test_data_ALU_A03	:	std_logic_vector(31 downto 0); 	
signal	test_data_ALU_A10,		test_data_ALU_A11,		test_data_ALU_A12,		test_data_ALU_A13   :	std_logic_vector(31 downto 0);
signal	test_data_ALU_A20,		test_data_ALU_A21,		test_data_ALU_A22,		test_data_ALU_A23   :	std_logic_vector(31 downto 0);
signal	test_data_ALU_A30, 		test_data_ALU_A31,		test_data_ALU_A32,		test_data_ALU_A33	: 	std_logic_vector(31 downto 0);

signal 	test_data_ALU_B00,   	test_data_ALU_B01, 		test_data_ALU_B02,  	test_data_ALU_B03   : 	std_logic_vector(31 downto 0);
signal 	test_data_ALU_B10,   	test_data_ALU_B11, 		test_data_ALU_B12,  	test_data_ALU_B13   : 	std_logic_vector(31 downto 0);
signal 	test_data_ALU_B20,   	test_data_ALU_B21, 		test_data_ALU_B22,  	test_data_ALU_B23   : 	std_logic_vector(31 downto 0);
signal 	test_data_ALU_B30,   	test_data_ALU_B31, 		test_data_ALU_B32,  	test_data_ALU_B33	: 	std_logic_vector(31 downto 0);

signal 	test_func_code_00 : std_logic_vector(7 downto 0);
signal 	test_func_code_01 : std_logic_vector(7 downto 0);
signal	test_func_code_02 : std_logic_vector(7 downto 0);
signal	test_func_code_03 : std_logic_vector(7 downto 0);
signal	test_func_code_10 : std_logic_vector(7 downto 0);
signal	test_func_code_11 : std_logic_vector(7 downto 0);
signal	test_func_code_12 : std_logic_vector(7 downto 0);
signal	test_func_code_13 : std_logic_vector(7 downto 0);
signal	test_func_code_20 : std_logic_vector(7 downto 0);
signal	test_func_code_21 : std_logic_vector(7 downto 0);
signal	test_func_code_22 : std_logic_vector(7 downto 0);
signal	test_func_code_23 : std_logic_vector(7 downto 0);
signal	test_func_code_30 : std_logic_vector(7 downto 0);
signal	test_func_code_31 : std_logic_vector(7 downto 0);
signal	test_func_code_32 : std_logic_vector(7 downto 0);
signal	test_func_code_33 : std_logic_vector(7 downto 0);

signal 	test_mux_config_code  : std_logic_vector(63 downto 0);
--signal test_alu_link  		: std_logic_vector(19 downto 0);
signal test_result_ALU00  : std_logic_vector(63 downto 0);
signal test_result_ALU01  : std_logic_vector(63 downto 0);
signal test_result_ALU02  : std_logic_vector(63 downto 0);
signal test_result_ALU03  : std_logic_vector(63 downto 0);
signal test_result_ALU10  : std_logic_vector(63 downto 0);
signal test_result_ALU11  : std_logic_vector(63 downto 0);
signal test_result_ALU12  : std_logic_vector(63 downto 0);
signal test_result_ALU13  : std_logic_vector(63 downto 0);
signal test_result_ALU20  : std_logic_vector(63 downto 0);
signal test_result_ALU21  : std_logic_vector(63 downto 0);
signal test_result_ALU22  : std_logic_vector(63 downto 0);
signal test_result_ALU23  : std_logic_vector(63 downto 0);
signal test_result_ALU30  : std_logic_vector(63 downto 0);
signal test_result_ALU31  : std_logic_vector(63 downto 0);
signal test_result_ALU32  : std_logic_vector(63 downto 0);
signal test_result_ALU33  : std_logic_vector(63 downto 0);
signal test_result_Real_out_k : std_logic_vector(63 downto 0) := (others => '0');
signal test_result_Real_out_j : std_logic_vector(63 downto 0) := (others => '0');
signal test_result_Img_out_k  : std_logic_vector(63 downto 0) := (others => '0');
signal test_result_Img_out_j  : std_logic_vector(63 downto 0) := (others => '0');


signal test_in_rdy_00, test_in_rdy_01, test_in_rdy_02, test_in_rdy_03  		: std_logic;
signal test_in_rdy_10, test_in_rdy_11, test_in_rdy_12, test_in_rdy_13  		: std_logic;
signal test_in_rdy_20, test_in_rdy_21, test_in_rdy_22, test_in_rdy_23  		: std_logic;
signal test_in_rdy_30, test_in_rdy_31, test_in_rdy_32, test_in_rdy_33  		: std_logic;
signal test_out_rdy_00, test_out_rdy_01, test_out_rdy_02, test_out_rdy_03 	: std_logic;
signal test_out_rdy_10, test_out_rdy_11, test_out_rdy_12, test_out_rdy_13 	: std_logic;
signal test_out_rdy_20, test_out_rdy_21, test_out_rdy_22, test_out_rdy_23 	: std_logic;
signal test_out_rdy_30, test_out_rdy_31, test_out_rdy_32, test_out_rdy_33 	: std_logic;




signal test_rdy_config, test_select_line_config, test_func_config, test_data_input_rdy : std_logic;

constant half_period 	: time := 5 ns;
constant full_period 	: time := half_period * 2;

begin
uut : entity work.fft_dfg 
	--generic map(ROWS  	=>  15,
	--			COLUMNS =>  3);	
	port map(
		clk  => test_clk,
		rst 				=> test_rst,
		rdy_config 			=> test_rdy_config,
		select_line_config  => test_select_line_config,
		func_config         => test_func_config,
		data_input_rdy      => test_data_input_rdy,
		input_bus           => test_input_bus, 

		in_rdy_00 => test_in_rdy_00,	in_rdy_01 => test_in_rdy_01,	in_rdy_02 => test_in_rdy_02,	in_rdy_03 => test_in_rdy_03,
		in_rdy_10 => test_in_rdy_10,	in_rdy_11 => test_in_rdy_11,    in_rdy_12 => test_in_rdy_12,	in_rdy_13 => test_in_rdy_13,
		in_rdy_20 => test_in_rdy_20,	in_rdy_21 => test_in_rdy_21,    in_rdy_22 => test_in_rdy_22,	in_rdy_23 => test_in_rdy_23,
		in_rdy_30 => test_in_rdy_30,	in_rdy_31 => test_in_rdy_31,    in_rdy_32 => test_in_rdy_32,	in_rdy_33 => test_in_rdy_33,
		
		out_rdy_00 => test_out_rdy_00,	out_rdy_01 => test_out_rdy_01,	out_rdy_02 => test_out_rdy_02,	out_rdy_03 => test_out_rdy_03,
		out_rdy_10 => test_out_rdy_10,	out_rdy_11 => test_out_rdy_11,	out_rdy_12 => test_out_rdy_12,	out_rdy_13 => test_out_rdy_13,
		out_rdy_20 => test_out_rdy_20,	out_rdy_21 => test_out_rdy_21,	out_rdy_22 => test_out_rdy_22,	out_rdy_23 => test_out_rdy_23,
		out_rdy_30 => test_out_rdy_30,	out_rdy_31 => test_out_rdy_31,	out_rdy_32 => test_out_rdy_32,	out_rdy_33 => test_out_rdy_33,
		

		data_ALU_A00	=> test_data_ALU_A00,
		data_ALU_A01 	=> test_data_ALU_A01,
		data_ALU_A02 	=> test_data_ALU_A02, 
		data_ALU_A10	=> test_data_ALU_A10,
		data_ALU_A11	=> test_data_ALU_A11,
		data_ALU_A12	=> test_data_ALU_A12,
		data_ALU_A20	=> test_data_ALU_A20 ,
		data_ALU_A21	=> test_data_ALU_A21,
		data_ALU_A22	=> test_data_ALU_A22,

		data_ALU_B00 	=> test_data_ALU_B00,
		data_ALU_B01 	=> test_data_ALU_B01,
		data_ALU_B02 	=> test_data_ALU_B02,
		data_ALU_B10 	=> test_data_ALU_B10,
		data_ALU_B11 	=> test_data_ALU_B11,
		data_ALU_B12 	=> test_data_ALU_B12,
		data_ALU_B20 	=> test_data_ALU_B20,
		data_ALU_B21 	=> test_data_ALU_B21,
		data_ALU_B22 	=> test_data_ALU_B22,

		result_ALU00	=> test_result_ALU00,
		result_ALU01	=> test_result_ALU01,
		result_ALU02	=> test_result_ALU02,
		result_ALU03	=> test_result_ALU03,
		result_ALU10	=> test_result_ALU10,
		result_ALU11	=> test_result_ALU11,
		result_ALU12	=> test_result_ALU12,
		result_ALU13	=> test_result_ALU13,
		result_ALU20	=> test_result_ALU20,
		result_ALU21	=> test_result_ALU21,
		result_ALU22	=> test_result_ALU22,
		result_ALU23	=> test_result_ALU23,
		result_ALU30	=> test_result_ALU30,
		result_ALU31	=> test_result_ALU31,
		result_ALU32	=> test_result_ALU32,
		result_ALU33	=> test_result_ALU33,
		result_Real_out_k	=> test_result_Real_out_k,
		result_Real_out_j	=> test_result_Real_out_j,
		result_Img_out_k	=> test_result_Img_out_k,
		result_Img_out_j	=> test_result_Img_out_j,

		FUNC_CODE_00 	=> test_FUNC_CODE_00,
		FUNC_CODE_01 	=> test_FUNC_CODE_01,
		FUNC_CODE_02 	=> test_FUNC_CODE_02,
		FUNC_CODE_03 	=> test_FUNC_CODE_03,
		FUNC_CODE_10 	=> test_FUNC_CODE_10,
		FUNC_CODE_11 	=> test_FUNC_CODE_11,
		FUNC_CODE_12 	=> test_FUNC_CODE_12,
		FUNC_CODE_13 	=> test_FUNC_CODE_13,
		FUNC_CODE_20 	=> test_FUNC_CODE_20,
		FUNC_CODE_21 	=> test_FUNC_CODE_21,
		FUNC_CODE_22 	=> test_FUNC_CODE_22,
		FUNC_CODE_23 	=> test_FUNC_CODE_23,
		FUNC_CODE_30 	=> test_FUNC_CODE_30,
		FUNC_CODE_31 	=> test_FUNC_CODE_31,
		FUNC_CODE_32 	=> test_FUNC_CODE_32,
		FUNC_CODE_33 	=> test_FUNC_CODE_33,
		MUX_CONFIG_CODE => test_MUX_CONFIG_CODE);

clock_gen : process is
	begin
		wait for half_period;
		test_clk <= '1'; 
		wait for half_period;
		test_clk <= '0'; 
end process clock_gen;


--------------------------------------------------------------
-- READ CONFIGURATION INSTRUCTION FILE
--------------------------------------------------------------
stm_test : process is
	variable config_file_line 	: line;
	variable data 				: std_logic_vector(131 downto 0);
	file 	 config_file		: text open read_mode is "C:\Modeltech_pe_edu_10.4a\ALU\revised_config_data";
begin

		------------------------------------------------------------------------------------------------------------------------
		-- Read inputs from hex -> std_logic_vector -> process-> alu(instruction(71 downto 64), instruc(63-32), instruc(31, 0);
		-------------------------------------------------------------------------------------------------------------------------
		--test_config_go <= '0';
		test_rst <= '1';
		wait for full_period;
		test_rst <= '0';
		wait for 30 * full_period;
		wait for (9 ns);
		test_func_code_00 <= OPCODE_FADD; 	--add 
		test_func_code_01 <= OPCODE_FMULT; 	--fp multiplication
		test_func_code_02 <= OPCODE_FMULT; 	--add 00000000
		test_func_code_03 <= OPCODE_FADD; 	--opcode_and "00000111"
		test_func_code_10 <= OPCODE_FSUB; 	--opcode_and "00000111"
		test_func_code_11 <= OPCODE_FSUB; 	--and "00000111"
		test_func_code_12 <= OPCODE_FMULT; 	--add 00000000
		test_func_code_13 <= OPCODE_FMULT;  --add 00000000
		test_func_code_20 <= OPCODE_FMULT;  --add 00000000
		test_func_code_21 <= OPCODE_FMULT;	--
		test_func_code_22 <= OPCODE_FSUB;
		test_func_code_23 <= OPCODE_FADD;
		test_func_code_30 <= OPCODE_FSUB;
		test_func_code_31 <= OPCODE_FADD;
		test_func_code_32 <= OPCODE_FSUB;
		test_func_code_33 <= OPCODE_FADD;
		test_mux_config_code <= "0010011001100110011001100110011001100101010001100101010001010101"; --GENERATED BY THE XML_PARSER_H FILE
		wait for 5 * full_period;
		while not endfile(config_file) loop
			readline(config_file, config_file_line);
			HREAD(config_file_line, data);
			--test_config_go <= data(172);
			--test_go <= test_config_en;
			--test_instr <= data(191 downto 0);
			
			test_input_bus <= data;
			--if (data(1) = '1' ) then 
			--	wait for 10 * full_period;
			--end if;
			--elsif(data(1) = '1') then 
			--	wait for 9 * full_period;
			--end if;
			--test_data_a00 <= data(127 downto 96);
			--test_data_a01 <= data(95 downto 64);
			--test_data_b00 <= data(63 downto 32);
			--test_data_b01 <= data(31 downto 0);
			
			--Intensionally left blank I'm sleeping here.
			--
			wait for full_period;
		end loop; 
		wait;
	end process;

end tb;