library ieee;
use ieee.std_logic_1164.all;

entity shift_reg_fadd is
	port(clk      			: in std_logic;
		 rst				: in std_logic;
	     data_in  	: in std_logic;
	     data_out 	: out std_logic);
end shift_reg_fadd;

architecture arc of shift_reg_fadd is
	signal reg : std_logic_vector(8 downto 0) := (others => '0');

begin
	
	process(clk,rst, data_in, reg) is 
	begin
		if(rst = '0') then
			if( clk = '1') then
					reg(8) <= data_in;
					reg(7) <= data_in;
					reg(6) <= data_in;
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