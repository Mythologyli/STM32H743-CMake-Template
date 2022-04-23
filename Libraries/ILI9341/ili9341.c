#include "main.h"

uint8_t SPI2_BasicReadWrite(uint8_t byte)
{
    LL_SPI_Enable(SPI2);
    LL_SPI_StartMasterTransfer(SPI2);

    while(!LL_SPI_IsActiveFlag_TXC(SPI2));
    LL_SPI_TransmitData8(SPI2, byte);

    while(!LL_SPI_IsActiveFlag_RXP(SPI2));
    return LL_SPI_ReceiveData8(SPI2);
}

uint8_t SPI2_ReadWrite8Bits(uint8_t TxData)
{
    return SPI2_BasicReadWrite(TxData);
}

void SPI2_ReadWriteBytes(uint8_t *pTxData, uint8_t *pRxData, uint32_t Count)
{
    for (uint32_t i = 0; i < Count; i++)
    {
        pRxData[i] = SPI2_BasicReadWrite(pTxData[i]);
    }
}

void SPI2_Write8Bits(uint8_t Data)
{
    SPI2_BasicReadWrite(Data);
}

void SPI2_Write16Bits(uint16_t Data)
{
    uint8_t temp[2];
    temp[0] = Data >> 8;
    temp[1] = Data;

    SPI2_BasicReadWrite(temp[0]);
    SPI2_BasicReadWrite(temp[1]);
}

void SPI2_Write32Bits(uint32_t Data)
{
    uint8_t temp[4];
    temp[0] = Data >> 24;
    temp[1] = Data >> 16;
    temp[2] = Data >> 8;
    temp[3] = Data;

    SPI2_BasicReadWrite(temp[0]);
    SPI2_BasicReadWrite(temp[1]);
    SPI2_BasicReadWrite(temp[2]);
    SPI2_BasicReadWrite(temp[3]);
}

void SPI2_WriteBytes(uint8_t *pData, uint32_t Count)
{
    for (uint32_t i = 0; i < Count; i++)
    {
        SPI2_BasicReadWrite(pData[i]);
    }
}

uint8_t SPI2_Read8Bits(void)
{
    return SPI2_BasicReadWrite(0);
}

void SPI2_ReadBytes(uint8_t *pData, uint32_t Count)
{
    for (uint32_t i = 0; i < Count; i++)
    {
        pData[i] = SPI2_BasicReadWrite(0);
    }
}

void ILI9341_SendCmd(uint8_t cmd)
{
    ILI9341_Cmd_Mode_On;

    SPI2_Write8Bits(cmd);
}

void ILI9341_SendData8Bits(uint8_t data)
{
    ILI9341_Data_Mode_On;

    SPI2_Write8Bits(data);
}

void ILI9341_SendData16Bits(uint16_t data)
{
    ILI9341_Data_Mode_On;

    SPI2_Write16Bits(data);
}

void ILI9341_SendData32Bits(uint32_t data)
{
    ILI9341_Data_Mode_On;

    SPI2_Write32Bits(data);
}

void ILI9341_SendDataBytes(uint8_t *pData, uint32_t Count)
{
    ILI9341_Data_Mode_On;

    SPI2_WriteBytes(pData, Count);
}

void ILI9341_SendCmdData8Bits(uint8_t cmd, uint8_t data)
{
    ILI9341_SendCmd(cmd);
    ILI9341_SendData8Bits(data);
}

void ILI9341_SendCmdData16Bits(uint8_t cmd, uint16_t data)
{
    ILI9341_SendCmd(cmd);
    ILI9341_SendData16Bits(data);
}

void ILI9341_SendCmdData32Bits(uint8_t cmd, uint32_t data)
{
    ILI9341_SendCmd(cmd);
    ILI9341_SendData32Bits(data);
}

void ILI9341_SendCmdDataBytes(uint8_t cmd, uint8_t *pData, uint32_t Count)
{
    ILI9341_SendCmd(cmd);
    ILI9341_SendDataBytes(pData, Count);
}

void ILI9341_Init(void)
{
    ILI9341_Stop_Send;
    ILI9341_Data_Mode_On;
    ILI9341_BLK_On;

    ILI9341_Start_Send;

    ILI9341_SendCmd(ILI9341_CMD_SWRESET);
    HAL_Delay(50);

    uint8_t pwctrlb_param[3] = {0x00, 0xd9, 0x30};
    ILI9341_SendCmdDataBytes(ILI9341_CMD_PWCTRLB, pwctrlb_param, 3);

    ILI9341_SendCmdData32Bits(ILI9341_CMD_PWOSCTRL, 0x64031281);

    uint8_t dtctrla_param[3] = {0x85, 0x10, 0x78};
    ILI9341_SendCmdDataBytes(ILI9341_CMD_DTCTRLA, dtctrla_param, 3);

    uint8_t pwctrla_param[5] = {0x39, 0x2c, 0x00, 0x34, 0x02};
    ILI9341_SendCmdDataBytes(ILI9341_CMD_PWCTRLA, pwctrla_param, 5);

    ILI9341_SendCmdData8Bits(ILI9341_CMD_PRCRTL, 0x20);

    ILI9341_SendCmdData16Bits(ILI9341_CMD_DTCTRLB, 0x0000);

    ILI9341_SendCmdData8Bits(ILI9341_CMD_PWCTRL1, 0x21);

    ILI9341_SendCmdData8Bits(ILI9341_CMD_PWCTRL2, 0x12);

    ILI9341_SendCmdData16Bits(ILI9341_CMD_VMCTRL1, 0x323c);

    ILI9341_SendCmdData8Bits(ILI9341_CMD_VMCTRL2, 0xc1);

    ILI9341_SendCmdData8Bits(ILI9341_CMD_MADCTL, ILI9341_CMD_MADCTL_PARAM);

    ILI9341_SendCmdData8Bits(ILI9341_CMD_PIXSET, 0x55);

    ILI9341_SendCmdData16Bits(ILI9341_CMD_FRMCTR1, 0x0018);

    ILI9341_SendCmdData16Bits(ILI9341_CMD_DISCTRL, 0x0aa2);

    ILI9341_SendCmdData8Bits(ILI9341_CMD_EN3G, 0x00);

    ILI9341_SendCmdData8Bits(ILI9341_CMD_GAMSET, 0x01);

    uint8_t pgamctrl_param[15] = {0x0f, 0x20, 0x1e, 0x09, 0x12, 0x0b, 0x50, 0xba, 0x44, 0x09, 0x14, 0x05, 0x23, 0x21,
                                  0x00};
    ILI9341_SendCmdDataBytes(ILI9341_CMD_PGAMCTRL, pgamctrl_param, 15);

    uint8_t ngamctrl_param[15] = {0x00, 0x19, 0x19, 0x00, 0x12, 0x07, 0x2d, 0x28, 0x3f, 0x02, 0x0a, 0x08, 0x25, 0x2d,
                                  0x0f};
    ILI9341_SendCmdDataBytes(ILI9341_CMD_NGAMCTRL, ngamctrl_param, 15);

    ILI9341_SendCmd(ILI9341_CMD_SLPOUT);

    ILI9341_Disp_On;

    ILI9341_SetWin(0, 0, ILI9341_WIDTH, ILI9341_HEIGHT);
}

void ILI9341_SetWin(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    ILI9341_SendCmdData32Bits(ILI9341_CMD_CASET, (x1 << 16) | x2);
    ILI9341_SendCmdData32Bits(ILI9341_CMD_PASET, (y1 << 16) | y2);
}
