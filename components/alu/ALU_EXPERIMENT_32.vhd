---------------------------------------------------------------------------------
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

library UNISIM;
use UNISIM.vcomponents.all;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.opcodes.all;


entity AlU_EXPERIMENT_32 is
	generic(data_width 	:	 	integer := 32);
	port(   
		A 						:		in std_logic_vector(31 downto 0); --input operands
		B						: 		in std_logic_vector(31 downto 0);
		clk					:     in std_logic;
		en						:		in std_logic;
		rst 					:     in std_logic;
		input_ready			:		in std_logic; 
		output_ready		:		out std_logic;
		Operation			: 		in std_logic_vector(7 downto 0); --select operation
		Result 				: 		out std_logic_vector(63 downto 0)
		--result_rdy      :     out std_logic_vector(17 downto 0)
		);
end;



architecture BEHAVIORAL of ALU_EXPERIMENT_32 is
--------------------------------------
--Signals inputs/outputs temporary
---------------------------------------

--Functional Bus
signal op								: std_logic_vector(7 downto 0)  := (others => '0');

--Internal Input Buses
signal invertB, inputA, inputB  	: std_logic_vector(31 downto 0) := (others => '0');

--Internal Output Buses
signal output, temp					: std_logic_vector(63 downto 0) := (others => '0');
signal parallel_load_signals		: std_logic_vector(11 downto 0);
signal EnableDin, EnableDout		: std_logic;
signal A_sign							: std_logic;
signal B_sign							: std_logic;
signal R_sign							: std_logic;

--Input/output Ready signals
signal input_ready_signal			: std_logic;
signal output_ready_signal 		: std_logic;
signal in_ready 						: std_logic_vector(18 downto 0) := (others => '0');
signal result_ready					: std_logic_vector(18 downto 0) := (others => '0'); 


--Result for arithmetic operations
signal r_add_sub 	: std_logic_vector(32 downto 0) := (others => '0');-- 	:= (others => '0');
signal r_mult		: std_logic_vector(63 downto 0) := (others => '0');
signal r_div		: std_logic_vector(63 downto 0) := (others => '0');

--Result for logical operations
signal r_or 		: std_logic_vector(31 downto 0) := (others => '0');
signal r_rol 		: std_logic_vector(31 downto 0) := (others => '0');
signal r_and 		: std_logic_vector(31 downto 0) := (others => '0');
signal r_xnor 		: std_logic_vector(31 downto 0) := (others => '0');
signal r_nor 		: std_logic_vector(31 downto 0) := (others => '0');
signal r_not 		: std_logic_vector(31 downto 0) := (others => '0');
signal r_xor 		: std_logic_vector(31 downto 0) := (others => '0');
signal r_sla 		: std_logic_vector(31 downto 0) := (others => '0'); 
signal r_sra 		: std_logic_vector(31 downto 0) := (others => '0'); 
signal r_sll 		: std_logic_vector(31 downto 0) := (others => '0');-- 	:= (others => '0');
signal r_srl 		: std_logic_vector(31 downto 0) := (others => '0');--    := (others => '0');
signal r_ror 		: std_logic_vector(31 downto 0) := (others => '0');
signal r_nand		: std_logic_vector(31 downto 0) := (others => '0');
--Floating Point Operations
signal r_fadd 		: std_logic_vector(31 downto 0) := (others => '0');
signal r_fsub 		: std_logic_vector(31 downto 0) := (others => '0');
signal r_fmult 	: std_logic_vector(31 downto 0) := (others => '0');
signal r_fdiv 		: std_logic_vector(31 downto 0) := (others => '0'); 

--Miscelleneous signals
signal cin 									: std_logic;
signal cout 								: std_logic;
signal rst_counter              		: std_logic;
signal alu_operation_ready          : std_logic;
signal clock_buf0							: std_logic;
signal clock_buf1							: std_logic;
signal clock_buf2							: std_logic;
signal clock_buf3							: std_logic;
signal clock_buf4							: std_logic;
signal clock_buf5							: std_logic;
signal clock_buf6							: std_logic;
signal clock_buf7							: std_logic;
signal clock_buf8							: std_logic;
signal clock_buf9							: std_logic;
signal clock_buf10						: std_logic;
signal clock_buf11						: std_logic;
signal clock_buf12						: std_logic;
signal clock_buf13						: std_logic;
signal clock_buf14						: std_logic;
signal clock_buf15						: std_logic;
signal clock_buf16						: std_logic;
signal clock_buf17						: std_logic;


signal clock_buf_en							: std_logic_vector(31 downto 0);



--Fifo signals 
signal rd_en_A, rd_en_B             : std_logic := '0';
signal full_fifo_A, full_fifo_B     : std_logic := '0';
signal empty_fifo_A, empty_fifo_B   : std_logic := '0'; 
signal input_ready_A, input_ready_B : std_logic := '0';
signal m_axis_result_tvalid 			: std_logic;
--signal dout_A, dout_B   				: std_logic_vector(31 downto 0);

	

	--component accumulator IS
  	--PORT (
   -- 	b : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
   -- 	clk : IN STD_LOGIC;
   -- 	add : IN STD_LOGIC;
   -- 	ce : IN STD_LOGIC;
   -- 	bypass : IN STD_LOGIC;
   -- 	q : OUT STD_LOGIC_VECTOR(47 DOWNTO 0)
  --	);
	--end component;

	--component sine_function IS
  --	PORT (
  --  	phase_in : IN STD_LOGIC_VECTOR(30 DOWNTO 0);
  --  	x_out : OUT STD_LOGIC_VECTOR(30 DOWNTO 0);
  --  	y_out : OUT STD_LOGIC_VECTOR(30 DOWNTO 0);
 ---   	rdy : OUT STD_LOGIC;
  -- 	 	clk : IN STD_LOGIC;
 --   	ce : IN STD_LOGIC
 -- 	);
--	end component;

	component add_sub_reg is
		generic ( bits 	: integer  := 32);
		port (
			A					: in signed(31 downto 0);
			B					: in signed(31 downto 0);
			clk				: in std_logic;
			rst 				: in std_logic;
			--en					: in std_logic;
			input_ready 	: in std_logic;
			output_ready 	: out std_logic;
			Result 			: out std_logic_vector(32 downto 0)
			);
	end component;
	
	--component add_sub_n is 
	--generic ( bits   : integer :=  32);
	--port ( 
	--		clk  : in std_logic; 
	--		A    : in signed(31 downto 0);
	--		B    : in signed(31 downto 0);
	--		result : out std_logic_vector(32 downto 0));
	--end component;

	component fp_add is
	  PORT (
			a 					: IN STD_LOGIC_VECTOR(31 DOWNTO 0);
			b 					: IN STD_LOGIC_VECTOR(31 DOWNTO 0);
			clk 				: IN STD_LOGIC;
			sclr 				: IN STD_LOGIC;
			ce 				: IN STD_LOGIC;
			result 			: OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
			rdy 				: OUT STD_LOGIC
			);
	end component;
	
	component mult_reg is
		generic(bits 		:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(63 downto 0)
			);
	end component;
	
	component or_reg is 	--Completed
		generic(bits 		:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0)
			);
	end component;

	component nor_reg is    --Completed
	generic(bits 			:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0)
			);
	end component;

	component and_reg is     --Completed
	generic(bits 			:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:       in std_logic;
			rst 				:       in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0)
			);
	end component;

	--component add_sub_n is
	--generic ( bits 		: integer :=  32);
	--		port (	
	--			clk 			: in std_logic;
	--			A				: in signed(31 downto 0);
	--			B				: in signed(31 downto 0);
	--			Result 		: out std_logic_vector(32 downto 0)
	--			);
	--end component;

	component xor_reg is     --Completed
	generic(bits 			:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0));
	end component;

	component xnor_reg is    --Completed
	generic(bits 			:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0));
	end component;

	component not_reg is    --Completed
	generic(bits 			:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0));
	end component;

	component sll_reg is    --Completed
	generic(bits 			:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0));
	end component;
  
	component srl_reg is    --Completed
	generic(bits 			:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0));
	end component;

	component sla_reg is    --Completed
	generic(bits 			:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0));
	end component;

	component sra_reg is    --Completed
	generic(bits 			:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0));
	end component;

	component ror_reg is    --Completed
	generic(bits 			:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0));
	end component;

	component rol_reg is    --Completed
		generic(bits 		:	 	integer := 32);
		port(   
			A 					:		in std_logic_vector(31 downto 0); --input operands
			B					: 		in std_logic_vector(31 downto 0);
			clk				:     in std_logic;
			rst 				:     in std_logic;
			input_ready		:		in std_logic; 
			output_ready	:		out std_logic;
			Result 			: 		out std_logic_vector(31 downto 0));
	end component;

	component fmult_reg is
		generic(bits 		: 		integer := 32);
		port (
			A     			: 		in std_logic_vector(31 downto 0);
			B     			: 		in std_logic_vector(31 downto 0);
			clk   			: 		in std_logic; 
			rst   			: 		in std_logic; 
			input_ready 	: 		in std_logic; 
			output_ready 	: 		out std_logic; 
			Result 			: 		out std_logic_vector(31 downto 0)
		);
	end component;

	component fsub_reg is
		generic(bits 		: 		integer := 32);
			port (
			A     			: 		in std_logic_vector(31 downto 0);
			B     			: 		in std_logic_vector(31 downto 0);
			clk  				: 		in std_logic; 
			rst  				: 		in std_logic; 
			input_ready 	: 		in std_logic; 
			output_ready 	:		out std_logic; 
			Result 			: 		out std_logic_vector(31 downto 0)
			);
	end component;

	component fadd_reg is
	generic(bits : integer := 32);
	port (
		A     				: 		in std_logic_vector(31 downto 0);
		B     				: 		in std_logic_vector(31 downto 0);
		clk   				: 		in std_logic; 
		rst   				: 		in std_logic; 
		input_ready 		: 		in std_logic; 
		output_ready 		: 		out std_logic; 
		Result 				: 		out std_logic_vector(31 downto 0)
		);
	end component;

	component fdiv_reg is
		port (
			A     			: 		in std_logic_vector(31 downto 0);
			B     			: 		in std_logic_vector(31 downto 0);
			clk   			: 		in std_logic; 
			rst   			: 		in std_logic; 
			input_ready 	: 		in std_logic; 
			output_ready 	:		out std_logic; 
			Result 			: 		out std_logic_vector(31 downto 0)
			);
	end component;
		
	component fifo_32 is 
 		PORT (
    		clk 				: 		IN STD_LOGIC;
    		rst 				: 		IN STD_LOGIC;
   		din 				: 		IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    		wr_en 			: 		IN STD_LOGIC;
    		rd_en 			: 		IN STD_LOGIC;
    		dout 				: 		OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    		full 				: 		OUT STD_LOGIC;
    		empty 			: 		OUT STD_LOGIC
  	);
	end component;

	component nand_reg is
	generic(bits 			: 		integer := 32);
		port(
			A 					: 		in std_logic_vector(31 downto 0); --input operands
			B 					: 		in std_logic_vector(31 downto 0);
			clk 				: 		in std_logic;
			rst				: 		in std_logic;
			input_ready 	: 		in std_logic;
			output_ready	: 		out std_logic;
			Result			: 		out std_logic_vector(31 downto 0));
	end component;
	
	COMPONENT demux_32_to_1
		PORT(
		--	clk							: IN STD_LOGIC;    --Legacy
			select_line 				: IN std_logic_vector(7 downto 0);
			clock_enable_input 		: IN std_logic;          
			clock_enable_output 		: OUT std_logic_vector(31 downto 0)
			);
	END COMPONENT;
	
begin	

	Inst_demux_32_to_1: demux_32_to_1 
	  PORT MAP(
		--			clk => clk,    --Legacy
					select_line => operation,
					clock_enable_input => clk,
					clock_enable_output => clock_buf_en
	);

	-- BUFGCE: Global Clock Buffer with Clock Enable
	-- 7 Series
	-- Xilinx HDL Libraries Guide, version 2012.2

	BUFGCE_inst_add_sub :  BUFGCE
		port map (
			 O => clock_buf0, -- 1-bit output: Clock output
			 CE  => clock_buf_en(0), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_MULT :  BUFGCE
		port map (
			 O => clock_buf1, -- 1-bit output: Clock output
			 CE  => clock_buf_en(1), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_OR :  BUFGCE
		port map (
			 O => clock_buf2, -- 1-bit output: Clock output
			 CE  => clock_buf_en(2), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_NOR :  BUFGCE
		port map (
			 O => clock_buf3, -- 1-bit output: Clock output
			 CE  => clock_buf_en(3), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_XOR :  BUFGCE
		port map (
			 O => clock_buf4, -- 1-bit output: Clock output
			 CE  => clock_buf_en(4), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_XNOR :  BUFGCE
		port map (
			 O => clock_buf5, -- 1-bit output: Clock output
			 CE  => clock_buf_en(5), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_NOT :  BUFGCE
		port map (
			 O => clock_buf6, -- 1-bit output: Clock output
			 CE  => clock_buf_en(6), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_SLL :  BUFGCE
		port map (
			 O => clock_buf7, -- 1-bit output: Clock output
			 CE  => clock_buf_en(7), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
		
		BUFGCE_inst_SRL :  BUFGCE
		port map (
			 O => clock_buf8, -- 1-bit output: Clock output
			 CE  => clock_buf_en(8), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_SLA :  BUFGCE
		port map (
			 O => clock_buf9, -- 1-bit output: Clock output
			 CE  => clock_buf_en(9), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_SRA :  BUFGCE
		port map (
			 O => clock_buf10, -- 1-bit output: Clock output
			 CE  => clock_buf_en(10), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_ROR :  BUFGCE
		port map (
			 O => clock_buf11, -- 1-bit output: Clock output
			 CE  => clock_buf_en(11), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_ROL :  BUFGCE
		port map (
			 O => clock_buf12, -- 1-bit output: Clock output
			 CE  => clock_buf_en(12), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_FADD :  BUFGCE
		port map (
			 O => clock_buf13, -- 1-bit output: Clock output
			 CE  => clock_buf_en(13), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
		
--		BUFGCE_inst_FSUB :  BUFGCE	-- Item not instantiated in original design. Uncomment this once substatiated to connect main clock line to ALU component through BUFGCE (Buffered Global Clock w/ Enable) 
--		port map (
--			 O => clock_buf14, -- 1-bit output: Clock output
--			 CE  => clock_buf_en(14), -- 1-bit input: Clock enable input for I0
--			 I => clk  -- 1-bit input: Primary clock
--			);
				
		BUFGCE_inst_FMULT :  BUFGCE
		port map (
			 O => clock_buf15, -- 1-bit output: Clock output
			 CE  => clock_buf_en(15), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_AND :  BUFGCE
		port map (
			 O => clock_buf16, -- 1-bit output: Clock output
			 CE  => clock_buf_en(16), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
		BUFGCE_inst_FDIV :  BUFGCE
		port map (
			 O => clock_buf17, -- 1-bit output: Clock output
			 CE  => clock_buf_en(17), -- 1-bit input: Clock enable input for I0
			 I => clk  -- 1-bit input: Primary clock
			);
			
	-- End of BUFGCE_inst instantiation

	--inputA <= A;
	--inputB <= B;
	input_ready_A <= input_ready;
	input_ready_B <= input_ready;
	alu_operation_ready <= not(empty_fifo_A) and not(empty_fifo_B);
	rd_en_A <= alu_operation_ready;
	rd_en_B <= alu_operation_ready;
	--Result <= output;
	


	

--	
--Port mapping fifo units	
--			
	PM_FIFO_32_16_A : fifo_32
		port map(clk => clk, 
					rst => rst, 
					din => A, 
					wr_en => input_ready_A, 
					rd_en => rd_en_A, 
					dout => inputA, 
					full => full_fifo_A, 
					empty => empty_fifo_A 
					);

	PM_FIFO_32_16_B : fifo_32 
		port map(clk => clk, 
					rst => rst, 
					din => B, 
					wr_en => input_ready_B, 
					rd_en => rd_en_B, 
					dout => inputB, 
					full => full_fifo_B, 
					empty => empty_fifo_B );




--	
--Port mapping operator_register components	
--			
	--	PM_add_sub : add_sub_n
	--	port map(clk => clk, A => signed(A), B => signed(B), result => r_add_sub);
	
	PM_add_sub : add_sub_reg 
		generic map ( bits => 32)
		port map(A  => signed(A), 
					B => signed(B), 
					clk  => clock_buf0,
					--en	=> en,
					rst => rst,  
					input_ready => in_ready(0), 
					output_ready => result_ready(0),  
					std_logic_vector(Result) => r_add_sub
					);
  
	PM_MULT : mult_reg
		generic map(bits => 32)
		port map(A => inputA,  
					B => inputB, 
					clk => clock_buf1,  
					rst => rst, 
					input_ready => in_ready(1), 
					output_ready => result_ready(1), 
					Result => r_mult
					);

	PM_OR : or_reg 
		generic map(bits => 32)
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf2, 
					rst => rst, 
					input_ready => in_ready(2), 
					output_ready => result_ready(2), 
					Result => r_or
					);
	
	PM_NOR : nor_reg 
		generic map ( bits => 32)
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf3, 
					rst => rst, 
					input_ready => in_ready(3), 
					output_ready => result_ready(3), 
					Result => r_nor
					);

	PM_XOR : xor_reg 
		generic map(bits => 32)
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf4, 
					rst => rst, 
					input_ready => in_ready(4), 
					output_ready => result_ready(4), 
					Result => r_xor );

	PM_XNOR : xnor_reg  
		generic map(bits => 32)
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf5, 
					rst => rst, 
					input_ready => in_ready(5), 
					output_ready => result_ready(5), 
					Result => r_xnor 
					);

	PM_NOT :  not_reg
		generic map(bits => 32)
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf6, 
					rst => rst, 
					input_ready => in_ready(6), 
					output_ready => result_ready(6), 
					Result => r_not 
					);

	PM_SLL : sll_reg
		generic map(bits => 32)
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf7, 
					rst => rst, 
					input_ready => in_ready(7), 
					output_ready => result_ready(7), 
					Result => r_sll 
					);

	PM_SRL : srl_reg 
		generic map(bits => 32)
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf8, 
					rst => rst, 
					input_ready => in_ready(8), 
					output_ready => result_ready(8), 
					Result => r_srl 
					);

	PM_SLA : sla_reg
		generic map(bits => 32)
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf9, 
					rst => rst, 
					input_ready => in_ready(9), 
					output_ready => result_ready(9), 
					Result => r_sla 
					);

	PM_SRA : sra_reg
		generic map(bits => 32)
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf10, 
					rst => rst, 
					input_ready => in_ready(10), 
					output_ready => result_ready(10), 
					Result => r_sra 
					);

	PM_ROR : ror_reg
		generic map(bits => 32)
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf11, 
					rst => rst, 
					input_ready => in_ready(11), 
					output_ready => result_ready(11), 
					Result => r_ror 
					);

	
	PM_ROL : rol_reg
		generic map(bits => 32)
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf12, 
					rst => rst, 
					input_ready => in_ready(12), 
					output_ready => result_ready(12), 
					Result => r_rol
					);

	PM_FADD : fadd_reg
		generic map(bits => 32)
		port map(A  => inputA, 
					B  => inputB, 
					clk => clock_buf13, 
					rst => rst, 
					input_ready => in_ready(13), 
					output_ready => result_ready(13), 
					Result => r_fadd
					);
	

	PM_FSUB : fsub_reg
		port map(A => inputA, 
					B => inputB,  
					clk => clock_buf14,	
					rst => rst, 
					input_ready => in_ready(14),  
					output_ready => result_ready(14), 
					Result => r_fsub);

	PM_FMULT : fmult_reg
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf15, 
					rst => rst,
					input_ready => in_ready(15),
					output_ready => result_ready(15), 
					Result => r_fmult
					);

	PM_AND : and_reg 
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf16, 
					rst => rst, 
					input_ready => in_ready(16), 
					output_ready => result_ready(16), 
					Result => r_and
					);

	PM_FDIV : fdiv_reg
		port map(A => inputA, 
					B => inputB, 
					clk => clock_buf17, 
					rst => rst, 
					input_ready => in_ready(17), 
					output_ready => result_ready(17), 
					Result => r_fdiv
					);
	
	--PM_NAND : nand_reg
		--generic map( bits => 32)
		--port map(A => inputA, 
					--B => inputB, 
					--clk => clk, 
					--rst => rst, 
					--input_ready => in_ready(18), 
					--output_ready => result_ready(18), 
					--Result => r_nand
					--);


----------------------------------------------------------------------------------------------
	alu_control : process(clk) is --, Operation,  input_ready, inputA, inputB, rst) is 
	begin 
	--if(rising_edge(clk) ) then --and rst = '0')  then-- and rst = '0') then 
	  
	  if (alu_operation_ready = '0') then 
	  	in_ready <= (others => '0');

	  

 
	  elsif(alu_operation_ready = '1') then 
	  	--rd_en_A <= '1';
	  	--rd_en_B <= '1';
		
		case Operation is
			--when OPCODE_RESET => 
			--	output_ready <= '0';	

			when OPCODE_CLEAR => 
				output(63 downto 0) <= (others => '0');
				--in_ready <= (others => '0');
				--result_ready <= (others => '0');

			when OPCODE_IDLE => 
				output(63 downto 0) <= (others => '0'); 
				--in_ready <= (others => '0');

			when OPCODE_ADD_SUB => output(32 downto 0) <= r_add_sub; -- 00001
				output(63 downto 33) <= (others => '0');
				in_ready(0) <= input_ready;
				in_ready(17 downto 1) <= (others => '0');
				
			when OPCODE_MULT => output <= r_mult; -- 00011
				in_ready(1) <= '1';
				in_ready(0) <= '0';
				in_ready(17 downto 2) <= (others => '0');
				--output <= r_mult;
				
			when OPCODE_OR => output(31 downto 0) <= r_or;	--00011
				output(63 downto 32) <= (others => '0');
				in_ready(1 downto 0) <= (others => '0');
				in_ready(2) <= input_ready;
				in_ready(17 downto 3) <= (others => '0');
			
			when OPCODE_NOR => output(31 downto 0) <= r_nor;
				output(63 downto 32) <= (others => '0');
				in_ready(2 downto 0) <= (others => '0');
				in_ready(3) <= '1';
				in_ready(17 downto 4) <= (others => '0');
				
			when OPCODE_XOR => output(31 downto 0) <= r_xor;
				output(63 downto 32) <= (others => '0');
				in_ready(3 downto 0) <= (others => '0');
				in_ready(4) <= input_ready;
				in_ready(17 downto 5) <= (others => '0');			

			when OPCODE_XNOR => output(31 downto 0) <= r_xnor;
				output(63 downto 32) <= (others => '0');
				in_ready(4 downto 0) <= (others => '0');
				in_ready(5) <= input_ready;
				in_ready(17 downto 6) <= (others => '0');

			when OPCODE_NOT => output(31 downto 0) <= r_not;
				output(63 downto 32) <= (others => '0');
				in_ready(5 downto 0) <= (others => '0');
				in_ready(6) <= input_ready;
				in_ready(17 downto 7) <= (others => '0');

			when OPCODE_SLL => output(31 downto 0) <= r_sll;
				output(63 downto 32) <= (others => '0');
				in_ready(6 downto 0) <= (others => '0');
				in_ready(7) <= input_ready;
				in_ready(17 downto 8) <= (others => '0');
			
			when OPCODE_SRL => output(31 downto 0) <= r_srl;
				output(63 downto 32) <= (others => '0');
				in_ready(7 downto 0) <= (others => '0');
				in_ready(8) <= input_ready;
				in_ready(17 downto 9) <= (others => '0');	

			when OPCODE_SLA => output(31 downto 0) <= r_sla;
				output(63 downto 32) <= (others => '0');
				in_ready(8 downto 0) <= (others => '0');
				in_ready(9) <= input_ready;
				in_ready(17 downto 10) <= (others => '0');

			when OPCODE_SRA => output(31 downto 0) <= r_sra;
				output(63 downto 32) <= (others => '0');
				in_ready(9 downto 0) <= (others => '0');
				in_ready(10) <= input_ready;
				in_ready(17 downto 11) <= (others => '0');	

			when OPCODE_ROR => output(31 downto 0) <= r_ror;
				output(63 downto 32) <= (others => '0');
				in_ready(10 downto 0) <= (others => '0');
				in_ready(11) <= input_ready;
				in_ready(17 downto 12) <= (others => '0');	
							
			when OPCODE_ROL => output(31 downto 0) <= r_rol;
				output(63 downto 32) <= (others => '0');
				in_ready(11 downto 0) <= (others => '0');
				in_ready(12) <= input_ready;
				in_ready(17 downto 13) <= (others => '0');		
							
			when OPCODE_FADD => output(31 downto 0) <= r_fadd;
				output(63 downto 32) <= (others => '0');
				in_ready(13) <= input_ready;
				in_ready(12 downto 0) <= (others => '0');
				in_ready(17 downto 14) <= (others => '0');
				--output_ready <= result_ready(13);
						
			when OPCODE_FSUB => output(31 downto 0) <= r_fsub;
				output(63 downto 32) <= (others => '0');
				in_ready(13 downto 0) <= (others => '0');
				in_ready(14) <= input_ready;
				in_ready(17 downto 15) <= (others => '0');				
							
			when OPCODE_FMULT => output(31 downto 0) <= r_fmult;
				output(63 downto 32) <= (others => '0');
				in_ready(14 downto 0) <= (others => '0');
				in_ready(15) <= input_ready;
				in_ready(17 downto 16) <= (others => '0');				
							
			when OPCODE_FDIV => output(31 downto 0) <= r_fdiv;
				output(63 downto 32) <= (others => '0');
				in_ready(17) <= input_ready;
				in_ready(16 downto 0) <= (others => '0');

			when OPCODE_AND => output(31 downto 0) <= r_and;
				output(63 downto 32) <= (others => '0');
				in_ready(17) <= '0';
				in_ready(16) <= input_ready;
				in_ready(15 downto 0) <= (others => '0');

		    when OPCODE_NAND => output(31 downto 0) <= r_nand;
				output(63 downto 32) <= (others => '0');
				in_ready(18) <= input_ready;
				in_ready(17 downto 0) <= (others => '0');
				in_ready(17 downto 0) <= (others =>'0');
			
			when others =>
				NULL;
		  
		  end case;
		end if;
   end process;
----------------------------------------------------------------------------	
  Result <= output;
  output_ready <=  result_ready(0) or 
						 result_ready(1) or 
						 result_ready(2) or 
						 result_ready(3) or 
						 result_ready(4) or 
						 result_ready(5) or 
						 result_ready(6) or 
						 result_ready(7) or 
						 result_ready(8) or 
						 result_ready(9) or 
						 result_ready(10) or 
						 result_ready(11) or 
						 result_ready(12) or 
						 result_ready(13) or 
						 result_ready(14) or 
						 result_ready(15) or 
						 result_ready(16) or 
						 result_ready(17) or 
						 result_ready(18);	
end BEHAVIORAL;

--SIMD Instructions Simple instructions multiple data.
--