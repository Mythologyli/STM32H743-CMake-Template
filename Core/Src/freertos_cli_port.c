#include "FreeRTOS.h"
#include "queue.h"

#include "stm32h7xx_ll_usart.h"
#include "usbd_cdc_if.h"

#include "freertos_cli_port.h"

#define serINVALID_QUEUE                ( ( QueueHandle_t ) 0 )

static QueueHandle_t xRxedChars;
static QueueHandle_t xCharsForTx;

void xSerialPortInitMinimal(unsigned portBASE_TYPE uxQueueLength)
{
    xRxedChars = xQueueCreate(uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( signed char ));
    xCharsForTx = xQueueCreate(uxQueueLength + 1, ( unsigned portBASE_TYPE ) sizeof( signed char ));
}

signed portBASE_TYPE xSerialGetChar(signed char *pcRxedChar, TickType_t xBlockTime)
{
    if (xQueueReceive(xRxedChars, pcRxedChar, xBlockTime))
    {
        return pdTRUE;
    }
    else
    {
        return pdFALSE;
    }
}

void vSerialPutString(const signed char *pcString)
{
    signed char *pxNext;

    pxNext = (signed char *) pcString;
    while (*pxNext)
    {
        xSerialPutChar(*pxNext, 0);
        pxNext++;
    }
}

signed portBASE_TYPE xSerialPutChar(signed char cOutChar, TickType_t xBlockTime)
{
    signed portBASE_TYPE xReturn;

    if (xQueueSend(xCharsForTx, &cOutChar, xBlockTime) == pdPASS)
    {
        xReturn = pdPASS;

        uint8_t data;
        if (xQueueReceive(xCharsForTx, &data, 0) == pdTRUE)
        {
            ConsoleSend(data);
        }
    }
    else
    {
        xReturn = pdFAIL;
    }

    return xReturn;
}

#if CONSOLE_USE_USART2 == 1

void Usart2Callback(void)
{
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    uint8_t data = LL_USART_ReceiveData8(USART2);
    xQueueSendFromISR(xRxedChars, &data, &xHigherPriorityTaskWoken);
}

#endif

#if CONSOLE_USE_USB == 1

void UsbCallback(uint8_t *data_buffer, uint32_t length)
{
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    for (int i = 0; i < length; i++)
    {
        xQueueSendFromISR(xRxedChars, data_buffer + i, &xHigherPriorityTaskWoken);
    }
}

#endif

int __io_putchar(int ch)
{
    uint8_t data = ch;
    ConsoleSend(data);
    return ch;
}
