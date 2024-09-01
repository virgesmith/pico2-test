# pico2-test

Simple C++ test app for the Pico 2, building for either ARM or RISC-V. Flashes onboard LED and prints to serial over USB, which can be seen using:

```sh
minicom -b 115200 -D /dev/ttyACM0
```

Also:
- example of writing to flash memory (which *is* preserved through a uf2 load). For some reason (probably bootrom errata E10, see datasheet) the final block doesn't preserve the data, but the penultimate one (and presumably all the others) does.

Build system avoids using the buggy and unreliable (as of Aug 24) pico vscode plugin (it's still in dev apparently).

RISC-V toolchain can be found [here](https://github.com/raspberrypi/pico-sdk-tools/releases/). NB Avoid the builds at https://www.embecosm.com/resources/tool-chain-downloads/#riscv-stable, binaries produced by them can reset the board.

ARM build works with `arm-none-eabi-gcc` 10.3 (ubuntu 22 default) and 13.2. `riscv32-unknown-elf-gcc` from above is 14.2.1.

See CMakeLists.txt:

- Set values `PICO_SDK_PATH` and `PICO_TOOLCHAIN_PATH`  appropriately
- Generate Makefile using either
  - `cd build && cmake -DPICO_PLATFORM=rp2350-arm-s ..`, or
  - `cd build && cmake -DPICO_PLATFORM=rp2350-riscv ..`

## See also

[https://www.raspberrypi.com/documentation/pico-sdk/](https://www.raspberrypi.com/documentation/pico-sdk/)

[https://datasheets.raspberrypi.com/rp2350/rp2350-datasheet.pdf](https://datasheets.raspberrypi.com/rp2350/rp2350-datasheet.pdf)

