//#include "flash.h"
#include "led.h"
#include "sha256.h"

#include "pico/stdlib.h"
#include "pico/rand.h"

#include <algorithm>

#include <cstdio>
#include <cstring>

#if defined(PICO_RISCV)
const char* arch = "RISC-V Hazard 3";
#else
const char* arch = "ARM Cortex M33";
#endif


int main() {
  stdio_init_all();
  LED led(PICO_DEFAULT_LED_PIN);

  std::vector<uint8_t> data;
  data.reserve(250);
  std::generate_n(std::back_inserter(data), 250, [n = 0]() mutable { return n++; });

  std::vector<uint8_t> hash = hw_sha256(data);

  // Write hash to flash
  // flash::write(hash);

  for (uint32_t i = 0;; ++i) {
    printf("Hello from %s (%d) random=%u\n", arch, i, get_rand_32());
    for (uint8_t byte : data) {
      printf("%02x", byte);
    }
    printf("\n");
    for (uint8_t byte : hash) {
      printf("%02x", byte);
    }
    printf("\n");
    // auto f = flash::read(32);
    // for (uint8_t byte : f) {
    //   printf("%02x", byte);
    // }
    // printf("\n");
    sleep_ms(750);
    led.on();
    sleep_ms(250);
    led.off();
  }
}
