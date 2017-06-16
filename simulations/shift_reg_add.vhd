library ieee;
use ieee.std_logic_1164.all;

entity shift_reg_add is
	port(clk      : in std_logic;
		 rst	  : in std_logic;
		 add_sub_input_ready   : in std_logic;
	     add_sub_output_ready  : out std_logic);
end shift_reg_add;

architecture arc of shift_reg_add is
	signal reg : std_logic_vector(0 downto 0);

begin
	--mult_output_ready <= reg(0);
	process(clk,rst, add_sub_input_ready) is 
		begin
		if (rst = '0') then
			if(rising_edge(clk)) then 
				add_sub_output_ready <= add_sub_input_ready;
			end if;
		elsif(rst = '1') then 
			add_sub_output_ready <= '0';
		end if;
	end process;
	--add_sub_output_ready <= reg(0);
	
end arc;
