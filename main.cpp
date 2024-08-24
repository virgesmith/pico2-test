#include "led.h"

#include "pico/stdlib.h"
#include <cstdio>


#if defined(PICO_RISCV)
const char* arch = "RISC-V Hazard 3";
#else
const char* arch = "ARM Cortex M33";
#endif

int main()
{
  stdio_init_all();
  LED led(PICO_DEFAULT_LED_PIN);

  for (uint32_t i = 0;; ++i)
  {
    printf("Hello from %s (%d)\n", arch, i);
    sleep_ms(750);
    led.on();
    sleep_ms(250);
    led.off();
  }
}
