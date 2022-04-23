#ifndef STM32H743_CMAKE_TEMPLATE_CONSOLE_CONF_H
#define STM32H743_CMAKE_TEMPLATE_CONSOLE_CONF_H

#define CONSOLE_USE_USART2 1
#define CONSOLE_USE_USB 0

#if CONSOLE_USE_USART2 == 1
#define ConsoleSend(__data__) LL_USART_TransmitData8(USART2, (__data__)); \
                              while (!LL_USART_IsActiveFlag_TXE(USART2))
#endif

#if CONSOLE_USE_USB == 1
#define ConsoleSend(__data__) while (CDC_Transmit_FS(&(__data__), 1))
#endif

#endif //STM32H743_CMAKE_TEMPLATE_CONSOLE_CONF_H
