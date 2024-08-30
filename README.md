# pico2-test

Simple C++ test app for the Pico 2, building for either ARM or RISC-V. Flashes onboard LED and prints to serial over USB, which can be seen using:

```sh
minicom -b 115200 -D /dev/ttyACM0
```

Also:
- reproducible example of RISC-V crash (board resets into bootsel mode when you run it)
- example of writing to flash memory (which *is* not preserved through a reboot (or power cycle?)). For some reason the final block doesnt preserve the data, but the penultimate one does.

Build system avoids using the buggy and unreliable (as of Aug 24) pico vscode plugin (it's still in dev apparently).

RISC-V toolchain can be found [here](https://www.embecosm.com/resources/tool-chain-downloads/#riscv-stable)

Works with `arm-none-eabi-gcc` 10.3 (ubuntu 22 default) and 13.2

See CMakeLists.txt:

- Set values `PICO_SDK_PATH` and `PICO_TOOLCHAIN_PATH`  appropriately
- Generate Makefile using either
  - `cmake -DPICO_PLATFORM=rp2350-arm-s`, or
  - `cmake -DPICO_PLATFORM=rp2350-riscv`

## See also

[https://www.raspberrypi.com/documentation/pico-sdk/](https://www.raspberrypi.com/documentation/pico-sdk/)

[https://datasheets.raspberrypi.com/rp2350/rp2350-datasheet.pdf](https://datasheets.raspberrypi.com/rp2350/rp2350-datasheet.pdf)

