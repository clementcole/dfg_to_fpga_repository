library ieee;
use ieee.std_logic_1164.all;

entity shift_reg_fsub is
	port(clk      			: in std_logic;
		 rst				: in std_logic;
	     data_in  	: in std_logic;
	     data_out 	: out std_logic);
end shift_reg_fsub;

architecture arc of shift_reg_fsub is
	signal reg : std_logic_vector(14 downto 0) := (others => '0');

begin
	
	process(clk) is 
	begin
	if( rising_edge(clk)) then
			reg(14) <= data_in;
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
    elsif(rst = '1') then 
			reg(14) <= '0';
			reg(13) <= '0';
			reg(12) <= '0';
			reg(11) <= '0';
			reg(10) <= '0';
			reg(9) <= '0';
			reg(8) <= '0';
			reg(7) <= '0';
			reg(6) <= '0';
			reg(5) <= '0';
			reg(4) <= '0';
			reg(3) <= '0';
			reg(2) <= '0';
			reg(1) <= '0';
			reg(0) <= '0';
	end if;
	end process;
	data_out <= reg(0);
end arc;
