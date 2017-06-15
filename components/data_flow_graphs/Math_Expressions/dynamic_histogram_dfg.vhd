library ieee;
library work;
use ieee.std_logic_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;
use IEEE.STD_LOGIC_TEXTIO.all;
use STD.TEXTIO.all;
use work.opcodes.all;



entity dynamic_histogram_dfg is
generic(ROWS 	:	 	integer := 8;
		COLUMNS : 		integer := 3);
	port(
		clk 					: in std_logic;
		rst 					: in std_logic;
		rdy_config 				: out std_logic;
		select_line_config      : out std_logic;
		func_config             : out std_logic;
		data_input_rdy          : out std_logic;
		input_bus               : in std_logic_vector(131 downto 0);
		in_rdy_0	: out std_logic;
		in_rdy_1	: out std_logic;
		in_rdy_2	: out std_logic;
		out_rdy_0	: out std_logic;
		out_rdy_1	: out std_logic;
		out_rdy_2	: out std_logic;
		in_rdy_3	: out std_logic;
		out_rdy_3   : out std_logic;
		data_ALU_A00	: out std_logic_vector(31 downto 0); 
		data_ALU_A01 	: out std_logic_vector(31 downto 0);
		data_ALU_A02 	: out std_logic_vector(31 downto 0); 
		data_ALU_A10	: out std_logic_vector(31 downto 0);
		data_ALU_A11	: out std_logic_vector(31 downto 0);
		data_ALU_A12	: out std_logic_vector(31 downto 0);
		data_ALU_A20	: out std_logic_vector(31 downto 0); 
		data_ALU_A21	: out std_logic_vector(31 downto 0);
		data_ALU_A22	: out std_logic_vector(31 downto 0);
		data_ALU_B00 	: out std_logic_vector(31 downto 0); 
		data_ALU_B01 	: out std_logic_vector(31 downto 0); 
		data_ALU_B02 	: out std_logic_vector(31 downto 0); 
		data_ALU_B10 	: out std_logic_vector(31 downto 0);
		data_ALU_B11 	: out std_logic_vector(31 downto 0);
		data_ALU_B12 	: out std_logic_vector(31 downto 0);
		data_ALU_B20 	: out std_logic_vector(31 downto 0);
		data_ALU_B21 	: out std_logic_vector(31 downto 0);
		data_ALU_B22 	: out std_logic_vector(31 downto 0);
		result_ALU0				: out std_logic_vector(63 downto 0);
		result_ALU1				: out std_logic_vector(63 downto 0);
		result_ALU2				: out std_logic_vector(63 downto 0);
		result_ALU3				: out std_logic_vector(63 downto 0);
		result_ALU4				: out std_logic_vector(63 downto 0);
		result_ALU5				: out std_logic_vector(63 downto 0);
		result_ALU6				: out std_logic_vector(63 downto 0);
		result_ALU7				: out std_logic_vector(63 downto 0);
		result_ALU8				: out std_logic_vector(63 downto 0); 
		result_BLUE				: out std_logic_vector(63 downto 0);
		result_GREEN			: out std_logic_vector(63 downto 0);
		result_RED				: out std_logic_vector(63 downto 0);
		FUNC_CODE_00 			: in std_logic_vector(7 downto 0);
		FUNC_CODE_01 			: in std_logic_vector(7 downto 0);
		FUNC_CODE_02 			: in std_logic_vector(7 downto 0);
		FUNC_CODE_10 			: in std_logic_vector(7 downto 0);
		FUNC_CODE_11 			: in std_logic_vector(7 downto 0);
		FUNC_CODE_12 			: in std_logic_vector(7 downto 0);
		FUNC_CODE_20 			: in std_logic_vector(7 downto 0);
		FUNC_CODE_21 			: in std_logic_vector(7 downto 0);
		FUNC_CODE_22 			: in std_logic_vector(7 downto 0);
		MUX_CONFIG_CODE 		: in std_logic_vector(35 downto 0)
		);
end entity;

architecture arch of dynamic_histogram_dfg is

type ALU_DATA_TYPE  	 			is  array(0 to ROWS) of std_logic_vector(31 downto 0);
type ALU_RDY_TYPE					is  array(0 to ROWS) of std_logic;
type ALU_OP_TYPE  					is  array(0 to ROWS) of std_logic_vector(7 downto 0);
type ALU_OUTPUT_TYPE		 		is 	array(0 to ROWS) of std_logic_vector(63 downto 0);
type mux_sel_typeA            		is  array(0 to ROWS) of std_logic_vector(1 downto 0); --Need to know if inputA or inputB so an extra bit
type mux_sel_typeB            		is  array(0 to ROWS) of std_logic_vector(1 downto 0);
type mux_data_flow_out_type       	is  array(0 to ROWS) of std_logic_vector(31 downto 0); --ACTUAL DATA FROM PREVIOUS ALU TO NEXT
type mux_data_flow_in_type			is  array(0 to ROWS) of std_logic_vector(63 downto 0);

type STATE_TYPE IS(idle_state, config_in_state, config_func_state, config_select_lines_state,  data_load_state);

signal current_state, next_state : STATE_TYPE;

--Modififications
signal   in_A, in_B 									: ALU_DATA_TYPE;
signal   in_rdy_sig, out_rdy_sig                        : ALU_RDY_TYPE;
signal   in_rdy_sig_demux, out_rdy_sig_demux            : ALU_RDY_TYPE;
signal 	 a_ready, b_ready								: ALU_RDY_TYPE;
signal   alu_op 										: ALU_OP_TYPE;
signal   alu_output 									: ALU_OUTPUT_TYPE;
signal   in_A64, in_B64, in_X64, in_Y64, out_Z64        : std_logic_vector(63 downto 0);
signal   zeros  										: std_logic_vector(63 downto 0);

signal   in_baseX, in_baseY, in_baseZ					: std_logic_vector(63 downto 0);
signal   config_sig, in_rdy_sigs : std_logic;


--MUXES
signal select_linesA 						: mux_sel_typeA;
signal select_linesB 						: mux_sel_typeB;
signal flow_AX0_out, flow_AX1_out       	: mux_data_flow_out_type;
signal flow_BX0_out, flow_BX1_out       	: mux_data_flow_out_type;
signal data_flow_out						: mux_data_flow_in_type;
signal data_rdy								: std_logic_vector(1 downto 0);


signal INTER_RDY_CONFIG			   :  std_logic;
signal INTER_SELECT_LINE_CONFIG      :  std_logic;
signal INTER_FUNC_CONFIG             :  std_logic;
signal INTER_DATA_INPUT_RDY          :  std_logic;


signal config_go 				:  std_logic;
signal in_rdy_sigs_config 		:  std_logic;
signal op_code_config_go       :  std_logic;
signal input_data_go 			:  std_logic; --input_data_en <= not(config_go)
signal instr 	:  std_logic_vector(131 downto 0);
begin

----------------------------------------------------------------------------------------
--CONFIGURING OPCODES
----------------------------------------------------------------------------------------
--Configuring OPCODES


--Dynamic configuration
--Select lines

----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------
--First row ALU0, ALU1, ALU2
			
			
			

--alus : for index in 0 to ROWS generate
--begin
--		alu_s : entity work.ALU_EXPERIMENT_32 
--					port map(in_A(index), in_B(index), clk,  rst,  in_rdy_sig(index),  out_rdy_sig(index), alu_op(index), data_flow_out(index));
--end generate;
	instr <= input_bus; -- (others => '0');

	config_sig <= input_bus(0);
	in_rdy_sigs_config <= config_sig;
	INTER_SELECT_LINE_CONFIG <= input_bus(1);
	INTER_FUNC_CONFIG <= input_bus(2);
	INTER_DATA_INPUT_RDY <= input_bus(3);

	rdy_config <= input_bus(0);
	select_line_config <= INTER_SELECT_LINE_CONFIG;
	func_config <= INTER_FUNC_CONFIG;
	data_input_rdy <= INTER_DATA_INPUT_RDY;


	

	

	
	

	alu_0 : entity work.ALU_EXPERIMENT_32
		port map(in_A(0), in_B(0), clk, rst, in_rdy_sig(0), out_rdy_sig(0), alu_op(0), data_flow_out(0));

	alu_1 : entity work.ALU_EXPERIMENT_32 
		port map(in_A(1), in_B(1), clk, rst, in_rdy_sig(1), out_rdy_sig(1), alu_op(1), data_flow_out(1));

	alu_2 : entity work.ALU_EXPERIMENT_32
		port map(in_A(2), in_B(2), clk, rst, in_rdy_sig(2), out_rdy_sig(2), alu_op(2), data_flow_out(2));

	alu_3 : entity work.ALU_EXPERIMENT_32
		port map(in_A(3), in_B(3), clk, rst, in_rdy_sig(3), out_rdy_sig(3), alu_op(3), data_flow_out(3));


	alu_4 : entity work.ALU_EXPERIMENT_32
		port map(in_A(4), in_B(4), clk, rst, in_rdy_sig(4), out_rdy_sig(4), alu_op(4), data_flow_out(4));


	alu_5 : entity work.ALU_EXPERIMENT_32
		port map(in_A(5), in_B(5), clk, rst, in_rdy_sig(5), out_rdy_sig(5), alu_op(5), data_flow_out(5));
		

	alu_6 : entity work.ALU_EXPERIMENT_32
		port map(in_A(6), in_B(6), clk, rst, in_rdy_sig(6), out_rdy_sig(6), alu_op(6), data_flow_out(6));
		

	alu_7 : entity work.ALU_EXPERIMENT_32
		port map(in_A(7), in_B(7), clk, rst, in_rdy_sig(7), out_rdy_sig(7), alu_op(7), data_flow_out(7));			
	

	alu_8 : entity work.ALU_EXPERIMENT_32
		port map(in_A(8), in_B(8), clk, rst, in_rdy_sig(8), out_rdy_sig(8), alu_op(8), data_flow_out(8));
	----------------------------------------
	--ALU_0
	----------------------------------------
	muxes_A0 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), input_bus(63 downto 0), data_flow_out(1), data_flow_out(2), select_linesA(0), in_A(0)); --sel 01
	muxes_B0 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), x"0000000000000010", data_flow_out(1), data_flow_out(2), select_linesB(0), in_B(0));--sel 01

	----------------------------------------
	--ALU_1
	----------------------------------------
	muxes_A1 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), input_bus(63 downto 0), data_flow_out(1), data_flow_out(2), select_linesA(1), in_A(1));--sel 01
	muxes_B1 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), x"0000000000000008", data_flow_out(1), data_flow_out(2), select_linesB(1), in_B(1));--sel 01

	----------------------------------------
	--ALU_2
	----------------------------------------
	muxes_A2 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), input_bus(63 downto 0), data_flow_out(1), data_flow_out(2), select_linesA(2), in_A(2));--sel 01
	muxes_B2 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), x"0000000000000000", data_flow_out(1), data_flow_out(2), select_linesB(2), in_B(2));--sel 01



	----------------------------------------
	--ALU_3
	----------------------------------------
	muxes_A3 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesA(3), in_A(3)); --sel 00
	muxes_B3 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), x"00000000000000FF", data_flow_out(2), data_flow_out(3), select_linesB(3), in_B(3));  --sel 01


	----------------------------------------
	--ALU_4
	----------------------------------------
	muxes_A4 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesA(4), in_A(4)); --sel 01
	muxes_B4 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), x"00000000000000FF", data_flow_out(2), data_flow_out(3), select_linesB(4), in_B(4));      --sel 01


	----------------------------------------
	--ALU_5
	----------------------------------------
	muxes_A5 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesA(5), in_A(5)); --sel 10
	muxes_B5 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), x"00000000000000FF", data_flow_out(2), data_flow_out(3), select_linesB(5), in_B(5));	--sel 01


	----------------------------------------
	--ALU_6
	----------------------------------------
	muxes_A6 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(6), in_A(6));	--sel 00
	muxes_B6 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), x"0000000000000001", data_flow_out(5), data_flow_out(6), select_linesB(6), in_B(6));	--sel 01

	----------------------------------------
	--ALU_7
	----------------------------------------
	muxes_A7 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(7), in_A(7)); --sel 01
	muxes_B7 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), x"0000000000000001", data_flow_out(5), data_flow_out(6), select_linesB(7), in_B(7));	--sel 01

	----------------------------------------
	--ALU_8
	----------------------------------------
	muxes_A8 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(8), in_A(8));	--sel 10
	muxes_B8 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(3), x"0000000000000001", data_flow_out(5), data_flow_out(6), select_linesB(8), in_B(8));	--sel 01

	--initiate : process(clk) is
	--begin 
		--if rst = '1' then 
			--next_state <= idle_state;

		--if (rising_edge(clk) ) then 
			in_rdy_sig(0) <= '1';
			in_rdy_sig(1) <= '1';
			in_rdy_sig(2) <= '1';

			in_rdy_sig(3) <= out_rdy_sig(0);
			in_rdy_sig(4) <= out_rdy_sig(1);
			in_rdy_sig(5) <= out_rdy_sig(2);

			in_rdy_sig(6) <= out_rdy_sig(3);
			in_rdy_sig(7) <= out_rdy_sig(4);
			in_rdy_sig(8) <= out_rdy_sig(5);

			
			--case current_state is 
				--when idle_state =>
				--	if (instr(0) = '1') then
				--		next_state <= config_in_state;
				--	else 
				--		next_state <= idle_state;
				--	end if;
				--when config_in_state =>
					--in_rdy_sig(0) <= '1'; --1 config_func_state, config_select_lines_state,  data_load_state
					--in_rdy_sig(1) <= '1'; --1
					--in_rdy_sig(2) <= '1'; --1

					--in_rdy_sig(3) <= in_rdy_sig(0);
					--in_rdy_sig(4) <= in_rdy_sig(1);
					--in_rdy_sig(5) <= in_rdy_sig(2);

					--in_rdy_sig(6) <= in_rdy_sig(3);
					--in_rdy_sig(7) <= in_rdy_sig(4);
					--in_rdy_sig(8) <= in_rdy_sig(5);
					--wait for 50 ns;
				--	if (instr(1) = '1') then -- and INTER_SELECT_LINE_CONFIG = '1') then
						--if instr(1) = '1' then 
				--		next_state <= config_select_lines_state;
					--else 
					--	state <= config_in_state;
				--	end if;
				--when config_select_lines_state => 
					
				--	if(instr(2) = '1') then 
				--		next_state <= config_func_state;
					--else 
					--	state <= config_select_lines_state;
				--	end if;
						
				--when config_func_state =>
				--	alu_op(0) <= instr(109 downto 102); --srl 00001100
				--	alu_op(1) <= instr(109 downto 102); --srl 00001100
				--	alu_op(2) <= instr(101 downto 94); --add 00000000
				--	alu_op(3) <= instr(93 downto 86); --opcode_and "00000111"
				--	alu_op(4) <= instr(93 downto 86); --opcode_and "00000111"
				---	alu_op(5) <= instr(93 downto 86); --and "00000111"
				--	alu_op(6) <= instr(101 downto 94); --add 00000000
				--	alu_op(7) <= instr(101 downto 94);   --add 00000000
				--	alu_op(8) <= instr(101 downto 94);  --add 00000000
				--	if(instr(3) = '1') then 
					--	next_state <= data_load_state;
					--else 
					--	state <= config_func_state;
					--end if;
						--0101 0101 0101 0001 0101 1001 0001 0101 1001
						--000011000000000000000111
				--when data_load_state =>
					--next_state <= data_load_state;
					--if (config_sig = '1') then 
					--	state <= data_load_state;
					--end if;
					--select_linesA(0) <= "11"; --01
					--in_rdy_sig(0) <= '1'; --1 config_func_state, config_select_lines_state,  data_load_state
					--in_rdy_sig(1) <= '1'; --1
					--in_rdy_sig(2) <= '1'; --1

					--in_baseX <= input_bus(67 downto 4);
					--in_baseY <= input_bus(67 downto 4);
					--in_baseZ <= input_bus(67 downto 4);
				--when others => 
				--	next_state <= data_load_state;
					--in_baseX <= input_bus(67 downto 4);
					--in_baseY <= input_bus(67 downto 4);
					--in_baseZ <= input_bus(67 downto 4);
			--end case;

			--end if; 
				--if(config_sig = '1') then  --Read signals configuration
					--in_rdy_sig(0) <= '1'; --1
					--in_rdy_sig(1) <= '1'; --1
					--in_rdy_sig(2) <= '1'; --1

					--select_linesA(0) <= "01"; --01
					--select_linesB(0) <= "01"; --01


					--select_linesA(1) <= "01"; --01
					--select_linesB(1) <= "01"; --01

					--select_linesA(2) <= "01"; --01
					--select_linesB(2) <= "01"; --01

					alu_op(0) <= FUNC_CODE_00; --srl 00001100
					alu_op(1) <= FUNC_CODE_01; --srl 00001100
					alu_op(2) <= FUNC_CODE_02; --add 00000000
					alu_op(3) <= FUNC_CODE_10; --opcode_and "00000111"
					alu_op(4) <= FUNC_CODE_11; --opcode_and "00000111"
					alu_op(5) <= FUNC_CODE_12; --and "00000111"
					alu_op(6) <= FUNC_CODE_20; --add 00000000
					alu_op(7) <= FUNC_CODE_21;   --add 00000000
					alu_op(8) <= FUNC_CODE_22;  --add 00000000


				
		--end if;
	--end process;
			
			

				
					select_linesA(0) <= MUX_CONFIG_CODE(35 downto 34); --"01"
					select_linesB(0) <= MUX_CONFIG_CODE(33 downto 32); --"01";

					select_linesA(1) <= MUX_CONFIG_CODE(31 downto 30); --"01";
					select_linesB(1) <= MUX_CONFIG_CODE(29 downto 28); --"01";

					select_linesA(2) <= MUX_CONFIG_CODE(27 downto 26); --"01";
					select_linesB(2) <= MUX_CONFIG_CODE(25 downto 24); --"01";
 				
					
					
					
							--Second row ALU3, ALU4, ALU5
					select_linesA(3) <= MUX_CONFIG_CODE(23 downto 22); --"00"; --00
					select_linesB(3) <= MUX_CONFIG_CODE(21 downto 20); --"01"; --01


					select_linesA(4) <= MUX_CONFIG_CODE(19 downto 18); --"01"; --01
					select_linesB(4) <= MUX_CONFIG_CODE(17 downto 16); --"01"; --01

					select_linesA(5) <= MUX_CONFIG_CODE(15 downto 14); --"10"; --10
					select_linesB(5) <= MUX_CONFIG_CODE(13 downto 12); --"01"; --01

							--Third row ALU6, ALU7, ALU8
					select_linesA(6) <= MUX_CONFIG_CODE(11 downto 10); --"00"; --00
					select_linesB(6) <= MUX_CONFIG_CODE(9 downto 8); --"01"; --01

					select_linesA(7) <= MUX_CONFIG_CODE(7 downto 6); --"01"; --01
					select_linesB(7) <= MUX_CONFIG_CODE(5 downto 4); --"01"; --01

					select_linesA(8) <= "10";--MUX_CONFIG_CODE(3 downto 2); --"10"; --10
					select_linesB(8) <= MUX_CONFIG_CODE(1 downto 0); --"01"; --01

					--select_linesA(9) <= "10";--MUX_CONFIG_CODE(3 downto 2); --"10"; --10
					--select_linesB(9) <= MUX_CONFIG_CODE(1 downto 0); --"01"; --01


					--select_linesA(10) <= "10";--MUX_CONFIG_CODE(3 downto 2); --"10"; --10
					--select_linesB(10) <= MUX_CONFIG_CODE(1 downto 0); --"01"; --01


					--select_linesA(11) <= "10";--MUX_CONFIG_CODE(3 downto 2); --"10"; --10
					--select_linesB(12) <= MUX_CONFIG_CODE(1 downto 0); --"01"; --01


					--select_linesA(13) <= "10";--MUX_CONFIG_CODE(3 downto 2); --"10"; --10
					--select_linesB(13) <= MUX_CONFIG_CODE(1 downto 0); --"01"; --01


					--select_linesA(14) <= "10";--MUX_CONFIG_CODE(3 downto 2); --"10"; --10
					--select_linesB(14) <= MUX_CONFIG_CODE(1 downto 0); --"01"; --01
					

					--select_linesA(15) <= "10";--MUX_CONFIG_CODE(3 downto 2); --"10"; --10
					--select_linesB(15) <= MUX_CONFIG_CODE(1 downto 0); --"01"; --01
				
					
				
				
				    data_ALU_A00	<= in_A(0); 
					data_ALU_A01 	<= in_A(1);
					data_ALU_A02 	<= in_A(2); 
					data_ALU_A10	<= in_A(3);
					data_ALU_A11	<= in_A(4);
					data_ALU_A12	<= in_A(5);
					data_ALU_A20	<= in_A(6);
					data_ALU_A21	<= in_A(7);
					data_ALU_A22 	<= in_A(8);
					data_ALU_B00 	<= in_B(0); 
					data_ALU_B01 	<= in_B(1); 
					data_ALU_B02 	<= in_B(2); 
					data_ALU_B10 	<= in_B(3);
					data_ALU_B11 	<= in_B(4);
					data_ALU_B12 	<= in_B(5);
					data_ALU_B20 	<= in_B(6);
					data_ALU_B21 	<= in_B(7);
					data_ALU_B22 	<= in_B(8);
				

				  	result_ALU0 <= data_flow_out(0); 
					result_ALU1 <= data_flow_out(1); 
					result_ALU2 <= data_flow_out(2); 
					result_ALU3 <= data_flow_out(3); 
					result_ALU4 <= data_flow_out(4);
					result_ALU5 <= data_flow_out(5);
					result_ALU6 <= data_flow_out(6);
					result_ALU7 <= data_flow_out(7);
					result_ALU8 <= data_flow_out(8);
					result_RED 	<= data_flow_out(6);
					result_GREEN <=data_flow_out(7);
					result_BLUE <= data_flow_out(8);

	
end arch;