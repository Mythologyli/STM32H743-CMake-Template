#include <string.h>
#include <stdio.h>

#include "main.h"
#include "FreeRTOS_CLI.h"

#include "origin_cli_commands.h"

static BaseType_t prvEchoCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvLed2ToggleCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

static const CLI_Command_Definition_t xEcho =
        {
                "echo",
                "\r\necho:\r\n Echo your input\r\n",
                prvEchoCommand,
                -1
        };

static BaseType_t prvEchoCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
    const char *pcParameter;
    BaseType_t xParameterStringLength;
    UBaseType_t uxParameterNumber = 1;

    memset(pcWriteBuffer, 0x00, xWriteBufferLen);

    for (;;)
    {
        pcParameter = FreeRTOS_CLIGetParameter
                (
                        pcCommandString,
                        uxParameterNumber,
                        &xParameterStringLength
                );

        if (pcParameter != NULL)
        {
            if (uxParameterNumber > 1)
            {
                strcat(pcWriteBuffer, " ");
            }

            strncat(pcWriteBuffer, pcParameter, (size_t) xParameterStringLength);

            uxParameterNumber++;
        }
        else
        {
            strcat(pcWriteBuffer, "\r\n");
            return pdFALSE;
        }
    }
}

static const CLI_Command_Definition_t xLed2Toggle =
        {
                "led2-toggle",
                "\r\nled2-toggle:\r\n Toggle LED2\r\n",
                prvLed2ToggleCommand,
                0
        };

static BaseType_t prvLed2ToggleCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
    Led2_Toggle;

    memset(pcWriteBuffer, 0x00, xWriteBufferLen);

    return pdFALSE;
}

void vRegisterCLICommands(void)
{
    FreeRTOS_CLIRegisterCommand(&xEcho);
    FreeRTOS_CLIRegisterCommand(&xLed2Toggle);

    vRegisterOriginCLICommands();
}
