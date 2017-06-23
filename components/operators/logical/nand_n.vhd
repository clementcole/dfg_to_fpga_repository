library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.opcodes.all;


entity nand_n is
	generic ( bits 	: integer := 32);
		port (	clk 			: in std_logic;
				A				: in std_logic_vector(31 downto 0);
				B				: in std_logic_vector(31 downto 0);
				Result 			: out std_logic_vector(31 downto 0));
	--Overflow : out std_logic;
	
		
end entity nand_n;

architecture behave of nand_n is
	signal temp : std_logic_vector(bits-1 downto 0); 

	--signal output : signed(32 downto 0);
	--signal out_rdy : std_logic;
	--
	-- Full adder component declaration here
	--
	-----------------------------------------
	-----------------------------------------
	--
	begin
		process(clk, A, B) is
		begin
			if(clk = '1') then 
				temp <= (A nand B);
			end if;
		end process;
		Result <= temp;
end behave;