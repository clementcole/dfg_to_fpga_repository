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


entity fadd_reg is
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

architecture behavioral of fadd_reg is 
signal dummy1, dummy2 : std_logic;


COMPONENT fp_add is
  PORT (
    a : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    b : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    clk : IN STD_LOGIC;
    sclr : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    result : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    rdy : OUT STD_LOGIC
  );
END COMPONENT;

	component shift_reg_fadd is 
		port(clk      	: in std_logic;
		 	rst	  		: in std_logic;
		 data_in   		: in std_logic;
	     data_out  		: out std_logic);
	end component;

	begin 
		PM_FADD_READY_SIGNAL : shift_reg_fadd
		 port map( clk => clk, rst => rst, data_in => input_ready, data_out => output_ready);

		PM_FADD : fp_add
			port map(A => A, B => B, clk => clk, sclr => rst, ce => '1', result => Result,  rdy => dummy1 );


end architecture;  
