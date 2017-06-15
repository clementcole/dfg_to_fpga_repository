library ieee;
use ieee.std_logic_1164.all;

entity shift_reg_mult is
	port(clk      			: in std_logic;
		 rst				: in std_logic;
	     mult_input_ready  	: in std_logic;
	     mult_output_ready 	: out std_logic);
end shift_reg_mult;

architecture arc of shift_reg_mult is
	signal reg : std_logic_vector(6 downto 0) := (others => '0');

begin
	--mult_output_ready <= reg(0);
	process(clk, rst, mult_input_ready) is 
	begin
	if (rst = '0') then 
		if( rising_edge(clk) ) then
				reg(6) <= mult_input_ready;
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
	mult_output_ready <= reg(0);
end arc;
