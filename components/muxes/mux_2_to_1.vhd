library ieee;
use ieee.std_logic_1164.all;

entity mux_2_to_1 is
  port (
    clk     : in std_logic;
    src_A    : in  std_logic_vector(31 downto 0);
    src_B    : in  std_logic_vector(31 downto 0);
    sel       : in  std_logic;
    dest       : out std_logic_vector(31 downto 0)
    );
end mux_2_to_1;

architecture arch of mux_2_to_1 is
---
begin
process(clk, sel)
begin  -- arch
    if(rising_edge(clk)) then
        case sel is
            when '0' =>
                dest <= src_A;
            when '1' =>
                dest <= src_B;
            when others =>
                NULL;
        end case;
    end if;
end process; 
end arch;