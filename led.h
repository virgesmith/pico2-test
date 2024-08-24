#pragma once

#include "pico/stdlib.h"

class LED {
public:
  LED(int pin) : m_pin(pin) {
    gpio_init(m_pin);
    gpio_set_dir(m_pin, GPIO_OUT);
  }

  void on() const {
    gpio_put(m_pin, 1);
  }

  void off() const {
    gpio_put(m_pin, 0);
  }

private:
  int m_pin;
};
