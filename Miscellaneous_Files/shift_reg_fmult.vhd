library ieee;
use ieee.std_logic_1164.all;

entity shift_reg_fmult is
	port(clk      			: in std_logic;
		 rst				: in std_logic;
	     data_in  	: in std_logic;
	     data_out 	: out std_logic);
end shift_reg_fmult;

architecture arc of shift_reg_fmult is
	signal reg : std_logic_vector(9 downto 0) := (others => '0');

begin
	
	process(clk) is 
	begin
	if( rising_edge(clk)) then
			reg(9) <= data_in;
			reg(8) <= reg(9);
			reg(7) <= reg(8);
			reg(6) <= reg(7);
			reg(5) <= reg(6);
			reg(4) <= reg(5);
			reg(3) <= reg(4);
			reg(2) <= reg(3);
			reg(1) <= reg(2);
			reg(0) <= reg(1);
    elsif(rst = '1') then 	
			reg <= (others => '0');
	end if;
	end process;
	data_out <= reg(0);
end arc;
