library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity top is
  Port (
    -- system clock
    sysclk_p : in STD_LOGIC;
    sysclk_n : in STD_LOGIC;
    -- LEDs 
    gpio_led_7_ls : out std_logic;
    gpio_led_6_ls : out std_logic;
    gpio_led_5_ls : out std_logic;      
    gpio_led_4_ls : out std_logic;
    gpio_led_3_ls : out std_logic;
    gpio_led_2_ls : out std_logic;
    gpio_led_1_ls : out std_logic;
    gpio_led_0_ls : out std_logic;
    -- DIP switch
    gpio_dip_sw1  : in std_logic
    );
end top;

architecture Behavioral of top is

  signal sysclk : STD_LOGIC;
  signal direction, reset : STD_LOGIC;
  signal leds : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
  signal initial_value : STD_LOGIC_VECTOR (7 downto 0);
  signal count_div : STD_LOGIC_VECTOR(27 downto 0) := (others => '0');

begin

  sysbuf : entity IBUFDS
  port map(
    I  => sysclk_p,
    IB => sysclk_n,
    O  => sysclk
    );

  
  
  counter : entity work.counter8b_rst
  port map(
    CLK       => sysclk,
    -- ctrl
    DIR       => direction,
    RST       => reset,
    INITV     => initial_value,
    -- outputs
    COUNT     => leds,
    COUNT_INT => count_div    
    );

  gpio_led_7_ls <= leds(7);
  gpio_led_6_ls <= leds(6);
  gpio_led_5_ls <= leds(5);
  gpio_led_4_ls <= leds(4);
  gpio_led_3_ls <= leds(3);
  gpio_led_2_ls <= leds(2);
  gpio_led_1_ls <= leds(1);
  gpio_led_0_ls <= leds(0);  

  -- take direction from vio instead ...
  --direction <= gpio_dip_sw1;
  
  myila : entity work.ila_0
    port map(
      clk        => sysclk,
      probe0(0)  => reset, --1b
      probe1(0)  => direction, --1b      
      probe2     => initial_value, --8b
      probe3     => leds, --8b
      probe4     => count_div --28b
      );

    myvio : entity work.vio_0 
    port map(
      clk            => sysclk,
      probe_out0(0)  => reset,
      probe_out1(0)  => direction,
      probe_out2     => initial_value,      
      probe_in0      => leds
      );
  

end Behavioral;
  
