#pragma once
#include "pico_wireless.hpp"
#include "spi_drv.hpp"

#include "pico/stdlib.h"


class Pico2Wireless: public pimoroni::PicoWireless {
 public:
  Pico2Wireless() {
// Workaround for apparent manifestation of E9 hardware bug
// Force the ACK pin low before init() is called
#ifdef PICO_RP2350
    auto ack = pimoroni::SpiDrv::DEFAULT_ACK_PIN;
    gpio_init(ack);
    gpio_set_dir(ack, GPIO_OUT);
    gpio_put(ack, 0);
#endif
  }
};


