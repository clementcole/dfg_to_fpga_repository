library ieee;
library work;
use ieee.std_logic_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;
use IEEE.STD_LOGIC_TEXTIO.all;
use STD.TEXTIO.all;
use work.opcodes.all;
--use work.Components.all;


entity dynamic_alu_conf is
		generic(data_width  : 	integer := 32);
		port(	
			clk     			: in std_logic;
			rst     			: in std_logic;
			in_rdy				: in std_logic;
			out_rdy             : out std_logic;
			CONFIG_BITS 		: in std_logic_vector(131 downto 0);
			op00 				: in std_logic_vector(7 downto 0);
			op01 				: in std_logic_vector(7 downto 0);
			op02 				: in std_logic_vector(7 downto 0);
			op10 				: in std_logic_vector(7 downto 0);
			op11 				: in std_logic_vector(7 downto 0);
			op12 				: in std_logic_vector(7 downto 0);
			op20 				: in std_logic_vector(7 downto 0);
			op21 				: in std_logic_vector(7 downto 0);
			op22  				: in std_logic_vector(7 downto 0);
			A00	   	        	: in std_logic_vector(31 downto 0);
			A01	   	        	: in std_logic_vector(31 downto 0);
			A02	   	        	: in std_logic_vector(31 downto 0);
			B00   				: in std_logic_vector(31 downto 0);
			B01   				: in std_logic_vector(31 downto 0);
			B02   				: in std_logic_vector(31 downto 0);
			output_00       	: out std_logic_vector(63 downto 0);
			output_01           : out std_logic_vector(63 downto 0);
			output_02           : out std_logic_vector(63 downto 0);
			output_10     		: out std_logic_vector(63 downto 0);
			output_11           : out std_logic_vector(63 downto 0);
			output_12           : out std_logic_vector(63 downto 0);
			output_20           : out std_logic_vector(63 downto 0);
			output_21 			: out std_logic_vector(63 downto 0);
			output_22           : out std_logic_vector(63 downto 0));
end dynamic_alu_conf;

architecture arch of dynamic_alu_conf is
	signal a_00, a_01, a_02, a_10, a_11, a_12, a_20, a_21, a_22 : std_logic_vector(31 downto 0);
	signal b_00, b_01, b_02, b_10, b_11, b_12, b_20, b_21, b_22 : std_logic_vector(31 downto 0);
	signal clk_00, clk_01, clk_02, clk_10, clk_11, clk_12, clk_20, clk_21, clk_22  : std_logic;  --inputs clk1, clk2, rst1, rst2, {1 bit each}
	signal rst_00, rst_01, rst_02, rst_10, rst_11, rst_12, rst_20, rst_21, rst_22 : std_logic;
	signal in_rdy_00, in_rdy_01, in_rdy_02, in_rdy_10, in_rdy_11, in_rdy_12,  in_rdy_20, in_rdy_21, in_rdy_22 : std_logic;									   --ready signals rdy1, rd2, rd3, {1 bit each}
	signal out_rdy_00, out_rdy_01, out_rdy_02, out_rdy_11, out_rdy_10,  out_rdy_12, out_rdy_20, out_rdy_21, out_rdy_22 : std_logic;									   --output ready signals (xy), (a+b) and (xy) + (a + b) {1 bit each} 
	signal op_00, op_01, op_02, op_10, op_11, op_12, op_20, op_21, op_22 : std_logic_vector(7 downto 0);							   --opcodes {plus, mult and plus}
	signal out_00, out_01, out_02, out_10, out_11, out_12, out_20, out_21, out_22 : std_logic_vector(63 downto 0);               --result signals {64 bits each}	
	signal sel_00, sel_01, sel_02, sel_10, sel_11, sel_12, sel_20, sel_21, sel_22 : std_logic_vector(2 downto 0);	
	signal out_rdy_demux_00, out_rdy_demux_01, out_rdy_demux_02 : std_logic;
	signal out_rdy_demux_10, out_rdy_demux_11, out_rdy_demux_12 : std_logic;  
	--signal out_rdy_demux_20, out_rdy_demux_21, out_rdy_demux_22 : std_logic;  


	begin 
		--Synchronizing clocks
		clk_00 <= clk;
		clk_01 <= clk;
		clk_02 <= clk;
		clk_10 <= clk;
		clk_11 <= clk;
		clk_12 <= clk;
		clk_20 <= clk;
		clk_21 <= clk; 
		clk_22 <= clk;

		--Synchronizing reset signals
		rst_00 <= rst;
		rst_01 <= rst;
		rst_02 <= rst;
		rst_10 <= rst;
		rst_11 <= rst;
		rst_12 <= rst;
		rst_20 <= rst;
		rst_21 <= rst;
		rst_22 <= rst;
		
		output_00 <= out_00;
		output_01 <= out_01;
		output_02 <= out_02;
		output_10 <= out_10;
		output_11 <= out_11;
		output_12 <= out_12;
		output_20 <= out_20;
		output_21 <= out_21;
		output_22 <= out_22;

		a_00 <= A00;
		a_01 <= A01;
		a_02 <= A02;
		b_00 <= B00;
		b_01 <= B01;
		b_02 <= B02;

		in_rdy_00 <= in_rdy;
		in_rdy_01 <= in_rdy;
		in_rdy_02 <= in_rdy;

		--in_rdy_10 <= in_rdy;
		--in_rdy_11 <= in_rdy;
		--in_rdy_12 <= in_rdy;
		--in_rdy_20 <= in_rdy;
		--in_rdy_21 <= in_rdy;
		--in_rdy_22 <= in_rdy;

		

		DEMUX_00_00 : entity work.demux_1_to_3
		port map (  out_00,  out_rdy_00,  clk, rst, sel_00,  a_10,  a_11,  a_12,  in_rdy_10, in_rdy_11, in_rdy_12);
		DEMUX_00_01 : entity work.demux_1_to_3
		port map (  out_01,  out_rdy_01,  clk, rst, sel_01,  b_10,  b_11,  b_12,  in_rdy_10, in_rdy_11, in_rdy_12);
		--DEMUX_00_02 : entity work.demux_1_to_3
		--port map (  out_01,  out_rdy_02,  clk, rst, sel_02,  b_10,  b_11,  b_12,  in_rdy_10, in_rdy_11, in_rdy_12);

		DEMUX_00_10 : entity work.demux_1_to_3
		port map (  out_10,  out_rdy_10,  clk, rst, sel_10,  a_20,  a_21,  a_22,  in_rdy_20, in_rdy_21, in_rdy_22);
		DEMUX_00_11 : entity work.demux_1_to_3
		port map (  out_11,  out_rdy_11,  clk, rst, sel_11,  b_20,  b_21,  b_22,  in_rdy_20, in_rdy_21, in_rdy_22);
		--DEMUX_00_12 : entity work.demux_1_to_3
		--port map (  out_12,  out_rdy_12,  clk, rst, sel_12,  a_20,  a_21,  a_12,  in_rdy_20, in_rdy_21, in_rdy_22);

		
		

		ALU_0_0 : entity work.ALU_EXPERIMENT_32
		generic map(data_width => data_width)
		port map(
				A                =>     a_00,
				B 				 =>     b_00,
				clk 			 =>     clk_00,
				rst              =>     rst_00, 
				input_ready      =>     in_rdy_00,
				output_ready     =>     out_rdy_00,
				Operation        =>     op_00,
				Result           =>     out_00
		);

		ALU_0_1 : entity work.ALU_EXPERIMENT_32 
		generic map(data_width => data_width)
		port map(
				A                =>     a_01,
				B 				 =>     b_01,
				clk 			 =>     clk_01,
				rst              =>     rst_01, 
				input_ready      =>     in_rdy_01,
				output_ready     =>     out_rdy_01,
				Operation        =>     op_01,
				Result           =>     out_01
		);
		ALU_0_2 : entity work.ALU_EXPERIMENT_32 
		generic map(data_width => data_width)
		port map(
				A                =>     a_02,
				B 				 =>     b_02,
				clk 			 =>     clk_02,
				rst              =>     rst_02, 
				input_ready      =>     in_rdy_02,
				output_ready     =>     out_rdy_02,
				Operation        =>     op_02,
				Result           =>     out_02
		);

		ALU_1_0 : entity work.ALU_EXPERIMENT_32
		generic map(data_width => data_width)
		port map(
				A                =>     a_10,
				B 				 =>     b_10,
				clk 			 =>     clk_10,
				rst              =>     rst_10, 
				input_ready      =>     in_rdy_10,
				output_ready     =>     out_rdy_10,
				Operation        =>     op_10,
				Result           =>     out_10
		);

		ALU_1_1 : entity work.ALU_EXPERIMENT_32
		generic map(data_width => data_width)
		port map(
				A                =>     a_11,
				B 				 =>     b_11,
				clk 			 =>     clk_11,
				rst              =>     rst_11, 
				input_ready      =>     in_rdy_11,
				output_ready     =>     out_rdy_11,
				Operation        =>     op_11,
				Result           =>     out_11
		);

		ALU_1_2 : entity work.ALU_EXPERIMENT_32
		generic map(data_width => data_width)
		port map(
				A                =>     a_12,
				B 				 =>     b_12,
				clk 			 =>     clk_12,
				rst              =>     rst_12, 
				input_ready      =>     in_rdy_12,
				output_ready     =>     out_rdy_12,
				Operation        =>     op_12,
				Result           =>     out_12
		);

		ALU_2_0 : entity work.ALU_EXPERIMENT_32 
		generic map(data_width => data_width)
		port map(
				A                =>     a_20,
				B 				 =>     b_20,
				clk 			 =>     clk_20,
				rst              =>     rst_20, 
				input_ready      =>     in_rdy_20,
				output_ready     =>     out_rdy_20,
				Operation        =>     op_20,
				Result           =>     out_20
		);

		ALU_2_1 : entity work.ALU_EXPERIMENT_32 
		generic map(data_width => data_width)
		port map(
				A                =>     a_21,
				B 				 =>     b_21,
				clk 			 =>     clk_21,
				rst              =>     rst_21, 
				input_ready      =>     in_rdy_21,
				output_ready     =>     out_rdy_21,
				Operation        =>     op_21,
				Result           =>     out_21
		);
		ALU_2_2 : entity work.ALU_EXPERIMENT_32 
		generic map(data_width => data_width)
		port map(
				A                =>     a_22,
				B 				 =>     b_22,
				clk 			 =>     clk_22,
				rst              =>     rst_22, 
				input_ready      =>     in_rdy_22,
				output_ready     =>     out_rdy_22,
				Operation        =>     op_22,
				Result           =>     out_22
		);

		routing : process(clk, CONFIG_BITS ) is 
		begin
			if(CONFIG_BITS(131) = '0') then
				case  CONFIG_BITS(131 downto 128) is 
					when  "0000" => 
						sel_00 <= CONFIG_BITS(127 downto 125);
						op_00 <= CONFIG_BITS(124 downto 117);
						--if(sel_00 = "000") then 

					when  "0001" => 
						sel_01 <= CONFIG_BITS(127 downto 125);
						op_01 <= CONFIG_BITS(124 downto 117);
					

					when "0010" =>
						sel_10 <= CONFIG_BITS(127 downto 125);
						op_10 <= CONFIG_BITS(124 downto 117);

					when "0011" =>
						sel_11 <= CONFIG_BITS(127 downto 125);
						op_11 <= CONFIG_BITS(124 downto 117);

					when others => 
						NULL;

				end case;
				--elsif(CONFIG_BITS(131 downto 128) = "0011") then
				--	sel_10 <= CONFIG_BITS(127 downto 125);
				--	op_10 <= CONFIG_BITS(124 downto 117);

				--elsif(CONFIG_BITS(131 downto 128) = "0100") then
				--	sel_11 <= CONFIG_BITS(127 downto 125);
				--	op_11 <= CONFIG_BITS(124 downto 117);


				--elsif(CONFIG_BITS(131 downto 128) = "0101") then
				--	sel_12 <= CONFIG_BITS(127 downto 125);
				--	op_12 <= CONFIG_BITS(124 downto 117);
				
			
			elsif(CONFIG_BITS(131) = '1') then
				
				a_00 <= CONFIG_BITS(31 downto 0);
				b_00 <= CONFIG_BITS(63 downto 32);
				a_01 <= CONFIG_BITS(95 downto 64);
				b_01 <= CONFIG_BITS(127 downto 96);
			end if;
		end process;
end;
