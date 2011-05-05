/*
 * vs1003.c
 *
 *  Created on: 25-04-2011
 *      Author: Przemek
 */
#include "vs1003.h"

void VS1003_GPIO_conf(){
 	GPIO_InitTypeDef GPIO_InitStructure;

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);

  	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE, ENABLE);

  	// SPI2 : SCK and MOSI
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin = CS_PIN;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(CS_PORT, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin = DREQ_PIN;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  	GPIO_Init(DREQ_PORT, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin = XDCS_PIN;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(XDCS_PORT, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin = XRESET_PIN;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(XRESET_PORT, &GPIO_InitStructure);

}

void VS1003_SPI_conf(){
	SPI_InitTypeDef   SPI_InitStructure;

	// Konfiguracja SPI2
  	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

  	// Narazie dla wyslania (SI rising edge)
  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;


  	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

  	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
  	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  	SPI_InitStructure.SPI_CRCPolynomial = 7;
  	SPI_Init(SPI2, &SPI_InitStructure);

  	// Wlacz NSS
  	//SPI_SSOutputCmd(SPI2, ENABLE);

  	// Wlacz SPI2
  	SPI_Cmd(SPI2, ENABLE);
}

uint8_t SPIPutChar(uint8_t outB){
	  /* Wait if TXE cleared, Tx FIFO is full. */
	   while ((SPI2->SR & TXE) == 0);
	   SPI2->DR = outB;
	   /* Wait if RNE cleared, Rx FIFO is empty. */
	   while ((SPI2->SR & RXNE) == 0);
	   return SPI_I2S_ReceiveData(SPI2);
}

void Delay(uint32_t nTime)
{
	unsigned int i;
	unsigned long j;
	for(i = nTime;i > 0;i--)
		for(j = 1000;j > 0;j--);
}

void ControlReset(uint8_t State){
	GPIO_WriteBit(XRESET_PORT,XRESET_PIN,!State);
}

void SCI_ChipSelect(uint8_t State){
	GPIO_WriteBit(CS_PORT,CS_PIN,!State);
}

void SDI_ChipSelect(uint8_t State){
	GPIO_WriteBit(XDCS_PORT,XDCS_PIN,!State);
}

void VS1003_SineTest(){
	ControlReset(SET);
	ResetChip();
	Delay(1000);
	SPIPutChar(0xff);

	SCI_ChipSelect(RESET);
	SDI_ChipSelect(RESET);
	ControlReset(RESET);

	//ResetChip();
	Delay(500);

	WriteRegister(SPI_MODE,0x08,0x20);//进入vs1003的测试模式
	Delay(500);

	while(GPIO_ReadInputDataBit(DREQ_PORT,DREQ_PIN) == 0);

	SDI_ChipSelect(SET);
	SPIPutChar(0x53);
	SPIPutChar(0xef);
	SPIPutChar(0x6e);
	SPIPutChar(0x24);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	SPIPutChar(0x00);
	Delay(1000);
	SDI_ChipSelect(RESET);

}

void WriteRegister(uint8_t addressbyte, uint8_t highbyte, uint8_t lowbyte)
{
	SDI_ChipSelect(RESET);
	while(GPIO_ReadInputDataBit(DREQ_PORT,DREQ_PIN) == 0);
	SCI_ChipSelect(SET);
	SPIPutChar(VS_WRITE_COMMAND);
	SPIPutChar(addressbyte);
	SPIPutChar(highbyte);
	SPIPutChar(lowbyte);
	SCI_ChipSelect(RESET);
}

void ResetChip(){
	ControlReset(SET);
	Delay(100);
	SPIPutChar(0xff);
	SCI_ChipSelect(RESET);
	SDI_ChipSelect(RESET);
	ControlReset(RESET);
	Delay(100);

	while(GPIO_ReadInputDataBit(DREQ_PORT,DREQ_PIN) == 0);
	Delay(100);
}

void VS1003_Start(){
	ControlReset(SET);
	Delay(1000);
	SPIPutChar(0xFF);
	SCI_ChipSelect(RESET);
	SDI_ChipSelect(RESET);
	ControlReset(RESET);
	Delay(1000);

	while(GPIO_ReadInputDataBit(DREQ_PORT,DREQ_PIN) == 0);

	WriteRegister(SPI_MODE,0x08,0x00);
	WriteRegister(SPI_CLOCKF,0x98,0x00);
	WriteRegister(SPI_AUDATA,0xAC,0x45);
	WriteRegister(SPI_BASS,0x08,0x00);
	WriteRegister(SPI_VOL,0x0F,0x0F);
	WriteRegister(0x0b,0x00,0x00);

	while(GPIO_ReadInputDataBit(DREQ_PORT,DREQ_PIN) == 0);
}

void VS1003_SendMusicBytes(uint8_t* music,int quantity){
	int i,j,k,m;

	j = quantity / 32;
	m = 0;

	SDI_ChipSelect(SET);
	for ( i = 0; i <= j; i++ )
	{
		while(GPIO_ReadInputDataBit(DREQ_PORT,DREQ_PIN) == 0);
		for (k=0; k < 32; k++)
		{
		SPIPutChar(music[m]);
		m++;
		}
	}
	//while(GPIO_ReadInputDataBit(DREQ_PORT,DREQ_PIN) == 0);
	while (m < quantity)
	{
		SPIPutChar(music[m]);
		m++;
	}
	SDI_ChipSelect(RESET);
}

