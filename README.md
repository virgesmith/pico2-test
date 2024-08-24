# pico2-test

Simple C++ test app for the Pico 2 building for either ARM or RISC-V. Flashes onboard LED and prints to serial over USB, which can be seen using:

```sh
minicom -b 115200 -D /dev/ttyACM0
```

Build system avoids using the buggy and unreliable (as of Aug 24) pico vscode plugin (it's still in dev).

RISC-V toolchain can be found [here](https://www.embecosm.com/resources/tool-chain-downloads/#riscv-stable)

Works with `arm-none-eabi-gcc` 10.3 (ubuntu 22 default) and 13.2

See CMakeLists.txt:

- Set `PICO_SDK_PATH` and `PICO_TOOLCHAIN_PATH`  appropriately
- Comment/uncomment `PICO_TOOLCHAIN_PATH` and `PICO_PLATFORM` definitions to switch between ARM and RISC-V

## TODO

- [ ] Get it working with a release version of Pico SDK (mbedtls version issues?)
- [ ] parameterise platform