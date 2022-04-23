#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>
#include <string.h>

#include "FreeRTOS_CLI.h"

#include "origin_cli_commands.h"

#define configINCLUDE_QUERY_HEAP_COMMAND 1

#ifndef configINCLUDE_QUERY_HEAP_COMMAND
#define configINCLUDE_QUERY_HEAP_COMMAND 0
#endif

void vRegisterCLICommands(void);

static BaseType_t prvTaskStatsCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

#if(configGENERATE_RUN_TIME_STATS == 1)

static BaseType_t prvRunTimeStatsCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

#endif

static BaseType_t
prvThreeParameterEchoCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

static BaseType_t prvParameterEchoCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

#if(configINCLUDE_QUERY_HEAP_COMMAND == 1)

static BaseType_t prvQueryHeapCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

#endif

static const CLI_Command_Definition_t xTaskStats =
        {
                "task-stats",
                "\r\ntask-stats:\r\n Displays a table showing the state of each FreeRTOS task\r\n",
                prvTaskStatsCommand,
                0
        };

static const CLI_Command_Definition_t xThreeParameterEcho =
        {
                "echo-3-parameters",
                "\r\necho-3-parameters <param1> <param2> <param3>:\r\n Expects three parameters, echos each in turn\r\n",
                prvThreeParameterEchoCommand,
                3
        };

static const CLI_Command_Definition_t xParameterEcho =
        {
                "echo-parameters",
                "\r\necho-parameters <...>:\r\n Take variable number of parameters, echos each in turn\r\n",
                prvParameterEchoCommand,
                -1
        };

#if(configGENERATE_RUN_TIME_STATS == 1)

static const CLI_Command_Definition_t xRunTimeStats =
        {
                "run-time-stats",
                "\r\nrun-time-stats:\r\n Displays a table showing how much processing time each FreeRTOS task has used\r\n",
                prvRunTimeStatsCommand, /* The function to run. */
                0
        };
#endif

#if(configINCLUDE_QUERY_HEAP_COMMAND == 1)

static const CLI_Command_Definition_t xQueryHeap =
        {
                "query-heap",
                "\r\nquery-heap:\r\n Displays the free heap space, and minimum ever free heap space.\r\n",
                prvQueryHeapCommand,
                0
        };
#endif

void vRegisterOriginCLICommands(void)
{
    FreeRTOS_CLIRegisterCommand(&xTaskStats);
    FreeRTOS_CLIRegisterCommand(&xThreeParameterEcho);
    FreeRTOS_CLIRegisterCommand(&xParameterEcho);

#if(configGENERATE_RUN_TIME_STATS == 1)
    {
        FreeRTOS_CLIRegisterCommand(&xRunTimeStats);
    }
#endif

#if(configINCLUDE_QUERY_HEAP_COMMAND == 1)
    {
        FreeRTOS_CLIRegisterCommand(&xQueryHeap);
    }
#endif
}

static BaseType_t prvTaskStatsCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
    const char *const pcHeader = "     State   Priority  Stack    #\r\n************************************************\r\n";
    BaseType_t xSpacePadding;

    (void) pcCommandString;
    (void) xWriteBufferLen;
    configASSERT(pcWriteBuffer);

    strcpy(pcWriteBuffer, "Task");
    pcWriteBuffer += strlen(pcWriteBuffer);

    configASSERT(configMAX_TASK_NAME_LEN > 3);
    for (xSpacePadding = strlen("Task"); xSpacePadding < (configMAX_TASK_NAME_LEN - 3); xSpacePadding++)
    {
        *pcWriteBuffer = ' ';
        pcWriteBuffer++;

        *pcWriteBuffer = 0x00;
    }
    strcpy(pcWriteBuffer, pcHeader);
    vTaskList(pcWriteBuffer + strlen(pcHeader));

    return pdFALSE;
}

#if(configINCLUDE_QUERY_HEAP_COMMAND == 1)

static BaseType_t prvQueryHeapCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
    (void) pcCommandString;
    (void) xWriteBufferLen;
    configASSERT(pcWriteBuffer);

    sprintf(pcWriteBuffer, "Current free heap %d bytes, minimum ever free heap %d bytes\r\n",
            (int) xPortGetFreeHeapSize(), (int) xPortGetMinimumEverFreeHeapSize());

    return pdFALSE;
}

#endif

#if(configGENERATE_RUN_TIME_STATS == 1)

static BaseType_t prvRunTimeStatsCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
    const char *const pcHeader = "  Abs Time      % Time\r\n****************************************\r\n";
    BaseType_t xSpacePadding;

    (void) pcCommandString;
    (void) xWriteBufferLen;
    configASSERT(pcWriteBuffer);

    strcpy(pcWriteBuffer, "Task");
    pcWriteBuffer += strlen(pcWriteBuffer);

    for (xSpacePadding = strlen("Task"); xSpacePadding < (configMAX_TASK_NAME_LEN - 3); xSpacePadding++)
    {
        *pcWriteBuffer = ' ';
        pcWriteBuffer++;

        *pcWriteBuffer = 0x00;
    }

    strcpy(pcWriteBuffer, pcHeader);
    vTaskGetRunTimeStats(pcWriteBuffer + strlen(pcHeader));

    return pdFALSE;
}

#endif

static BaseType_t prvThreeParameterEchoCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
    const char *pcParameter;
    BaseType_t xParameterStringLength, xReturn;
    static UBaseType_t uxParameterNumber = 0;

    (void) pcCommandString;
    (void) xWriteBufferLen;
    configASSERT(pcWriteBuffer);

    if (uxParameterNumber == 0)
    {
        sprintf(pcWriteBuffer, "The three parameters were:\r\n");

        uxParameterNumber = 1U;

        xReturn = pdPASS;
    }
    else
    {
        pcParameter = FreeRTOS_CLIGetParameter
                (
                        pcCommandString,
                        uxParameterNumber,
                        &xParameterStringLength
                );

        configASSERT(pcParameter);

        memset(pcWriteBuffer, 0x00, xWriteBufferLen);
        sprintf(pcWriteBuffer, "%d: ", (int) uxParameterNumber);
        strncat(pcWriteBuffer, pcParameter, (size_t) xParameterStringLength);
        strcat(pcWriteBuffer, "\r\n");

        if (uxParameterNumber == 3U)
        {
            xReturn = pdFALSE;
            uxParameterNumber = 0;
        }
        else
        {
            xReturn = pdTRUE;
            uxParameterNumber++;
        }
    }

    return xReturn;
}

static BaseType_t prvParameterEchoCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
    const char *pcParameter;
    BaseType_t xParameterStringLength, xReturn;
    static UBaseType_t uxParameterNumber = 0;

    (void) pcCommandString;
    (void) xWriteBufferLen;
    configASSERT(pcWriteBuffer);

    if (uxParameterNumber == 0)
    {
        sprintf(pcWriteBuffer, "The parameters were:\r\n");

        uxParameterNumber = 1U;
        xReturn = pdPASS;
    }
    else
    {
        pcParameter = FreeRTOS_CLIGetParameter
                (
                        pcCommandString,
                        uxParameterNumber,
                        &xParameterStringLength
                );

        if (pcParameter != NULL)
        {
            memset(pcWriteBuffer, 0x00, xWriteBufferLen);
            sprintf(pcWriteBuffer, "%d: ", (int) uxParameterNumber);
            strncat(pcWriteBuffer, (char *) pcParameter, (size_t) xParameterStringLength);
            strcat(pcWriteBuffer, "\r\n");

            xReturn = pdTRUE;
            uxParameterNumber++;
        }
        else
        {
            pcWriteBuffer[0] = 0x00;
            xReturn = pdFALSE;
            uxParameterNumber = 0;
        }
    }

    return xReturn;
}
