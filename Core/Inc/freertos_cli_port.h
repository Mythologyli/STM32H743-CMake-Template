#ifndef STM32H743_CMAKE_TEMPLATE_FREERTOS_CLI_PORT_H
#define STM32H743_CMAKE_TEMPLATE_FREERTOS_CLI_PORT_H

#include "console_conf.h"

void xSerialPortInitMinimal(unsigned portBASE_TYPE uxQueueLength);

void vSerialPutString(const signed char *pcString);

signed portBASE_TYPE xSerialGetChar(signed char *pcRxedChar, TickType_t xBlockTime);

signed portBASE_TYPE xSerialPutChar(signed char cOutChar, TickType_t xBlockTime);

#if CONSOLE_USE_USART2

void Usart2Callback(void);

#endif

#if CONSOLE_USE_USB

void UsbCallback(uint8_t *data_buffer, uint32_t length);

#endif

#endif
