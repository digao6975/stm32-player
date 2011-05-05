#include "radio.h"

static uint8_t out_buf[] = {0XF0,0X2C,0XD0,0X12,0X40};

void init_i2c(void) {
	I2C_InitTypeDef I2C_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // SCL,SDA
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	I2C_SoftwareResetCmd(I2C2, ENABLE);
	I2C_ITConfig(I2C2,I2C_IT_ERR,ENABLE);
	I2C_StructInit(&I2C_InitStruct);
	I2C_DeInit(I2C2);
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C2, &I2C_InitStruct);
	I2C_Cmd(I2C2, ENABLE);
}

void init_NVIC_out() {
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init ( &NVIC_InitStructure );
}

void init_DMA_out() {
	DMA_InitTypeDef DMA_InitStruct;

	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE );

	//Inicjalizuje kanal 4 do zapisu danych
	DMA_DeInit(DMA1_Channel4);
	DMA_StructInit( &DMA_InitStruct );
	DMA_InitStruct.DMA_PeripheralBaseAddr = (unsigned int)&(I2C2 -> DR);
	DMA_InitStruct.DMA_BufferSize = 4;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_MemoryBaseAddr = (int)&(out_buf[1]);
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA1_Channel4, &DMA_InitStruct);
}

void init_DMA_in() {
	DMA_InitTypeDef DMA_InitStruct;

	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE );

	DMA_DeInit(DMA1_Channel5);
	DMA_StructInit( &DMA_InitStruct );
	DMA_InitStruct.DMA_PeripheralBaseAddr = (unsigned int)&(I2C2 -> DR);
	DMA_InitStruct.DMA_BufferSize = 4;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_MemoryBaseAddr = (int)out_buf;
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_Init(DMA1_Channel5, &DMA_InitStruct);
	DMA_Cmd( DMA1_Channel5, ENABLE );
}

void sendData() {
	while(I2C_GetFlagStatus( I2C2, I2C_FLAG_BUSY ));
	I2C_GenerateSTART( I2C2, ENABLE );
	while( !I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) );
	I2C_Send7bitAddress( I2C2, FM_WRITE_ADDRESS, I2C_Direction_Transmitter );
	while( !I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) );
	I2C_SendData( I2C2, out_buf[0] );
	while( !I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) );

	/* Enable the DMA Channel4 Transfer Complete IT */
	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC | DMA_IT_TE, ENABLE);
	I2C_DMACmd(I2C2, ENABLE);
	DMA_Cmd( DMA1_Channel4, ENABLE );

}
