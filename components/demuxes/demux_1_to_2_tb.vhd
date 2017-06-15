----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    08:43:13 07/20/2016 
-- Design Name: 
-- Module Name:    alu_main_32 - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.opcodes.all;


entity demux_1_to_2_tb is
end demux_1_to_2_tb;


architecture testbench of demux_1_to_2_tb is
	signal dest_A00, dest_A01 : std_logic_vector(31 downto 0);
	signal src : std_logic_vector(63 downto 0);
	signal sel : std_logic;
	signal test_clk : std_logic;

	begin
		uut: entity work.demux_1_to_2 
			port map (  clk        => test_clk,
					    src        => src,
					    sel        => sel, 
					    dest_inX0     => dest_A00,
					    dest_inX1     => dest_A01 );
	--------------------------------------------------------------
	-- Clock gen
	--------------------------------------------------------------
	clock_gen : process is
	begin
		wait for 5 ns;
		test_clk <= '1'; 
		wait for 5 ns;
		test_clk <= '0'; 
	end process;


	--------------------------------------------------------------
	-- Unit test
	--------------------------------------------------------------
	test_proc: process 
	begin
		wait for 10 ns;
		src <= x"FFFFFFFD00000004";
		sel <= 'X';
		
		wait for 20 ns;
		
		src <= x"0000000400000012";
		sel <= '0';
		
		wait for 30 ns;
		
		src <= x"0000001000000013";
		sel <= '1';
		
		wait for 40 ns;
		
		src <= x"0000001200000010";
		sel <= '0';
			
		wait for 50 ns;
		
		src <= x"00000013FFFFFFFD";
		sel <= '1';
		
		wait;	

	end process;
end testbench;