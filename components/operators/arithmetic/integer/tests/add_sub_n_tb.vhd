library ieee;
library work;
use ieee.std_logic_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;
use IEEE.STD_LOGIC_TEXTIO.all;
use STD.TEXTIO.all;
use work.opcodes.all;


entity ADD_SUB_N_TB is
end;

architecture testbench of ADD_SUB_N_TB is

--component add_sub_n is
--	generic ( bits 	: integer);
--		port (	clk 			: in std_logic;
--				A				: in signed(31 downto 0);
--				B				: in signed(31 downto 0);
--				Result 			: out std_logic_vector(32 downto 0));		
--end component;
component  add_sub_reg is
	generic(bits : integer := 32);
	port (
		A     : in signed(31 downto 0);
		B     : in signed(31 downto 0);
		clk   : in std_logic; 
		rst   : in std_logic; 
		input_ready : in std_logic; 
		output_ready : out std_logic; 
		Result : out std_logic_vector(32 downto 0)
		);
end component;

signal A, B : signed(31 downto 0) := (others => '0');
signal Result : std_logic_vector(32 downto 0) := (others => '0');
signal clk, rst, input_ready, output_ready : std_logic;

constant Period 	: time := 10 ns;

begin

	PM_add_sub : add_sub_reg 
		generic map ( bits => 32)
		port map(A     => A, B => B, clk  => clk,  rst => rst,  input_ready => input_ready, output_ready => output_ready,  Result => Result);

clock_gen : process is
begin
	    clk <= '1'; wait for (period / 2);
	    clk <= '0'; wait for (period / 2);
	
end process;


--------------------------------------------------------------
	-- Test file processing
	--------------------------------------------------------------
	stm_test : process is
	begin

		wait for 10 * period;
		-- insert stimulus here 
	 	A <= x"00000003";
	 	B <= x"00000003";
	 	input_ready <= '1';
	 	--Operation <= OPCODE_ADD_SUB;
	 	--input_ready <= '1';
	 	wait for 10 * period;
	 	input_ready <= '0';
	 	wait for 5 * period; 
	 	A <= x"00000009";
	 	B <= x"00000003";
	 	--Operation <= OPCODE_ADD_SUB;
	 	--input_ready <= '1';
	 	wait for 10 * period;
	 end process;
	 
END;
--https://www.youtube.com/watch?v=KWS9A5bhdxM&index=4&list=PL5PHm2jkkXmidJOd59REog9jDnPDTG6IJ&spfreload=1
--http://csg.csail.mit.edu/6.S078/6_S078_2012_www/handouts/lectures/L06-SMIPS.pdf
--https://github.com/warrenm/von-neumann-papers
--http://ggnindia.dronacharya.info/csedept/Downloads/QuestionBank/Even/IV%20sem/Section_A_Unit-2.pdf
--http://www.ece.cmu.edu/~ece447/s15/lib/exe/fetch.php?media=onur-447-spring15-lecture2-isa-afterlecture.pdf
--