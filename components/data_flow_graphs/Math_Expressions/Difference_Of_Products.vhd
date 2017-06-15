library ieee;
library work;
use ieee.std_logic_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;
use IEEE.STD_LOGIC_TEXTIO.all;
use STD.TEXTIO.all;
use work.opcodes.all;
--use work.Components.all;


entity Difference_Of_Products is
		generic(data_width  : 	integer := 32);
		port(	
			clk     			: in std_logic;
			rst     			: in std_logic;
			in_rdy				: in std_logic;
			in_rdy_mult1 		: out std_logic;
			in_rdy_mult2 	    : out std_logic;
			in_rdy_sum			: out std_logic;
			out_rdy_mult1   	: out std_logic;
			out_rdy_mult2   	: out std_logic;
			out_rdy_sum 		: out std_logic;
			out_rdy 		 	: out std_logic;
			x	   	        	: in std_logic_vector(31 downto 0);
			y	    	    	: in std_logic_vector(31 downto 0);
			a 					: in std_logic_vector(31 downto 0);
			b 					: in std_logic_vector(31 downto 0);
			MULT1	    		: in std_logic_vector(7 downto 0);
			MULT2         		: in std_logic_vector(7 downto 0);
			SUM 				: in std_logic_vector(7 downto 0);
			PRODUCT_x_y	    	: out std_logic_vector(63 downto 0);
			PRODUCT_a_b       	: out std_logic_vector(63 downto 0);
			Result	    		: out std_logic_vector(63 downto 0));
end Difference_Of_Products;

architecture arch of Difference_Of_Products is
	--Equation is E = MC^2
	signal input_mult1_ready  : std_logic := '0'; 
	signal input_mult2_ready  : std_logic := '0'; 
	signal input_sum_ready 	  : std_logic := '0'; 
	signal output_sum_ready   : std_logic := '0';
	signal output_mult1_ready : std_logic := '0';
	signal output_mult2_ready : std_logic := '0';
	signal out_mult1 : std_logic_vector(63 downto 0);	
	signal out_mult2 : std_logic_vector(63 downto 0);
	signal out_sum : std_logic_vector(63 downto 0);

	--component AlU_EXPERIMENT_32 is
	--	generic(data_width 	:	 	integer := 32);
	--	port(   
	--		A 				:		in std_logic_vector(31 downto 0); --input operands
	--		B				: 		in std_logic_vector(31 downto 0);
	--		clk				:       in std_logic;
	--		rst 			:       in std_logic;
	--		input_ready		:		in std_logic; 
	--		output_ready	:		out std_logic;
	--		Operation		: 		in std_logic_vector(7 downto 0); --select operation
	--		Result 			: 		out std_logic_vector(63 downto 0));
			--result_rdy      :       out std_logic_vector(17 downto 0));
	--end component;
begin

	input_mult1_ready <= in_rdy; 
	input_mult2_ready <= in_rdy; 
	input_sum_ready <= (output_mult1_ready and output_mult2_ready);

	in_rdy_mult1 <= input_mult1_ready;
	in_rdy_mult2 <= input_mult2_ready;
	in_rdy_sum <= input_sum_ready;


	--input_sum_ready <= (output_mult1_ready and output_mult2_ready);
	out_rdy <=  output_sum_ready;
	out_rdy_mult1 <= output_mult1_ready;
	out_rdy_mult2 <= output_mult2_ready;

	PRODUCT_x_y <= out_mult1;
	PRODUCT_a_b <= out_mult2;
	Result <= out_sum;
	--x*y
	X_TIMES_Y: entity work.ALU_EXPERIMENT_32
	generic map(data_width => data_width)
	port map(
			A 				=>      x,
			B				=> 		y,
			clk				=>      clk,
			rst     		=>     	rst, 
			input_ready		=>		input_mult1_ready,
			output_ready	=>		output_mult1_ready,
			Operation		=>      MULT1,
			Result 			=>   	out_mult1 );
	--
	--reg_shift_mult here
	--
	--a*b
	A_TIMES_B : entity work.ALU_EXPERIMENT_32
	generic map(data_width => data_width)
	port map(
			A 				=>      a,
			B				=> 		b,
			clk				=>      clk,
			rst   			=>     	rst, 
			input_ready		=>		input_mult1_ready,
			output_ready	=>      output_mult2_ready,
			Operation		=>      MULT2,
			Result 			=>      out_mult2
	);
	--
	--reg_shift_mult here
	--

	--(x*y)+(a*b)
	XY_MINUS_AB : entity work.ALU_EXPERIMENT_32 
	generic map (data_width => data_width)
	port map( 
			A 				=>   out_mult1(31 downto 0), 
			B  				=>   out_mult2(31 downto 0), 
			clk 			=>   clk, 
			rst  			=>   rst, 
			input_ready 	=>   input_sum_ready,
			output_ready 	=>   output_sum_ready, 
			Operation       =>   SUM, 
			Result 			=>   out_sum );
	--
	--reg_shift_add here
	--
	
end arch;

