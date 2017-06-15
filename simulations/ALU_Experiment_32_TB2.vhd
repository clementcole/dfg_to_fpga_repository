library ieee;
library work;
use ieee.std_logic_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;
use IEEE.STD_LOGIC_TEXTIO.all;
use STD.TEXTIO.all;
use work.opcodes.all;



entity ALU_EXPERIMENT_32_TB2 is
end;

architecture testbench of ALU_EXPERIMENT_32_TB2 is

----------------------------------------------
	-- ALU COMPONENT
	----------------------------------------------
	component ALU_EXPERIMENT_32 is
	generic(data_width 	:	 	integer := 32);
	port(   
		A 		:		in std_logic_vector(31 downto 0); --input operands
		B		: 		in std_logic_vector(31 downto 0);
		clk		:       in std_logic;
		rst     :     	in std_logic;
		input_ready	:		in std_logic;
		output_ready	:	out std_logic;
		Operation	: 		in std_logic_vector(7 downto 0); --select operation
		Result 		: 		out std_logic_vector(63 downto 0));
		--count		:       buffer std_logic_vector(5 downto 1));  --Reg3
	end component;

	----------------------------------------------------------
	-- Signal declarations
	----------------------------------------------------------
	signal A		: std_logic_vector(31 downto 0)  :=  (others => '0');
	signal B		: std_logic_vector(31 downto 0)  :=  (others => '0');
	signal clk		: std_logic := '1';
	signal rst		: std_logic := '1';
	signal input_ready		: std_logic  := '0';
	signal output_ready		: std_logic  := '0';
	signal Operation	: std_logic_vector(7 downto 0)  := OPCODE_IDLE;
	signal Result		: std_logic_vector(63 downto 0); --:= (others => '0');
	
	constant Period 	: time := 10 ns;
	
	begin
	----------------------------------------------------------
	-- Port mapping
	----------------------------------------------------------
	uut : ALU_EXPERIMENT_32
		generic map(data_width => 32)
		port map(A => A, B => B, clk => clk,   rst => rst,  input_ready => input_ready, output_ready => output_ready, Operation => Operation, Result => Result);	

	--------------------------------------------------------------
	-- Clock gen
	--------------------------------------------------------------
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
		rst <= '1';
		wait for 4 * period;
		rst <= '0';
		wait for 20 * period;
		
		--Operation <= OPCODE_MULT;
	    A <= x"00000001";
	    B <= x"00000001";
	    input_ready <= '1';
	    Operation <= OPCODE_MULT;
	    
	    wait for (2 * period);

	    A <= x"00000001";
	    B <= x"00000001";
	  
	    wait for (2 * period);
	    A <= x"00000002";
	    B <= x"00000002";
	    wait for (2 * period);
	    A <= x"00000003";
	    B <= x"00000003";
	    wait for (2 * period);
	    A <= x"00000003";
	    B <= x"00000003";
	    wait for (2 * period);
	    A <= x"00000005";
	    B <= x"00000005";
	    wait for (2 * period);
	    A <= x"00000006";
	     B <= x"00000003";
	    wait for (8 * period); 
	    A <= x"00000007";
	     B <= x"00000003";
	    wait for (8 * period);
	    A <= x"00000008";
	     B <= x"00000003";
	    wait for (8 * period);
	    A <= x"00000009";
	     B <= x"00000003";
	    wait for (8 * period);
	    A <= x"0000000A";
	     B <= x"00000003";
	    wait for (8 * period);
	    A <= x"0000000B";
	     B <= x"00000003";
	   wait for (8 * period);
	    A <= x"0000000C";
	     B <= x"00000003";
	    wait for (8 * period);
	    A <= x"0000000D";
	     B <= x"00000003";
	   wait for (8 * period);
	    A <= x"0000000E";
	     B <= x"00000003";
	    wait for (8 * period);
	    A <= x"0000000F";
	     B <= x"00000003";
	    wait for (8 * period);
	    A <= x"00000010";
	     B <= x"00000003";
	    wait for (8 * period);
	    A <= x"00000000";
	    B <= x"00000003";
	    wait for (8 * period);
		--input_ready <= '1';
	 	A <= x"00000003";
	 	B <= x"00000003";
	 	wait for (8 * period);
	 	A <= x"00000003";
	 	B <= x"00000003";
	 	wait for (8 * period);
	 end process;
	 
END;

		