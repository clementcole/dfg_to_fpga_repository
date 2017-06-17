library ieee;
use ieee.std_logic_1164.all;

entity shift_reg_ror is
	port(clk      : in std_logic;
		 rst      : in std_logic;
	     data_in  : in std_logic;
	     data_out : out std_logic);
end shift_reg_ror;

architecture arc of shift_reg_ror is
	signal reg : std_logic_vector( 1 downto 0);

begin
	process(clk, rst, data_in) 
	begin
		if(rst = '0') then
			if(rising_edge(clk)) then
				reg(1) <= data_in;
				reg(0) <= reg(1);
			end if;
		elsif(rst = '1') then
			reg <= (others => '0');	
		end if;
	end process;
		data_out <= reg(0);
end arc;
