----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    22:20:20 12/10/2017 
-- Design Name: 
-- Module Name:    demux_32_to_1 - arch 
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
use IEEE.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;


-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity demux_32_to_1 is
    Port ( 
--			  clk							: in	STD_LOGIC;
			  select_line 				: in  STD_LOGIC_VECTOR (7 downto 0);
           clock_enable_input 	: in  STD_LOGIC;
           clock_enable_output 	: out STD_LOGIC_VECTOR (31 downto 0)
			);
			
end demux_32_to_1;

architecture Behavioral of demux_32_to_1 is

begin

  process(clock_enable_input,select_line)
	begin
		--if(rising_edge(clk)) then
        case select_line is
            when X"00" =>
                clock_enable_output(0) <= clock_enable_input;
					 clock_enable_output(31 downto 1) <= "0000000000000000000000000000000"; 
					 
            when X"01" =>
                clock_enable_output(1) <= clock_enable_input;
					 clock_enable_output(0) <= '0';
					 clock_enable_output(31 downto 2) <= "000000000000000000000000000000"; 
					 
            when X"03" =>
                clock_enable_output(2) <= clock_enable_input;
					 clock_enable_output(1 downto 0) <= "00";
					 clock_enable_output(31 downto 3) <= "00000000000000000000000000000";
					 
            when X"04" =>
                clock_enable_output(3) <= clock_enable_input;
					 clock_enable_output(2 downto 0) <= "000";
					 clock_enable_output(31 downto 4) <= "0000000000000000000000000000";
					 
            when X"05" =>
                clock_enable_output(4) <= clock_enable_input;
					 clock_enable_output(3 downto 0) <= "0000";
					 clock_enable_output(31 downto 5) <= "000000000000000000000000000";
					 
            when X"06" =>
                clock_enable_output(5) <= clock_enable_input;
					 clock_enable_output(4 downto 0) <= "00000";
					 clock_enable_output(31 downto 6) <= "00000000000000000000000000";
					 
            when X"08" =>
                clock_enable_output(6) <= clock_enable_input;
					 clock_enable_output(5 downto 0) <= "000000";
					 clock_enable_output(31 downto 7) <= "0000000000000000000000000";
					 
            when X"0B" =>
                clock_enable_output(7) <= clock_enable_input;
					 clock_enable_output(6 downto 0) <= "0000000";
					 clock_enable_output(31 downto 8) <= "000000000000000000000000";
					 
            when X"0C" =>
                clock_enable_output(8) <= clock_enable_input;
					 clock_enable_output(7 downto 0) <= "00000000";
					 clock_enable_output(31 downto 9) <= "00000000000000000000000";
					 
            when X"09" =>
                clock_enable_output(9) <= clock_enable_input;
					 clock_enable_output(8 downto 0) <= "000000000";
					 clock_enable_output(31 downto 10) <= "0000000000000000000000";
					 
            when X"0A" =>
                clock_enable_output(10) <= clock_enable_input;
					 clock_enable_output(9 downto 0) <= "0000000000";
					 clock_enable_output(31 downto 11) <= "000000000000000000000";
					 
            when X"0D" =>
                clock_enable_output(11) <= clock_enable_input;
					 clock_enable_output(10 downto 0) <= "00000000000";
					 clock_enable_output(31 downto 12) <= "00000000000000000000";
					 
            when X"0E" =>
                clock_enable_output(12) <= clock_enable_input;
					 clock_enable_output(11 downto 0) <= "000000000000";
					 clock_enable_output(31 downto 13) <= "0000000000000000000";
					 
            when X"0F" =>
                clock_enable_output(13) <= clock_enable_input;
					 clock_enable_output(12 downto 0) <= "0000000000000";
					 clock_enable_output(31 downto 14) <= "000000000000000000";
					 
            when X"10" =>
                clock_enable_output(14) <= clock_enable_input;
					 clock_enable_output(13 downto 0) <= "00000000000000";
					 clock_enable_output(31 downto 15) <= "00000000000000000";
					 
            when X"11" =>
                clock_enable_output(15) <= clock_enable_input;
					 clock_enable_output(14 downto 0) <= "000000000000000";
					 clock_enable_output(31 downto 16) <= "0000000000000000";

            when X"07" =>
                clock_enable_output(16) <= clock_enable_input;
					 clock_enable_output(15 downto 0) <= "0000000000000000";
					 clock_enable_output(31 downto 17) <= "000000000000000";
					 
            when X"12" =>
                clock_enable_output(17) <= clock_enable_input;
					 clock_enable_output(16 downto 0) <= "00000000000000000";
					 clock_enable_output(31 downto 18) <= "00000000000000";
					 -------------Don't need anything past this atm-----------
            when others =>
                NULL;
		end case;
--end if;
 	end process;
end Behavioral;

