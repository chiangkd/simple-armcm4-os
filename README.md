# simple-armcm4-os

A minimal multi-tasking OS kernel for ARM CM4

Motivated by [mini-arm-os](https://github.com/jserv/mini-arm-os)

## Architecture
- CMSIS (From [CMSIS-Core](https://github.com/ARM-software/CMSIS_5/tree/develop/CMSIS/Core) and [CMSIS-Device](https://developer.arm.com/embedded/cmsis/cmsis-packs/devices/))
- SPL (Standard Peripheral Library from [ST](https://www.st.com/en/embedded-software/stm32-standard-peripheral-libraries.html))
- [NUCLEO-F303ZE](https://os.mbed.com/platforms/ST-Nucleo-F303ZE/) for example

## Quick Start

Run `make` to compile, `make upload` to upload the program to device, `make debug` for [openocd](https://openocd.org/)

Connecting VCM on ST-LINK
```shell
screen /dev/ttyACM0 115200
```
- `Ctrl-A` + `K` to exit