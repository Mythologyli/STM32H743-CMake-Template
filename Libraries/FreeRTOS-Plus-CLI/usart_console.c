#include "string.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "FreeRTOS_CLI.h"

#include "freertos_cli_port.h"

#define cmdMAX_INPUT_SIZE 50
#define cmdQUEUE_LENGTH 25
#define cmdASCII_DEL ( 0x7F )
#define cmdMAX_MUTEX_WAIT pdMS_TO_TICKS( 300 )

static void prvUARTCommandConsoleTask(void *pvParameters);

void vUARTCommandConsoleStart(uint16_t usStackSize, UBaseType_t uxPriority);

static const char *const pcWelcomeMessage = "STM32H743 Console.\r\nType 'help' to view commands.\r\n\r\n>";
static const char *const pcEndOfOutputMessage = "\r\n[Press ENTER to execute the previous command again]\r\n>";
static const char *const pcNewLine = "\r\n";

static SemaphoreHandle_t xTxMutex = NULL;

void vUARTCommandConsoleStart(uint16_t usStackSize, UBaseType_t uxPriority)
{
    xTxMutex = xSemaphoreCreateMutex();
    configASSERT(xTxMutex);

    xTaskCreate(prvUARTCommandConsoleTask,
                "CLI",
                usStackSize,
                NULL,
                uxPriority,
                NULL);
}

static void prvUARTCommandConsoleTask(void *pvParameters)
{
    signed char cRxedChar;
    uint8_t ucInputIndex = 0;
    char *pcOutputString;
    static char cInputString[cmdMAX_INPUT_SIZE], cLastInputString[cmdMAX_INPUT_SIZE];
    BaseType_t xReturned;

    (void) pvParameters;

    pcOutputString = FreeRTOS_CLIGetOutputBuffer();

    xSerialPortInitMinimal(cmdQUEUE_LENGTH);

    vSerialPutString((signed char *) pcWelcomeMessage);

    for (;;)
    {
        while (xSerialGetChar(&cRxedChar, portMAX_DELAY) != pdPASS);

        if (xSemaphoreTake(xTxMutex, cmdMAX_MUTEX_WAIT) == pdPASS)
        {
            xSerialPutChar(cRxedChar, portMAX_DELAY);

            if (cRxedChar == '\n' || cRxedChar == '\r')
            {
                vSerialPutString((signed char *) pcNewLine);

                if (ucInputIndex == 0)
                {
                    strcpy(cInputString, cLastInputString);
                }

                do
                {
                    xReturned = FreeRTOS_CLIProcessCommand(cInputString, pcOutputString,
                                                           configCOMMAND_INT_MAX_OUTPUT_SIZE);

                    vSerialPutString((signed char *) pcOutputString);

                } while (xReturned != pdFALSE);

                strcpy(cLastInputString, cInputString);
                ucInputIndex = 0;
                memset(cInputString, 0x00, cmdMAX_INPUT_SIZE);

                vSerialPutString((signed char *) pcEndOfOutputMessage);
            }
            else
            {
                if (cRxedChar == '\r')
                {

                }
                else if ((cRxedChar == '\b') || (cRxedChar == cmdASCII_DEL))
                {
                    if (ucInputIndex > 0)
                    {
                        ucInputIndex--;
                        cInputString[ucInputIndex] = '\0';
                    }
                }
                else
                {
                    if ((cRxedChar >= ' ') && (cRxedChar <= '~'))
                    {
                        if (ucInputIndex < cmdMAX_INPUT_SIZE)
                        {
                            cInputString[ucInputIndex] = cRxedChar;
                            ucInputIndex++;
                        }
                    }
                }
            }

            xSemaphoreGive(xTxMutex);
        }
    }
}
