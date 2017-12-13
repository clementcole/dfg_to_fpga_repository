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


entity fmult_reg is
	generic(bits : integer := 32);
	port (
		A     : in std_logic_vector(31 downto 0);
		B     : in std_logic_vector(31 downto 0);
		clk   : in std_logic; 
		rst   : in std_logic; 
		input_ready : in std_logic; 
		output_ready : out std_logic; 
		Result : out std_logic_vector(31 downto 0)
		);
end;

architecture behavioral of fmult_reg is 

	component fp_mult is    --
		port(  
			a 	: IN STD_LOGIC_VECTOR(31 DOWNTO 0);
			b 	: IN STD_LOGIC_VECTOR(31 DOWNTO 0);
			clk 	: IN STD_LOGIC;
			result : OUT STD_LOGIC_VECTOR(31 DOWNTO 0));
	end component;

	component shift_reg_fmult is 
		port(clk      	: in std_logic;
		 	rst	  		: in std_logic;
		 data_in   		: in std_logic;
	     data_out  		: out std_logic);
	end component;

	begin 
		PM_FMULT_READY_SIGNAL : shift_reg_fmult
		 port map( clk => clk, 
					  rst => rst, 
					  data_in => input_ready, 
					  data_out => output_ready);

		PM_FMULT : fp_mult
		 port map(a => A, 
					 b => B, 
					 clk => clk, 
					 result => Result);

end architecture;  
