library ieee;
use ieee.std_logic_1164.all;

entity demux_1_to_2 is
  port (
    clk         : in std_logic;
    src         : in  std_logic_vector(63 downto 0);
    sel         : in  std_logic;
    dest_inX0      : out std_logic_vector(31 downto 0);
    dest_inX1      : out std_logic_vector(31 downto 0)
    );
end demux_1_to_2;

architecture arch of demux_1_to_2 is
begin
process(clk, sel)
begin  -- arch
    if(rising_edge(clk)) then
        case sel is
            when '0' =>
                dest_inX0 <= src(31 downto 0);
            when '1' =>
                dest_inX1 <= src(31 downto 0);
            when others =>
                NULL;
        end case;
    end if;
end process; 
end arch;