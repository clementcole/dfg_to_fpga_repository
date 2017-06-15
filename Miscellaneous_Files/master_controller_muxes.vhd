library ieee;
library work;
use ieee.std_logic_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.ALL;
use IEEE.STD_LOGIC_TEXTIO.all;
use STD.TEXTIO.all;
use work.opcodes.all;
--use work.Components.all;



--entity master_controller is 
--port (
	--clk : in std_logic; 
	-- nrst : in std_logic; 
	-- ir_load : out std_logic; 
	-- ir_valid : out std_logic; 
	-- ir_address : out std_logic; 
	-- pc_inc : out std_logic; 
	-- pc_load : out std_logic;
	-- pc_valid : out std_logic;
	-- mdr_load : out std_logic;
	-- mar_load : out std_logic;
	-- mar_valid : out std_logic;
	-- m_en : out std_logic;
	-- m_rw : out std_logic_vector;
	--alu_cmd : out std_logic_vector;
	-- control_bus : inout std_logic_vector(n - 1 downto 0)

--);		
--end master_controller;

entity master_controller_muxes is 
	generic(ROWS 	:	 	integer := 15;
			COLUMNS : 		integer := 3);
	port(
		clk 					: in std_logic;
		rst 					: in std_logic;
		go                      : in std_logic;
		config_en 	      		: in std_logic;
		busy 					: out std_logic;
		instr					: in std_logic_vector(43 downto 0);
		input_bus               : in std_logic_vector(127 downto 0);
		data_A0					: out std_logic_vector(31 downto 0); 
		data_A1 				: out std_logic_vector(31 downto 0); 
		result_0 				: out std_logic_vector(63 downto 0);
		result_1               : out std_logic_vector(63 downto 0);
		result_2               : out std_logic_vector(63 downto 0);
		result_3               : out std_logic_vector(63 downto 0);
		data_A2 				: out std_logic_vector(31 downto 0); 
		data_A3					: out std_logic_vector(31 downto 0); 
		data_B0 				: out std_logic_vector(31 downto 0); 
		data_B1 				: out std_logic_vector(31 downto 0); 
		data_B2 				: out std_logic_vector(31 downto 0); 
		data_B3 				: out std_logic_vector(31 downto 0); 
		config_done  			: out std_logic; 
		src_alu 				: in std_logic_vector(31 downto 0); 
		dest_alu				: in std_logic_vector(31 downto 0);
		result                  : out std_logic_vector(63 downto 0));

end master_controller_muxes;


architecture arch of master_controller_muxes is


--MUX
--component mux_2_to_1 is
--  port (
--    clk     	: in std_logic;
 --   src_A    	: in  std_logic_vector(31 downto 0);
--    src_B    	: in  std_logic_vector(31 downto 0);
 --   sel       	: in  std_logic;
 --   dest       	: out std_logic_vector(31 downto 0)
 --   );
--end component;

--Definition of input signals type
--Using these types currently
type ALU_DATA_TYPE  	 			is  array(0 to ROWS) of std_logic_vector(31 downto 0);
type ALU_RDY_TYPE					is  array(0 to ROWS) of std_logic;
type ALU_OP_TYPE  					is  array(0 to ROWS) of std_logic_vector(7 downto 0);
type ALU_OUTPUT_TYPE		 		is 	array(0 to ROWS) of std_logic_vector(63 downto 0);
type mux_sel_typeA            		is  array(0 to ROWS) of std_logic_vector(1 downto 0); --Need to know if inputA or inputB so an extra bit
type mux_sel_typeB            		is  array(0 to ROWS) of std_logic_vector(1 downto 0);
type mux_data_flow_out_type       	is  array(0 to ROWS) of std_logic_vector(31 downto 0); --ACTUAL DATA FROM PREVIOUS ALU TO NEXT
type mux_data_flow_in_type			is  array(0 to ROWS) of std_logic_vector(63 downto 0);




--ALU signals
--signal 	 Vec_reset, Vec_clock, Vec_input_ready  	: single;
--signal   Vec_out_ready, sel_demux_i, sel_mux_i		: single;
--signal   demux_sel, mux_selA, mux_selB 				: single;
--signal 	 in_ALU_A, in_ALU_B, mux_srcA, mux_srcB  	: Vec_inputs;

--Modififications
signal   in_A, in_B 									: ALU_DATA_TYPE;
signal   in_rdy_sig, out_rdy_sig                        : ALU_RDY_TYPE;
signal   in_rdy_sig_demux, out_rdy_sig_demux            : ALU_RDY_TYPE;
signal 	 a_ready, b_ready								: ALU_RDY_TYPE;
signal   alu_op 										: ALU_OP_TYPE;
signal   alu_output 									: ALU_OUTPUT_TYPE;
signal   in_A64, in_B64, in_X64, in_Y64, out_Z64        : std_logic_vector(63 downto 0);
signal   zeros  										: std_logic_vector(63 downto 0);


--MUXES
signal select_linesA 					: mux_sel_typeA;
signal select_linesB 					: mux_sel_typeB;
signal flow_AX0_out, flow_AX1_out       : mux_data_flow_out_type;
signal flow_BX0_out, flow_BX1_out       : mux_data_flow_out_type;
signal data_flow_out					: mux_data_flow_in_type;
signal data_rdy							: std_logic_vector(1 downto 0);




--State machine  signal declaration
--signal current_state, next_state : types_master_fsm := start;
--signal start_configuration, done_configuration,  enable_config_device, disable_config_device : std_logic  := '0';
--signal demux0, demux1 : std_logic;
--signal 

--
--

begin

	--in_A(0) <= input_bus(31 downto 0);
	--in_B(0) <= input_bus(63 downto 32);
	--in_A(0) <= input_bus(95 downto 64);
	--in_B(0) <= input_bus(127 downto 96);

	result_0 <= data_flow_out(0); 
	result_1 <= data_flow_out(1); 
	result_2 <= data_flow_out(1); 
	result_3 <= data_flow_out(1); 
	result <= data_flow_out(1);
	--result <= data_flow_out(1, 1);
	data_A0   <= in_A(0); 
	data_A1   <= in_A(1); 
	data_B0   <= in_B(0);
	data_B1   <= in_B(1);


	data_A2   <= in_A(2);
	data_A3   <= in_A(3);
	data_B2   <= in_B(2);
	data_B3   <= in_B(3);
	

	--Dynamic configuration
	--Select lines 
	select_linesA(0) <= "01";
	select_linesB(0) <= "01";

	select_linesA(1) <= "01";
	select_linesB(1) <= "01";

	select_linesA(2) <= "00";
	select_linesB(2) <= "01";

	select_linesA(3) <= "01";
	select_linesB(3) <= "10";
	


	--Configuring OPCODES
	alu_op(0) <= OPCODE_ADD_SUB;
	alu_op(1) <= OPCODE_ADD_SUB;
	alu_op(2) <= OPCODE_MULT;
	alu_op(3) <= OPCODE_ADD_SUB;

	--select_lines(0, 0) <= "01";
	--select_lines(0, 1) <= "01";

	--Input ready signals
	in_rdy_sig(2) <= out_rdy_sig( 0) and out_rdy_sig(1);
	in_rdy_sig(3) <= out_rdy_sig( 0) and out_rdy_sig(1);

	--------------------------------------------------------------
	
	alus : for index in 0 to ROWS generate
	begin
			alu_s : entity work.ALU_EXPERIMENT_32 
						port map(in_A(index), in_B(index), clk,  rst,  in_rdy_sig(index),  out_rdy_sig(index), alu_op(index), data_flow_out(index));
	end generate;

	--for index in 0 to ROWS loop
	--	data_flow_out(ROWS) <= zeros;
	--end loop;
	
	----------------------------------------
	--ALU_0
	----------------------------------------
	muxes_A0 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), input_bus(63 downto 0), data_flow_out(1), data_flow_out(2), select_linesA(0), in_A(0));
	muxes_B0 : entity work.mux_4_to_1 
						port map(clk,  data_flow_out(0), input_bus(127 downto 64), data_flow_out(1), data_flow_out(2), select_linesB(0), in_B(0));

	----------------------------------------
	--ALU_1
	----------------------------------------
	muxes_A1 : entity work.mux_4_to_1 
						port map(clk, data_flow_out(1), input_bus(127 downto 64), data_flow_out(2), data_flow_out(3), select_linesA(1), in_A(1));
	muxes_B1 : entity work.mux_4_to_1 
						port map(clk, data_flow_out(1), input_bus(95 downto 32), data_flow_out(2), data_flow_out(3), select_linesB(1), in_B(1));					
	
	----------------------------------------
	--ALU_2
	----------------------------------------
    muxes_A2 : entity work.mux_4_to_1 
						port map(clk, data_flow_out(1), data_flow_out(2), data_flow_out(3), data_flow_out(3), select_linesA(2), in_A(2));

	muxes_B2 : entity work.mux_4_to_1 
						port map(clk, data_flow_out(1), data_flow_out(2), data_flow_out(3), data_flow_out(3), select_linesB(2), in_B(2));	

    ----------------------------------------
	--ALU_3
	----------------------------------------
	muxes_A3 : entity work.mux_4_to_1 
						port map(clk, data_flow_out(0),  data_flow_out(1), data_flow_out(2), data_flow_out(3),  select_linesA(3), in_A(3));

	muxes_B3 : entity work.mux_4_to_1 
						port map(clk, data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesB(3), in_B(3));	

	----------------------------------------
	--ALU_4
	----------------------------------------
    muxes_A4 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesA(4), in_B(4));	

    muxes_B4 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(0), data_flow_out(1), data_flow_out(2), data_flow_out(3), select_linesB(4), in_B(4));	

	----------------------------------------
	--ALU_5
	----------------------------------------
    muxes_A5 : entity work.mux_4_to_1 
    					port map(clk, data_flow_out(1), data_flow_out(2), data_flow_out(3), data_flow_out(4), select_linesA(5), in_A(5));	

    muxes_B5 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(1), data_flow_out(2), data_flow_out(3), data_flow_out(4), select_linesB(5), in_B(5));	

	----------------------------------------
	--ALU_6
	----------------------------------------
    muxes_A6 : entity work.mux_4_to_1 
    					port map(clk, data_flow_out(2), data_flow_out(3), data_flow_out(4), data_flow_out(5), select_linesA(6), in_A(6));	

    muxes_B6 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(2), data_flow_out(3), data_flow_out(4), data_flow_out(5), select_linesB(6), in_B(6));


	----------------------------------------
	--ALU_7
	----------------------------------------
    muxes_A7 : entity work.mux_4_to_1 
    					port map(clk, data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesA(7), in_A(7));	

    muxes_B7 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(3), data_flow_out(4), data_flow_out(5), data_flow_out(6), select_linesB(7), in_B(7));  	


	----------------------------------------
	--ALU_8
	----------------------------------------
    muxes_A8 : entity work.mux_4_to_1 
    					port map(clk, data_flow_out(4), data_flow_out(5), data_flow_out(6), data_flow_out(7), select_linesA(8), in_A(8));	

    muxes_B8 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(4), data_flow_out(5), data_flow_out(6), data_flow_out(7), select_linesB(8), in_B(8));


	----------------------------------------
	--ALU_9
	----------------------------------------
    muxes_A9 : entity work.mux_4_to_1 
    					port map(clk, data_flow_out(5), data_flow_out(6), data_flow_out(7), data_flow_out(8), select_linesA(9), in_A(9));	

    muxes_B9 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(5), data_flow_out(6), data_flow_out(7), data_flow_out(8), select_linesB(9), in_B(9));


	----------------------------------------
	--ALU_10
	----------------------------------------
    muxes_A10 : entity work.mux_4_to_1 
    					port map(clk, data_flow_out(6), data_flow_out(7), data_flow_out(8), data_flow_out(9), select_linesA(10), in_A(10));	

    muxes_B10 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(6), data_flow_out(7), data_flow_out(8), data_flow_out(9), select_linesB(10), in_B(10));

	----------------------------------------
	--ALU_11
	----------------------------------------
    muxes_A11 : entity work.mux_4_to_1 
    					port map(clk, data_flow_out(7), data_flow_out(8), data_flow_out(9), data_flow_out(10), select_linesA(11), in_A(11));	

    muxes_B11 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(7), data_flow_out(8), data_flow_out(9), data_flow_out(10), select_linesB(11), in_B(11));

	----------------------------------------
	--ALU_12
	----------------------------------------
	muxes_A12 : entity work.mux_4_to_1 
    					port map(clk, data_flow_out(8), data_flow_out(9), data_flow_out(10), data_flow_out(11), select_linesA(12), in_A(12));	

    muxes_B12 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(8), data_flow_out(9), data_flow_out(10), data_flow_out(11), select_linesB(12), in_B(12));

	----------------------------------------
	--ALU_13
	----------------------------------------
 	muxes_A13 : entity work.mux_4_to_1 
    					port map(clk, data_flow_out(9), data_flow_out(10), data_flow_out(11), data_flow_out(12), select_linesA(13), in_A(13));	

    muxes_B13 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(9), data_flow_out(10), data_flow_out(11), data_flow_out(12), select_linesB(13), in_B(13));


	----------------------------------------
	--ALU_14
	----------------------------------------
    muxes_A14 : entity work.mux_4_to_1 
    					port map(clk, data_flow_out(10), data_flow_out(11), data_flow_out(12), data_flow_out(13), select_linesA(14), in_A(14));	

    muxes_B14 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(10), data_flow_out(11), data_flow_out(12), data_flow_out(13), select_linesB(14), in_B(14));

	----------------------------------------
	--ALU_15
	----------------------------------------
    muxes_A15 : entity work.mux_4_to_1 
    					port map(clk, data_flow_out(11), data_flow_out(11), data_flow_out(12), data_flow_out(14), select_linesA(15), in_A(15));	

    muxes_B15 : entity work.mux_4_to_1
    					port map(clk, data_flow_out(11), data_flow_out(11), data_flow_out(12), data_flow_out(14), select_linesB(15), in_B(15));



state_machine : process( clk) is
begin 
	
	if (rising_edge(clk)) then 
		
			
			--alu_op(0) <= OPCODE_ADD_SUB;
			--alu_op(1) <= OPCODE_ADD_SUB;
			--alu_op(2) <= OPCODE_MULT;
			--alu_op(3) <= OPCODE_ADD_SUB;
			in_rdy_sig(0) <= '1';
			in_rdy_sig(1) <= '1'; 
		--end if;
		
		
	end if;
end process;
end arch;


