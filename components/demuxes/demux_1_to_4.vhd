library ieee;
use ieee.std_logic_1164.all;

entity demux_1_to_4 is
  port (
    clk         : in std_logic;
    src_data            : in  std_logic_vector(63 downto 0);
   -- src_out_rdy         : in  std_logic;
    sel                 : in  std_logic_vector(1 downto 0);
   -- dest_inX0_rdy       : out std_logic;
   -- dest_inX1_rdy       : out std_logic;
   -- dest_inX2_rdy       : out std_logic;
  --  dest_inX3_rdy       : out std_logic;
    dest_inX0           : out std_logic_vector(31 downto 0);
    dest_inX1           : out std_logic_vector(31 downto 0);
    dest_inX2           : out std_logic_vector(31 downto 0);
    dest_inX3           : out std_logic_vector(31 downto 0)
    );
end demux_1_to_4;

architecture arch of demux_1_to_4 is
begin
process(clk, sel)
begin  -- arch
    if(rising_edge(clk)) then
        case sel is
            when "00" =>
                dest_inX0 <= src_data(31 downto 0);
                --dest_inX0_rdy <= src_out_rdy;
            when "01" =>
                dest_inX1 <= src_data(31 downto 0);
               -- dest_inX1_rdy <= src_out_rdy;
            when "10" =>
                dest_inX2 <= src_data(31 downto 0);
               -- dest_inX2_rdy <= src_out_rdy;
            when "11" =>
                dest_inX3 <= src_data(31 downto 0);
               -- dest_inX3_rdy <= src_out_rdy;

            when others =>
                NULL;
        end case;
    end if;
end process; 
end arch;