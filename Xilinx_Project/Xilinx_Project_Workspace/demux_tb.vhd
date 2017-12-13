--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   14:48:35 12/13/2017
-- Design Name:   
-- Module Name:   C:/Users/Kinaesthetic/Xilinx/dfg_to_fpga_repository-master/Xilinx_Project/Xilinx_Project_Workspace/demux_tb.vhd
-- Project Name:  Xilinx_Project_Workspace
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: demux_32_to_1
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY demux_tb IS
END demux_tb;
 
ARCHITECTURE behavior OF demux_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT demux_32_to_1
    PORT(
         clk : IN  std_logic;
         select_line : IN  std_logic_vector(7 downto 0);
         clock_enable_input : IN  std_logic;
         clock_enable_output : OUT  std_logic_vector(31 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal select_line : std_logic_vector(7 downto 0) := (others => '0');
   signal clock_enable_input : std_logic := '0';

 	--Outputs
   signal clock_enable_output : std_logic_vector(31 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
   constant clock_enable_input_period : time := 10 ns;
   constant clock_enable_output_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: demux_32_to_1 PORT MAP (
          clk => clk,
          select_line => select_line,
          clock_enable_input => clock_enable_input,
          clock_enable_output => clock_enable_output
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 1 ms.
     

      wait for clk_period*10;
		

      -- insert stimulus here 

		select_line <= X"01";
		clock_enable_input <= '1';
		

      wait;
   end process;

END;
