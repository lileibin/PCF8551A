/*******************************************************************************
*                             LED Middle Driver for PCF8551
*
* File      	: LEDMiddle.c
* Version   	: V1.00
* By        	:
*
* For       	: PCF8551A
*
* Description :
*
* Date        : 2017.12.07
*******************************************************************************/
#include "LEDMiddle.h"


unsigned char Display_Buffer1[24];	//显示缓存1
unsigned char Display_Buffer2[24];	//显示缓存2

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/

void Pcf8551_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//定义GPIO初始化结构体

	/* Enable GPIO clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* Configure 1SCL pin as output */
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Configure 1SDA pin as output */
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Configure 2SCL pin as output */
	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Configure 2SCL pin as output */
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
void Pcf8551Init(void)
{
	memset(Display_Buffer1, 0, sizeof(Display_Buffer1));	//确保显存数组为空
	memset(Display_Buffer2, 0, sizeof(Display_Buffer2));

	Display_Buffer1[0] = PCF8551A_RET;
	Display_Buffer1[1] = PCF8551A_CTR;
	Display_Buffer1[2] = PCF8551A_CTR1;
	Display_Buffer1[3] = PCF8551A_CTR2;

	ISendStr(PCF8551A_ADD_W, PCF8551A_REG_BASE, Display_Buffer1, 24);
	ISendStr2(PCF8551A_ADD_W, PCF8551A_REG_BASE, Display_Buffer1, 24);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
void Pcf8551Refresh(void)
{
	ISendStr(PCF8551A_ADD_W, PCF8551A_DATA_BASE, Display_Buffer1, 20);
	ISendStr2(PCF8551A_ADD_W, PCF8551A_DATA_BASE, Display_Buffer2, 20);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/

void Pcf8551_All_ON(void)
{
	memset(Display_Buffer1, 0xFF, sizeof(Display_Buffer1));
	memset(Display_Buffer2, 0xFF, sizeof(Display_Buffer2));
	Pcf8551Refresh();
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/

void Pcf8551_All_OFF(void)
{
	memset(Display_Buffer1, 0, sizeof(Display_Buffer1));
	memset(Display_Buffer2, 0, sizeof(Display_Buffer2));

	Pcf8551Refresh();
}

//******************************************以下为单个7断码管显示，一级驱动***********************************************************

static void ShowSpeedInt1(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[3] |= 0x02;
			  Display_Buffer2[8] |= 0x02;
			  Display_Buffer2[13] |= 0x02;
			  Display_Buffer2[18] |= 0x02;
			  Display_Buffer2[13] |= 0x01;
			  Display_Buffer2[3] |= 0x01;
			  Display_Buffer2[8] &= 0xFE;
	}
		break;

	case 1:
	{
			  Display_Buffer2[3] &= 0xFD;
			  Display_Buffer2[8] |= 0x02;
			  Display_Buffer2[13] |= 0x02;
			  Display_Buffer2[18] &= 0xFD;
			  Display_Buffer2[13] &= 0xFE;
			  Display_Buffer2[3] &= 0xFE;
			  Display_Buffer2[8] &= 0xFE;
	}
		break;

	case 2:
	{
			  Display_Buffer2[3] |= 0x02;
			  Display_Buffer2[8] |= 0x02;
			  Display_Buffer2[13] &= 0xFD;
			  Display_Buffer2[18] |= 0x02;
			  Display_Buffer2[13] |= 0x01;
			  Display_Buffer2[3] &= 0xFE;
			  Display_Buffer2[8] |= 0x01;
	}
		break;

	case 3:
	{
			  Display_Buffer2[3] |= 0x02;
			  Display_Buffer2[8] |= 0x02;
			  Display_Buffer2[13] |= 0x02;
			  Display_Buffer2[18] |= 0x02;
			  Display_Buffer2[13] &= 0xFE;
			  Display_Buffer2[3] &= 0xFE;
			  Display_Buffer2[8] |= 0x01;
	}
		break;

	case 4:
	{
			  Display_Buffer2[3] &= 0xFD;
			  Display_Buffer2[8] |= 0x02;
			  Display_Buffer2[13] |= 0x02;
			  Display_Buffer2[18] &= 0xFD;
			  Display_Buffer2[13] &= 0xFE;
			  Display_Buffer2[3] |= 0x01;
			  Display_Buffer2[8] |= 0x01;
	}
		break;

	case 5:
	{
			  Display_Buffer2[3] |= 0x02;
			  Display_Buffer2[8] &= 0xFD;
			  Display_Buffer2[13] |= 0x02;
			  Display_Buffer2[18] |= 0x02;
			  Display_Buffer2[13] &= 0xFE;
			  Display_Buffer2[3] |= 0x01;
			  Display_Buffer2[8] |= 0x01;
	}
		break;

	case 6:
	{
			  Display_Buffer2[3] |= 0x02;
			  Display_Buffer2[8] &= 0xFD;
			  Display_Buffer2[13] |= 0x02;
			  Display_Buffer2[18] |= 0x02;
			  Display_Buffer2[13] |= 0x01;
			  Display_Buffer2[3] |= 0x01;
			  Display_Buffer2[8] |= 0x01;
	}
		break;

	case 7:
	{
			  Display_Buffer2[3] |= 0x02;
			  Display_Buffer2[8] |= 0x02;
			  Display_Buffer2[13] |= 0x02;
			  Display_Buffer2[18] &= 0xFD;
			  Display_Buffer2[13] &= 0xFE;
			  Display_Buffer2[3] &= 0xFE;
			  Display_Buffer2[8] &= 0xFE;
	}

		break;

	case 8:
	{
			  Display_Buffer2[3] |= 0x02;
			  Display_Buffer2[8] |= 0x02;
			  Display_Buffer2[13] |= 0x02;
			  Display_Buffer2[18] |= 0x02;
			  Display_Buffer2[13] |= 0x01;
			  Display_Buffer2[3] |= 0x01;
			  Display_Buffer2[8] |= 0x01;
	}
		break;

	case 9:
	{
			  Display_Buffer2[3] |= 0x02;
			  Display_Buffer2[8] |= 0x02;
			  Display_Buffer2[13] |= 0x02;
			  Display_Buffer2[18] |= 0x02;
			  Display_Buffer2[13] &= 0xFE;
			  Display_Buffer2[3] |= 0x01;
			  Display_Buffer2[8] |= 0x01;
	}
		break;

	default:
	{
			   Display_Buffer2[3] &= 0xFD;
			   Display_Buffer2[8] &= 0xFD;
			   Display_Buffer2[13] &= 0xFD;
			   Display_Buffer2[18] &= 0xFD;
			   Display_Buffer2[13] &= 0xFE;
			   Display_Buffer2[3] &= 0xFE;
			   Display_Buffer2[8] &= 0xFE;
	}
		break;
	}
}

static void ShowSpeedInt2(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[3] |= 0x08;
			  Display_Buffer2[8] |= 0x08;
			  Display_Buffer2[13] |= 0x08;
			  Display_Buffer2[18] |= 0x08;
			  Display_Buffer2[13] |= 0x04;
			  Display_Buffer2[3] |= 0x04;
			  Display_Buffer2[8] &= 0xFB;
	}
		break;

	case 1:
	{
			  Display_Buffer2[3] &= 0xF7;
			  Display_Buffer2[8] |= 0x08;
			  Display_Buffer2[13] |= 0x08;
			  Display_Buffer2[18] &= 0xF7;
			  Display_Buffer2[13] &= 0xFB;
			  Display_Buffer2[3] &= 0xFB;
			  Display_Buffer2[8] &= 0xFB;
	}
		break;

	case 2:
	{
			  Display_Buffer2[3] |= 0x08;
			  Display_Buffer2[8] |= 0x08;
			  Display_Buffer2[13] &= 0xF7;
			  Display_Buffer2[18] |= 0x08;
			  Display_Buffer2[13] |= 0x04;
			  Display_Buffer2[3] &= 0xFB;
			  Display_Buffer2[8] |= 0x04;
	}
		break;

	case 3:
	{
			  Display_Buffer2[3] |= 0x08;
			  Display_Buffer2[8] |= 0x08;
			  Display_Buffer2[13] |= 0x08;
			  Display_Buffer2[18] |= 0x08;
			  Display_Buffer2[13] &= 0xFB;
			  Display_Buffer2[3] &= 0xFB;
			  Display_Buffer2[8] |= 0x04;
	}
		break;

	case 4:
	{
			  Display_Buffer2[3] &= 0xF7;
			  Display_Buffer2[8] |= 0x08;
			  Display_Buffer2[13] |= 0x08;
			  Display_Buffer2[18] &= 0xF7;
			  Display_Buffer2[13] &= 0xFB;
			  Display_Buffer2[3] |= 0x04;
			  Display_Buffer2[8] |= 0x04;
	}
		break;

	case 5:
	{
			  Display_Buffer2[3] |= 0x08;
			  Display_Buffer2[8] &= 0xF7;
			  Display_Buffer2[13] |= 0x08;
			  Display_Buffer2[18] |= 0x08;
			  Display_Buffer2[13] &= 0xFB;
			  Display_Buffer2[3] |= 0x04;
			  Display_Buffer2[8] |= 0x04;
	}
		break;

	case 6:
	{
			  Display_Buffer2[3] |= 0x08;
			  Display_Buffer2[8] &= 0xF7;
			  Display_Buffer2[13] |= 0x08;
			  Display_Buffer2[18] |= 0x08;
			  Display_Buffer2[13] |= 0x04;
			  Display_Buffer2[3] |= 0x04;
			  Display_Buffer2[8] |= 0x04;
	}
		break;

	case 7:
	{
			  Display_Buffer2[3] |= 0x08;
			  Display_Buffer2[8] |= 0x08;
			  Display_Buffer2[13] |= 0x08;
			  Display_Buffer2[18] &= 0xF7;
			  Display_Buffer2[13] &= 0xFB;
			  Display_Buffer2[3] &= 0xFB;
			  Display_Buffer2[8] &= 0xFB;
	}
		break;

	case 8:
	{
			  Display_Buffer2[3] |= 0x08;
			  Display_Buffer2[8] |= 0x08;
			  Display_Buffer2[13] |= 0x08;
			  Display_Buffer2[18] |= 0x08;
			  Display_Buffer2[13] |= 0x04;
			  Display_Buffer2[3] |= 0x04;
			  Display_Buffer2[8] |= 0x04;
	}
		break;

	case 9:
	{
			  Display_Buffer2[3] |= 0x08;
			  Display_Buffer2[8] |= 0x08;
			  Display_Buffer2[13] |= 0x08;
			  Display_Buffer2[18] |= 0x08;
			  Display_Buffer2[13] &= 0xFB;
			  Display_Buffer2[3] |= 0x04;
			  Display_Buffer2[8] |= 0x04;
	}
		break;

	default:
	{
			   Display_Buffer2[3] &= 0xF7;
			   Display_Buffer2[8] &= 0xF7;
			   Display_Buffer2[13] &= 0xF7;
			   Display_Buffer2[18] &= 0xF7;
			   Display_Buffer2[13] &= 0xFB;
			   Display_Buffer2[3] &= 0xFB;
			   Display_Buffer2[8] &= 0xFB;
	}
		break;

	}

}


static void ShowSpeedInt3(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[3] |= 0x20;
			  Display_Buffer2[8] |= 0x20;
			  Display_Buffer2[13] |= 0x20;
			  Display_Buffer2[18] |= 0x20;
			  Display_Buffer2[13] |= 0x10;
			  Display_Buffer2[3] |= 0x10;
			  Display_Buffer2[8] &= 0xEF;
	}
		break;

	case 1:
	{
			  Display_Buffer2[3] &= 0xDF;
			  Display_Buffer2[8] |= 0x20;
			  Display_Buffer2[13] |= 0x20;
			  Display_Buffer2[18] &= 0xDF;
			  Display_Buffer2[13] &= 0xEF;
			  Display_Buffer2[3] &= 0xEF;
			  Display_Buffer2[8] &= 0xEF;
	}
		break;

	case 2:
	{
			  Display_Buffer2[3] |= 0x20;
			  Display_Buffer2[8] |= 0x20;
			  Display_Buffer2[13] &= 0xDF;
			  Display_Buffer2[18] |= 0x20;
			  Display_Buffer2[13] |= 0x10;
			  Display_Buffer2[3] &= 0xEF;
			  Display_Buffer2[8] |= 0x10;
	}
		break;

	case 3:
	{
			  Display_Buffer2[3] |= 0x20;
			  Display_Buffer2[8] |= 0x20;
			  Display_Buffer2[13] |= 0x20;
			  Display_Buffer2[18] |= 0x20;
			  Display_Buffer2[13] &= 0xEF;
			  Display_Buffer2[3] &= 0xEF;
			  Display_Buffer2[8] |= 0x10;
	}
		break;

	case 4:
	{
			  Display_Buffer2[3] &= 0xDF;
			  Display_Buffer2[8] |= 0x20;
			  Display_Buffer2[13] |= 0x20;
			  Display_Buffer2[18] &= 0xDF;
			  Display_Buffer2[13] &= 0xEF;
			  Display_Buffer2[3] |= 0x10;
			  Display_Buffer2[8] |= 0x10;
	}
		break;

	case 5:
	{
			  Display_Buffer2[3] |= 0x20;
			  Display_Buffer2[8] &= 0xDF;
			  Display_Buffer2[13] |= 0x20;
			  Display_Buffer2[18] |= 0x20;
			  Display_Buffer2[13] &= 0xEF;
			  Display_Buffer2[3] |= 0x10;
			  Display_Buffer2[8] |= 0x10;
	}
		break;

	case 6:
	{
			  Display_Buffer2[3] |= 0x20;
			  Display_Buffer2[8] &= 0xDF;
			  Display_Buffer2[13] |= 0x20;
			  Display_Buffer2[18] |= 0x20;
			  Display_Buffer2[13] |= 0x10;
			  Display_Buffer2[3] |= 0x10;
			  Display_Buffer2[8] |= 0x10;
	}
		break;

	case 7:
	{
			  Display_Buffer2[3] |= 0x20;
			  Display_Buffer2[8] |= 0x20;
			  Display_Buffer2[13] |= 0x20;
			  Display_Buffer2[18] &= 0xDF;
			  Display_Buffer2[13] &= 0xEF;
			  Display_Buffer2[3] &= 0xEF;
			  Display_Buffer2[8] &= 0xEF;
	}
		break;

	case 8:
	{
			  Display_Buffer2[3] |= 0x20;
			  Display_Buffer2[8] |= 0x20;
			  Display_Buffer2[13] |= 0x20;
			  Display_Buffer2[18] |= 0x20;
			  Display_Buffer2[13] |= 0x10;
			  Display_Buffer2[3] |= 0x10;
			  Display_Buffer2[8] |= 0x10;
	}
		break;

	case 9:
	{
			  Display_Buffer2[3] |= 0x20;
			  Display_Buffer2[8] |= 0x20;
			  Display_Buffer2[13] |= 0x20;
			  Display_Buffer2[18] |= 0x20;
			  Display_Buffer2[13] &= 0xEF;
			  Display_Buffer2[3] |= 0x10;
			  Display_Buffer2[8] |= 0x10;
	}
		break;

	default:
	{
			   Display_Buffer2[3] &= 0xDF;
			   Display_Buffer2[8] &= 0xDF;
			   Display_Buffer2[13] &= 0xDF;
			   Display_Buffer2[18] &= 0xDF;
			   Display_Buffer2[13] &= 0xEF;
			   Display_Buffer2[3] &= 0xEF;
			   Display_Buffer2[8] &= 0xEF;
	}
		break;

	}

}


static void ShowSpeedInt4(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[3] |= 0x80;
			  Display_Buffer2[8] |= 0x80;
			  Display_Buffer2[13] |= 0x80;
			  Display_Buffer2[18] |= 0x80;
			  Display_Buffer2[13] |= 0x40;
			  Display_Buffer2[3] |= 0x40;
			  Display_Buffer2[8] &= 0xBF;
	}
		break;

	case 1:
	{
			  Display_Buffer2[3] &= 0x7F;
			  Display_Buffer2[8] |= 0x80;
			  Display_Buffer2[13] |= 0x80;
			  Display_Buffer2[18] &= 0x7F;
			  Display_Buffer2[13] &= 0xBF;
			  Display_Buffer2[3] &= 0xBF;
			  Display_Buffer2[8] &= 0xBF;
	}
		break;

	case 2:
	{
			  Display_Buffer2[3] |= 0x80;
			  Display_Buffer2[8] |= 0x80;
			  Display_Buffer2[13] &= 0x7F;
			  Display_Buffer2[18] |= 0x80;
			  Display_Buffer2[13] |= 0x40;
			  Display_Buffer2[3] &= 0xBF;
			  Display_Buffer2[8] |= 0x40;
	}
		break;

	case 3:
	{
			  Display_Buffer2[3] |= 0x80;
			  Display_Buffer2[8] |= 0x80;
			  Display_Buffer2[13] |= 0x80;
			  Display_Buffer2[18] |= 0x80;
			  Display_Buffer2[13] &= 0xBF;
			  Display_Buffer2[3] &= 0xBF;
			  Display_Buffer2[8] |= 0x40;
	}
		break;

	case 4:
	{
			  Display_Buffer2[3] &= 0x7F;
			  Display_Buffer2[8] |= 0x80;
			  Display_Buffer2[13] |= 0x80;
			  Display_Buffer2[18] &= 0x7F;
			  Display_Buffer2[13] &= 0xBF;
			  Display_Buffer2[3] |= 0x40;
			  Display_Buffer2[8] |= 0x40;
	}
		break;

	case 5:
	{
			  Display_Buffer2[3] |= 0x80;
			  Display_Buffer2[8] &= 0x7F;
			  Display_Buffer2[13] |= 0x80;
			  Display_Buffer2[18] |= 0x80;
			  Display_Buffer2[13] &= 0xBF;
			  Display_Buffer2[3] |= 0x40;
			  Display_Buffer2[8] |= 0x40;
	}
		break;

	case 6:
	{
			  Display_Buffer2[3] |= 0x80;
			  Display_Buffer2[8] &= 0x7F;
			  Display_Buffer2[13] |= 0x80;
			  Display_Buffer2[18] |= 0x80;
			  Display_Buffer2[13] |= 0x40;
			  Display_Buffer2[3] |= 0x40;
			  Display_Buffer2[8] |= 0x40;
	}
		break;

	case 7:
	{
			  Display_Buffer2[3] |= 0x80;
			  Display_Buffer2[8] |= 0x80;
			  Display_Buffer2[13] |= 0x80;
			  Display_Buffer2[18] &= 0x7F;
			  Display_Buffer2[13] &= 0xBF;
			  Display_Buffer2[3] &= 0xBF;
			  Display_Buffer2[8] &= 0xBF;
	}
		break;

	case 8:
	{
			  Display_Buffer2[3] |= 0x80;
			  Display_Buffer2[8] |= 0x80;
			  Display_Buffer2[13] |= 0x80;
			  Display_Buffer2[18] |= 0x80;
			  Display_Buffer2[13] |= 0x40;
			  Display_Buffer2[3] |= 0x40;
			  Display_Buffer2[8] |= 0x40;
	}
		break;

	case 9:
	{
			  Display_Buffer2[3] |= 0x80;
			  Display_Buffer2[8] |= 0x80;
			  Display_Buffer2[13] |= 0x80;
			  Display_Buffer2[18] |= 0x80;
			  Display_Buffer2[13] &= 0xBF;
			  Display_Buffer2[3] |= 0x40;
			  Display_Buffer2[8] |= 0x40;
	}
		break;

	default:
	{
			   Display_Buffer2[3] &= 0x7F;
			   Display_Buffer2[8] &= 0x7F;
			   Display_Buffer2[13] &= 0x7F;
			   Display_Buffer2[18] &= 0x7F;
			   Display_Buffer2[13] &= 0xBF;
			   Display_Buffer2[3] &= 0xBF;
			   Display_Buffer2[8] &= 0xBF;
	}
		break;

	}
}

static void ShowSpeedFloat1(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[4] |= 0x02;
			  Display_Buffer2[9] |= 0x02;
			  Display_Buffer2[14] |= 0x02;
			  Display_Buffer2[19] |= 0x02;
			  Display_Buffer2[14] |= 0x01;
			  Display_Buffer2[4] |= 0x01;
			  Display_Buffer2[9] &= 0xFE;
	}
		break;

	case 1:
	{
			  Display_Buffer2[4] &= 0xFD;
			  Display_Buffer2[9] |= 0x02;
			  Display_Buffer2[14] |= 0x02;
			  Display_Buffer2[19] &= 0xFD;
			  Display_Buffer2[14] &= 0xFE;
			  Display_Buffer2[4] &= 0xFE;
			  Display_Buffer2[9] &= 0xFE;
	}
		break;

	case 2:
	{
			  Display_Buffer2[4] |= 0x02;
			  Display_Buffer2[9] |= 0x02;
			  Display_Buffer2[14] &= 0xFD;
			  Display_Buffer2[19] |= 0x02;
			  Display_Buffer2[14] |= 0x01;
			  Display_Buffer2[4] &= 0xFE;
			  Display_Buffer2[9] |= 0x01;
	}
		break;

	case 3:
	{
			  Display_Buffer2[4] |= 0x02;
			  Display_Buffer2[9] |= 0x02;
			  Display_Buffer2[14] |= 0x02;
			  Display_Buffer2[19] |= 0x02;
			  Display_Buffer2[14] &= 0xFE;
			  Display_Buffer2[4] &= 0xFE;
			  Display_Buffer2[9] |= 0x01;
	}
		break;

	case 4:
	{
			  Display_Buffer2[4] &= 0xFD;
			  Display_Buffer2[9] |= 0x02;
			  Display_Buffer2[14] |= 0x02;
			  Display_Buffer2[19] &= 0xFD;
			  Display_Buffer2[14] &= 0xFE;
			  Display_Buffer2[4] |= 0x01;
			  Display_Buffer2[9] |= 0x01;
	}
		break;

	case 5:
	{
			  Display_Buffer2[4] |= 0x02;
			  Display_Buffer2[9] &= 0xFD;
			  Display_Buffer2[14] |= 0x02;
			  Display_Buffer2[19] |= 0x02;
			  Display_Buffer2[14] &= 0xFE;
			  Display_Buffer2[4] |= 0x01;
			  Display_Buffer2[9] |= 0x01;
	}
		break;

	case 6:
	{
			  Display_Buffer2[4] |= 0x02;
			  Display_Buffer2[9] &= 0xFD;
			  Display_Buffer2[14] |= 0x02;
			  Display_Buffer2[19] |= 0x02;
			  Display_Buffer2[14] |= 0x01;
			  Display_Buffer2[4] |= 0x01;
			  Display_Buffer2[9] |= 0x01;
	}
		break;

	case 7:
	{
			  Display_Buffer2[4] |= 0x02;
			  Display_Buffer2[9] |= 0x02;
			  Display_Buffer2[14] |= 0x02;
			  Display_Buffer2[19] &= 0xFD;
			  Display_Buffer2[14] &= 0xFE;
			  Display_Buffer2[4] &= 0xFE;
			  Display_Buffer2[9] &= 0xFE;
	}
		break;

	case 8:
	{
			  Display_Buffer2[4] |= 0x02;
			  Display_Buffer2[9] |= 0x02;
			  Display_Buffer2[14] |= 0x02;
			  Display_Buffer2[19] |= 0x02;
			  Display_Buffer2[14] |= 0x01;
			  Display_Buffer2[4] |= 0x01;
			  Display_Buffer2[9] |= 0x01;
	}
		break;

	case 9:
	{
			  Display_Buffer2[4] |= 0x02;
			  Display_Buffer2[9] |= 0x02;
			  Display_Buffer2[14] |= 0x02;
			  Display_Buffer2[19] |= 0x02;
			  Display_Buffer2[14] &= 0xFE;
			  Display_Buffer2[4] |= 0x01;
			  Display_Buffer2[9] |= 0x01;
	}
		break;

	default:
	{
			   Display_Buffer2[4] &= 0xFD;
			   Display_Buffer2[9] &= 0xFD;
			   Display_Buffer2[14] &= 0xFD;
			   Display_Buffer2[19] &= 0xFD;
			   Display_Buffer2[14] &= 0xFE;
			   Display_Buffer2[4] &= 0xFE;
			   Display_Buffer2[9] &= 0xFE;
	}
		break;
	}
}

static void ShowSpeedFloat2(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[4] |= 0x08;
			  Display_Buffer2[9] |= 0x08;
			  Display_Buffer2[14] |= 0x08;
			  Display_Buffer2[19] |= 0x08;
			  Display_Buffer2[14] |= 0x04;
			  Display_Buffer2[4] |= 0x04;
			  Display_Buffer2[9] &= 0xFB;
	}
		break;

	case 1:
	{
			  Display_Buffer2[4] &= 0xF7;
			  Display_Buffer2[9] |= 0x08;
			  Display_Buffer2[14] |= 0x08;
			  Display_Buffer2[19] &= 0xF7;
			  Display_Buffer2[14] &= 0xFB;
			  Display_Buffer2[4] &= 0xFB;
			  Display_Buffer2[9] &= 0xFB;
	}
		break;

	case 2:
	{
			  Display_Buffer2[4] |= 0x08;
			  Display_Buffer2[9] |= 0x08;
			  Display_Buffer2[14] &= 0xF7;
			  Display_Buffer2[19] |= 0x08;
			  Display_Buffer2[14] |= 0x04;
			  Display_Buffer2[4] &= 0xFB;
			  Display_Buffer2[9] |= 0x04;
	}
		break;

	case 3:
	{
			  Display_Buffer2[4] |= 0x08;
			  Display_Buffer2[9] |= 0x08;
			  Display_Buffer2[14] |= 0x08;
			  Display_Buffer2[19] |= 0x08;
			  Display_Buffer2[14] &= 0xFB;
			  Display_Buffer2[4] &= 0xFB;
			  Display_Buffer2[9] |= 0x04;
	}
		break;

	case 4:
	{
			  Display_Buffer2[4] &= 0xF7;
			  Display_Buffer2[9] |= 0x08;
			  Display_Buffer2[14] |= 0x08;
			  Display_Buffer2[19] &= 0xF7;
			  Display_Buffer2[14] &= 0xFB;
			  Display_Buffer2[4] |= 0x04;
			  Display_Buffer2[9] |= 0x04;
	}
		break;

	case 5:
	{
			  Display_Buffer2[4] |= 0x08;
			  Display_Buffer2[9] &= 0xF7;
			  Display_Buffer2[14] |= 0x08;
			  Display_Buffer2[19] |= 0x08;
			  Display_Buffer2[14] &= 0xFB;
			  Display_Buffer2[4] |= 0x04;
			  Display_Buffer2[9] |= 0x04;
	}
		break;

	case 6:
	{
			  Display_Buffer2[4] |= 0x08;
			  Display_Buffer2[9] &= 0xF7;
			  Display_Buffer2[14] |= 0x08;
			  Display_Buffer2[19] |= 0x08;
			  Display_Buffer2[14] |= 0x04;
			  Display_Buffer2[4] |= 0x04;
			  Display_Buffer2[9] |= 0x04;
	}
		break;

	case 7:
	{
			  Display_Buffer2[4] |= 0x08;
			  Display_Buffer2[9] |= 0x08;
			  Display_Buffer2[14] |= 0x08;
			  Display_Buffer2[19] &= 0xF7;
			  Display_Buffer2[14] &= 0xFB;
			  Display_Buffer2[4] &= 0xFB;
			  Display_Buffer2[9] &= 0xFB;
	}
		break;

	case 8:
	{
			  Display_Buffer2[4] |= 0x08;
			  Display_Buffer2[9] |= 0x08;
			  Display_Buffer2[14] |= 0x08;
			  Display_Buffer2[19] |= 0x08;
			  Display_Buffer2[14] |= 0x04;
			  Display_Buffer2[4] |= 0x04;
			  Display_Buffer2[9] |= 0x04;
	}
		break;

	case 9:
	{
			  Display_Buffer2[4] |= 0x08;
			  Display_Buffer2[9] |= 0x08;
			  Display_Buffer2[14] |= 0x08;
			  Display_Buffer2[19] |= 0x08;
			  Display_Buffer2[14] &= 0xFB;
			  Display_Buffer2[4] |= 0x04;
			  Display_Buffer2[9] |= 0x04;
	}
		break;

	default:
	{
			   Display_Buffer2[4] &= 0xF7;
			   Display_Buffer2[9] &= 0xF7;
			   Display_Buffer2[14] &= 0xF7;
			   Display_Buffer2[19] &= 0xF7;
			   Display_Buffer2[14] &= 0xFB;
			   Display_Buffer2[4] &= 0xFB;
			   Display_Buffer2[9] &= 0xFB;
	}
		break;
	}
}

static void ShowGKInt1(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[15] |= 0x08;
			  Display_Buffer2[10] |= 0x08;
			  Display_Buffer2[5] |= 0x08;
			  Display_Buffer2[0] |= 0x08;
			  Display_Buffer2[0] |= 0x04;
			  Display_Buffer2[10] |= 0x04;
			  Display_Buffer2[5] &= 0xFB;
	}
		break;

	case 1:
	{
			  Display_Buffer2[15] &= 0xF7;
			  Display_Buffer2[10] |= 0x08;
			  Display_Buffer2[5] |= 0x08;
			  Display_Buffer2[0] &= 0xF7;
			  Display_Buffer2[0] &= 0xFB;
			  Display_Buffer2[10] &= 0xFB;
			  Display_Buffer2[5] &= 0xFB;
	}
		break;

	case 2:
	{
			  Display_Buffer2[15] |= 0x08;
			  Display_Buffer2[10] |= 0x08;
			  Display_Buffer2[5] &= 0xF7;
			  Display_Buffer2[0] |= 0x08;
			  Display_Buffer2[0] |= 0x04;
			  Display_Buffer2[10] &= 0xFB;
			  Display_Buffer2[5] |= 0x04;
	}
		break;

	case 3:
	{
			  Display_Buffer2[15] |= 0x08;
			  Display_Buffer2[10] |= 0x08;
			  Display_Buffer2[5] |= 0x08;
			  Display_Buffer2[0] |= 0x08;
			  Display_Buffer2[0] &= 0xFB;
			  Display_Buffer2[10] &= 0xFB;
			  Display_Buffer2[5] |= 0x04;
	}
		break;

	case 4:
	{
			  Display_Buffer2[15] &= 0xF7;
			  Display_Buffer2[10] |= 0x08;
			  Display_Buffer2[5] |= 0x08;
			  Display_Buffer2[0] &= 0xF7;
			  Display_Buffer2[0] &= 0xFB;
			  Display_Buffer2[10] |= 0x04;
			  Display_Buffer2[5] |= 0x04;
	}
		break;

	case 5:
	{
			  Display_Buffer2[15] |= 0x08;
			  Display_Buffer2[10] &= 0xF7;
			  Display_Buffer2[5] |= 0x08;
			  Display_Buffer2[0] |= 0x08;
			  Display_Buffer2[0] &= 0xFB;
			  Display_Buffer2[10] |= 0x04;
			  Display_Buffer2[5] |= 0x04;
	}
		break;

	case 6:
	{
			  Display_Buffer2[15] |= 0x08;
			  Display_Buffer2[10] &= 0xF7;
			  Display_Buffer2[5] |= 0x08;
			  Display_Buffer2[0] |= 0x08;
			  Display_Buffer2[0] |= 0x04;
			  Display_Buffer2[10] |= 0x04;
			  Display_Buffer2[5] |= 0x04;
	}
		break;

	case 7:
	{
			  Display_Buffer2[15] |= 0x08;
			  Display_Buffer2[10] |= 0x08;
			  Display_Buffer2[5] |= 0x08;
			  Display_Buffer2[0] &= 0xF7;
			  Display_Buffer2[0] &= 0xFB;
			  Display_Buffer2[10] &= 0xFB;
			  Display_Buffer2[5] &= 0xFB;
	}
		break;

	case 8:
	{
			  Display_Buffer2[15] |= 0x08;
			  Display_Buffer2[10] |= 0x08;
			  Display_Buffer2[5] |= 0x08;
			  Display_Buffer2[0] |= 0x08;
			  Display_Buffer2[0] |= 0x04;
			  Display_Buffer2[10] |= 0x04;
			  Display_Buffer2[5] |= 0x04;
	}
		break;

	case 9:
	{
			  Display_Buffer2[15] |= 0x08;
			  Display_Buffer2[10] |= 0x08;
			  Display_Buffer2[5] |= 0x08;
			  Display_Buffer2[0] |= 0x08;
			  Display_Buffer2[0] &= 0xFB;
			  Display_Buffer2[10] |= 0x04;
			  Display_Buffer2[5] |= 0x04;
	}
		break;

	default:
	{
			   Display_Buffer2[15] &= 0xF7;
			   Display_Buffer2[10] &= 0xF7;
			   Display_Buffer2[5] &= 0xF7;
			   Display_Buffer2[0] &= 0xF7;
			   Display_Buffer2[0] &= 0xFB;
			   Display_Buffer2[10] &= 0xFB;
			   Display_Buffer2[5] &= 0xFB;
	}
		break;

	}
}

static void ShowGKInt2(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[15] |= 0x20;
			  Display_Buffer2[10] |= 0x20;
			  Display_Buffer2[5] |= 0x20;
			  Display_Buffer2[0] |= 0x20;
			  Display_Buffer2[0] |= 0x10;
			  Display_Buffer2[10] |= 0x10;
			  Display_Buffer2[5] &= 0xEF;
	}
		break;

	case 1:
	{
			  Display_Buffer2[15] &= 0xDF;
			  Display_Buffer2[10] |= 0x20;
			  Display_Buffer2[5] |= 0x20;
			  Display_Buffer2[0] &= 0xDF;
			  Display_Buffer2[0] &= 0xEF;
			  Display_Buffer2[10] &= 0xEF;
			  Display_Buffer2[5] &= 0xEF;
	}
		break;

	case 2:
	{
			  Display_Buffer2[15] |= 0x20;
			  Display_Buffer2[10] |= 0x20;
			  Display_Buffer2[5] &= 0xDF;
			  Display_Buffer2[0] |= 0x20;
			  Display_Buffer2[0] |= 0x10;
			  Display_Buffer2[10] &= 0xEF;
			  Display_Buffer2[5] |= 0x10;
	}
		break;

	case 3:
	{
			  Display_Buffer2[15] |= 0x20;
			  Display_Buffer2[10] |= 0x20;
			  Display_Buffer2[5] |= 0x20;
			  Display_Buffer2[0] |= 0x20;
			  Display_Buffer2[0] &= 0xEF;
			  Display_Buffer2[10] &= 0xEF;
			  Display_Buffer2[5] |= 0x10;
	}
		break;

	case 4:
	{
			  Display_Buffer2[15] &= 0xDF;
			  Display_Buffer2[10] |= 0x20;
			  Display_Buffer2[5] |= 0x20;
			  Display_Buffer2[0] &= 0xDF;
			  Display_Buffer2[0] &= 0xEF;
			  Display_Buffer2[10] |= 0x10;
			  Display_Buffer2[5] |= 0x10;
	}
		break;

	case 5:
	{
			  Display_Buffer2[15] |= 0x20;
			  Display_Buffer2[10] &= 0xDF;
			  Display_Buffer2[5] |= 0x20;
			  Display_Buffer2[0] |= 0x20;
			  Display_Buffer2[0] &= 0xEF;
			  Display_Buffer2[10] |= 0x10;
			  Display_Buffer2[5] |= 0x10;
	}
		break;

	case 6:
	{
			  Display_Buffer2[15] |= 0x20;
			  Display_Buffer2[10] &= 0xDF;
			  Display_Buffer2[5] |= 0x20;
			  Display_Buffer2[0] |= 0x20;
			  Display_Buffer2[0] |= 0x10;
			  Display_Buffer2[10] |= 0x10;
			  Display_Buffer2[5] |= 0x10;
	}
		break;

	case 7:
	{
			  Display_Buffer2[15] |= 0x20;
			  Display_Buffer2[10] |= 0x20;
			  Display_Buffer2[5] |= 0x20;
			  Display_Buffer2[0] &= 0xDF;
			  Display_Buffer2[0] &= 0xEF;
			  Display_Buffer2[10] &= 0xEF;
			  Display_Buffer2[5] &= 0xEF;
	}
		break;

	case 8:
	{
			  Display_Buffer2[15] |= 0x20;
			  Display_Buffer2[10] |= 0x20;
			  Display_Buffer2[5] |= 0x20;
			  Display_Buffer2[0] |= 0x20;
			  Display_Buffer2[0] |= 0x10;
			  Display_Buffer2[10] |= 0x10;
			  Display_Buffer2[5] |= 0x10;
	}
		break;

	case 9:
	{
			  Display_Buffer2[15] |= 0x20;
			  Display_Buffer2[10] |= 0x20;
			  Display_Buffer2[5] |= 0x20;
			  Display_Buffer2[0] |= 0x20;
			  Display_Buffer2[0] &= 0xEF;
			  Display_Buffer2[10] |= 0x10;
			  Display_Buffer2[5] |= 0x10;
	}
		break;

	default:
	{
			   Display_Buffer2[15] &= 0xDF;
			   Display_Buffer2[10] &= 0xDF;
			   Display_Buffer2[5] &= 0xDF;
			   Display_Buffer2[0] &= 0xDF;
			   Display_Buffer2[0] &= 0xEF;
			   Display_Buffer2[10] &= 0xEF;
			   Display_Buffer2[5] &= 0xEF;
	}
		break;
	}
}

static void ShowGKInt3(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[15] |= 0x80;
			  Display_Buffer2[10] |= 0x80;
			  Display_Buffer2[5] |= 0x80;
			  Display_Buffer2[0] |= 0x80;
			  Display_Buffer2[0] |= 0x40;
			  Display_Buffer2[10] |= 0x40;
			  Display_Buffer2[5] &= 0xBF;
	}
		break;

	case 1:
	{
			  Display_Buffer2[15] &= 0x7F;
			  Display_Buffer2[10] |= 0x80;
			  Display_Buffer2[5] |= 0x80;
			  Display_Buffer2[0] &= 0x7F;
			  Display_Buffer2[0] &= 0xBF;
			  Display_Buffer2[10] &= 0xBF;
			  Display_Buffer2[5] &= 0xBF;
	}
		break;

	case 2:
	{
			  Display_Buffer2[15] |= 0x80;
			  Display_Buffer2[10] |= 0x80;
			  Display_Buffer2[5] &= 0x7F;
			  Display_Buffer2[0] |= 0x80;
			  Display_Buffer2[0] |= 0x40;
			  Display_Buffer2[10] &= 0xBF;
			  Display_Buffer2[5] |= 0x40;
	}
		break;

	case 3:
	{
			  Display_Buffer2[15] |= 0x80;
			  Display_Buffer2[10] |= 0x80;
			  Display_Buffer2[5] |= 0x80;
			  Display_Buffer2[0] |= 0x80;
			  Display_Buffer2[0] &= 0xBF;
			  Display_Buffer2[10] &= 0xBF;
			  Display_Buffer2[5] |= 0x40;
	}
		break;

	case 4:
	{
			  Display_Buffer2[15] &= 0x7F;
			  Display_Buffer2[10] |= 0x80;
			  Display_Buffer2[5] |= 0x80;
			  Display_Buffer2[0] &= 0x7F;
			  Display_Buffer2[0] &= 0xBF;
			  Display_Buffer2[10] |= 0x40;
			  Display_Buffer2[5] |= 0x40;
	}
		break;

	case 5:
	{
			  Display_Buffer2[15] |= 0x80;
			  Display_Buffer2[10] &= 0x7F;
			  Display_Buffer2[5] |= 0x80;
			  Display_Buffer2[0] |= 0x80;
			  Display_Buffer2[0] &= 0xBF;
			  Display_Buffer2[10] |= 0x40;
			  Display_Buffer2[5] |= 0x40;
	}
		break;

	case 6:
	{
			  Display_Buffer2[15] |= 0x80;
			  Display_Buffer2[10] &= 0x7F;
			  Display_Buffer2[5] |= 0x80;
			  Display_Buffer2[0] |= 0x80;
			  Display_Buffer2[0] |= 0x40;
			  Display_Buffer2[10] |= 0x40;
			  Display_Buffer2[5] |= 0x40;
	}
		break;

	case 7:
	{
			  Display_Buffer2[15] |= 0x80;
			  Display_Buffer2[10] |= 0x80;
			  Display_Buffer2[5] |= 0x80;
			  Display_Buffer2[0] &= 0x7F;
			  Display_Buffer2[0] &= 0xBF;
			  Display_Buffer2[10] &= 0xBF;
			  Display_Buffer2[5] &= 0xBF;
	}
		break;

	case 8:
	{
			  Display_Buffer2[15] |= 0x80;
			  Display_Buffer2[10] |= 0x80;
			  Display_Buffer2[5] |= 0x80;
			  Display_Buffer2[0] |= 0x80;
			  Display_Buffer2[0] |= 0x40;
			  Display_Buffer2[10] |= 0x40;
			  Display_Buffer2[5] |= 0x40;
	}
		break;

	case 9:
	{
			  Display_Buffer2[15] |= 0x80;
			  Display_Buffer2[10] |= 0x80;
			  Display_Buffer2[5] |= 0x80;
			  Display_Buffer2[0] |= 0x80;
			  Display_Buffer2[0] &= 0xBF;
			  Display_Buffer2[10] |= 0x40;
			  Display_Buffer2[5] |= 0x40;
	}
		break;

	default:
	{
			   Display_Buffer2[15] &= 0x7F;
			   Display_Buffer2[10] &= 0x7F;
			   Display_Buffer2[5] &= 0x7F;
			   Display_Buffer2[0] &= 0x7F;
			   Display_Buffer2[0] &= 0xBF;
			   Display_Buffer2[10] &= 0xBF;
			   Display_Buffer2[5] &= 0xBF;
	}
		break;

	}
}

static void ShowGKInt4(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[16] |= 0x02;
			  Display_Buffer2[11] |= 0x02;
			  Display_Buffer2[6] |= 0x02;
			  Display_Buffer2[1] |= 0x02;
			  Display_Buffer2[1] |= 0x01;
			  Display_Buffer2[11] |= 0x01;
			  Display_Buffer2[6] &= 0xFE;
	}
		break;

	case 1:
	{
			  Display_Buffer2[16] &= 0xFD;
			  Display_Buffer2[11] |= 0x02;
			  Display_Buffer2[6] |= 0x02;
			  Display_Buffer2[1] &= 0xFD;
			  Display_Buffer2[1] &= 0xFE;
			  Display_Buffer2[11] &= 0xFE;
			  Display_Buffer2[6] &= 0xFE;
	}
		break;

	case 2:
	{
			  Display_Buffer2[16] |= 0x02;
			  Display_Buffer2[11] |= 0x02;
			  Display_Buffer2[6] &= 0xFD;
			  Display_Buffer2[1] |= 0x02;
			  Display_Buffer2[1] |= 0x01;
			  Display_Buffer2[11] &= 0xFE;
			  Display_Buffer2[6] |= 0x01;
	}
		break;

	case 3:
	{
			  Display_Buffer2[16] |= 0x02;
			  Display_Buffer2[11] |= 0x02;
			  Display_Buffer2[6] |= 0x02;
			  Display_Buffer2[1] |= 0x02;
			  Display_Buffer2[1] &= 0xFE;
			  Display_Buffer2[11] &= 0xFE;
			  Display_Buffer2[6] |= 0x01;
	}
		break;

	case 4:
	{
			  Display_Buffer2[16] &= 0xFD;
			  Display_Buffer2[11] |= 0x02;
			  Display_Buffer2[6] |= 0x02;
			  Display_Buffer2[1] &= 0xFD;
			  Display_Buffer2[1] &= 0xFE;
			  Display_Buffer2[11] |= 0x01;
			  Display_Buffer2[6] |= 0x01;
	}
		break;

	case 5:
	{
			  Display_Buffer2[16] |= 0x02;
			  Display_Buffer2[11] &= 0xFD;
			  Display_Buffer2[6] |= 0x02;
			  Display_Buffer2[1] |= 0x02;
			  Display_Buffer2[1] &= 0xFE;
			  Display_Buffer2[11] |= 0x01;
			  Display_Buffer2[6] |= 0x01;
	}
		break;

	case 6:
	{
			  Display_Buffer2[16] |= 0x02;
			  Display_Buffer2[11] &= 0xFD;
			  Display_Buffer2[6] |= 0x02;
			  Display_Buffer2[1] |= 0x02;
			  Display_Buffer2[1] |= 0x01;
			  Display_Buffer2[11] |= 0x01;
			  Display_Buffer2[6] |= 0x01;
	}
		break;

	case 7:
	{
			  Display_Buffer2[16] |= 0x02;
			  Display_Buffer2[11] |= 0x02;
			  Display_Buffer2[6] |= 0x02;
			  Display_Buffer2[1] &= 0xFD;
			  Display_Buffer2[1] &= 0xFE;
			  Display_Buffer2[11] &= 0xFE;
			  Display_Buffer2[6] &= 0xFE;
	}
		break;

	case 8:
	{
			  Display_Buffer2[16] |= 0x02;
			  Display_Buffer2[11] |= 0x02;
			  Display_Buffer2[6] |= 0x02;
			  Display_Buffer2[1] |= 0x02;
			  Display_Buffer2[1] |= 0x01;
			  Display_Buffer2[11] |= 0x01;
			  Display_Buffer2[6] |= 0x01;
	}
		break;

	case 9:
	{
			  Display_Buffer2[16] |= 0x02;
			  Display_Buffer2[11] |= 0x02;
			  Display_Buffer2[6] |= 0x02;
			  Display_Buffer2[1] |= 0x02;
			  Display_Buffer2[1] &= 0xFE;
			  Display_Buffer2[11] |= 0x01;
			  Display_Buffer2[6] |= 0x01;
	}
		break;

	default:
	{
			   Display_Buffer2[16] &= 0xFD;
			   Display_Buffer2[11] &= 0xFD;
			   Display_Buffer2[6] &= 0xFD;
			   Display_Buffer2[1] &= 0xFD;
			   Display_Buffer2[1] &= 0xFE;
			   Display_Buffer2[11] &= 0xFE;
			   Display_Buffer2[6] &= 0xFE;
	}
		break;

	}
}

static void ShowGKInt5(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[16] |= 0x08;
			  Display_Buffer2[11] |= 0x08;
			  Display_Buffer2[6] |= 0x08;
			  Display_Buffer2[1] |= 0x08;
			  Display_Buffer2[6] |= 0x04;
			  Display_Buffer2[16] |= 0x04;
			  Display_Buffer2[11] &= 0xFB;
	}
		break;

	case 1:
	{
			  Display_Buffer2[16] &= 0xF7;
			  Display_Buffer2[11] |= 0x08;
			  Display_Buffer2[6] |= 0x08;
			  Display_Buffer2[1] &= 0xF7;
			  Display_Buffer2[6] &= 0xFB;
			  Display_Buffer2[16] &= 0xFB;
			  Display_Buffer2[11] &= 0xFB;
	}
		break;

	case 2:
	{
			  Display_Buffer2[16] |= 0x08;
			  Display_Buffer2[11] |= 0x08;
			  Display_Buffer2[6] &= 0xF7;
			  Display_Buffer2[1] |= 0x08;
			  Display_Buffer2[6] |= 0x04;
			  Display_Buffer2[16] &= 0xFB;
			  Display_Buffer2[11] |= 0x04;
	}
		break;

	case 3:
	{
			  Display_Buffer2[16] |= 0x08;
			  Display_Buffer2[11] |= 0x08;
			  Display_Buffer2[6] |= 0x08;
			  Display_Buffer2[1] |= 0x08;
			  Display_Buffer2[6] &= 0xFB;
			  Display_Buffer2[16] &= 0xFB;
			  Display_Buffer2[11] |= 0x04;
	}
		break;

	case 4:
	{
			  Display_Buffer2[16] &= 0xF7;
			  Display_Buffer2[11] |= 0x08;
			  Display_Buffer2[6] |= 0x08;
			  Display_Buffer2[1] &= 0xF7;
			  Display_Buffer2[6] &= 0xFB;
			  Display_Buffer2[16] |= 0x04;
			  Display_Buffer2[11] |= 0x04;
	}
		break;

	case 5:
	{
			  Display_Buffer2[16] |= 0x08;
			  Display_Buffer2[11] &= 0xF7;
			  Display_Buffer2[6] |= 0x08;
			  Display_Buffer2[1] |= 0x08;
			  Display_Buffer2[6] &= 0xFB;
			  Display_Buffer2[16] |= 0x04;
			  Display_Buffer2[11] |= 0x04;
	}
		break;

	case 6:
	{
			  Display_Buffer2[16] |= 0x08;
			  Display_Buffer2[11] &= 0xF7;
			  Display_Buffer2[6] |= 0x08;
			  Display_Buffer2[1] |= 0x08;
			  Display_Buffer2[6] |= 0x04;
			  Display_Buffer2[16] |= 0x04;
			  Display_Buffer2[11] |= 0x04;
	}
		break;

	case 7:
	{
			  Display_Buffer2[16] |= 0x08;
			  Display_Buffer2[11] |= 0x08;
			  Display_Buffer2[6] |= 0x08;
			  Display_Buffer2[1] &= 0xF7;
			  Display_Buffer2[6] &= 0xFB;
			  Display_Buffer2[16] &= 0xFB;
			  Display_Buffer2[11] &= 0xFB;
	}
		break;

	case 8:
	{
			  Display_Buffer2[16] |= 0x08;
			  Display_Buffer2[11] |= 0x08;
			  Display_Buffer2[6] |= 0x08;
			  Display_Buffer2[1] |= 0x08;
			  Display_Buffer2[6] |= 0x04;
			  Display_Buffer2[16] |= 0x04;
			  Display_Buffer2[11] |= 0x04;
	}
		break;

	case 9:
	{
			  Display_Buffer2[16] |= 0x08;
			  Display_Buffer2[11] |= 0x08;
			  Display_Buffer2[6] |= 0x08;
			  Display_Buffer2[1] |= 0x08;
			  Display_Buffer2[6] &= 0xFB;
			  Display_Buffer2[16] |= 0x04;
			  Display_Buffer2[11] |= 0x04;
	}
		break;

	default:
	{
			   Display_Buffer2[16] &= 0xF7;
			   Display_Buffer2[11] &= 0xF7;
			   Display_Buffer2[6] &= 0xF7;
			   Display_Buffer2[1] &= 0xF7;
			   Display_Buffer2[6] &= 0xFB;
			   Display_Buffer2[16] &= 0xFB;
			   Display_Buffer2[11] &= 0xFB;
	}
		break;

	}
}

static void ShowGKInt6(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[16] |= 0x20;
			  Display_Buffer2[11] |= 0x20;
			  Display_Buffer2[6] |= 0x20;
			  Display_Buffer2[1] |= 0x20;
			  Display_Buffer2[6] |= 0x10;
			  Display_Buffer2[16] |= 0x10;
			  Display_Buffer2[11] &= 0xEF;
	}
		break;

	case 1:
	{
			  Display_Buffer2[16] &= 0xDF;
			  Display_Buffer2[11] |= 0x20;
			  Display_Buffer2[6] |= 0x20;
			  Display_Buffer2[1] &= 0xDF;
			  Display_Buffer2[6] &= 0xEF;
			  Display_Buffer2[16] &= 0xEF;
			  Display_Buffer2[11] &= 0xEF;
	}
		break;

	case 2:
	{
			  Display_Buffer2[16] |= 0x20;
			  Display_Buffer2[11] |= 0x20;
			  Display_Buffer2[6] &= 0xDF;
			  Display_Buffer2[1] |= 0x20;
			  Display_Buffer2[6] |= 0x10;
			  Display_Buffer2[16] &= 0xEF;
			  Display_Buffer2[11] |= 0x10;
	}
		break;

	case 3:
	{
			  Display_Buffer2[16] |= 0x20;
			  Display_Buffer2[11] |= 0x20;
			  Display_Buffer2[6] |= 0x20;
			  Display_Buffer2[1] |= 0x20;
			  Display_Buffer2[6] &= 0xEF;
			  Display_Buffer2[16] &= 0xEF;
			  Display_Buffer2[11] |= 0x10;
	}
		break;

	case 4:
	{
			  Display_Buffer2[16] &= 0xDF;
			  Display_Buffer2[11] |= 0x20;
			  Display_Buffer2[6] |= 0x20;
			  Display_Buffer2[1] &= 0xDF;
			  Display_Buffer2[6] &= 0xEF;
			  Display_Buffer2[16] |= 0x10;
			  Display_Buffer2[11] |= 0x10;
	}
		break;

	case 5:
	{
			  Display_Buffer2[16] |= 0x20;
			  Display_Buffer2[11] &= 0xDF;
			  Display_Buffer2[6] |= 0x20;
			  Display_Buffer2[1] |= 0x20;
			  Display_Buffer2[6] &= 0xEF;
			  Display_Buffer2[16] |= 0x10;
			  Display_Buffer2[11] |= 0x10;
	}
		break;

	case 6:
	{
			  Display_Buffer2[16] |= 0x20;
			  Display_Buffer2[11] &= 0xDF;
			  Display_Buffer2[6] |= 0x20;
			  Display_Buffer2[1] |= 0x20;
			  Display_Buffer2[6] |= 0x10;
			  Display_Buffer2[16] |= 0x10;
			  Display_Buffer2[11] |= 0x10;
	}
		break;

	case 7:
	{
			  Display_Buffer2[16] |= 0x20;
			  Display_Buffer2[11] |= 0x20;
			  Display_Buffer2[6] |= 0x20;
			  Display_Buffer2[1] &= 0xDF;
			  Display_Buffer2[6] &= 0xEF;
			  Display_Buffer2[16] &= 0xEF;
			  Display_Buffer2[11] &= 0xEF;
	}
		break;

	case 8:
	{
			  Display_Buffer2[16] |= 0x20;
			  Display_Buffer2[11] |= 0x20;
			  Display_Buffer2[6] |= 0x20;
			  Display_Buffer2[1] |= 0x20;
			  Display_Buffer2[6] |= 0x10;
			  Display_Buffer2[16] |= 0x10;
			  Display_Buffer2[11] |= 0x10;
	}
		break;

	case 9:
	{
			  Display_Buffer2[16] |= 0x20;
			  Display_Buffer2[11] |= 0x20;
			  Display_Buffer2[6] |= 0x20;
			  Display_Buffer2[1] |= 0x20;
			  Display_Buffer2[6] &= 0xEF;
			  Display_Buffer2[16] |= 0x10;
			  Display_Buffer2[11] |= 0x10;
	}
		break;

	default:
	{
			   Display_Buffer2[16] &= 0xDF;
			   Display_Buffer2[11] &= 0xDF;
			   Display_Buffer2[6] &= 0xDF;
			   Display_Buffer2[1] &= 0xDF;
			   Display_Buffer2[6] &= 0xEF;
			   Display_Buffer2[16] &= 0xEF;
			   Display_Buffer2[11] &= 0xEF;
	}
		break;

	}
}

static void ShowGKInt7(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[16] |= 0x80;
			  Display_Buffer2[11] |= 0x80;
			  Display_Buffer2[6] |= 0x80;
			  Display_Buffer2[1] |= 0x80;
			  Display_Buffer2[6] |= 0x40;
			  Display_Buffer2[16] |= 0x40;
			  Display_Buffer2[11] &= 0xBF;
	}
		break;

	case 1:
	{
			  Display_Buffer2[16] &= 0x7F;
			  Display_Buffer2[11] |= 0x80;
			  Display_Buffer2[6] |= 0x80;
			  Display_Buffer2[1] &= 0x7F;
			  Display_Buffer2[6] &= 0xBF;
			  Display_Buffer2[16] &= 0xBF;
			  Display_Buffer2[11] &= 0xBF;
	}
		break;

	case 2:
	{
			  Display_Buffer2[16] |= 0x80;
			  Display_Buffer2[11] |= 0x80;
			  Display_Buffer2[6] &= 0x7F;
			  Display_Buffer2[1] |= 0x80;
			  Display_Buffer2[6] |= 0x40;
			  Display_Buffer2[16] &= 0xBF;
			  Display_Buffer2[11] |= 0x40;
	}
		break;

	case 3:
	{
			  Display_Buffer2[16] |= 0x80;
			  Display_Buffer2[11] |= 0x80;
			  Display_Buffer2[6] |= 0x80;
			  Display_Buffer2[1] |= 0x80;
			  Display_Buffer2[6] &= 0xBF;
			  Display_Buffer2[16] &= 0xBF;
			  Display_Buffer2[11] |= 0x40;
	}
		break;

	case 4:
	{
			  Display_Buffer2[16] &= 0x7F;
			  Display_Buffer2[11] |= 0x80;
			  Display_Buffer2[6] |= 0x80;
			  Display_Buffer2[1] &= 0x7F;
			  Display_Buffer2[6] &= 0xBF;
			  Display_Buffer2[16] |= 0x40;
			  Display_Buffer2[11] |= 0x40;
	}
		break;

	case 5:
	{
			  Display_Buffer2[16] |= 0x80;
			  Display_Buffer2[11] &= 0x7F;
			  Display_Buffer2[6] |= 0x80;
			  Display_Buffer2[1] |= 0x80;
			  Display_Buffer2[6] &= 0xBF;
			  Display_Buffer2[16] |= 0x40;
			  Display_Buffer2[11] |= 0x40;
	}
		break;

	case 6:
	{
			  Display_Buffer2[16] |= 0x80;
			  Display_Buffer2[11] &= 0x7F;
			  Display_Buffer2[6] |= 0x80;
			  Display_Buffer2[1] |= 0x80;
			  Display_Buffer2[6] |= 0x40;
			  Display_Buffer2[16] |= 0x40;
			  Display_Buffer2[11] |= 0x40;
	}
		break;

	case 7:
	{
			  Display_Buffer2[16] |= 0x80;
			  Display_Buffer2[11] |= 0x80;
			  Display_Buffer2[6] |= 0x80;
			  Display_Buffer2[1] &= 0x7F;
			  Display_Buffer2[6] &= 0xBF;
			  Display_Buffer2[16] &= 0xBF;
			  Display_Buffer2[11] &= 0xBF;
	}
		break;

	case 8:
	{
			  Display_Buffer2[16] |= 0x80;
			  Display_Buffer2[11] |= 0x80;
			  Display_Buffer2[6] |= 0x80;
			  Display_Buffer2[1] |= 0x80;
			  Display_Buffer2[6] |= 0x40;
			  Display_Buffer2[16] |= 0x40;
			  Display_Buffer2[11] |= 0x40;
	}
		break;

	case 9:
	{
			  Display_Buffer2[16] |= 0x80;
			  Display_Buffer2[11] |= 0x80;
			  Display_Buffer2[6] |= 0x80;
			  Display_Buffer2[1] |= 0x80;
			  Display_Buffer2[6] &= 0xBF;
			  Display_Buffer2[16] |= 0x40;
			  Display_Buffer2[11] |= 0x40;
	}
		break;

	default:
	{
			   Display_Buffer2[16] &= 0x7F;
			   Display_Buffer2[11] &= 0x7F;
			   Display_Buffer2[6] &= 0x7F;
			   Display_Buffer2[1] &= 0x7F;
			   Display_Buffer2[6] &= 0xBF;
			   Display_Buffer2[16] &= 0xBF;
			   Display_Buffer2[11] &= 0xBF;
	}
		break;

	}
}

static void ShowGKInt8(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[17] |= 0x02;
			  Display_Buffer2[12] |= 0x02;
			  Display_Buffer2[7] |= 0x02;
			  Display_Buffer2[2] |= 0x02;
			  Display_Buffer2[7] |= 0x01;
			  Display_Buffer2[17] |= 0x01;
			  Display_Buffer2[12] &= 0xFE;
	}
		break;

	case 1:
	{
			  Display_Buffer2[17] &= 0xFD;
			  Display_Buffer2[12] |= 0x02;
			  Display_Buffer2[7] |= 0x02;
			  Display_Buffer2[2] &= 0xFD;
			  Display_Buffer2[7] &= 0xFE;
			  Display_Buffer2[17] &= 0xFE;
			  Display_Buffer2[12] &= 0xFE;
	}
		break;

	case 2:
	{
			  Display_Buffer2[17] |= 0x02;
			  Display_Buffer2[12] |= 0x02;
			  Display_Buffer2[7] &= 0xFD;
			  Display_Buffer2[2] |= 0x02;
			  Display_Buffer2[7] |= 0x01;
			  Display_Buffer2[17] &= 0xFE;
			  Display_Buffer2[12] |= 0x01;
	}
		break;

	case 3:
	{
			  Display_Buffer2[17] |= 0x02;
			  Display_Buffer2[12] |= 0x02;
			  Display_Buffer2[7] |= 0x02;
			  Display_Buffer2[2] |= 0x02;
			  Display_Buffer2[7] &= 0xFE;
			  Display_Buffer2[17] &= 0xFE;
			  Display_Buffer2[12] |= 0x01;
	}
		break;

	case 4:
	{
			  Display_Buffer2[17] &= 0xFD;
			  Display_Buffer2[12] |= 0x02;
			  Display_Buffer2[7] |= 0x02;
			  Display_Buffer2[2] &= 0xFD;
			  Display_Buffer2[7] &= 0xFE;
			  Display_Buffer2[17] |= 0x01;
			  Display_Buffer2[12] |= 0x01;
	}
		break;

	case 5:
	{
			  Display_Buffer2[17] |= 0x02;
			  Display_Buffer2[12] &= 0xFD;
			  Display_Buffer2[7] |= 0x02;
			  Display_Buffer2[2] |= 0x02;
			  Display_Buffer2[7] &= 0xFE;
			  Display_Buffer2[17] |= 0x01;
			  Display_Buffer2[12] |= 0x01;
	}
		break;

	case 6:
	{
			  Display_Buffer2[17] |= 0x02;
			  Display_Buffer2[12] &= 0xFD;
			  Display_Buffer2[7] |= 0x02;
			  Display_Buffer2[2] |= 0x02;
			  Display_Buffer2[7] |= 0x01;
			  Display_Buffer2[17] |= 0x01;
			  Display_Buffer2[12] |= 0x01;
	}
		break;

	case 7:
	{
			  Display_Buffer2[17] |= 0x02;
			  Display_Buffer2[12] |= 0x02;
			  Display_Buffer2[7] |= 0x02;
			  Display_Buffer2[2] &= 0xFD;
			  Display_Buffer2[7] &= 0xFE;
			  Display_Buffer2[17] &= 0xFE;
			  Display_Buffer2[12] &= 0xFE;
	}
		break;

	case 8:
	{
			  Display_Buffer2[17] |= 0x02;
			  Display_Buffer2[12] |= 0x02;
			  Display_Buffer2[7] |= 0x02;
			  Display_Buffer2[2] |= 0x02;
			  Display_Buffer2[7] |= 0x01;
			  Display_Buffer2[17] |= 0x01;
			  Display_Buffer2[12] |= 0x01;
	}
		break;

	case 9:
	{
			  Display_Buffer2[17] |= 0x02;
			  Display_Buffer2[12] |= 0x02;
			  Display_Buffer2[7] |= 0x02;
			  Display_Buffer2[2] |= 0x02;
			  Display_Buffer2[7] &= 0xFE;
			  Display_Buffer2[17] |= 0x01;
			  Display_Buffer2[12] |= 0x01;
	}
		break;

	default:
	{
			   Display_Buffer2[17] &= 0xFD;
			   Display_Buffer2[12] &= 0xFD;
			   Display_Buffer2[7] &= 0xFD;
			   Display_Buffer2[2] &= 0xFD;
			   Display_Buffer2[7] &= 0xFE;
			   Display_Buffer2[17] &= 0xFE;
			   Display_Buffer2[12] &= 0xFE;
	}
		break;

	}
}

static void ShowGKFloat1(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[17] |= 0x08;
			  Display_Buffer2[12] |= 0x08;
			  Display_Buffer2[7] |= 0x08;
			  Display_Buffer2[2] |= 0x08;
			  Display_Buffer2[7] |= 0x04;
			  Display_Buffer2[17] |= 0x04;
			  Display_Buffer2[12] &= 0xFB;
	}
		break;

	case 1:
	{
			  Display_Buffer2[17] &= 0xF7;
			  Display_Buffer2[12] |= 0x08;
			  Display_Buffer2[7] |= 0x08;
			  Display_Buffer2[2] &= 0xF7;
			  Display_Buffer2[7] &= 0xFB;
			  Display_Buffer2[17] &= 0xFB;
			  Display_Buffer2[12] &= 0xFB;
	}
		break;

	case 2:
	{
			  Display_Buffer2[17] |= 0x08;
			  Display_Buffer2[12] |= 0x08;
			  Display_Buffer2[7] &= 0xF7;
			  Display_Buffer2[2] |= 0x08;
			  Display_Buffer2[7] |= 0x04;
			  Display_Buffer2[17] &= 0xFB;
			  Display_Buffer2[12] |= 0x04;
	}
		break;

	case 3:
	{
			  Display_Buffer2[17] |= 0x08;
			  Display_Buffer2[12] |= 0x08;
			  Display_Buffer2[7] |= 0x08;
			  Display_Buffer2[2] |= 0x08;
			  Display_Buffer2[7] &= 0xFB;
			  Display_Buffer2[17] &= 0xFB;
			  Display_Buffer2[12] |= 0x04;
	}
		break;

	case 4:
	{
			  Display_Buffer2[17] &= 0xF7;
			  Display_Buffer2[12] |= 0x08;
			  Display_Buffer2[7] |= 0x08;
			  Display_Buffer2[2] &= 0xF7;
			  Display_Buffer2[7] &= 0xFB;
			  Display_Buffer2[17] |= 0x04;
			  Display_Buffer2[12] |= 0x04;
	}
		break;

	case 5:
	{
			  Display_Buffer2[17] |= 0x08;
			  Display_Buffer2[12] &= 0xF7;
			  Display_Buffer2[7] |= 0x08;
			  Display_Buffer2[2] |= 0x08;
			  Display_Buffer2[7] &= 0xFB;
			  Display_Buffer2[17] |= 0x04;
			  Display_Buffer2[12] |= 0x04;
	}
		break;

	case 6:
	{
			  Display_Buffer2[17] |= 0x08;
			  Display_Buffer2[12] &= 0xF7;
			  Display_Buffer2[7] |= 0x08;
			  Display_Buffer2[2] |= 0x08;
			  Display_Buffer2[7] |= 0x04;
			  Display_Buffer2[17] |= 0x04;
			  Display_Buffer2[12] |= 0x04;
	}
		break;

	case 7:
	{
			  Display_Buffer2[17] |= 0x08;
			  Display_Buffer2[12] |= 0x08;
			  Display_Buffer2[7] |= 0x08;
			  Display_Buffer2[2] &= 0xF7;
			  Display_Buffer2[7] &= 0xFB;
			  Display_Buffer2[17] &= 0xFB;
			  Display_Buffer2[12] &= 0xFB;
	}
		break;

	case 8:
	{
			  Display_Buffer2[17] |= 0x08;
			  Display_Buffer2[12] |= 0x08;
			  Display_Buffer2[7] |= 0x08;
			  Display_Buffer2[2] |= 0x08;
			  Display_Buffer2[7] |= 0x04;
			  Display_Buffer2[17] |= 0x04;
			  Display_Buffer2[12] |= 0x04;
	}
		break;

	case 9:
	{
			  Display_Buffer2[17] |= 0x08;
			  Display_Buffer2[12] |= 0x08;
			  Display_Buffer2[7] |= 0x08;
			  Display_Buffer2[2] |= 0x08;
			  Display_Buffer2[7] &= 0xFB;
			  Display_Buffer2[17] |= 0x04;
			  Display_Buffer2[12] |= 0x04;
	}
		break;

	default:
	{
			   Display_Buffer2[17] &= 0xF7;
			   Display_Buffer2[12] &= 0xF7;
			   Display_Buffer2[7] &= 0xF7;
			   Display_Buffer2[2] &= 0xF7;
			   Display_Buffer2[7] &= 0xFB;
			   Display_Buffer2[17] &= 0xFB;
			   Display_Buffer2[12] &= 0xFB;
	}
		break;

	}
}

static void ShowGKFloat2(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[17] |= 0x20;
			  Display_Buffer2[12] |= 0x20;
			  Display_Buffer2[7] |= 0x20;
			  Display_Buffer2[2] |= 0x20;
			  Display_Buffer2[7] |= 0x10;
			  Display_Buffer2[17] |= 0x10;
			  Display_Buffer2[12] &= 0xEF;
	}
		break;

	case 1:
	{
			  Display_Buffer2[17] &= 0xDF;
			  Display_Buffer2[12] |= 0x20;
			  Display_Buffer2[7] |= 0x20;
			  Display_Buffer2[2] &= 0xDF;
			  Display_Buffer2[7] &= 0xEF;
			  Display_Buffer2[17] &= 0xEF;
			  Display_Buffer2[12] &= 0xEF;
	}
		break;

	case 2:
	{
			  Display_Buffer2[17] |= 0x20;
			  Display_Buffer2[12] |= 0x20;
			  Display_Buffer2[7] &= 0xDF;
			  Display_Buffer2[2] |= 0x20;
			  Display_Buffer2[7] |= 0x10;
			  Display_Buffer2[17] &= 0xEF;
			  Display_Buffer2[12] |= 0x10;
	}
		break;

	case 3:
	{
			  Display_Buffer2[17] |= 0x20;
			  Display_Buffer2[12] |= 0x20;
			  Display_Buffer2[7] |= 0x20;
			  Display_Buffer2[2] |= 0x20;
			  Display_Buffer2[7] &= 0xEF;
			  Display_Buffer2[17] &= 0xEF;
			  Display_Buffer2[12] |= 0x10;
	}
		break;

	case 4:
	{
			  Display_Buffer2[17] &= 0xDF;
			  Display_Buffer2[12] |= 0x20;
			  Display_Buffer2[7] |= 0x20;
			  Display_Buffer2[2] &= 0xDF;
			  Display_Buffer2[7] &= 0xEF;
			  Display_Buffer2[17] |= 0x10;
			  Display_Buffer2[12] |= 0x10;
	}
		break;

	case 5:
	{
			  Display_Buffer2[17] |= 0x20;
			  Display_Buffer2[12] &= 0xDF;
			  Display_Buffer2[7] |= 0x20;
			  Display_Buffer2[2] |= 0x20;
			  Display_Buffer2[7] &= 0xEF;
			  Display_Buffer2[17] |= 0x10;
			  Display_Buffer2[12] |= 0x10;
	}
		break;

	case 6:
	{
			  Display_Buffer2[17] |= 0x20;
			  Display_Buffer2[12] &= 0xDF;
			  Display_Buffer2[7] |= 0x20;
			  Display_Buffer2[2] |= 0x20;
			  Display_Buffer2[7] |= 0x10;
			  Display_Buffer2[17] |= 0x10;
			  Display_Buffer2[12] |= 0x10;
	}
		break;

	case 7:
	{
			  Display_Buffer2[17] |= 0x20;
			  Display_Buffer2[12] |= 0x20;
			  Display_Buffer2[7] |= 0x20;
			  Display_Buffer2[2] &= 0xDF;
			  Display_Buffer2[7] &= 0xEF;
			  Display_Buffer2[17] &= 0xEF;
			  Display_Buffer2[12] &= 0xEF;
	}
		break;

	case 8:
	{
			  Display_Buffer2[17] |= 0x20;
			  Display_Buffer2[12] |= 0x20;
			  Display_Buffer2[7] |= 0x20;
			  Display_Buffer2[2] |= 0x20;
			  Display_Buffer2[7] |= 0x10;
			  Display_Buffer2[17] |= 0x10;
			  Display_Buffer2[12] |= 0x10;
	}
		break;

	case 9:
	{
			  Display_Buffer2[17] |= 0x20;
			  Display_Buffer2[12] |= 0x20;
			  Display_Buffer2[7] |= 0x20;
			  Display_Buffer2[2] |= 0x20;
			  Display_Buffer2[7] &= 0xEF;
			  Display_Buffer2[17] |= 0x10;
			  Display_Buffer2[12] |= 0x10;
	}
		break;

	default:
	{
			   Display_Buffer2[17] &= 0xDF;
			   Display_Buffer2[12] &= 0xDF;
			   Display_Buffer2[7] &= 0xDF;
			   Display_Buffer2[2] &= 0xDF;
			   Display_Buffer2[7] &= 0xEF;
			   Display_Buffer2[17] &= 0xEF;
			   Display_Buffer2[12] &= 0xEF;
	}
		break;

	}
}

static void ShowGKFloat3(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[17] |= 0x80;
			  Display_Buffer2[12] |= 0x80;
			  Display_Buffer2[7] |= 0x80;
			  Display_Buffer2[2] |= 0x80;
			  Display_Buffer2[7] |= 0x40;
			  Display_Buffer2[17] |= 0x40;
			  Display_Buffer2[12] &= 0xBF;
	}
		break;

	case 1:
	{
			  Display_Buffer2[17] &= 0x7F;
			  Display_Buffer2[12] |= 0x80;
			  Display_Buffer2[7] |= 0x80;
			  Display_Buffer2[2] &= 0x7F;
			  Display_Buffer2[7] &= 0xBF;
			  Display_Buffer2[17] &= 0xBF;
			  Display_Buffer2[12] &= 0xBF;
	}
		break;

	case 2:
	{
			  Display_Buffer2[17] |= 0x80;
			  Display_Buffer2[12] |= 0x80;
			  Display_Buffer2[7] &= 0x7F;
			  Display_Buffer2[2] |= 0x80;
			  Display_Buffer2[7] |= 0x40;
			  Display_Buffer2[17] &= 0xBF;
			  Display_Buffer2[12] |= 0x40;
	}
		break;

	case 3:
	{
			  Display_Buffer2[17] |= 0x80;
			  Display_Buffer2[12] |= 0x80;
			  Display_Buffer2[7] |= 0x80;
			  Display_Buffer2[2] |= 0x80;
			  Display_Buffer2[7] &= 0xBF;
			  Display_Buffer2[17] &= 0xBF;
			  Display_Buffer2[12] |= 0x40;
	}
		break;

	case 4:
	{
			  Display_Buffer2[17] &= 0x7F;
			  Display_Buffer2[12] |= 0x80;
			  Display_Buffer2[7] |= 0x80;
			  Display_Buffer2[2] &= 0x7F;
			  Display_Buffer2[7] &= 0xBF;
			  Display_Buffer2[17] |= 0x40;
			  Display_Buffer2[12] |= 0x40;
	}
		break;

	case 5:
	{
			  Display_Buffer2[17] |= 0x80;
			  Display_Buffer2[12] &= 0x7F;
			  Display_Buffer2[7] |= 0x80;
			  Display_Buffer2[2] |= 0x80;
			  Display_Buffer2[7] &= 0xBF;
			  Display_Buffer2[17] |= 0x40;
			  Display_Buffer2[12] |= 0x40;
	}
		break;

	case 6:
	{
			  Display_Buffer2[17] |= 0x80;
			  Display_Buffer2[12] &= 0x7F;
			  Display_Buffer2[7] |= 0x80;
			  Display_Buffer2[2] |= 0x80;
			  Display_Buffer2[7] |= 0x40;
			  Display_Buffer2[17] |= 0x40;
			  Display_Buffer2[12] |= 0x40;
	}
		break;

	case 7:
	{
			  Display_Buffer2[17] |= 0x80;
			  Display_Buffer2[12] |= 0x80;
			  Display_Buffer2[7] |= 0x80;
			  Display_Buffer2[2] &= 0x7F;
			  Display_Buffer2[7] &= 0xBF;
			  Display_Buffer2[17] &= 0xBF;
			  Display_Buffer2[12] &= 0xBF;
	}
		break;

	case 8:
	{
			  Display_Buffer2[17] |= 0x80;
			  Display_Buffer2[12] |= 0x80;
			  Display_Buffer2[7] |= 0x80;
			  Display_Buffer2[2] |= 0x80;
			  Display_Buffer2[7] |= 0x40;
			  Display_Buffer2[17] |= 0x40;
			  Display_Buffer2[12] |= 0x40;
	}
		break;

	case 9:
	{
			  Display_Buffer2[17] |= 0x80;
			  Display_Buffer2[12] |= 0x80;
			  Display_Buffer2[7] |= 0x80;
			  Display_Buffer2[2] |= 0x80;
			  Display_Buffer2[7] &= 0xBF;
			  Display_Buffer2[17] |= 0x40;
			  Display_Buffer2[12] |= 0x40;
	}
		break;

	default:
	{
			   Display_Buffer2[17] &= 0x7F;
			   Display_Buffer2[12] &= 0x7F;
			   Display_Buffer2[7] &= 0x7F;
			   Display_Buffer2[2] &= 0x7F;
			   Display_Buffer2[7] &= 0xBF;
			   Display_Buffer2[17] &= 0xBF;
			   Display_Buffer2[12] &= 0xBF;
	}
		break;
	}
}

static void ShowBKInt1(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[15] |= 0x02;
			  Display_Buffer2[10] |= 0x02;
			  Display_Buffer2[5] |= 0x02;
			  Display_Buffer2[0] |= 0x02;
			  Display_Buffer2[5] |= 0x01;
			  Display_Buffer2[15] |= 0x01;
			  Display_Buffer2[10] &= 0xFE;
	}
		break;

	case 1:
	{
			  Display_Buffer2[15] &= 0xFD;
			  Display_Buffer2[10] |= 0x02;
			  Display_Buffer2[5] |= 0x02;
			  Display_Buffer2[0] &= 0xFD;
			  Display_Buffer2[5] &= 0xFE;
			  Display_Buffer2[15] &= 0xFE;
			  Display_Buffer2[10] &= 0xFE;
	}
		break;

	case 2:
	{
			  Display_Buffer2[15] |= 0x02;
			  Display_Buffer2[10] |= 0x02;
			  Display_Buffer2[5] &= 0xFD;
			  Display_Buffer2[0] |= 0x02;
			  Display_Buffer2[5] |= 0x01;
			  Display_Buffer2[15] &= 0xFE;
			  Display_Buffer2[10] |= 0x01;
	}
		break;

	case 3:
	{
			  Display_Buffer2[15] |= 0x02;
			  Display_Buffer2[10] |= 0x02;
			  Display_Buffer2[5] |= 0x02;
			  Display_Buffer2[0] |= 0x02;
			  Display_Buffer2[5] &= 0xFE;
			  Display_Buffer2[15] &= 0xFE;
			  Display_Buffer2[10] |= 0x01;
	}
		break;

	case 4:
	{
			  Display_Buffer2[15] &= 0xFD;
			  Display_Buffer2[10] |= 0x02;
			  Display_Buffer2[5] |= 0x02;
			  Display_Buffer2[0] &= 0xFD;
			  Display_Buffer2[5] &= 0xFE;
			  Display_Buffer2[15] |= 0x01;
			  Display_Buffer2[10] |= 0x01;
	}
		break;

	case 5:
	{
			  Display_Buffer2[15] |= 0x02;
			  Display_Buffer2[10] &= 0xFD;
			  Display_Buffer2[5] |= 0x02;
			  Display_Buffer2[0] |= 0x02;
			  Display_Buffer2[5] &= 0xFE;
			  Display_Buffer2[15] |= 0x01;
			  Display_Buffer2[10] |= 0x01;
	}
		break;

	case 6:
	{
			  Display_Buffer2[15] |= 0x02;
			  Display_Buffer2[10] &= 0xFD;
			  Display_Buffer2[5] |= 0x02;
			  Display_Buffer2[0] |= 0x02;
			  Display_Buffer2[5] |= 0x01;
			  Display_Buffer2[15] |= 0x01;
			  Display_Buffer2[10] |= 0x01;
	}
		break;

	case 7:
	{
			  Display_Buffer2[15] |= 0x02;
			  Display_Buffer2[10] |= 0x02;
			  Display_Buffer2[5] |= 0x02;
			  Display_Buffer2[0] &= 0xFD;
			  Display_Buffer2[5] &= 0xFE;
			  Display_Buffer2[15] &= 0xFE;
			  Display_Buffer2[10] &= 0xFE;
	}
		break;

	case 8:
	{
			  Display_Buffer2[15] |= 0x02;
			  Display_Buffer2[10] |= 0x02;
			  Display_Buffer2[5] |= 0x02;
			  Display_Buffer2[0] |= 0x02;
			  Display_Buffer2[5] |= 0x01;
			  Display_Buffer2[15] |= 0x01;
			  Display_Buffer2[10] |= 0x01;
	}
		break;

	case 9:
	{
			  Display_Buffer2[15] |= 0x02;
			  Display_Buffer2[10] |= 0x02;
			  Display_Buffer2[5] |= 0x02;
			  Display_Buffer2[0] |= 0x02;
			  Display_Buffer2[5] &= 0xFE;
			  Display_Buffer2[15] |= 0x01;
			  Display_Buffer2[10] |= 0x01;
	}
		break;
	
	case 10://显示-
	{
				Display_Buffer2[15] &= 0xFD;
			  Display_Buffer2[10] &= 0xFD;
			  Display_Buffer2[5] &= 0xFD;
			  Display_Buffer2[0] &= 0xFD;
			  Display_Buffer2[5] &= 0xFE;
			  Display_Buffer2[15] &= 0xFE;
			  Display_Buffer2[10] |= 0x01;
	}
		break;

	default:
	{
			   Display_Buffer2[15] &= 0xFD;
			   Display_Buffer2[10] &= 0xFD;
			   Display_Buffer2[5] &= 0xFD;
			   Display_Buffer2[0] &= 0xFD;
			   Display_Buffer2[5] &= 0xFE;
			   Display_Buffer2[15] &= 0xFE;
			   Display_Buffer2[10] &= 0xFE;
	}
		break;

	}
}

static void ShowBKInt2(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer2[1] |= 0x40;
			  Display_Buffer2[2] |= 0x01;
			  Display_Buffer2[2] |= 0x40;
			  Display_Buffer2[0] |= 0x01;
			  Display_Buffer2[1] |= 0x04;
			  Display_Buffer2[1] |= 0x10;
			  Display_Buffer2[2] &= 0xEF;
	}
		break;

	case 1:
	{
			  Display_Buffer2[1] &= 0xBF;
			  Display_Buffer2[2] |= 0x01;
			  Display_Buffer2[2] |= 0x40;
			  Display_Buffer2[0] &= 0xFE;
			  Display_Buffer2[1] &= 0xFB;
			  Display_Buffer2[1] &= 0xEF;
			  Display_Buffer2[2] &= 0xEF;
	}
		break;

	case 2:
	{
			  Display_Buffer2[1] |= 0x40;
			  Display_Buffer2[2] |= 0x01;
			  Display_Buffer2[2] &= 0xBF;
			  Display_Buffer2[0] |= 0x01;
			  Display_Buffer2[1] |= 0x04;
			  Display_Buffer2[1] &= 0xEF;
			  Display_Buffer2[2] |= 0x10;
	}
		break;

	case 3:
	{
			  Display_Buffer2[1] |= 0x40;
			  Display_Buffer2[2] |= 0x01;
			  Display_Buffer2[2] |= 0x40;
			  Display_Buffer2[0] |= 0x01;
			  Display_Buffer2[1] &= 0xFB;
			  Display_Buffer2[1] &= 0xEF;
			  Display_Buffer2[2] |= 0x10;
	}
		break;

	case 4:
	{
			  Display_Buffer2[1] &= 0xBF;
			  Display_Buffer2[2] |= 0x01;
			  Display_Buffer2[2] |= 0x40;
			  Display_Buffer2[0] &= 0xFE;
			  Display_Buffer2[1] &= 0xFB;
			  Display_Buffer2[1] |= 0x10;
			  Display_Buffer2[2] |= 0x10;
	}
		break;

	case 5:
	{
			  Display_Buffer2[1] |= 0x40;
			  Display_Buffer2[2] &= 0xFE;
			  Display_Buffer2[2] |= 0x40;
			  Display_Buffer2[0] |= 0x01;
			  Display_Buffer2[1] &= 0xFB;
			  Display_Buffer2[1] |= 0x10;
			  Display_Buffer2[2] |= 0x10;
	}
		break;

	case 6:
	{
			  Display_Buffer2[1] |= 0x40;
			  Display_Buffer2[2] &= 0xFE;
			  Display_Buffer2[2] |= 0x40;
			  Display_Buffer2[0] |= 0x01;
			  Display_Buffer2[1] |= 0x04;
			  Display_Buffer2[1] |= 0x10;
			  Display_Buffer2[2] |= 0x10;
	}
		break;

	case 7:
	{
			  Display_Buffer2[1] |= 0x40;
			  Display_Buffer2[2] |= 0x01;
			  Display_Buffer2[2] |= 0x40;
			  Display_Buffer2[0] &= 0xFE;
			  Display_Buffer2[1] &= 0xFB;
			  Display_Buffer2[1] &= 0xEF;
			  Display_Buffer2[2] &= 0xEF;
	}
		break;

	case 8:
	{
			  Display_Buffer2[1] |= 0x40;
			  Display_Buffer2[2] |= 0x01;
			  Display_Buffer2[2] |= 0x40;
			  Display_Buffer2[0] |= 0x01;
			  Display_Buffer2[1] |= 0x04;
			  Display_Buffer2[1] |= 0x10;
			  Display_Buffer2[2] |= 0x10;
	}
		break;

	case 9:
	{
			  Display_Buffer2[1] |= 0x40;
			  Display_Buffer2[2] |= 0x01;
			  Display_Buffer2[2] |= 0x40;
			  Display_Buffer2[0] |= 0x01;
			  Display_Buffer2[1] &= 0xFB;
			  Display_Buffer2[1] |= 0x10;
			  Display_Buffer2[2] |= 0x10;
	}
		break;

	case 10://显示-
	{
			   Display_Buffer2[1] &= 0xBF;
			   Display_Buffer2[2] &= 0xFE;
			   Display_Buffer2[2] &= 0xBF;
			   Display_Buffer2[0] &= 0xFE;
			   Display_Buffer2[1] &= 0xFB;
			   Display_Buffer2[1] &= 0xEF;
			   Display_Buffer2[2] |= 0x10;
	}
		break;
	
	default:
	{
			   Display_Buffer2[1] &= 0xBF;
			   Display_Buffer2[2] &= 0xFE;
			   Display_Buffer2[2] &= 0xBF;
			   Display_Buffer2[0] &= 0xFE;
			   Display_Buffer2[1] &= 0xFB;
			   Display_Buffer2[1] &= 0xEF;
			   Display_Buffer2[2] &= 0xEF;
	}
		break;

	}
}

static void ShowBKInt3(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[4] |= 0x08;
			  Display_Buffer1[4] |= 0x02;
			  Display_Buffer1[3] |= 0x20;
			  Display_Buffer1[3] |= 0x08;
			  Display_Buffer1[2] |= 0x80;
			  Display_Buffer1[1] |= 0x04;
			  Display_Buffer1[3] &= 0x7F;
	}
		break;

	case 1:
	{
			  Display_Buffer1[4] &= 0xF7;
			  Display_Buffer1[4] |= 0x02;
			  Display_Buffer1[3] |= 0x20;
			  Display_Buffer1[3] &= 0xF7;
			  Display_Buffer1[2] &= 0x7F;
			  Display_Buffer1[1] &= 0xFB;
			  Display_Buffer1[3] &= 0x7F;
	}
		break;

	case 2:
	{
			  Display_Buffer1[4] |= 0x08;
			  Display_Buffer1[4] |= 0x02;
			  Display_Buffer1[3] &= 0xDF;
			  Display_Buffer1[3] |= 0x08;
			  Display_Buffer1[2] |= 0x80;
			  Display_Buffer1[1] &= 0xFB;
			  Display_Buffer1[3] |= 0x80;
	}
		break;

	case 3:
	{
			  Display_Buffer1[4] |= 0x08;
			  Display_Buffer1[4] |= 0x02;
			  Display_Buffer1[3] |= 0x20;
			  Display_Buffer1[3] |= 0x08;
			  Display_Buffer1[2] &= 0x7F;
			  Display_Buffer1[1] &= 0xFB;
			  Display_Buffer1[3] |= 0x80;
	}
		break;

	case 4:
	{
			  Display_Buffer1[4] &= 0xF7;
			  Display_Buffer1[4] |= 0x02;
			  Display_Buffer1[3] |= 0x20;
			  Display_Buffer1[3] &= 0xF7;
			  Display_Buffer1[2] &= 0x7F;
			  Display_Buffer1[1] |= 0x04;
			  Display_Buffer1[3] |= 0x80;
	}
		break;

	case 5:
	{
			  Display_Buffer1[4] |= 0x08;
			  Display_Buffer1[4] &= 0xFD;
			  Display_Buffer1[3] |= 0x20;
			  Display_Buffer1[3] |= 0x08;
			  Display_Buffer1[2] &= 0x7F;
			  Display_Buffer1[1] |= 0x04;
			  Display_Buffer1[3] |= 0x80;
	}
		break;

	case 6:
	{
			  Display_Buffer1[4] |= 0x08;
			  Display_Buffer1[4] &= 0xFD;
			  Display_Buffer1[3] |= 0x20;
			  Display_Buffer1[3] |= 0x08;
			  Display_Buffer1[2] |= 0x80;
			  Display_Buffer1[1] |= 0x04;
			  Display_Buffer1[3] |= 0x80;
	}
		break;

	case 7:
	{
			  Display_Buffer1[4] |= 0x08;
			  Display_Buffer1[4] |= 0x02;
			  Display_Buffer1[3] |= 0x20;
			  Display_Buffer1[3] &= 0xF7;
			  Display_Buffer1[2] &= 0x7F;
			  Display_Buffer1[1] &= 0xFB;
			  Display_Buffer1[3] &= 0x7F;
	}
		break;

	case 8:
	{
			  Display_Buffer1[4] |= 0x08;
			  Display_Buffer1[4] |= 0x02;
			  Display_Buffer1[3] |= 0x20;
			  Display_Buffer1[3] |= 0x08;
			  Display_Buffer1[2] |= 0x80;
			  Display_Buffer1[1] |= 0x04;
			  Display_Buffer1[3] |= 0x80;
	}
		break;

	case 9:
	{
			  Display_Buffer1[4] |= 0x08;
			  Display_Buffer1[4] |= 0x02;
			  Display_Buffer1[3] |= 0x20;
			  Display_Buffer1[3] |= 0x08;
			  Display_Buffer1[2] &= 0x7F;
			  Display_Buffer1[1] |= 0x04;
			  Display_Buffer1[3] |= 0x80;
	}
		break;
	
	case 10:
	{
			   Display_Buffer1[4] &= 0xF7;
			   Display_Buffer1[4] &= 0xFD;
			   Display_Buffer1[3] &= 0xDF;
			   Display_Buffer1[3] &= 0xF7;
			   Display_Buffer1[2] &= 0x7F;
			   Display_Buffer1[1] &= 0xFB;
			   Display_Buffer1[3] |= 0x80;
	}
		break;

	default:
	{
			   Display_Buffer1[4] &= 0xF7;
			   Display_Buffer1[4] &= 0xFD;
			   Display_Buffer1[3] &= 0xDF;
			   Display_Buffer1[3] &= 0xF7;
			   Display_Buffer1[2] &= 0x7F;
			   Display_Buffer1[1] &= 0xFB;
			   Display_Buffer1[3] &= 0x7F;
	}
		break;

	}
}

static void ShowBKInt4(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[19] |= 0x04;
			  Display_Buffer1[14] |= 0x04;
			  Display_Buffer1[9] |= 0x04;
			  Display_Buffer1[4] |= 0x04;
			  Display_Buffer1[9] |= 0x08;
			  Display_Buffer1[19] |= 0x08;
			  Display_Buffer1[14] &= 0xF7;
	}
		break;

	case 1:
	{
			  Display_Buffer1[19] &= 0xFB;
			  Display_Buffer1[14] |= 0x04;
			  Display_Buffer1[9] |= 0x04;
			  Display_Buffer1[4] &= 0xFB;
			  Display_Buffer1[9] &= 0xF7;
			  Display_Buffer1[19] &= 0xF7;
			  Display_Buffer1[14] &= 0xF7;
	}
		break;

	case 2:
	{
			  Display_Buffer1[19] |= 0x04;
			  Display_Buffer1[14] |= 0x04;
			  Display_Buffer1[9] &= 0xFB;
			  Display_Buffer1[4] |= 0x04;
			  Display_Buffer1[9] |= 0x08;
			  Display_Buffer1[19] &= 0xF7;
			  Display_Buffer1[14] |= 0x08;
	}
		break;

	case 3:
	{
			  Display_Buffer1[19] |= 0x04;
			  Display_Buffer1[14] |= 0x04;
			  Display_Buffer1[9] |= 0x04;
			  Display_Buffer1[4] |= 0x04;
			  Display_Buffer1[9] &= 0xF7;
			  Display_Buffer1[19] &= 0xF7;
			  Display_Buffer1[14] |= 0x08;
	}
		break;

	case 4:
	{
			  Display_Buffer1[19] &= 0xFB;
			  Display_Buffer1[14] |= 0x04;
			  Display_Buffer1[9] |= 0x04;
			  Display_Buffer1[4] &= 0xFB;
			  Display_Buffer1[9] &= 0xF7;
			  Display_Buffer1[19] |= 0x08;
			  Display_Buffer1[14] |= 0x08;
	}
		break;

	case 5:
	{
			  Display_Buffer1[19] |= 0x04;
			  Display_Buffer1[14] &= 0xFB;
			  Display_Buffer1[9] |= 0x04;
			  Display_Buffer1[4] |= 0x04;
			  Display_Buffer1[9] &= 0xF7;
			  Display_Buffer1[19] |= 0x08;
			  Display_Buffer1[14] |= 0x08;
	}
		break;

	case 6:
	{
			  Display_Buffer1[19] |= 0x04;
			  Display_Buffer1[14] &= 0xFB;
			  Display_Buffer1[9] |= 0x04;
			  Display_Buffer1[4] |= 0x04;
			  Display_Buffer1[9] |= 0x08;
			  Display_Buffer1[19] |= 0x08;
			  Display_Buffer1[14] |= 0x08;
	}
		break;

	case 7:
	{
			  Display_Buffer1[19] |= 0x04;
			  Display_Buffer1[14] |= 0x04;
			  Display_Buffer1[9] |= 0x04;
			  Display_Buffer1[4] &= 0xFB;
			  Display_Buffer1[9] &= 0xF7;
			  Display_Buffer1[19] &= 0xF7;
			  Display_Buffer1[14] &= 0xF7;
	}
		break;

	case 8:
	{
			  Display_Buffer1[19] |= 0x04;
			  Display_Buffer1[14] |= 0x04;
			  Display_Buffer1[9] |= 0x04;
			  Display_Buffer1[4] |= 0x04;
			  Display_Buffer1[9] |= 0x08;
			  Display_Buffer1[19] |= 0x08;
			  Display_Buffer1[14] |= 0x08;
	}
		break;

	case 9:
	{
			  Display_Buffer1[19] |= 0x04;
			  Display_Buffer1[14] |= 0x04;
			  Display_Buffer1[9] |= 0x04;
			  Display_Buffer1[4] |= 0x04;
			  Display_Buffer1[9] &= 0xF7;
			  Display_Buffer1[19] |= 0x08;
			  Display_Buffer1[14] |= 0x08;
	}
		break;
	
	case 10:
	{
			   Display_Buffer1[19] &= 0xFB;
			   Display_Buffer1[14] &= 0xFB;
			   Display_Buffer1[9] &= 0xFB;
			   Display_Buffer1[4] &= 0xFB;
			   Display_Buffer1[9] &= 0xF7;
			   Display_Buffer1[19] &= 0xF7;
			   Display_Buffer1[14] |= 0x08;
	}
		break;

	default:
	{
			   Display_Buffer1[19] &= 0xFB;
			   Display_Buffer1[14] &= 0xFB;
			   Display_Buffer1[9] &= 0xFB;
			   Display_Buffer1[4] &= 0xFB;
			   Display_Buffer1[9] &= 0xF7;
			   Display_Buffer1[19] &= 0xF7;
			   Display_Buffer1[14] &= 0xF7;
	}
		break;

	}
}

static void ShowBKInt5(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[19] |= 0x01;
			  Display_Buffer1[14] |= 0x01;
			  Display_Buffer1[9] |= 0x01;
			  Display_Buffer1[4] |= 0x01;
			  Display_Buffer1[9] |= 0x02;
			  Display_Buffer1[19] |= 0x02;
			  Display_Buffer1[14] &= 0xFD;
	}
		break;

	case 1:
	{
			  Display_Buffer1[19] &= 0xFE;
			  Display_Buffer1[14] |= 0x01;
			  Display_Buffer1[9] |= 0x01;
			  Display_Buffer1[4] &= 0xFE;
			  Display_Buffer1[9] &= 0xFD;
			  Display_Buffer1[19] &= 0xFD;
			  Display_Buffer1[14] &= 0xFD;
	}
		break;

	case 2:
	{
			  Display_Buffer1[19] |= 0x01;
			  Display_Buffer1[14] |= 0x01;
			  Display_Buffer1[9] &= 0xFE;
			  Display_Buffer1[4] |= 0x01;
			  Display_Buffer1[9] |= 0x02;
			  Display_Buffer1[19] &= 0xFD;
			  Display_Buffer1[14] |= 0x02;
	}
		break;

	case 3:
	{
			  Display_Buffer1[19] |= 0x01;
			  Display_Buffer1[14] |= 0x01;
			  Display_Buffer1[9] |= 0x01;
			  Display_Buffer1[4] |= 0x01;
			  Display_Buffer1[9] &= 0xFD;
			  Display_Buffer1[19] &= 0xFD;
			  Display_Buffer1[14] |= 0x02;
	}
		break;

	case 4:
	{
			  Display_Buffer1[19] &= 0xFE;
			  Display_Buffer1[14] |= 0x01;
			  Display_Buffer1[9] |= 0x01;
			  Display_Buffer1[4] &= 0xFE;
			  Display_Buffer1[9] &= 0xFD;
			  Display_Buffer1[19] |= 0x02;
			  Display_Buffer1[14] |= 0x02;
	}
		break;

	case 5:
	{
			  Display_Buffer1[19] |= 0x01;
			  Display_Buffer1[14] &= 0xFE;
			  Display_Buffer1[9] |= 0x01;
			  Display_Buffer1[4] |= 0x01;
			  Display_Buffer1[9] &= 0xFD;
			  Display_Buffer1[19] |= 0x02;
			  Display_Buffer1[14] |= 0x02;
	}
		break;

	case 6:
	{
			  Display_Buffer1[19] |= 0x01;
			  Display_Buffer1[14] &= 0xFE;
			  Display_Buffer1[9] |= 0x01;
			  Display_Buffer1[4] |= 0x01;
			  Display_Buffer1[9] |= 0x02;
			  Display_Buffer1[19] |= 0x02;
			  Display_Buffer1[14] |= 0x02;
	}
		break;

	case 7:
	{
			  Display_Buffer1[19] |= 0x01;
			  Display_Buffer1[14] |= 0x01;
			  Display_Buffer1[9] |= 0x01;
			  Display_Buffer1[4] &= 0xFE;
			  Display_Buffer1[9] &= 0xFD;
			  Display_Buffer1[19] &= 0xFD;
			  Display_Buffer1[14] &= 0xFD;
	}
		break;

	case 8:
	{
			  Display_Buffer1[19] |= 0x01;
			  Display_Buffer1[14] |= 0x01;
			  Display_Buffer1[9] |= 0x01;
			  Display_Buffer1[4] |= 0x01;
			  Display_Buffer1[9] |= 0x02;
			  Display_Buffer1[19] |= 0x02;
			  Display_Buffer1[14] |= 0x02;
	}
		break;

	case 9:
	{
			  Display_Buffer1[19] |= 0x01;
			  Display_Buffer1[14] |= 0x01;
			  Display_Buffer1[9] |= 0x01;
			  Display_Buffer1[4] |= 0x01;
			  Display_Buffer1[9] &= 0xFD;
			  Display_Buffer1[19] |= 0x02;
			  Display_Buffer1[14] |= 0x02;
	}
		break;
	
	case 10:
	{
			   Display_Buffer1[19] &= 0xFE;
			   Display_Buffer1[14] &= 0xFE;
			   Display_Buffer1[9] &= 0xFE;
			   Display_Buffer1[4] &= 0xFE;
			   Display_Buffer1[9] &= 0xFD;
			   Display_Buffer1[19] &= 0xFD;
			   Display_Buffer1[14] |= 0x02;
	}
		break;

	default:
	{
			   Display_Buffer1[19] &= 0xFE;
			   Display_Buffer1[14] &= 0xFE;
			   Display_Buffer1[9] &= 0xFE;
			   Display_Buffer1[4] &= 0xFE;
			   Display_Buffer1[9] &= 0xFD;
			   Display_Buffer1[19] &= 0xFD;
			   Display_Buffer1[14] &= 0xFD;
	}
		break;

	}
}

static void ShowBKInt6(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[18] |= 0x40;
			  Display_Buffer1[13] |= 0x40;
			  Display_Buffer1[8] |= 0x40;
			  Display_Buffer1[3] |= 0x40;
			  Display_Buffer1[8] |= 0x80;
			  Display_Buffer1[18] |= 0x80;
			  Display_Buffer1[13] &= 0x7F;
	}
		break;

	case 1:
	{
			  Display_Buffer1[18] &= 0xBF;
			  Display_Buffer1[13] |= 0x40;
			  Display_Buffer1[8] |= 0x40;
			  Display_Buffer1[3] &= 0xBF;
			  Display_Buffer1[8] &= 0x7F;
			  Display_Buffer1[18] &= 0x7F;
			  Display_Buffer1[13] &= 0x7F;
	}
		break;

	case 2:
	{
			  Display_Buffer1[18] |= 0x40;
			  Display_Buffer1[13] |= 0x40;
			  Display_Buffer1[8] &= 0xBF;
			  Display_Buffer1[3] |= 0x40;
			  Display_Buffer1[8] |= 0x80;
			  Display_Buffer1[18] &= 0x7F;
			  Display_Buffer1[13] |= 0x80;
	}
		break;

	case 3:
	{
			  Display_Buffer1[18] |= 0x40;
			  Display_Buffer1[13] |= 0x40;
			  Display_Buffer1[8] |= 0x40;
			  Display_Buffer1[3] |= 0x40;
			  Display_Buffer1[8] &= 0x7F;
			  Display_Buffer1[18] &= 0x7F;
			  Display_Buffer1[13] |= 0x80;
	}
		break;

	case 4:
	{
			  Display_Buffer1[18] &= 0xBF;
			  Display_Buffer1[13] |= 0x40;
			  Display_Buffer1[8] |= 0x40;
			  Display_Buffer1[3] &= 0xBF;
			  Display_Buffer1[8] &= 0x7F;
			  Display_Buffer1[18] |= 0x80;
			  Display_Buffer1[13] |= 0x80;
	}
		break;

	case 5:
	{
			  Display_Buffer1[18] |= 0x40;
			  Display_Buffer1[13] &= 0xBF;
			  Display_Buffer1[8] |= 0x40;
			  Display_Buffer1[3] |= 0x40;
			  Display_Buffer1[8] &= 0x7F;
			  Display_Buffer1[18] |= 0x80;
			  Display_Buffer1[13] |= 0x80;
	}
		break;

	case 6:
	{
			  Display_Buffer1[18] |= 0x40;
			  Display_Buffer1[13] &= 0xBF;
			  Display_Buffer1[8] |= 0x40;
			  Display_Buffer1[3] |= 0x40;
			  Display_Buffer1[8] |= 0x80;
			  Display_Buffer1[18] |= 0x80;
			  Display_Buffer1[13] |= 0x80;
	}
		break;

	case 7:
	{
			  Display_Buffer1[18] |= 0x40;
			  Display_Buffer1[13] |= 0x40;
			  Display_Buffer1[8] |= 0x40;
			  Display_Buffer1[3] &= 0xBF;
			  Display_Buffer1[8] &= 0x7F;
			  Display_Buffer1[18] &= 0x7F;
			  Display_Buffer1[13] &= 0x7F;
	}
		break;

	case 8:
	{
			  Display_Buffer1[18] |= 0x40;
			  Display_Buffer1[13] |= 0x40;
			  Display_Buffer1[8] |= 0x40;
			  Display_Buffer1[3] |= 0x40;
			  Display_Buffer1[8] |= 0x80;
			  Display_Buffer1[18] |= 0x80;
			  Display_Buffer1[13] |= 0x80;
	}
		break;

	case 9:
	{
			  Display_Buffer1[18] |= 0x40;
			  Display_Buffer1[13] |= 0x40;
			  Display_Buffer1[8] |= 0x40;
			  Display_Buffer1[3] |= 0x40;
			  Display_Buffer1[8] &= 0x7F;
			  Display_Buffer1[18] |= 0x80;
			  Display_Buffer1[13] |= 0x80;
	}
		break;
	
	case 10:
	{
			   Display_Buffer1[18] &= 0xBF;
			   Display_Buffer1[13] &= 0xBF;
			   Display_Buffer1[8] &= 0xBF;
			   Display_Buffer1[3] &= 0xBF;
			   Display_Buffer1[8] &= 0x7F;
			   Display_Buffer1[18] &= 0x7F;
			   Display_Buffer1[13] |= 0x80;
	}
		break;

	default:
	{
			   Display_Buffer1[18] &= 0xBF;
			   Display_Buffer1[13] &= 0xBF;
			   Display_Buffer1[8] &= 0xBF;
			   Display_Buffer1[3] &= 0xBF;
			   Display_Buffer1[8] &= 0x7F;
			   Display_Buffer1[18] &= 0x7F;
			   Display_Buffer1[13] &= 0x7F;
	}
		break;

	}
}

static void ShowBKInt7(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[18] |= 0x10;
			  Display_Buffer1[13] |= 0x10;
			  Display_Buffer1[8] |= 0x10;
			  Display_Buffer1[3] |= 0x10;
			  Display_Buffer1[8] |= 0x20;
			  Display_Buffer1[18] |= 0x20;
			  Display_Buffer1[13] &= 0xDF;
	}
		break;

	case 1:
	{
			  Display_Buffer1[18] &= 0xEF;
			  Display_Buffer1[13] |= 0x10;
			  Display_Buffer1[8] |= 0x10;
			  Display_Buffer1[3] &= 0xEF;
			  Display_Buffer1[8] &= 0xDF;
			  Display_Buffer1[18] &= 0xDF;
			  Display_Buffer1[13] &= 0xDF;
	}
		break;

	case 2:
	{
			  Display_Buffer1[18] |= 0x10;
			  Display_Buffer1[13] |= 0x10;
			  Display_Buffer1[8] &= 0xEF;
			  Display_Buffer1[3] |= 0x10;
			  Display_Buffer1[8] |= 0x20;
			  Display_Buffer1[18] &= 0xDF;
			  Display_Buffer1[13] |= 0x20;
	}
		break;

	case 3:
	{
			  Display_Buffer1[18] |= 0x10;
			  Display_Buffer1[13] |= 0x10;
			  Display_Buffer1[8] |= 0x10;
			  Display_Buffer1[3] |= 0x10;
			  Display_Buffer1[8] &= 0xDF;
			  Display_Buffer1[18] &= 0xDF;
			  Display_Buffer1[13] |= 0x20;
	}
		break;

	case 4:
	{
			  Display_Buffer1[18] &= 0xEF;
			  Display_Buffer1[13] |= 0x10;
			  Display_Buffer1[8] |= 0x10;
			  Display_Buffer1[3] &= 0xEF;
			  Display_Buffer1[8] &= 0xDF;
			  Display_Buffer1[18] |= 0x20;
			  Display_Buffer1[13] |= 0x20;
	}
		break;

	case 5:
	{
			  Display_Buffer1[18] |= 0x10;
			  Display_Buffer1[13] &= 0xEF;
			  Display_Buffer1[8] |= 0x10;
			  Display_Buffer1[3] |= 0x10;
			  Display_Buffer1[8] &= 0xDF;
			  Display_Buffer1[18] |= 0x20;
			  Display_Buffer1[13] |= 0x20;
	}
		break;

	case 6:
	{
			  Display_Buffer1[18] |= 0x10;
			  Display_Buffer1[13] &= 0xEF;
			  Display_Buffer1[8] |= 0x10;
			  Display_Buffer1[3] |= 0x10;
			  Display_Buffer1[8] |= 0x20;
			  Display_Buffer1[18] |= 0x20;
			  Display_Buffer1[13] |= 0x20;
	}
		break;

	case 7:
	{
			  Display_Buffer1[18] |= 0x10;
			  Display_Buffer1[13] |= 0x10;
			  Display_Buffer1[8] |= 0x10;
			  Display_Buffer1[3] &= 0xEF;
			  Display_Buffer1[8] &= 0xDF;
			  Display_Buffer1[18] &= 0xDF;
			  Display_Buffer1[13] &= 0xDF;
	}
		break;

	case 8:
	{
			  Display_Buffer1[18] |= 0x10;
			  Display_Buffer1[13] |= 0x10;
			  Display_Buffer1[8] |= 0x10;
			  Display_Buffer1[3] |= 0x10;
			  Display_Buffer1[8] |= 0x20;
			  Display_Buffer1[18] |= 0x20;
			  Display_Buffer1[13] |= 0x20;
	}
		break;

	case 9:
	{
			  Display_Buffer1[18] |= 0x10;
			  Display_Buffer1[13] |= 0x10;
			  Display_Buffer1[8] |= 0x10;
			  Display_Buffer1[3] |= 0x10;
			  Display_Buffer1[8] &= 0xDF;
			  Display_Buffer1[18] |= 0x20;
			  Display_Buffer1[13] |= 0x20;
	}
		break;
	
	case 10:
	{
			   Display_Buffer1[18] &= 0xEF;
			   Display_Buffer1[13] &= 0xEF;
			   Display_Buffer1[8] &= 0xEF;
			   Display_Buffer1[3] &= 0xEF;
			   Display_Buffer1[8] &= 0xDF;
			   Display_Buffer1[18] &= 0xDF;
			   Display_Buffer1[13] |= 0x20;
	}
		break;

	default:
	{
			   Display_Buffer1[18] &= 0xEF;
			   Display_Buffer1[13] &= 0xEF;
			   Display_Buffer1[8] &= 0xEF;
			   Display_Buffer1[3] &= 0xEF;
			   Display_Buffer1[8] &= 0xDF;
			   Display_Buffer1[18] &= 0xDF;
			   Display_Buffer1[13] &= 0xDF;
	}
		break;

	}

}

static void ShowBKInt8(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[18] |= 0x04;
			  Display_Buffer1[13] |= 0x04;
			  Display_Buffer1[8] |= 0x04;
			  Display_Buffer1[3] |= 0x04;
			  Display_Buffer1[8] |= 0x08;
			  Display_Buffer1[18] |= 0x08;
			  Display_Buffer1[13] &= 0xF7;
	}
		break;

	case 1:
	{
			  Display_Buffer1[18] &= 0xFB;
			  Display_Buffer1[13] |= 0x04;
			  Display_Buffer1[8] |= 0x04;
			  Display_Buffer1[3] &= 0xFB;
			  Display_Buffer1[8] &= 0xF7;
			  Display_Buffer1[18] &= 0xF7;
			  Display_Buffer1[13] &= 0xF7;
	}
		break;

	case 2:
	{
			  Display_Buffer1[18] |= 0x04;
			  Display_Buffer1[13] |= 0x04;
			  Display_Buffer1[8] &= 0xFB;
			  Display_Buffer1[3] |= 0x04;
			  Display_Buffer1[8] |= 0x08;
			  Display_Buffer1[18] &= 0xF7;
			  Display_Buffer1[13] |= 0x08;
	}
		break;

	case 3:
	{
			  Display_Buffer1[18] |= 0x04;
			  Display_Buffer1[13] |= 0x04;
			  Display_Buffer1[8] |= 0x04;
			  Display_Buffer1[3] |= 0x04;
			  Display_Buffer1[8] &= 0xF7;
			  Display_Buffer1[18] &= 0xF7;
			  Display_Buffer1[13] |= 0x08;
	}
		break;

	case 4:
	{
			  Display_Buffer1[18] &= 0xFB;
			  Display_Buffer1[13] |= 0x04;
			  Display_Buffer1[8] |= 0x04;
			  Display_Buffer1[3] &= 0xFB;
			  Display_Buffer1[8] &= 0xF7;
			  Display_Buffer1[18] |= 0x08;
			  Display_Buffer1[13] |= 0x08;
	}
		break;

	case 5:
	{
			  Display_Buffer1[18] |= 0x04;
			  Display_Buffer1[13] &= 0xFB;
			  Display_Buffer1[8] |= 0x04;
			  Display_Buffer1[3] |= 0x04;
			  Display_Buffer1[8] &= 0xF7;
			  Display_Buffer1[18] |= 0x08;
			  Display_Buffer1[13] |= 0x08;
	}
		break;

	case 6:
	{
			  Display_Buffer1[18] |= 0x04;
			  Display_Buffer1[13] &= 0xFB;
			  Display_Buffer1[8] |= 0x04;
			  Display_Buffer1[3] |= 0x04;
			  Display_Buffer1[8] |= 0x08;
			  Display_Buffer1[18] |= 0x08;
			  Display_Buffer1[13] |= 0x08;
	}
		break;

	case 7:
	{
			  Display_Buffer1[18] |= 0x04;
			  Display_Buffer1[13] |= 0x04;
			  Display_Buffer1[8] |= 0x04;
			  Display_Buffer1[3] &= 0xFB;
			  Display_Buffer1[8] &= 0xF7;
			  Display_Buffer1[18] &= 0xF7;
			  Display_Buffer1[13] &= 0xF7;
	}
		break;

	case 8:
	{
			  Display_Buffer1[18] |= 0x04;
			  Display_Buffer1[13] |= 0x04;
			  Display_Buffer1[8] |= 0x04;
			  Display_Buffer1[3] |= 0x04;
			  Display_Buffer1[8] |= 0x08;
			  Display_Buffer1[18] |= 0x08;
			  Display_Buffer1[13] |= 0x08;
	}
		break;

	case 9:
	{
			  Display_Buffer1[18] |= 0x04;
			  Display_Buffer1[13] |= 0x04;
			  Display_Buffer1[8] |= 0x04;
			  Display_Buffer1[3] |= 0x04;
			  Display_Buffer1[8] &= 0xF7;
			  Display_Buffer1[18] |= 0x08;
			  Display_Buffer1[13] |= 0x08;
	}
		break;
	
	case 10:
	{
			   Display_Buffer1[18] &= 0xFB;
			   Display_Buffer1[13] &= 0xFB;
			   Display_Buffer1[8] &= 0xFB;
			   Display_Buffer1[3] &= 0xFB;
			   Display_Buffer1[8] &= 0xF7;
			   Display_Buffer1[18] &= 0xF7;
			   Display_Buffer1[13] |= 0x08;
	}
		break;

	default:
	{
			   Display_Buffer1[18] &= 0xFB;
			   Display_Buffer1[13] &= 0xFB;
			   Display_Buffer1[8] &= 0xFB;
			   Display_Buffer1[3] &= 0xFB;
			   Display_Buffer1[8] &= 0xF7;
			   Display_Buffer1[18] &= 0xF7;
			   Display_Buffer1[13] &= 0xF7;
	}
		break;

	}
}

static void ShowBKFloat1(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[18] |= 0x01;
			  Display_Buffer1[13] |= 0x01;
			  Display_Buffer1[8] |= 0x01;
			  Display_Buffer1[3] |= 0x01;
			  Display_Buffer1[8] |= 0x02;
			  Display_Buffer1[18] |= 0x02;
			  Display_Buffer1[13] &= 0xFD;
	}
		break;

	case 1:
	{
			  Display_Buffer1[18] &= 0xFE;
			  Display_Buffer1[13] |= 0x01;
			  Display_Buffer1[8] |= 0x01;
			  Display_Buffer1[3] &= 0xFE;
			  Display_Buffer1[8] &= 0xFD;
			  Display_Buffer1[18] &= 0xFD;
			  Display_Buffer1[13] &= 0xFD;
	}
		break;

	case 2:
	{
			  Display_Buffer1[18] |= 0x01;
			  Display_Buffer1[13] |= 0x01;
			  Display_Buffer1[8] &= 0xFE;
			  Display_Buffer1[3] |= 0x01;
			  Display_Buffer1[8] |= 0x02;
			  Display_Buffer1[18] &= 0xFD;
			  Display_Buffer1[13] |= 0x02;
	}
		break;

	case 3:
	{
			  Display_Buffer1[18] |= 0x01;
			  Display_Buffer1[13] |= 0x01;
			  Display_Buffer1[8] |= 0x01;
			  Display_Buffer1[3] |= 0x01;
			  Display_Buffer1[8] &= 0xFD;
			  Display_Buffer1[18] &= 0xFD;
			  Display_Buffer1[13] |= 0x02;
	}
		break;

	case 4:
	{
			  Display_Buffer1[18] &= 0xFE;
			  Display_Buffer1[13] |= 0x01;
			  Display_Buffer1[8] |= 0x01;
			  Display_Buffer1[3] &= 0xFE;
			  Display_Buffer1[8] &= 0xFD;
			  Display_Buffer1[18] |= 0x02;
			  Display_Buffer1[13] |= 0x02;
	}
		break;

	case 5:
	{
			  Display_Buffer1[18] |= 0x01;
			  Display_Buffer1[13] &= 0xFE;
			  Display_Buffer1[8] |= 0x01;
			  Display_Buffer1[3] |= 0x01;
			  Display_Buffer1[8] &= 0xFD;
			  Display_Buffer1[18] |= 0x02;
			  Display_Buffer1[13] |= 0x02;
	}
		break;

	case 6:
	{
			  Display_Buffer1[18] |= 0x01;
			  Display_Buffer1[13] &= 0xFE;
			  Display_Buffer1[8] |= 0x01;
			  Display_Buffer1[3] |= 0x01;
			  Display_Buffer1[8] |= 0x02;
			  Display_Buffer1[18] |= 0x02;
			  Display_Buffer1[13] |= 0x02;
	}
		break;

	case 7:
	{
			  Display_Buffer1[18] |= 0x01;
			  Display_Buffer1[13] |= 0x01;
			  Display_Buffer1[8] |= 0x01;
			  Display_Buffer1[3] &= 0xFE;
			  Display_Buffer1[8] &= 0xFD;
			  Display_Buffer1[18] &= 0xFD;
			  Display_Buffer1[13] &= 0xFD;
	}
		break;

	case 8:
	{
			  Display_Buffer1[18] |= 0x01;
			  Display_Buffer1[13] |= 0x01;
			  Display_Buffer1[8] |= 0x01;
			  Display_Buffer1[3] |= 0x01;
			  Display_Buffer1[8] |= 0x02;
			  Display_Buffer1[18] |= 0x02;
			  Display_Buffer1[13] |= 0x02;
	}
		break;

	case 9:
	{
			  Display_Buffer1[18] |= 0x01;
			  Display_Buffer1[13] |= 0x01;
			  Display_Buffer1[8] |= 0x01;
			  Display_Buffer1[3] |= 0x01;
			  Display_Buffer1[8] &= 0xFD;
			  Display_Buffer1[18] |= 0x02;
			  Display_Buffer1[13] |= 0x02;
	}
		break;

	default:
	{
			   Display_Buffer1[18] &= 0xFE;
			   Display_Buffer1[13] &= 0xFE;
			   Display_Buffer1[8] &= 0xFE;
			   Display_Buffer1[3] &= 0xFE;
			   Display_Buffer1[8] &= 0xFD;
			   Display_Buffer1[18] &= 0xFD;
			   Display_Buffer1[13] &= 0xFD;
	}
		break;

	}
}

static void ShowBKFloat2(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[17] |= 0x40;
			  Display_Buffer1[12] |= 0x40;
			  Display_Buffer1[7] |= 0x40;
			  Display_Buffer1[2] |= 0x40;
			  Display_Buffer1[7] |= 0x80;
			  Display_Buffer1[17] |= 0x80;
			  Display_Buffer1[12] &= 0x7F;
	}
		break;

	case 1:
	{
			  Display_Buffer1[17] &= 0xBF;
			  Display_Buffer1[12] |= 0x40;
			  Display_Buffer1[7] |= 0x40;
			  Display_Buffer1[2] &= 0xBF;
			  Display_Buffer1[7] &= 0x7F;
			  Display_Buffer1[17] &= 0x7F;
			  Display_Buffer1[12] &= 0x7F;
	}
		break;

	case 2:
	{
			  Display_Buffer1[17] |= 0x40;
			  Display_Buffer1[12] |= 0x40;
			  Display_Buffer1[7] &= 0xBF;
			  Display_Buffer1[2] |= 0x40;
			  Display_Buffer1[7] |= 0x80;
			  Display_Buffer1[17] &= 0x7F;
			  Display_Buffer1[12] |= 0x80;
	}
		break;

	case 3:
	{
			  Display_Buffer1[17] |= 0x40;
			  Display_Buffer1[12] |= 0x40;
			  Display_Buffer1[7] |= 0x40;
			  Display_Buffer1[2] |= 0x40;
			  Display_Buffer1[7] &= 0x7F;
			  Display_Buffer1[17] &= 0x7F;
			  Display_Buffer1[12] |= 0x80;
	}
		break;

	case 4:
	{
			  Display_Buffer1[17] &= 0xBF;
			  Display_Buffer1[12] |= 0x40;
			  Display_Buffer1[7] |= 0x40;
			  Display_Buffer1[2] &= 0xBF;
			  Display_Buffer1[7] &= 0x7F;
			  Display_Buffer1[17] |= 0x80;
			  Display_Buffer1[12] |= 0x80;
	}
		break;

	case 5:
	{
			  Display_Buffer1[17] |= 0x40;
			  Display_Buffer1[12] &= 0xBF;
			  Display_Buffer1[7] |= 0x40;
			  Display_Buffer1[2] |= 0x40;
			  Display_Buffer1[7] &= 0x7F;
			  Display_Buffer1[17] |= 0x80;
			  Display_Buffer1[12] |= 0x80;
	}
		break;

	case 6:
	{
			  Display_Buffer1[17] |= 0x40;
			  Display_Buffer1[12] &= 0xBF;
			  Display_Buffer1[7] |= 0x40;
			  Display_Buffer1[2] |= 0x40;
			  Display_Buffer1[7] |= 0x80;
			  Display_Buffer1[17] |= 0x80;
			  Display_Buffer1[12] |= 0x80;
	}
		break;

	case 7:
	{
			  Display_Buffer1[17] |= 0x40;
			  Display_Buffer1[12] |= 0x40;
			  Display_Buffer1[7] |= 0x40;
			  Display_Buffer1[2] &= 0xBF;
			  Display_Buffer1[7] &= 0x7F;
			  Display_Buffer1[17] &= 0x7F;
			  Display_Buffer1[12] &= 0x7F;
	}
		break;

	case 8:
	{
			  Display_Buffer1[17] |= 0x40;
			  Display_Buffer1[12] |= 0x40;
			  Display_Buffer1[7] |= 0x40;
			  Display_Buffer1[2] |= 0x40;
			  Display_Buffer1[7] |= 0x80;
			  Display_Buffer1[17] |= 0x80;
			  Display_Buffer1[12] |= 0x80;
	}
		break;

	case 9:
	{
			  Display_Buffer1[17] |= 0x40;
			  Display_Buffer1[12] |= 0x40;
			  Display_Buffer1[7] |= 0x40;
			  Display_Buffer1[2] |= 0x40;
			  Display_Buffer1[7] &= 0x7F;
			  Display_Buffer1[17] |= 0x80;
			  Display_Buffer1[12] |= 0x80;
	}
		break;

	default:
	{
			   Display_Buffer1[17] &= 0xBF;
			   Display_Buffer1[12] &= 0xBF;
			   Display_Buffer1[7] &= 0xBF;
			   Display_Buffer1[2] &= 0xBF;
			   Display_Buffer1[7] &= 0x7F;
			   Display_Buffer1[17] &= 0x7F;
			   Display_Buffer1[12] &= 0x7F;
	}
		break;

	}
}

static void ShowBKFloat3(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[17] |= 0x10;
			  Display_Buffer1[12] |= 0x10;
			  Display_Buffer1[7] |= 0x10;
			  Display_Buffer1[2] |= 0x10;
			  Display_Buffer1[7] |= 0x20;
			  Display_Buffer1[17] |= 0x20;
			  Display_Buffer1[12] &= 0xDF;
	}
		break;

	case 1:
	{
			  Display_Buffer1[17] &= 0xEF;
			  Display_Buffer1[12] |= 0x10;
			  Display_Buffer1[7] |= 0x10;
			  Display_Buffer1[2] &= 0xEF;
			  Display_Buffer1[7] &= 0xDF;
			  Display_Buffer1[17] &= 0xDF;
			  Display_Buffer1[12] &= 0xDF;
	}
		break;

	case 2:
	{
			  Display_Buffer1[17] |= 0x10;
			  Display_Buffer1[12] |= 0x10;
			  Display_Buffer1[7] &= 0xEF;
			  Display_Buffer1[2] |= 0x10;
			  Display_Buffer1[7] |= 0x20;
			  Display_Buffer1[17] &= 0xDF;
			  Display_Buffer1[12] |= 0x20;
	}
		break;

	case 3:
	{
			  Display_Buffer1[17] |= 0x10;
			  Display_Buffer1[12] |= 0x10;
			  Display_Buffer1[7] |= 0x10;
			  Display_Buffer1[2] |= 0x10;
			  Display_Buffer1[7] &= 0xDF;
			  Display_Buffer1[17] &= 0xDF;
			  Display_Buffer1[12] |= 0x20;
	}
		break;

	case 4:
	{
			  Display_Buffer1[17] &= 0xEF;
			  Display_Buffer1[12] |= 0x10;
			  Display_Buffer1[7] |= 0x10;
			  Display_Buffer1[2] &= 0xEF;
			  Display_Buffer1[7] &= 0xDF;
			  Display_Buffer1[17] |= 0x20;
			  Display_Buffer1[12] |= 0x20;
	}
		break;

	case 5:
	{
			  Display_Buffer1[17] |= 0x10;
			  Display_Buffer1[12] &= 0xEF;
			  Display_Buffer1[7] |= 0x10;
			  Display_Buffer1[2] |= 0x10;
			  Display_Buffer1[7] &= 0xDF;
			  Display_Buffer1[17] |= 0x20;
			  Display_Buffer1[12] |= 0x20;
	}
		break;

	case 6:
	{
			  Display_Buffer1[17] |= 0x10;
			  Display_Buffer1[12] &= 0xEF;
			  Display_Buffer1[7] |= 0x10;
			  Display_Buffer1[2] |= 0x10;
			  Display_Buffer1[7] |= 0x20;
			  Display_Buffer1[17] |= 0x20;
			  Display_Buffer1[12] |= 0x20;
	}
		break;

	case 7:
	{
			  Display_Buffer1[17] |= 0x10;
			  Display_Buffer1[12] |= 0x10;
			  Display_Buffer1[7] |= 0x10;
			  Display_Buffer1[2] &= 0xEF;
			  Display_Buffer1[7] &= 0xDF;
			  Display_Buffer1[17] &= 0xDF;
			  Display_Buffer1[12] &= 0xDF;
	}
		break;

	case 8:
	{
			  Display_Buffer1[17] |= 0x10;
			  Display_Buffer1[12] |= 0x10;
			  Display_Buffer1[7] |= 0x10;
			  Display_Buffer1[2] |= 0x10;
			  Display_Buffer1[7] |= 0x20;
			  Display_Buffer1[17] |= 0x20;
			  Display_Buffer1[12] |= 0x20;
	}
		break;

	case 9:
	{
			  Display_Buffer1[17] |= 0x10;
			  Display_Buffer1[12] |= 0x10;
			  Display_Buffer1[7] |= 0x10;
			  Display_Buffer1[2] |= 0x10;
			  Display_Buffer1[7] &= 0xDF;
			  Display_Buffer1[17] |= 0x20;
			  Display_Buffer1[12] |= 0x20;
	}
		break;

	default:
	{
			   Display_Buffer1[17] &= 0xEF;
			   Display_Buffer1[12] &= 0xEF;
			   Display_Buffer1[7] &= 0xEF;
			   Display_Buffer1[2] &= 0xEF;
			   Display_Buffer1[7] &= 0xDF;
			   Display_Buffer1[17] &= 0xDF;
			   Display_Buffer1[12] &= 0xDF;
	}
		break;

	}
}

static void ShowTmpInt2(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[0] |= 0x08;
			  Display_Buffer1[5] |= 0x08;
			  Display_Buffer1[10] |= 0x08;
			  Display_Buffer1[15] |= 0x08;
			  Display_Buffer1[15] |= 0x04;
			  Display_Buffer1[5] |= 0x04;
			  Display_Buffer1[10] &= 0xFB;
	}
		break;

	case 1:
	{
			  Display_Buffer1[0] &= 0xF7;
			  Display_Buffer1[5] |= 0x08;
			  Display_Buffer1[10] |= 0x08;
			  Display_Buffer1[15] &= 0xF7;
			  Display_Buffer1[15] &= 0xFB;
			  Display_Buffer1[5] &= 0xFB;
			  Display_Buffer1[10] &= 0xFB;
	}
		break;

	case 2:
	{
			  Display_Buffer1[0] |= 0x08;
			  Display_Buffer1[5] |= 0x08;
			  Display_Buffer1[10] &= 0xF7;
			  Display_Buffer1[15] |= 0x08;
			  Display_Buffer1[15] |= 0x04;
			  Display_Buffer1[5] &= 0xFB;
			  Display_Buffer1[10] |= 0x04;
	}
		break;

	case 3:
	{
			  Display_Buffer1[0] |= 0x08;
			  Display_Buffer1[5] |= 0x08;
			  Display_Buffer1[10] |= 0x08;
			  Display_Buffer1[15] |= 0x08;
			  Display_Buffer1[15] &= 0xFB;
			  Display_Buffer1[5] &= 0xFB;
			  Display_Buffer1[10] |= 0x04;
	}
		break;

	case 4:
	{
			  Display_Buffer1[0] &= 0xF7;
			  Display_Buffer1[5] |= 0x08;
			  Display_Buffer1[10] |= 0x08;
			  Display_Buffer1[15] &= 0xF7;
			  Display_Buffer1[15] &= 0xFB;
			  Display_Buffer1[5] |= 0x04;
			  Display_Buffer1[10] |= 0x04;
	}
		break;

	case 5:
	{
			  Display_Buffer1[0] |= 0x08;
			  Display_Buffer1[5] &= 0xF7;
			  Display_Buffer1[10] |= 0x08;
			  Display_Buffer1[15] |= 0x08;
			  Display_Buffer1[15] &= 0xFB;
			  Display_Buffer1[5] |= 0x04;
			  Display_Buffer1[10] |= 0x04;
	}
		break;

	case 6:
	{
			  Display_Buffer1[0] |= 0x08;
			  Display_Buffer1[5] &= 0xF7;
			  Display_Buffer1[10] |= 0x08;
			  Display_Buffer1[15] |= 0x08;
			  Display_Buffer1[15] |= 0x04;
			  Display_Buffer1[5] |= 0x04;
			  Display_Buffer1[10] |= 0x04;
	}
		break;

	case 7:
	{
			  Display_Buffer1[0] |= 0x08;
			  Display_Buffer1[5] |= 0x08;
			  Display_Buffer1[10] |= 0x08;
			  Display_Buffer1[15] &= 0xF7;
			  Display_Buffer1[15] &= 0xFB;
			  Display_Buffer1[5] &= 0xFB;
			  Display_Buffer1[10] &= 0xFB;
	}
		break;

	case 8:
	{
			  Display_Buffer1[0] |= 0x08;
			  Display_Buffer1[5] |= 0x08;
			  Display_Buffer1[10] |= 0x08;
			  Display_Buffer1[15] |= 0x08;
			  Display_Buffer1[15] |= 0x04;
			  Display_Buffer1[5] |= 0x04;
			  Display_Buffer1[10] |= 0x04;
	}
		break;

	case 9:
	{
			  Display_Buffer1[0] |= 0x08;
			  Display_Buffer1[5] |= 0x08;
			  Display_Buffer1[10] |= 0x08;
			  Display_Buffer1[15] |= 0x08;
			  Display_Buffer1[15] &= 0xFB;
			  Display_Buffer1[5] |= 0x04;
			  Display_Buffer1[10] |= 0x04;
	}
		break;

	default:
	{
			   Display_Buffer1[0] &= 0xF7;
			   Display_Buffer1[5] &= 0xF7;
			   Display_Buffer1[10] &= 0xF7;
			   Display_Buffer1[15] &= 0xF7;
			   Display_Buffer1[15] &= 0xFB;
			   Display_Buffer1[5] &= 0xFB;
			   Display_Buffer1[10] &= 0xFB;
	}
		break;

	}
}

static void ShowTmpInt1(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[0] |= 0x02;
			  Display_Buffer1[5] |= 0x02;
			  Display_Buffer1[10] |= 0x02;
			  Display_Buffer1[15] |= 0x02;
			  Display_Buffer1[15] |= 0x01;
			  Display_Buffer1[5] |= 0x01;
			  Display_Buffer1[10] &= 0xFE;
	}
		break;

	case 1:
	{
			  Display_Buffer1[0] &= 0xFD;
			  Display_Buffer1[5] |= 0x02;
			  Display_Buffer1[10] |= 0x02;
			  Display_Buffer1[15] &= 0xFD;
			  Display_Buffer1[15] &= 0xFE;
			  Display_Buffer1[5] &= 0xFE;
			  Display_Buffer1[10] &= 0xFE;
	}
		break;

	case 2:
	{
			  Display_Buffer1[0] |= 0x02;
			  Display_Buffer1[5] |= 0x02;
			  Display_Buffer1[10] &= 0xFD;
			  Display_Buffer1[15] |= 0x02;
			  Display_Buffer1[15] |= 0x01;
			  Display_Buffer1[5] &= 0xFE;
			  Display_Buffer1[10] |= 0x01;
	}
		break;

	case 3:
	{
			  Display_Buffer1[0] |= 0x02;
			  Display_Buffer1[5] |= 0x02;
			  Display_Buffer1[10] |= 0x02;
			  Display_Buffer1[15] |= 0x02;
			  Display_Buffer1[15] &= 0xFE;
			  Display_Buffer1[5] &= 0xFE;
			  Display_Buffer1[10] |= 0x01;
	}
		break;

	case 4:
	{
			  Display_Buffer1[0] &= 0xFD;
			  Display_Buffer1[5] |= 0x02;
			  Display_Buffer1[10] |= 0x02;
			  Display_Buffer1[15] &= 0xFD;
			  Display_Buffer1[15] &= 0xFE;
			  Display_Buffer1[5] |= 0x01;
			  Display_Buffer1[10] |= 0x01;
	}
		break;

	case 5:
	{
			  Display_Buffer1[0] |= 0x02;
			  Display_Buffer1[5] &= 0xFD;
			  Display_Buffer1[10] |= 0x02;
			  Display_Buffer1[15] |= 0x02;
			  Display_Buffer1[15] &= 0xFE;
			  Display_Buffer1[5] |= 0x01;
			  Display_Buffer1[10] |= 0x01;
	}
		break;

	case 6:
	{
			  Display_Buffer1[0] |= 0x02;
			  Display_Buffer1[5] &= 0xFD;
			  Display_Buffer1[10] |= 0x02;
			  Display_Buffer1[15] |= 0x02;
			  Display_Buffer1[15] |= 0x01;
			  Display_Buffer1[5] |= 0x01;
			  Display_Buffer1[10] |= 0x01;
	}
		break;

	case 7:
	{
			  Display_Buffer1[0] |= 0x02;
			  Display_Buffer1[5] |= 0x02;
			  Display_Buffer1[10] |= 0x02;
			  Display_Buffer1[15] &= 0xFD;
			  Display_Buffer1[15] &= 0xFE;
			  Display_Buffer1[5] &= 0xFE;
			  Display_Buffer1[10] &= 0xFE;
	}
		break;

	case 8:
	{
			  Display_Buffer1[0] |= 0x02;
			  Display_Buffer1[5] |= 0x02;
			  Display_Buffer1[10] |= 0x02;
			  Display_Buffer1[15] |= 0x02;
			  Display_Buffer1[15] |= 0x01;
			  Display_Buffer1[5] |= 0x01;
			  Display_Buffer1[10] |= 0x01;
	}
		break;

	case 9:
	{
			  Display_Buffer1[0] |= 0x02;
			  Display_Buffer1[5] |= 0x02;
			  Display_Buffer1[10] |= 0x02;
			  Display_Buffer1[15] |= 0x02;
			  Display_Buffer1[15] &= 0xFE;
			  Display_Buffer1[5] |= 0x01;
			  Display_Buffer1[10] |= 0x01;
	}
		break;

	default:
	{
			   Display_Buffer1[0] &= 0xFD;
			   Display_Buffer1[5] &= 0xFD;
			   Display_Buffer1[10] &= 0xFD;
			   Display_Buffer1[15] &= 0xFD;
			   Display_Buffer1[15] &= 0xFE;
			   Display_Buffer1[5] &= 0xFE;
			   Display_Buffer1[10] &= 0xFE;
	}
		break;

	}
}

static void ShowTmpFloat1(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[0] |= 0x20;
			  Display_Buffer1[5] |= 0x20;
			  Display_Buffer1[10] |= 0x20;
			  Display_Buffer1[15] |= 0x20;
			  Display_Buffer1[10] |= 0x10;
			  Display_Buffer1[0] |= 0x10;
			  Display_Buffer1[5] &= 0xEF;
	}
		break;

	case 1:
	{
			  Display_Buffer1[0] &= 0xDF;
			  Display_Buffer1[5] |= 0x20;
			  Display_Buffer1[10] |= 0x20;
			  Display_Buffer1[15] &= 0xDF;
			  Display_Buffer1[10] &= 0xEF;
			  Display_Buffer1[0] &= 0xEF;
			  Display_Buffer1[5] &= 0xEF;
	}
		break;

	case 2:
	{
			  Display_Buffer1[0] |= 0x20;
			  Display_Buffer1[5] |= 0x20;
			  Display_Buffer1[10] &= 0xDF;
			  Display_Buffer1[15] |= 0x20;
			  Display_Buffer1[10] |= 0x10;
			  Display_Buffer1[0] &= 0xEF;
			  Display_Buffer1[5] |= 0x10;
	}
		break;

	case 3:
	{
			  Display_Buffer1[0] |= 0x20;
			  Display_Buffer1[5] |= 0x20;
			  Display_Buffer1[10] |= 0x20;
			  Display_Buffer1[15] |= 0x20;
			  Display_Buffer1[10] &= 0xEF;
			  Display_Buffer1[0] &= 0xEF;
			  Display_Buffer1[5] |= 0x10;
	}
		break;

	case 4:
	{
			  Display_Buffer1[0] &= 0xDF;
			  Display_Buffer1[5] |= 0x20;
			  Display_Buffer1[10] |= 0x20;
			  Display_Buffer1[15] &= 0xDF;
			  Display_Buffer1[10] &= 0xEF;
			  Display_Buffer1[0] |= 0x10;
			  Display_Buffer1[5] |= 0x10;
	}
		break;

	case 5:
	{
			  Display_Buffer1[0] |= 0x20;
			  Display_Buffer1[5] &= 0xDF;
			  Display_Buffer1[10] |= 0x20;
			  Display_Buffer1[15] |= 0x20;
			  Display_Buffer1[10] &= 0xEF;
			  Display_Buffer1[0] |= 0x10;
			  Display_Buffer1[5] |= 0x10;
	}
		break;

	case 6:
	{
			  Display_Buffer1[0] |= 0x20;
			  Display_Buffer1[5] &= 0xDF;
			  Display_Buffer1[10] |= 0x20;
			  Display_Buffer1[15] |= 0x20;
			  Display_Buffer1[10] |= 0x10;
			  Display_Buffer1[0] |= 0x10;
			  Display_Buffer1[5] |= 0x10;
	}
		break;

	case 7:
	{
			  Display_Buffer1[0] |= 0x20;
			  Display_Buffer1[5] |= 0x20;
			  Display_Buffer1[10] |= 0x20;
			  Display_Buffer1[15] &= 0xDF;
			  Display_Buffer1[10] &= 0xEF;
			  Display_Buffer1[0] &= 0xEF;
			  Display_Buffer1[5] &= 0xEF;
	}
		break;

	case 8:
	{
			  Display_Buffer1[0] |= 0x20;
			  Display_Buffer1[5] |= 0x20;
			  Display_Buffer1[10] |= 0x20;
			  Display_Buffer1[15] |= 0x20;
			  Display_Buffer1[10] |= 0x10;
			  Display_Buffer1[0] |= 0x10;
			  Display_Buffer1[5] |= 0x10;
	}
		break;

	case 9:
	{
			  Display_Buffer1[0] |= 0x20;
			  Display_Buffer1[5] |= 0x20;
			  Display_Buffer1[10] |= 0x20;
			  Display_Buffer1[15] |= 0x20;
			  Display_Buffer1[10] &= 0xEF;
			  Display_Buffer1[0] |= 0x10;
			  Display_Buffer1[5] |= 0x10;
	}
		break;

	default:
	{
			   Display_Buffer1[0] &= 0xDF;
			   Display_Buffer1[5] &= 0xDF;
			   Display_Buffer1[10] &= 0xDF;
			   Display_Buffer1[15] &= 0xDF;
			   Display_Buffer1[10] &= 0xEF;
			   Display_Buffer1[0] &= 0xEF;
			   Display_Buffer1[5] &= 0xEF;
	}
		break;

	}
}

static void ShowPressInt1(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[0] |= 0x80;
			  Display_Buffer1[5] |= 0x80;
			  Display_Buffer1[10] |= 0x80;
			  Display_Buffer1[15] |= 0x80;
			  Display_Buffer1[15] |= 0x40;
			  Display_Buffer1[5] |= 0x40;
			  Display_Buffer1[10] &= 0xBF;
	}
		break;

	case 1:
	{
			  Display_Buffer1[0] &= 0x7F;
			  Display_Buffer1[5] |= 0x80;
			  Display_Buffer1[10] |= 0x80;
			  Display_Buffer1[15] &= 0x7F;
			  Display_Buffer1[15] &= 0xBF;
			  Display_Buffer1[5] &= 0xBF;
			  Display_Buffer1[10] &= 0xBF;
	}
		break;

	case 2:
	{
			  Display_Buffer1[0] |= 0x80;
			  Display_Buffer1[5] |= 0x80;
			  Display_Buffer1[10] &= 0x7F;
			  Display_Buffer1[15] |= 0x80;
			  Display_Buffer1[15] |= 0x40;
			  Display_Buffer1[5] &= 0xBF;
			  Display_Buffer1[10] |= 0x40;
	}
		break;

	case 3:
	{
			  Display_Buffer1[0] |= 0x80;
			  Display_Buffer1[5] |= 0x80;
			  Display_Buffer1[10] |= 0x80;
			  Display_Buffer1[15] |= 0x80;
			  Display_Buffer1[15] &= 0xBF;
			  Display_Buffer1[5] &= 0xBF;
			  Display_Buffer1[10] |= 0x40;
	}
		break;

	case 4:
	{
			  Display_Buffer1[0] &= 0x7F;
			  Display_Buffer1[5] |= 0x80;
			  Display_Buffer1[10] |= 0x80;
			  Display_Buffer1[15] &= 0x7F;
			  Display_Buffer1[15] &= 0xBF;
			  Display_Buffer1[5] |= 0x40;
			  Display_Buffer1[10] |= 0x40;
	}
		break;

	case 5:
	{
			  Display_Buffer1[0] |= 0x80;
			  Display_Buffer1[5] &= 0x7F;
			  Display_Buffer1[10] |= 0x80;
			  Display_Buffer1[15] |= 0x80;
			  Display_Buffer1[15] &= 0xBF;
			  Display_Buffer1[5] |= 0x40;
			  Display_Buffer1[10] |= 0x40;
	}
		break;

	case 6:
	{
			  Display_Buffer1[0] |= 0x80;
			  Display_Buffer1[5] &= 0x7F;
			  Display_Buffer1[10] |= 0x80;
			  Display_Buffer1[15] |= 0x80;
			  Display_Buffer1[15] |= 0x40;
			  Display_Buffer1[5] |= 0x40;
			  Display_Buffer1[10] |= 0x40;
	}
		break;

	case 7:
	{
			  Display_Buffer1[0] |= 0x80;
			  Display_Buffer1[5] |= 0x80;
			  Display_Buffer1[10] |= 0x80;
			  Display_Buffer1[15] &= 0x7F;
			  Display_Buffer1[15] &= 0xBF;
			  Display_Buffer1[5] &= 0xBF;
			  Display_Buffer1[10] &= 0xBF;
	}
		break;

	case 8:
	{
			  Display_Buffer1[0] |= 0x80;
			  Display_Buffer1[5] |= 0x80;
			  Display_Buffer1[10] |= 0x80;
			  Display_Buffer1[15] |= 0x80;
			  Display_Buffer1[15] |= 0x40;
			  Display_Buffer1[5] |= 0x40;
			  Display_Buffer1[10] |= 0x40;
	}
		break;

	case 9:
	{
			  Display_Buffer1[0] |= 0x80;
			  Display_Buffer1[5] |= 0x80;
			  Display_Buffer1[10] |= 0x80;
			  Display_Buffer1[15] |= 0x80;
			  Display_Buffer1[15] &= 0xBF;
			  Display_Buffer1[5] |= 0x40;
			  Display_Buffer1[10] |= 0x40;
	}
		break;

	default:
	{
			   Display_Buffer1[0] &= 0x7F;
			   Display_Buffer1[5] &= 0x7F;
			   Display_Buffer1[10] &= 0x7F;
			   Display_Buffer1[15] &= 0x7F;
			   Display_Buffer1[15] &= 0xBF;
			   Display_Buffer1[5] &= 0xBF;
			   Display_Buffer1[10] &= 0xBF;
	}
		break;

	}
}

static void ShowPressInt2(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[1] |= 0x02;
			  Display_Buffer1[6] |= 0x02;
			  Display_Buffer1[11] |= 0x02;
			  Display_Buffer1[16] |= 0x02;
			  Display_Buffer1[16] |= 0x01;
			  Display_Buffer1[6] |= 0x01;
			  Display_Buffer1[11] &= 0xFE;
	}
		break;

	case 1:
	{
			  Display_Buffer1[1] &= 0xFD;
			  Display_Buffer1[6] |= 0x02;
			  Display_Buffer1[11] |= 0x02;
			  Display_Buffer1[16] &= 0xFD;
			  Display_Buffer1[16] &= 0xFE;
			  Display_Buffer1[6] &= 0xFE;
			  Display_Buffer1[11] &= 0xFE;
	}
		break;

	case 2:
	{
			  Display_Buffer1[1] |= 0x02;
			  Display_Buffer1[6] |= 0x02;
			  Display_Buffer1[11] &= 0xFD;
			  Display_Buffer1[16] |= 0x02;
			  Display_Buffer1[16] |= 0x01;
			  Display_Buffer1[6] &= 0xFE;
			  Display_Buffer1[11] |= 0x01;
	}
		break;

	case 3:
	{
			  Display_Buffer1[1] |= 0x02;
			  Display_Buffer1[6] |= 0x02;
			  Display_Buffer1[11] |= 0x02;
			  Display_Buffer1[16] |= 0x02;
			  Display_Buffer1[16] &= 0xFE;
			  Display_Buffer1[6] &= 0xFE;
			  Display_Buffer1[11] |= 0x01;
	}
		break;

	case 4:
	{
			  Display_Buffer1[1] &= 0xFD;
			  Display_Buffer1[6] |= 0x02;
			  Display_Buffer1[11] |= 0x02;
			  Display_Buffer1[16] &= 0xFD;
			  Display_Buffer1[16] &= 0xFE;
			  Display_Buffer1[6] |= 0x01;
			  Display_Buffer1[11] |= 0x01;
	}
		break;

	case 5:
	{
			  Display_Buffer1[1] |= 0x02;
			  Display_Buffer1[6] &= 0xFD;
			  Display_Buffer1[11] |= 0x02;
			  Display_Buffer1[16] |= 0x02;
			  Display_Buffer1[16] &= 0xFE;
			  Display_Buffer1[6] |= 0x01;
			  Display_Buffer1[11] |= 0x01;
	}
		break;

	case 6:
	{
			  Display_Buffer1[1] |= 0x02;
			  Display_Buffer1[6] &= 0xFD;
			  Display_Buffer1[11] |= 0x02;
			  Display_Buffer1[16] |= 0x02;
			  Display_Buffer1[16] |= 0x01;
			  Display_Buffer1[6] |= 0x01;
			  Display_Buffer1[11] |= 0x01;
	}
		break;

	case 7:
	{
			  Display_Buffer1[1] |= 0x02;
			  Display_Buffer1[6] |= 0x02;
			  Display_Buffer1[11] |= 0x02;
			  Display_Buffer1[16] &= 0xFD;
			  Display_Buffer1[16] &= 0xFE;
			  Display_Buffer1[6] &= 0xFE;
			  Display_Buffer1[11] &= 0xFE;
	}
		break;

	case 8:
	{
			  Display_Buffer1[1] |= 0x02;
			  Display_Buffer1[6] |= 0x02;
			  Display_Buffer1[11] |= 0x02;
			  Display_Buffer1[16] |= 0x02;
			  Display_Buffer1[16] |= 0x01;
			  Display_Buffer1[6] |= 0x01;
			  Display_Buffer1[11] |= 0x01;
	}
		break;

	case 9:
	{
			  Display_Buffer1[1] |= 0x02;
			  Display_Buffer1[6] |= 0x02;
			  Display_Buffer1[11] |= 0x02;
			  Display_Buffer1[16] |= 0x02;
			  Display_Buffer1[16] &= 0xFE;
			  Display_Buffer1[6] |= 0x01;
			  Display_Buffer1[11] |= 0x01;
	}
		break;

	default:
	{
			   Display_Buffer1[1] &= 0xFD;
			   Display_Buffer1[6] &= 0xFD;
			   Display_Buffer1[11] &= 0xFD;
			   Display_Buffer1[16] &= 0xFD;
			   Display_Buffer1[16] &= 0xFE;
			   Display_Buffer1[6] &= 0xFE;
			   Display_Buffer1[11] &= 0xFE;
	}
		break;

	}
}

static void ShowPressInt3(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[1] |= 0x08;
			  Display_Buffer1[6] |= 0x08;
			  Display_Buffer1[11] |= 0x08;
			  Display_Buffer1[16] |= 0x08;
			  Display_Buffer1[16] |= 0x04;
			  Display_Buffer1[6] |= 0x04;
			  Display_Buffer1[11] &= 0xFB;
	}
		break;

	case 1:
	{
			  Display_Buffer1[1] &= 0xF7;
			  Display_Buffer1[6] |= 0x08;
			  Display_Buffer1[11] |= 0x08;
			  Display_Buffer1[16] &= 0xF7;
			  Display_Buffer1[16] &= 0xFB;
			  Display_Buffer1[6] &= 0xFB;
			  Display_Buffer1[11] &= 0xFB;
	}
		break;

	case 2:
	{
			  Display_Buffer1[1] |= 0x08;
			  Display_Buffer1[6] |= 0x08;
			  Display_Buffer1[11] &= 0xF7;
			  Display_Buffer1[16] |= 0x08;
			  Display_Buffer1[16] |= 0x04;
			  Display_Buffer1[6] &= 0xFB;
			  Display_Buffer1[11] |= 0x04;
	}
		break;

	case 3:
	{
			  Display_Buffer1[1] |= 0x08;
			  Display_Buffer1[6] |= 0x08;
			  Display_Buffer1[11] |= 0x08;
			  Display_Buffer1[16] |= 0x08;
			  Display_Buffer1[16] &= 0xFB;
			  Display_Buffer1[6] &= 0xFB;
			  Display_Buffer1[11] |= 0x04;
	}
		break;

	case 4:
	{
			  Display_Buffer1[1] &= 0xF7;
			  Display_Buffer1[6] |= 0x08;
			  Display_Buffer1[11] |= 0x08;
			  Display_Buffer1[16] &= 0xF7;
			  Display_Buffer1[16] &= 0xFB;
			  Display_Buffer1[6] |= 0x04;
			  Display_Buffer1[11] |= 0x04;
	}
		break;

	case 5:
	{
			  Display_Buffer1[1] |= 0x08;
			  Display_Buffer1[6] &= 0xF7;
			  Display_Buffer1[11] |= 0x08;
			  Display_Buffer1[16] |= 0x08;
			  Display_Buffer1[16] &= 0xFB;
			  Display_Buffer1[6] |= 0x04;
			  Display_Buffer1[11] |= 0x04;
	}
		break;

	case 6:
	{
			  Display_Buffer1[1] |= 0x08;
			  Display_Buffer1[6] &= 0xF7;
			  Display_Buffer1[11] |= 0x08;
			  Display_Buffer1[16] |= 0x08;
			  Display_Buffer1[16] |= 0x04;
			  Display_Buffer1[6] |= 0x04;
			  Display_Buffer1[11] |= 0x04;
	}
		break;

	case 7:
	{
			  Display_Buffer1[1] |= 0x08;
			  Display_Buffer1[6] |= 0x08;
			  Display_Buffer1[11] |= 0x08;
			  Display_Buffer1[16] &= 0xF7;
			  Display_Buffer1[16] &= 0xFB;
			  Display_Buffer1[6] &= 0xFB;
			  Display_Buffer1[11] &= 0xFB;
	}
		break;

	case 8:
	{
			  Display_Buffer1[1] |= 0x08;
			  Display_Buffer1[6] |= 0x08;
			  Display_Buffer1[11] |= 0x08;
			  Display_Buffer1[16] |= 0x08;
			  Display_Buffer1[16] |= 0x04;
			  Display_Buffer1[6] |= 0x04;
			  Display_Buffer1[11] |= 0x04;
	}
		break;

	case 9:
	{
			  Display_Buffer1[1] |= 0x08;
			  Display_Buffer1[6] |= 0x08;
			  Display_Buffer1[11] |= 0x08;
			  Display_Buffer1[16] |= 0x08;
			  Display_Buffer1[16] &= 0xFB;
			  Display_Buffer1[6] |= 0x04;
			  Display_Buffer1[11] |= 0x04;
	}
		break;

	default:
	{
			   Display_Buffer1[1] &= 0xF7;
			   Display_Buffer1[6] &= 0xF7;
			   Display_Buffer1[11] &= 0xF7;
			   Display_Buffer1[16] &= 0xF7;
			   Display_Buffer1[16] &= 0xFB;
			   Display_Buffer1[6] &= 0xFB;
			   Display_Buffer1[11] &= 0xFB;
	}
		break;

	}
}

static void ShowPressFloat1(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[1] |= 0x20;
			  Display_Buffer1[6] |= 0x20;
			  Display_Buffer1[11] |= 0x20;
			  Display_Buffer1[16] |= 0x20;
			  Display_Buffer1[11] |= 0x10;
			  Display_Buffer1[1] |= 0x10;
			  Display_Buffer1[6] &= 0xEF;
	}
		break;

	case 1:
	{
			  Display_Buffer1[1] &= 0xDF;
			  Display_Buffer1[6] |= 0x20;
			  Display_Buffer1[11] |= 0x20;
			  Display_Buffer1[16] &= 0xDF;
			  Display_Buffer1[11] &= 0xEF;
			  Display_Buffer1[1] &= 0xEF;
			  Display_Buffer1[6] &= 0xEF;
	}
		break;

	case 2:
	{
			  Display_Buffer1[1] |= 0x20;
			  Display_Buffer1[6] |= 0x20;
			  Display_Buffer1[11] &= 0xDF;
			  Display_Buffer1[16] |= 0x20;
			  Display_Buffer1[11] |= 0x10;
			  Display_Buffer1[1] &= 0xEF;
			  Display_Buffer1[6] |= 0x10;
	}
		break;

	case 3:
	{
			  Display_Buffer1[1] |= 0x20;
			  Display_Buffer1[6] |= 0x20;
			  Display_Buffer1[11] |= 0x20;
			  Display_Buffer1[16] |= 0x20;
			  Display_Buffer1[11] &= 0xEF;
			  Display_Buffer1[1] &= 0xEF;
			  Display_Buffer1[6] |= 0x10;
	}
		break;

	case 4:
	{
			  Display_Buffer1[1] &= 0xDF;
			  Display_Buffer1[6] |= 0x20;
			  Display_Buffer1[11] |= 0x20;
			  Display_Buffer1[16] &= 0xDF;
			  Display_Buffer1[11] &= 0xEF;
			  Display_Buffer1[1] |= 0x10;
			  Display_Buffer1[6] |= 0x10;
	}
		break;

	case 5:
	{
			  Display_Buffer1[1] |= 0x20;
			  Display_Buffer1[6] &= 0xDF;
			  Display_Buffer1[11] |= 0x20;
			  Display_Buffer1[16] |= 0x20;
			  Display_Buffer1[11] &= 0xEF;
			  Display_Buffer1[1] |= 0x10;
			  Display_Buffer1[6] |= 0x10;
	}
		break;

	case 6:
	{
			  Display_Buffer1[1] |= 0x20;
			  Display_Buffer1[6] &= 0xDF;
			  Display_Buffer1[11] |= 0x20;
			  Display_Buffer1[16] |= 0x20;
			  Display_Buffer1[11] |= 0x10;
			  Display_Buffer1[1] |= 0x10;
			  Display_Buffer1[6] |= 0x10;
	}
		break;

	case 7:
	{
			  Display_Buffer1[1] |= 0x20;
			  Display_Buffer1[6] |= 0x20;
			  Display_Buffer1[11] |= 0x20;
			  Display_Buffer1[16] &= 0xDF;
			  Display_Buffer1[11] &= 0xEF;
			  Display_Buffer1[1] &= 0xEF;
			  Display_Buffer1[6] &= 0xEF;
	}
		break;

	case 8:
	{
			  Display_Buffer1[1] |= 0x20;
			  Display_Buffer1[6] |= 0x20;
			  Display_Buffer1[11] |= 0x20;
			  Display_Buffer1[16] |= 0x20;
			  Display_Buffer1[11] |= 0x10;
			  Display_Buffer1[1] |= 0x10;
			  Display_Buffer1[6] |= 0x10;
	}
		break;

	case 9:
	{
			  Display_Buffer1[1] |= 0x20;
			  Display_Buffer1[6] |= 0x20;
			  Display_Buffer1[11] |= 0x20;
			  Display_Buffer1[16] |= 0x20;
			  Display_Buffer1[11] &= 0xEF;
			  Display_Buffer1[1] |= 0x10;
			  Display_Buffer1[6] |= 0x10;
	}
		break;

	default:
	{
			   Display_Buffer1[1] &= 0xDF;
			   Display_Buffer1[6] &= 0xDF;
			   Display_Buffer1[11] &= 0xDF;
			   Display_Buffer1[16] &= 0xDF;
			   Display_Buffer1[11] &= 0xEF;
			   Display_Buffer1[1] &= 0xEF;
			   Display_Buffer1[6] &= 0xEF;
	}
		break;

	}
}

static void ShowPercentInt1(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[1] |= 0x80;
			  Display_Buffer1[6] |= 0x80;
			  Display_Buffer1[11] |= 0x80;
			  Display_Buffer1[16] |= 0x80;
			  Display_Buffer1[16] |= 0x40;
			  Display_Buffer1[6] |= 0x40;
			  Display_Buffer1[11] &= 0xBF;
	}
		break;

	case 1:
	{
			  Display_Buffer1[1] &= 0x7F;
			  Display_Buffer1[6] |= 0x80;
			  Display_Buffer1[11] |= 0x80;
			  Display_Buffer1[16] &= 0x7F;
			  Display_Buffer1[16] &= 0xBF;
			  Display_Buffer1[6] &= 0xBF;
			  Display_Buffer1[11] &= 0xBF;
	}
		break;

	case 2:
	{
			  Display_Buffer1[1] |= 0x80;
			  Display_Buffer1[6] |= 0x80;
			  Display_Buffer1[11] &= 0x7F;
			  Display_Buffer1[16] |= 0x80;
			  Display_Buffer1[16] |= 0x40;
			  Display_Buffer1[6] &= 0xBF;
			  Display_Buffer1[11] |= 0x40;
	}
		break;

	case 3:
	{
			  Display_Buffer1[1] |= 0x80;
			  Display_Buffer1[6] |= 0x80;
			  Display_Buffer1[11] |= 0x80;
			  Display_Buffer1[16] |= 0x80;
			  Display_Buffer1[16] &= 0xBF;
			  Display_Buffer1[6] &= 0xBF;
			  Display_Buffer1[11] |= 0x40;
	}
		break;

	case 4:
	{
			  Display_Buffer1[1] &= 0x7F;
			  Display_Buffer1[6] |= 0x80;
			  Display_Buffer1[11] |= 0x80;
			  Display_Buffer1[16] &= 0x7F;
			  Display_Buffer1[16] &= 0xBF;
			  Display_Buffer1[6] |= 0x40;
			  Display_Buffer1[11] |= 0x40;
	}
		break;

	case 5:
	{
			  Display_Buffer1[1] |= 0x80;
			  Display_Buffer1[6] &= 0x7F;
			  Display_Buffer1[11] |= 0x80;
			  Display_Buffer1[16] |= 0x80;
			  Display_Buffer1[16] &= 0xBF;
			  Display_Buffer1[6] |= 0x40;
			  Display_Buffer1[11] |= 0x40;
	}
		break;

	case 6:
	{
			  Display_Buffer1[1] |= 0x80;
			  Display_Buffer1[6] &= 0x7F;
			  Display_Buffer1[11] |= 0x80;
			  Display_Buffer1[16] |= 0x80;
			  Display_Buffer1[16] |= 0x40;
			  Display_Buffer1[6] |= 0x40;
			  Display_Buffer1[11] |= 0x40;
	}
		break;

	case 7:
	{
			  Display_Buffer1[1] |= 0x80;
			  Display_Buffer1[6] |= 0x80;
			  Display_Buffer1[11] |= 0x80;
			  Display_Buffer1[16] &= 0x7F;
			  Display_Buffer1[16] &= 0xBF;
			  Display_Buffer1[6] &= 0xBF;
			  Display_Buffer1[11] &= 0xBF;
	}
		break;

	case 8:
	{
			  Display_Buffer1[1] |= 0x80;
			  Display_Buffer1[6] |= 0x80;
			  Display_Buffer1[11] |= 0x80;
			  Display_Buffer1[16] |= 0x80;
			  Display_Buffer1[16] |= 0x40;
			  Display_Buffer1[6] |= 0x40;
			  Display_Buffer1[11] |= 0x40;
	}
		break;

	case 9:
	{
			  Display_Buffer1[1] |= 0x80;
			  Display_Buffer1[6] |= 0x80;
			  Display_Buffer1[11] |= 0x80;
			  Display_Buffer1[16] |= 0x80;
			  Display_Buffer1[16] &= 0xBF;
			  Display_Buffer1[6] |= 0x40;
			  Display_Buffer1[11] |= 0x40;
	}
		break;

	default:
	{
			   Display_Buffer1[1] &= 0x7F;
			   Display_Buffer1[6] &= 0x7F;
			   Display_Buffer1[11] &= 0x7F;
			   Display_Buffer1[16] &= 0x7F;
			   Display_Buffer1[16] &= 0xBF;
			   Display_Buffer1[6] &= 0xBF;
			   Display_Buffer1[11] &= 0xBF;
	}
		break;

	}
}

static void ShowPercentInt2(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[2] |= 0x02;
			  Display_Buffer1[7] |= 0x02;
			  Display_Buffer1[12] |= 0x02;
			  Display_Buffer1[17] |= 0x02;
			  Display_Buffer1[17] |= 0x01;
			  Display_Buffer1[7] |= 0x01;
			  Display_Buffer1[12] &= 0xFE;
	}
		break;

	case 1:
	{
			  Display_Buffer1[2] &= 0xFD;
			  Display_Buffer1[7] |= 0x02;
			  Display_Buffer1[12] |= 0x02;
			  Display_Buffer1[17] &= 0xFD;
			  Display_Buffer1[17] &= 0xFE;
			  Display_Buffer1[7] &= 0xFE;
			  Display_Buffer1[12] &= 0xFE;
	}
		break;

	case 2:
	{
			  Display_Buffer1[2] |= 0x02;
			  Display_Buffer1[7] |= 0x02;
			  Display_Buffer1[12] &= 0xFD;
			  Display_Buffer1[17] |= 0x02;
			  Display_Buffer1[17] |= 0x01;
			  Display_Buffer1[7] &= 0xFE;
			  Display_Buffer1[12] |= 0x01;
	}
		break;

	case 3:
	{
			  Display_Buffer1[2] |= 0x02;
			  Display_Buffer1[7] |= 0x02;
			  Display_Buffer1[12] |= 0x02;
			  Display_Buffer1[17] |= 0x02;
			  Display_Buffer1[17] &= 0xFE;
			  Display_Buffer1[7] &= 0xFE;
			  Display_Buffer1[12] |= 0x01;
	}
		break;

	case 4:
	{
			  Display_Buffer1[2] &= 0xFD;
			  Display_Buffer1[7] |= 0x02;
			  Display_Buffer1[12] |= 0x02;
			  Display_Buffer1[17] &= 0xFD;
			  Display_Buffer1[17] &= 0xFE;
			  Display_Buffer1[7] |= 0x01;
			  Display_Buffer1[12] |= 0x01;
	}
		break;

	case 5:
	{
			  Display_Buffer1[2] |= 0x02;
			  Display_Buffer1[7] &= 0xFD;
			  Display_Buffer1[12] |= 0x02;
			  Display_Buffer1[17] |= 0x02;
			  Display_Buffer1[17] &= 0xFE;
			  Display_Buffer1[7] |= 0x01;
			  Display_Buffer1[12] |= 0x01;
	}
		break;

	case 6:
	{
			  Display_Buffer1[2] |= 0x02;
			  Display_Buffer1[7] &= 0xFD;
			  Display_Buffer1[12] |= 0x02;
			  Display_Buffer1[17] |= 0x02;
			  Display_Buffer1[17] |= 0x01;
			  Display_Buffer1[7] |= 0x01;
			  Display_Buffer1[12] |= 0x01;
	}
		break;

	case 7:
	{
			  Display_Buffer1[2] |= 0x02;
			  Display_Buffer1[7] |= 0x02;
			  Display_Buffer1[12] |= 0x02;
			  Display_Buffer1[17] &= 0xFD;
			  Display_Buffer1[17] &= 0xFE;
			  Display_Buffer1[7] &= 0xFE;
			  Display_Buffer1[12] &= 0xFE;
	}
		break;

	case 8:
	{
			  Display_Buffer1[2] |= 0x02;
			  Display_Buffer1[7] |= 0x02;
			  Display_Buffer1[12] |= 0x02;
			  Display_Buffer1[17] |= 0x02;
			  Display_Buffer1[17] |= 0x01;
			  Display_Buffer1[7] |= 0x01;
			  Display_Buffer1[12] |= 0x01;
	}
		break;

	case 9:
	{
			  Display_Buffer1[2] |= 0x02;
			  Display_Buffer1[7] |= 0x02;
			  Display_Buffer1[12] |= 0x02;
			  Display_Buffer1[17] |= 0x02;
			  Display_Buffer1[17] &= 0xFE;
			  Display_Buffer1[7] |= 0x01;
			  Display_Buffer1[12] |= 0x01;
	}
		break;

	default:
	{
			   Display_Buffer1[2] &= 0xFD;
			   Display_Buffer1[7] &= 0xFD;
			   Display_Buffer1[12] &= 0xFD;
			   Display_Buffer1[17] &= 0xFD;
			   Display_Buffer1[17] &= 0xFE;
			   Display_Buffer1[7] &= 0xFE;
			   Display_Buffer1[12] &= 0xFE;
	}
		break;

	}
}

static void ShowPercentInt3(uint8 NUM)
{
	switch (NUM)
	{
	case 0:
	{
			  Display_Buffer1[2] |= 0x08;
			  Display_Buffer1[7] |= 0x08;
			  Display_Buffer1[12] |= 0x08;
			  Display_Buffer1[17] |= 0x08;
			  Display_Buffer1[17] |= 0x04;
			  Display_Buffer1[7] |= 0x04;
			  Display_Buffer1[12] &= 0xFB;
	}
		break;

	case 1:
	{
			  Display_Buffer1[2] &= 0xF7;
			  Display_Buffer1[7] |= 0x08;
			  Display_Buffer1[12] |= 0x08;
			  Display_Buffer1[17] &= 0xF7;
			  Display_Buffer1[17] &= 0xFB;
			  Display_Buffer1[7] &= 0xFB;
			  Display_Buffer1[12] &= 0xFB;
	}
		break;

	case 2:
	{
			  Display_Buffer1[2] |= 0x08;
			  Display_Buffer1[7] |= 0x08;
			  Display_Buffer1[12] &= 0xF7;
			  Display_Buffer1[17] |= 0x08;
			  Display_Buffer1[17] |= 0x04;
			  Display_Buffer1[7] &= 0xFB;
			  Display_Buffer1[12] |= 0x04;
	}
		break;

	case 3:
	{
			  Display_Buffer1[2] |= 0x08;
			  Display_Buffer1[7] |= 0x08;
			  Display_Buffer1[12] |= 0x08;
			  Display_Buffer1[17] |= 0x08;
			  Display_Buffer1[17] &= 0xFB;
			  Display_Buffer1[7] &= 0xFB;
			  Display_Buffer1[12] |= 0x04;
	}
		break;

	case 4:
	{
			  Display_Buffer1[2] &= 0xF7;
			  Display_Buffer1[7] |= 0x08;
			  Display_Buffer1[12] |= 0x08;
			  Display_Buffer1[17] &= 0xF7;
			  Display_Buffer1[17] &= 0xFB;
			  Display_Buffer1[7] |= 0x04;
			  Display_Buffer1[12] |= 0x04;
	}
		break;

	case 5:
	{
			  Display_Buffer1[2] |= 0x08;
			  Display_Buffer1[7] &= 0xF7;
			  Display_Buffer1[12] |= 0x08;
			  Display_Buffer1[17] |= 0x08;
			  Display_Buffer1[17] &= 0xFB;
			  Display_Buffer1[7] |= 0x04;
			  Display_Buffer1[12] |= 0x04;
	}
		break;

	case 6:
	{
			  Display_Buffer1[2] |= 0x08;
			  Display_Buffer1[7] &= 0xF7;
			  Display_Buffer1[12] |= 0x08;
			  Display_Buffer1[17] |= 0x08;
			  Display_Buffer1[17] |= 0x04;
			  Display_Buffer1[7] |= 0x04;
			  Display_Buffer1[12] |= 0x04;
	}
		break;

	case 7:
	{
			  Display_Buffer1[2] |= 0x08;
			  Display_Buffer1[7] |= 0x08;
			  Display_Buffer1[12] |= 0x08;
			  Display_Buffer1[17] &= 0xF7;
			  Display_Buffer1[17] &= 0xFB;
			  Display_Buffer1[7] &= 0xFB;
			  Display_Buffer1[12] &= 0xFB;
	}
		break;

	case 8:
	{
			  Display_Buffer1[2] |= 0x08;
			  Display_Buffer1[7] |= 0x08;
			  Display_Buffer1[12] |= 0x08;
			  Display_Buffer1[17] |= 0x08;
			  Display_Buffer1[17] |= 0x04;
			  Display_Buffer1[7] |= 0x04;
			  Display_Buffer1[12] |= 0x04;
	}
		break;

	case 9:
	{
			  Display_Buffer1[2] |= 0x08;
			  Display_Buffer1[7] |= 0x08;
			  Display_Buffer1[12] |= 0x08;
			  Display_Buffer1[17] |= 0x08;
			  Display_Buffer1[17] &= 0xFB;
			  Display_Buffer1[7] |= 0x04;
			  Display_Buffer1[12] |= 0x04;
	}
		break;

	default:
	{
			   Display_Buffer1[2] &= 0xF7;
			   Display_Buffer1[7] &= 0xF7;
			   Display_Buffer1[12] &= 0xF7;
			   Display_Buffer1[17] &= 0xF7;
			   Display_Buffer1[17] &= 0xFB;
			   Display_Buffer1[7] &= 0xFB;
			   Display_Buffer1[12] &= 0xFB;
	}
		break;

	}
}
//******************************************以上为单个7断码管显示，一级驱动***********************************************************





//**************************************************LED二级驱动***************************************************************


/*******************************************************************************
* 名    称：DisplayGasSpeed(uint8_t Mode,float Speed)
* 功    能：
* 入口参数：Mode,Speed
* 出口参数：
* 说    明：		Mode:	0:关闭显示  1：显示工况  2：显示标况 			Fla:  0:空气   1：天然气
*******************************************************************************/

void DisplayGasSpeed(float Speed,BOOL Flag)
{
	float speed = Speed;
	uint16_t Int = 0,Flo = 0;

	if((Speed >= 10000.00f)||(Speed < 0))
	{
		speed = 9999.99f;
	}
	
	Int = (unsigned int)speed;
	
	Flo = (unsigned int)((speed - Int)*100);//4舍5入
	
	if(Int >= 1000)
	{
		ShowSpeedInt1(Int/1000);
		ShowSpeedInt2((Int%1000)/100);
		ShowSpeedInt3((Int%100)/10);
		ShowSpeedInt4(Int%10);
	}
	else if(Int >= 100)
	{
		ShowSpeedInt1(0xFF);
		ShowSpeedInt2(Int/100);
		ShowSpeedInt3((Int%100)/10);
		ShowSpeedInt4(Int%10);
	}
	else if(Int >= 10)
	{
		ShowSpeedInt1(0xFF);
		ShowSpeedInt2(0xFF);
		ShowSpeedInt3(Int/10);
		ShowSpeedInt4(Int%10);
	}
	else
	{
		ShowSpeedInt1(0xFF);
		ShowSpeedInt2(0xFF);
		ShowSpeedInt3(0xFF);
		ShowSpeedInt4(Int);
	}
	
	SHOW_SPEEDPOINT();
	
	ShowSpeedFloat1(Flo/10);
	ShowSpeedFloat2(Flo%10);
	
	SHOW_M3H();
	
	if(Flag)
	{
		SHOW_T();
		CLR_K();
	}
	else
	{
		SHOW_K();
		CLR_T();		
	}
	
	Pcf8551Refresh();//
}

void DisplayWorkData(unsigned long int Num_H,float Num_L,BOOL GBFlag,BOOL VolFlag,BOOL FaultFlag)
{
	uint32_t Float;
	
	if(Num_H >= 10000000)
	{
		ShowGKInt1(Num_H/10000000);
		ShowGKInt2((Num_H%10000000)/1000000);
		ShowGKInt3((Num_H%1000000)/100000);
		ShowGKInt4((Num_H%100000)/10000);
		ShowGKInt5((Num_H%10000)/1000);
		ShowGKInt6((Num_H%1000)/100);
		ShowGKInt7((Num_H%100)/10);
		ShowGKInt8(Num_H%10);
	}
	else if(Num_H >= 1000000)
	{
		ShowGKInt1(0xFF);
		ShowGKInt2(Num_H/1000000);
		ShowGKInt3((Num_H%1000000)/100000);
		ShowGKInt4((Num_H%100000)/10000);
		ShowGKInt5((Num_H%10000)/1000);
		ShowGKInt6((Num_H%1000)/100);
		ShowGKInt7((Num_H%100)/10);
		ShowGKInt8(Num_H%10);
	}
	else if(Num_H >= 100000)
	{
		ShowGKInt1(0xFF);
		ShowGKInt2(0xFF);
		ShowGKInt3(Num_H/100000);
		ShowGKInt4((Num_H%100000)/10000);
		ShowGKInt5((Num_H%10000)/1000);
		ShowGKInt6((Num_H%1000)/100);
		ShowGKInt7((Num_H%100)/10);
		ShowGKInt8(Num_H%10);
	}
	else if(Num_H >= 10000)
	{
		ShowGKInt1(0xFF);
		ShowGKInt2(0xFF);
		ShowGKInt3(0xFF);
		ShowGKInt4(Num_H/10000);
		ShowGKInt5((Num_H%10000)/1000);
		ShowGKInt6((Num_H%1000)/100);
		ShowGKInt7((Num_H%100)/10);
		ShowGKInt8(Num_H%10);
	}
	else if(Num_H >= 1000)
	{
		ShowGKInt1(0xFF);
		ShowGKInt2(0xFF);
		ShowGKInt3(0xFF);
		ShowGKInt4(0xFF);
		ShowGKInt5(Num_H/1000);
		ShowGKInt6((Num_H%1000)/100);
		ShowGKInt7((Num_H%100)/10);
		ShowGKInt8(Num_H%10);
	}
	else if(Num_H >= 100)
	{
		ShowGKInt1(0xFF);
		ShowGKInt2(0xFF);
		ShowGKInt3(0xFF);
		ShowGKInt4(0xFF);
		ShowGKInt5(0xFF);
		ShowGKInt6(Num_H/100);
		ShowGKInt7((Num_H%100)/10);
		ShowGKInt8(Num_H%10);
	}
	else if(Num_H >= 10)
	{
		ShowGKInt1(0xFF);
		ShowGKInt2(0xFF);
		ShowGKInt3(0xFF);
		ShowGKInt4(0xFF);
		ShowGKInt5(0xFF);
		ShowGKInt6(0xFF);
		ShowGKInt7(Num_H/10);
		ShowGKInt8(Num_H%10);
	}
	else
	{
		ShowGKInt1(0xFF);
		ShowGKInt2(0xFF);
		ShowGKInt3(0xFF);
		ShowGKInt4(0xFF);
		ShowGKInt5(0xFF);
		ShowGKInt6(0xFF);
		ShowGKInt7(0xFF);
		ShowGKInt8(Num_H%10);
	}
	
	SHOW_GKPOINT();
	
	Float = (unsigned int)(Num_L*1000);
	
	ShowGKFloat1(Float/100);
	ShowGKFloat2((Float%100)/10);
	ShowGKFloat3(Float%10);
	
	if(GBFlag) //1为工况
	{
		SHOW_GK();
		CLR_BK();
	}
	else
	{
		SHOW_BK();
		CLR_GK();
	}
	
	if(VolFlag)
	{
		SHOW_LowVol();
	}
	else
	{
		CLR_LowVol();
	}
	
	if(FaultFlag)
	{
		SHOW_FAULT();
	}
	else
	{
		CLR_FAULT();
	}
	
	SHOW_GKM3();
	
	Pcf8551Refresh();//
}

static void DisplayTmp(float Tmp)
{
	float temp = Tmp;
	uint32_t Int,Flo;
	
	if(temp < 0)
	{
		temp = -temp;
	}
	
	if(Tmp>=100)
	{
		temp = 99.9f;
	}
	
	Int = (unsigned int)temp;
	Flo = (unsigned int)((temp -Int)*10);
	
	if(0 == (Int/10))
	{
		ShowTmpInt1(0xFF);
	}
	else
	{
		ShowTmpInt1(Int/10);
	}
	ShowTmpInt2(Int%10);
	
	SHOW_TMPPOINT();
	
	ShowTmpFloat1(Flo%10);
	
	if(Tmp < 0)
	{
		SHOW_MINUS();
	}
	else
	{
		CLR_MINUS();
	}
	
	SHOW_TMP();	
}

static void DisplayPress(float Press)
{
	uint32_t Int,Flo;
	
	Int = (unsigned int)(Press);
	Flo = (unsigned int)((Press - Int)*10);
	
	if(Int >= 100)
	{
		ShowPressInt1(Int/100);
		ShowPressInt2((Int/10)%10);
		ShowPressInt3(Int%10);
	}
	else
	{
		ShowPressInt1(0xFF);
		ShowPressInt2(Int/10);
		ShowPressInt3(Int%10);
	}
	
	SHOW_PRESSPOINT();
	
	ShowPressFloat1(Flo);
	
	SHOW_KPA();
}

void DisplayTmp_Press(float Tmp, float Press)
{
	DisplayTmp(Tmp);
	DisplayPress(Press);
	Pcf8551Refresh();
}

//**************************************************LED二级驱动***************************************************************

void Test(void)
{
//	for (uint8 i = 0; i < 11; i++)
//	{
//		ShowPercentInt3(i);
//		Pcf8551Refresh();
//		delay_ms(500);//
//	}
	DisplayTmp_Press(21.2,102.5);
	Pcf8551Refresh();
}
