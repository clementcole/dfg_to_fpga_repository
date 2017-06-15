library ieee;
library work;
use ieee.std_logic_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;
use IEEE.STD_LOGIC_TEXTIO.all;
use STD.TEXTIO.all;
use work.opcodes.all;
--use work.Components.all;



entity dynamic_alu_conf_tb is
end dynamic_alu_conf_tb;



architecture testbench of dynamic_alu_conf_tb is
	signal a_00, a_01, a_02, a_10, a_11, a_12, a_20, a_21, a_22 : std_logic_vector(31 downto 0);
	signal b_00, b_01, b_02, b_10, b_11, b_12, b_20, b_21, b_22 : std_logic_vector(31 downto 0);
	signal clk, clk_00, clk_01, clk_02, clk_10, clk_11, clk_12, clk_20, clk_21, clk_22  : std_logic;  --inputs clk1, clk2, rst1, rst2, {1 bit each}
	signal rst, rst_00, rst_01, rst_02, rst_10, rst_11,  rst_20, rst_21, rst_22 : std_logic;
	signal in_rdy, in_rdy_00, in_rdy_01, in_rdy_02, in_rdy_10, in_rdy_11, in_rdy_12,  in_rdy_20, in_rdy_21, in_rdy_22 : std_logic;									   --ready signals rdy1, rd2, rd3, {1 bit each}
	signal out_rdy, out_rdy_00, out_rdy_01, out_rdy_02, out_rdy_10,  out_rdy_11, out_rdy_12,out_rdy_20, out_rdy_21, out_rdy_22 : std_logic;									   --output ready signals (xy), (a+b) and (xy) + (a + b) {1 bit each} 
	signal op_00, op_01, op_02, op_10, op_11, op_12, op_20, op_21, op_22 : std_logic_vector(7 downto 0);	
	signal conf : std_logic_vector(131 downto 0);						   --opcodes {plus, mult and plus}
	signal out_00, out_01, out_02, out_10, out_11, out_12, out_20, out_21, out_22 : std_logic_vector(63 downto 0);               --result signals {64 bits each}	
	signal sel_00, sel_01, sel_02, sel_10, sel_11, sel_12, sel_20, sel_21, sel_22 : std_logic_vector(2 downto 0);	
	signal out_rdy_demux_00, out_rdy_demux_01, out_rdy_demux_02 : std_logic;
	signal out_rdy_demux_10, out_rdy_demux_11, out_rdy_demux_12 : std_logic;  

	begin
	uut: entity work.dynamic_alu_conf
		port map(	clk => clk,			
					rst => rst,
					in_rdy => in_rdy,
					out_rdy => out_rdy,
					CONFIG_BITS => conf,
					op00 => op_00,
					op01 => op_01,
					op02 => op_02, 
					op10 => op_10, 
					op11 => op_11, 
					op12 => op_12,
					op20 => op_20, 
					op21 => op_21,
					op22 => op_22, 
					A00 => a_00, 
					A01 => a_01, 
					A02 => a_02,
					B00 => b_00, 
					B01 => b_01, 
					B02 => b_02,
					output_00 => out_00,	output_01 => out_01,	output_02 => out_02,	output_10 => out_10,	
					output_11 => out_11,	output_12 => out_12,	output_20 => out_20,	output_21 => out_21,	
					output_22 => out_22);
	
	--------------------------------------------------------------
	-- Clock gen
	--------------------------------------------------------------
	clock_gen : process is
	begin
		wait for 5 ns;
		clk <= '1'; 
		wait for 5 ns;
		clk <= '0'; 
	end process;


	--------------------------------------------------------------
	-- Test file processing
	--------------------------------------------------------------
	stm_test : process is
		variable file_line 	: line;
		variable data 		: std_logic_vector(131 downto 0);
		file 	test_file	: text open read_mode is "C:\Modeltech_pe_edu_10.4a\ALU\dynamic_config_data";
	begin

		------------------------------------------------------------------------------------------------------------------------
		-- Read inputs from hex -> std_logic_vector -> process-> alu(instruction(71 downto 64), instruc(63-32), instruc(31, 0);
		-------------------------------------------------------------------------------------------------------------------------
		rst <= '1';
		wait for 10 ns;
		rst <= '0';
		wait for 50 ns;
		wait for 9 ns;
		
		while not endfile(test_file) loop
			readline(test_file, file_line);
			HREAD(file_line, data);
			conf <= data;
			in_rdy <= '1';
			wait for 20 ns;
		end loop; 
		wait;
	end process;
end testbench;