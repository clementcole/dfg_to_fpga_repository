--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   13:56:22 12/13/2017
-- Design Name:   
-- Module Name:   C:/Users/Kinaesthetic/Xilinx/dfg_to_fpga_repository-master/Xilinx_Project/Xilinx_Project_Workspace/dfga_new_tb.vhd
-- Project Name:  Xilinx_Project_Workspace
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: AlU_EXPERIMENT_32
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
 
ENTITY dfga_new_tb IS
END dfga_new_tb;
 
ARCHITECTURE behavior OF dfga_new_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT AlU_EXPERIMENT_32
    PORT(
         A : IN  std_logic_vector(31 downto 0);
         B : IN  std_logic_vector(31 downto 0);
         clk : IN  std_logic;
         en : IN  std_logic;
         rst : IN  std_logic;
         input_ready : IN  std_logic;
         output_ready : OUT  std_logic;
         Operation : IN  std_logic_vector(7 downto 0);
         Result : OUT  std_logic_vector(63 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal A : std_logic_vector(31 downto 0) := (others => '0');
   signal B : std_logic_vector(31 downto 0) := (others => '0');
   signal clk : std_logic := '0';
   signal en : std_logic := '0';
   signal rst : std_logic := '0';
   signal input_ready : std_logic := '0';
   signal Operation : std_logic_vector(7 downto 0) := (others => '0');

 	--Outputs
   signal output_ready : std_logic;
   signal Result : std_logic_vector(63 downto 0);

   -- Clock period definitions
   constant clk_period : time := 0.1 ms;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: AlU_EXPERIMENT_32 PORT MAP (
          A => A,
          B => B,
          clk => clk,
          en => en,
          rst => rst,
          input_ready => input_ready,
          output_ready => output_ready,
          Operation => Operation,
          Result => Result
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
      -- hold reset state for 100 ns.
      wait for 1 ms;
      -- insert stimulus here 
		en <= '1';
		input_ready <= '1';

		A <= "01001011101101011110111111001011";
		B <= "01001011001101010110111111101011";
		Operation <= x"01";

      wait;
   end process;

END;
