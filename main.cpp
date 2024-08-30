#include "flash.h"
#include "led.h"
#include "sha256.h"

#include "pico/stdlib.h"

#include <algorithm>

#include <cstdio>
#include <cstring>

#if defined(PICO_RISCV)
const char* arch = "RISC-V Hazard 3";
#else
const char* arch = "ARM Cortex M33";
#endif

// calling this function resets the pico into bootsel mode when running on RISC-V
void append(std::vector<uint8_t>& b, const std::vector<uint8_t>& extra) {
  // b.reserve(b.size() + extra.size()); this shouldnt be necessary, and doesnt help anyway
  b.insert(b.end(), extra.begin(), extra.end());
}

int main() {
  stdio_init_all();
  LED led(PICO_DEFAULT_LED_PIN);

  std::vector<uint8_t> data;
  // this also triggers the crash below
  // data.reserve(250);
  // std::generate_n(std::back_inserter(data), 250, [n = 0]() mutable { return n++; });
  // this doesn't
  data.resize(250);
  for (uint8_t i = 0; i < 250; ++i) {
    data[i] = i;
  }

  std::vector<uint8_t> hash = hw_sha256(data);

  // Uncomment to reproduce RISC-V crash
  // append(hash, hash); // kaboom on RISC-V!
  // hash.insert(hash.end(), hash.begin(), hash.end()); // works!!

  // Write hash to flash
  // flash::write(hash);

  for (uint32_t i = 0;; ++i) {
    printf("Hello from %s (%d) flash_size=%08x xip_base=%08x\n", arch, i, PICO_FLASH_SIZE_BYTES, XIP_BASE);
    for (uint8_t byte : data) {
      printf("%02x", byte);
    }
    printf("\n");
    for (uint8_t byte : hash) {
      printf("%02x", byte);
    }
    printf("\n");
    auto f = flash::read(32);
    for (uint8_t byte : f) {
      printf("%02x", byte);
    }
    printf("\n");
    sleep_ms(750);
    led.on();
    sleep_ms(250);
    led.off();
  }
}
