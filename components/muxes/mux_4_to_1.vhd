library ieee;
use ieee.std_logic_1164.all;

entity mux_4_to_1 is
  port (
    clk     : in std_logic;
    src_X0    : in  std_logic_vector(63 downto 0);
    src_X1    : in  std_logic_vector(63 downto 0);
    src_X2    : in  std_logic_vector(63 downto 0);
    src_X3    : in  std_logic_vector(63 downto 0);
    sel       : in  std_logic_vector(1 downto 0);
    dest      : out std_logic_vector(31 downto 0)
    );
end mux_4_to_1;

architecture arch of mux_4_to_1 is
---
begin
process(sel, clk)
begin  -- arch
    if(rising_edge(clk)) then
        case sel is
            when "00" =>
                dest <= src_X0(31 downto 0);
            when "01" =>
                dest <= src_X1(31 downto 0);
            when "10" =>
                dest <= src_X2(31 downto 0);
            when "11" =>
                dest <= src_X3(31 downto 0);
            when others =>
                NULL;
        end case;
    end if;
end process; 
end arch;