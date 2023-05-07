library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity counter8b is
  Port (
    -- input clock
    CLK : in STD_LOGIC;
    -- LEDs to display count
    COUNT : out STD_LOGIC_VECTOR (7 downto 0);
    -- direction of counter (up or down)
    DIR : in STD_LOGIC);
end counter8b;

architecture Behavioral of counter8b is

  signal clk_div : STD_LOGIC_VECTOR (28 downto 0) := (others => '0');
  signal counter : STD_LOGIC_VECTOR (7 downto 0) := X"00";

begin

  -- clock divider
  process (CLK)
  begin
    if ( rising_edge(CLK) ) then
      clk_div <= clk_div + '1';
    end if;
  end process;


  
  -- up/down counter, 200 MHz -> 0.75 Hz
  process (clk_div(28), DIR)
  begin
    -- counting up
    if ( rising_edge(clk_div(28)) ) then
      if (DIR = '1') then
        counter <= counter + '1';
      -- counting down
      elsif (DIR = '0') then
        counter <= counter - '1';
      end if;
    end if;      
  end process;

COUNT <= counter;
--COUNT <= not count;

end Behavioral;
  
