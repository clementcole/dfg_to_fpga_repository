library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;
library work;


entity srl_n is
	generic ( bits 	: integer);
		port (	clk 			: in std_logic;
				A				: in std_logic_vector(31 downto 0);
				B				: in std_logic_vector(31 downto 0);
				Result 			: out std_logic_vector(31 downto 0));
	--Overflow : out std_logic;
	
		
end entity srl_n;

architecture behave of srl_n is 
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
			if (clk = '1') then
				Result <= std_logic_vector(to_stdlogicvector(to_bitvector(std_logic_vector(A)) srl to_integer(unsigned(B))) );
			end if;
		end process;
		
			
end behave;
