# STM32H743 CMake Template [![wakatime](https://wakatime.com/badge/user/fbf439cc-9e02-45cc-bb7f-21ca6fd95e8d/project/f985af85-c488-46b1-bfa1-013a09d145e9.svg)](https://wakatime.com/badge/user/fbf439cc-9e02-45cc-bb7f-21ca6fd95e8d/project/f985af85-c488-46b1-bfa1-013a09d145e9)

A template for developing projects for STM32H743 with [CLion](https://www.jetbrains.com/clion/) and [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html).

## Details

+ PA1 - LED
+ USART2/USB - [Serial console](https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_CLI/FreeRTOS_Plus_Command_Line_Interface.html), printf redirection
+ [FreeRTOS](https://www.freertos.org/) + [CMSIS V2](https://www.keil.com/pack/doc/CMSIS/RTOS2/html/index.html)
+ ILI9341 on SPI2
+ [LVGL](https://lvgl.io/)