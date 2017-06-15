--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   11:31:56 06/12/2017
-- Design Name:   
-- Module Name:   C:/Modeltech_pe_edu_10.4a/ALU/ALU_TEST.vhd
-- Project Name:  ALU
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: AlU_MAIN_32
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
library ieee;
library work;
use ieee.std_logic_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;
use IEEE.STD_LOGIC_TEXTIO.all;
use STD.TEXTIO.all;
use work.opcodes.all;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY ALU_TEST IS
END ALU_TEST;
 
ARCHITECTURE behavior OF ALU_TEST IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT AlU_MAIN_32
    PORT(
         clk : IN  std_logic;
         reset : IN  std_logic;
         A : IN  std_logic_vector(31 downto 0);
         B : IN  std_logic_vector(31 downto 0);
         Operation : IN  std_logic_vector(7 downto 0);
         Result : OUT  std_logic_vector(63 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal reset : std_logic := '0';
   signal A : std_logic_vector(31 downto 0) := (others => '0');
   signal B : std_logic_vector(31 downto 0) := (others => '0');
   signal Operation : std_logic_vector(7 downto 0) := (others => '0');

 	--Outputs
   signal Result : std_logic_vector(63 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: AlU_MAIN_32 PORT MAP (
          clk => clk,
          reset => reset,
          A => A,
          B => B,
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
 
  --------------------------------------------------------------
  -- Test file processing
  --------------------------------------------------------------
  stm_test : process is
    variable file_line  : line;
    variable data     : std_logic_vector(71 downto 0);
    file  test_file : text open read_mode is "/home/clement/workspace/ALU_VHDL/VHDL-Components/alu/data_input";
  begin
    ------------------------------------------------------------------------------------------------------------------------
    -- Read inputs from hex -> std_logic_vector -> process-> alu(instruction(71 downto 64), instruc(63-32), instruc(31, 0);
    -------------------------------------------------------------------------------------------------------------------------
    reset <= '0';
    wait for 1 * Period;
    reset <= '1';
    wait for Period;
    reset <= '0';
    while not endfile(test_file) loop
      readline(test_file, file_line);
      HREAD(file_line, data); 
      --test_instruction <= (data);
      Operation <= data(71 downto 64);
      A        <=  (data(63 downto 32));
      B        <=  (data(31 downto 0)); 
      wait for 40 * Period;
      wait;
   end process;

END;
