library ieee;
use ieee.std_logic_1164.all;

entity demux_rdy_1_to_2 is
  port (
    clk                 : in std_logic;
    src_out_rdy         : in  std_logic;
    sel                 : in  std_logic;
    dest_in_rdy1        : out std_logic;
    dest_in_rdy2        : out std_logic
    );
end demux_rdy_1_to_2;

architecture arch of demux_rdy_1_to_2 is
begin
process(clk, sel)
begin  -- arch
    if(rising_edge(clk)) then
        case sel is
            when '0' =>
                dest_in_rdy1 <= src_out_rdy;
            when '1' =>
                dest_in_rdy2 <= src_out_rdy;
            when others =>
                NULL;
        end case;
    end if;
end process; 
end arch;