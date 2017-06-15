library ieee;
library work;
use ieee.std_logic_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;
use IEEE.STD_LOGIC_TEXTIO.all;
use STD.TEXTIO.all;
use work.opcodes.all;
--use work.Components.all;



entity dynamic_dfg_histogram_tb is
end;

architecture tb of dynamic_dfg_histogram_tb is

signal test_input_bus : std_logic_vector(131 downto 0);
signal test_clk, test_rst 	: std_logic;
signal test_dynamic_config_done, test_config_done 		: std_logic;
--signal test_src_alu, test_dest_alu 						: std_logic_vector(31 downto 0);
--signal test_data_a_b_x_y								: std_logic_vector(127 downto 0);


--configuration instruction format:+
--{7 downto 0 ==> OPCODE of Current ALU,  9 downto 8 => src ALU Position, 11 downto 10 => dest alu, 13 downto 12 => input a? b}
--signal 	test_instr 		: std_logic_vector(191 downto 0) := (others => '0');  
signal 	test_data_ALU_A00,	test_data_ALU_A01,  	test_data_ALU_A02,  	test_data_ALU_A10					:	std_logic_vector(31 downto 0); 	
signal	test_data_ALU_A11,	test_data_ALU_A12,	test_data_ALU_A20,	test_data_ALU_A21,	test_data_ALU_A22	: 	std_logic_vector(31 downto 0);
signal 	test_data_ALU_B00,   test_data_ALU_B01, 	test_data_ALU_B02,  	test_data_ALU_B10 					: 	std_logic_vector(31 downto 0);
signal 	test_data_ALU_B11,   test_data_ALU_B12, 	test_data_ALU_B20,  	test_data_ALU_B21,	test_data_ALU_B22 	: 	std_logic_vector(31 downto 0);

signal 	test_func_code_00 : std_logic_vector(7 downto 0);
signal 	test_func_code_01 : std_logic_vector(7 downto 0);
signal	test_func_code_02 : std_logic_vector(7 downto 0);
signal	test_func_code_10 : std_logic_vector(7 downto 0);
signal	test_func_code_11 : std_logic_vector(7 downto 0);
signal	test_func_code_12 : std_logic_vector(7 downto 0);
signal	test_func_code_20 : std_logic_vector(7 downto 0);
signal	test_func_code_21 : std_logic_vector(7 downto 0);
signal	test_func_code_22 : std_logic_vector(7 downto 0);

signal 	test_mux_config_code  : std_logic_vector(35 downto 0);
--signal test_alu_link  		: std_logic_vector(19 downto 0);
signal test_result_0       	: std_logic_vector(63 downto 0);
signal test_result_1       	: std_logic_vector(63 downto 0);
signal test_result_2       	: std_logic_vector(63 downto 0);
signal test_result_3       	: std_logic_vector(63 downto 0);
signal test_result_4       	: std_logic_vector(63 downto 0);
signal test_result_5       	: std_logic_vector(63 downto 0);
signal test_result_6       	: std_logic_vector(63 downto 0);
signal test_result_7       	: std_logic_vector(63 downto 0);
signal test_result_8       	: std_logic_vector(63 downto 0);
signal test_result_blue       	: std_logic_vector(63 downto 0) := (others => '0');
signal test_result_green       	: std_logic_vector(63 downto 0) := (others => '0');
signal test_result_red       	: std_logic_vector(63 downto 0) := (others => '0');

signal test_in_rdy_0, test_in_rdy_1, test_in_rdy_2, test_in_rdy_3  		: std_logic;
signal test_out_rdy_0, test_out_rdy_1, test_out_rdy_2, test_out_rdy_3 	: std_logic;

signal test_rdy_config, test_select_line_config, test_func_config, test_data_input_rdy : std_logic;

constant half_period 	: time := 5 ns;
constant full_period 	: time := half_period * 2;

begin
uut : entity work.dynamic_histogram_dfg 
	generic map( ROWS => 8,  COLUMNS => 3)
	port map(
		clk 					=> 	test_clk,
		rst 					=> 	test_rst,
		RDY_CONFIG			   	=> test_rdy_config,
		SELECT_LINE_CONFIG    	=> test_select_line_config,
		FUNC_CONFIG            	=> test_func_config,
		DATA_INPUT_RDY         	=> test_data_input_rdy,
		input_bus               =>	test_input_bus,
		in_rdy_0				=>	test_in_rdy_0,
		in_rdy_1				=>	test_in_rdy_1,
		in_rdy_2				=>	test_in_rdy_2,
		out_rdy_0				=>	test_out_rdy_0,
		out_rdy_1				=>	test_out_rdy_1,
		out_rdy_2				=>	test_out_rdy_2,
		in_rdy_3				=>  test_in_rdy_3,
		out_rdy_3   			=>  test_out_rdy_3,
		data_ALU_A00					=>	test_data_ALU_A00, 
		data_ALU_A01 				=>	test_data_ALU_A01,
		data_ALU_A02 				=>	test_data_ALU_A02, 
		data_ALU_A10					=>	test_data_ALU_A10,
		data_ALU_A11					=>	test_data_ALU_A11,
		data_ALU_A12					=>	test_data_ALU_A12,
		data_ALU_A20					=>	test_data_ALU_A20, 
		data_ALU_A21					=>	test_data_ALU_A21,
		data_ALU_A22					=>	test_data_ALU_A22,
		data_ALU_B00 				=>	test_data_ALU_B00, 
		data_ALU_B01 				=>	test_data_ALU_B01, 
		data_ALU_B02 				=>	test_data_ALU_B02, 
		data_ALU_B10 				=>	test_data_ALU_B10, 
		data_ALU_B11 				=>	test_data_ALU_B11, 
		data_ALU_B12 				=>	test_data_ALU_B12, 
		data_ALU_B20 				=>	test_data_ALU_B20, 
		data_ALU_B21 				=>	test_data_ALU_B21, 
		data_ALU_B22 				=>	test_data_ALU_B22, 
		result_ALU0				=>	test_result_0,
		result_ALU1				=>	test_result_1,
		result_ALU2				=>	test_result_2,
		result_ALU3				=>	test_result_3,
		result_ALU4				=>	test_result_4,
		result_ALU5				=>	test_result_5,
		result_ALU6				=>	test_result_6,
		result_ALU7				=>	test_result_7,
		result_ALU8				=>	test_result_8, 
		result_BLUE				=>	test_result_blue,
		result_GREEN			=>	test_result_green,
		result_RED				=>	test_result_red,
		FUNC_CODE_00			=>  test_func_code_00,
		FUNC_CODE_01            =>  test_func_code_01,
		FUNC_CODE_02 			=>  test_func_code_02,
		FUNC_CODE_10 			=>  test_func_code_10,
		FUNC_CODE_11 			=>  test_func_code_11,
		FUNC_CODE_12  			=>  test_func_code_12,
		FUNC_CODE_20  			=>  test_func_code_20,
		FUNC_CODE_21 			=>  test_func_code_21,
		FUNC_CODE_22 			=>  test_func_code_22,
		MUX_CONFIG_CODE  		=>  test_mux_config_code
		);

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
		test_func_code_00 <= OPCODE_SRL; --srl 00001100
		test_func_code_01 <= OPCODE_SRL; --srl 00001100
		test_func_code_02 <= OPCODE_SRL; --add 00000000
		test_func_code_10 <= OPCODE_AND; --opcode_and "00000111"
		test_func_code_11 <= OPCODE_AND; --opcode_and "00000111"
		test_func_code_12 <= OPCODE_AND; --and "00000111"
		test_func_code_20 <= OPCODE_ADD_SUB; --add 00000000
		test_func_code_21 <= OPCODE_ADD_SUB;   --add 00000000
		test_func_code_22 <= OPCODE_ADD_SUB;  --add 00000000
		test_mux_config_code <= "010101010101000101011001000101011001"; --GENERATED BY THE XML_PARSER_H FILE
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