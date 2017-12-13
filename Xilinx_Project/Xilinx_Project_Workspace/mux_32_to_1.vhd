----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    21:59:51 12/10/2017 
-- Design Name: 
-- Module Name:    mux_32_to_1 - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity mux_32_to_1 is
    Port ( 
			  --clk							: in std_logic;
			  select_line 				: in  STD_LOGIC_VECTOR (4 downto 0);
           clock_enable_input 	: in  STD_LOGIC;
           clock_enable_output 	: out  STD_LOGIC		  
			);
end mux_32_to_1;

architecture Behavioral of mux_32_to_1 is

begin

process(select_line, clk)
	begin
	--if(rising_edge(clk)) then
        case select_line is
            when "00000" =>
                clock_enable_output <= clock_enable_input;
					 
            when "00001" =>
                clock_enable_output <= clock_enable_input;
					 
            when "00010" =>
                clock_enable_output <= clock_enable_input;
					 
            when "00011" =>
                clock_enable_output <= clock_enable_input;
					 
            when "00100" =>
                clock_enable_output <= clock_enable_input;
					 
            when "00101" =>
                clock_enable_output <= clock_enable_input;
					 
            when "00110" =>
                clock_enable_output <= clock_enable_input;
					 
            when "00111" =>
                clock_enable_output <= clock_enable_input;
					 
            when "01000" =>
                clock_enable_output <= clock_enable_input;
					 
            when "01001" =>
                clock_enable_output <= clock_enable_input;
					 
            when "01010" =>
                clock_enable_output <= clock_enable_input;
					 
            when "01011" =>
                clock_enable_output <= clock_enable_input;
					 
            when "01100" =>
                clock_enable_output <= clock_enable_input;
					 
            when "01101" =>
                clock_enable_output <= clock_enable_input;
					 
            when "01110" =>
                clock_enable_output <= clock_enable_input;
					 
            when "01111" =>
                clock_enable_output <= clock_enable_input;
				--------	 
            when "10000" =>
                clock_enable_output <= clock_enable_input;
					 
            when "10001" =>
                clock_enable_output <= clock_enable_input;
					 -------------Don't need anything past this atm-----------
            
            when others =>
                NULL;
        end case;
	
	--end if;
	
end process;

end Behavioral;

