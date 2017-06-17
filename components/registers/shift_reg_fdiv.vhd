library ieee;
use ieee.std_logic_1164.all;

entity shift_reg_fdiv is
	port(clk      			: in std_logic;
		 rst				: in std_logic;
	     data_in  	: in std_logic;
	     data_out 	: out std_logic);
end shift_reg_fdiv;

architecture arc of shift_reg_fdiv is
	signal reg : std_logic_vector(29 downto 0) := (others => '0');

begin
	
	process(clk, rst, data_in) is 
	begin
	if(rst = '0') then
		if( rising_edge(clk)) then
				reg(29) <= data_in;
				reg(28) <= reg(29);
				reg(27) <= reg(28);
				reg(26) <= reg(27);
				reg(25) <= reg(26);
				reg(24) <= reg(25);
				reg(23) <= reg(24);
				reg(22) <= reg(23);
				reg(21) <= reg(22);
				reg(20) <= reg(21);
				reg(19) <= reg(20);
				reg(18) <= reg(19);
				reg(17) <= reg(18);
				reg(16) <= reg(17);
				reg(15) <= reg(16);
				reg(14) <= reg(15);
				reg(13) <= reg(14);
				reg(12) <= reg(13);
				reg(11) <= reg(12);
				reg(10) <= reg(11);
				reg(9) <= reg(10);
				reg(8) <= reg(9);
				reg(7) <= reg(8);
				reg(6) <= reg(7);
				reg(5) <= reg(6);
				reg(4) <= reg(5);
				reg(3) <= reg(4);
				reg(2) <= reg(3);
				reg(1) <= reg(2);
				reg(0) <= reg(1);
		end if;
    elsif(rst = '1') then 
    		reg <= (others => '0');
	end if;
	end process;
	data_out <= reg(0);
end arc;
