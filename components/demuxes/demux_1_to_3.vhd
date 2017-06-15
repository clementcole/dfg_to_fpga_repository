----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    08:43:13 07/20/2016 
-- Design Name: 
-- Module Name:    alu_main_32 - Behavioral 
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
library work;
use work.opcodes.all;


entity demux_1_to_3 is 
	port ( 	Previous_ALU_OUTPUT_X_X 			: in std_logic_vector(63 downto 0); -- Includes the out_ready signal to avoid using two demuxes
			Previous_Level_Output_Ready_X_X 	: in std_logic;
			clk		   							: in std_logic;  -- Sync with above ALU
			rst        							: in std_logic;  -- Sync reset with above ALU
			Select_Lines						: in std_logic_vector(2 downto 0);
			Next_Level_ALU_Input_X_0			: out std_logic_vector(31 downto 0);
			Next_Level_ALU_Input_X_1        	: out std_logic_vector(31 downto 0);
			Next_Level_ALU_Input_X_2        	: out std_logic_vector(31 downto 0);
			Next_Level_Input_Ready_X_0			: out std_logic;
			Next_Level_Input_Ready_X_1			: out std_logic;
			Next_Level_Input_Ready_X_2			: out std_logic
			--Next_Level_Input_Ready_X_3        	: out std_logic
			);
end demux_1_to_3;	

architecture behavioral of demux_1_to_3 is
begin
	process(Select_Lines, clk, Previous_Level_Output_Ready_X_X, Previous_ALU_OUTPUT_X_X) is 
	begin
		--if(rising_edge(clk)) then 
			case Select_Lines is 
				when "000" =>
					Next_Level_ALU_Input_X_0 <= Previous_ALU_OUTPUT_X_X(31 downto 0);
					Next_Level_Input_Ready_X_0 <= Previous_Level_Output_Ready_X_X;
				when "001" =>
					Next_Level_ALU_Input_X_1 <= Previous_ALU_OUTPUT_X_X(31 downto 0);
					Next_Level_Input_Ready_X_1 <= Previous_Level_Output_Ready_X_X;
				when "010" => 
					Next_Level_ALU_Input_X_2 <= Previous_ALU_OUTPUT_X_X(31 downto 0);
					Next_Level_Input_Ready_X_2 <= Previous_Level_Output_Ready_X_X;

				--when "011" => 
				--	Next_Level_ALU_Input_X_3 <= Previous_ALU_OUTPUT_X_X(31 downto 0);
				--	Next_Level_Input_Ready_X_3 <= Previous_Level_Output_Ready_X_X;
				when others =>
					NULL;
			end case;
		--end if;
	end process;

end behavioral;