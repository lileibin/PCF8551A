/*******************************************************************************
*                              PCF8551 Drivers
*
* File      	: PCF8551.h
* Version   	: V1.00
* By        	: 
*
* For       	: PCF8551A
*
* Description : ����stm32оƬ��ƽ̨
*
* Date        : 2017.12.05
*******************************************************************************/
#ifndef   __PCF8551_H__
#define   __PCF8551_H__

#include "config.h"
#include "string.h"

//****************************************************************************************************

#define DAT_O     LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6,LL_GPIO_MODE_OUTPUT)    	//�����߷���
#define DAT_I     LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6,LL_GPIO_MODE_INPUT)
#define DAT_H     LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_6)    										//���������
#define DAT_L     LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6)
#define DAT_D     HAL_GPIO_ReadPin(GPIOA,LL_GPIO_PIN_6)															//����������

#define CLK_O     LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5,LL_GPIO_MODE_OUTPUT)    	//ʱ���߷���
//#define CLK_I     LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5,LL_GPIO_MODE_INPUT)
#define CLK_H     LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5)												//ʱ�������
#define CLK_L     LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5)
//***********************************
#define DAT2_O     LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_2,LL_GPIO_MODE_OUTPUT)    	//�����߷���
#define DAT2_I     LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_2,LL_GPIO_MODE_INPUT)
#define DAT2_H     LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2)    										//���������
#define DAT2_L     LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_2)
#define DAT2_D     HAL_GPIO_ReadPin(GPIOB,LL_GPIO_PIN_2)														//����������

#define CLK2_O     LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7,LL_GPIO_MODE_OUTPUT)    	//ʱ���߷���
//#define CLK2_I   LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7,LL_GPIO_MODE_INPUT)
#define CLK2_H     LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_7)												//ʱ�������
#define CLK2_L     LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_7)

//****************************************************************************************************

unsigned char ISendStr(unsigned char sla, unsigned char rla,unsigned char *s, unsigned char no);
unsigned char ISendStr2(unsigned char sla, unsigned char rla,unsigned char *s, unsigned char no);

#endif
