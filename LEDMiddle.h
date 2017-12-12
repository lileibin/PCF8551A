#ifndef __LEDMiddle_H__
#define __LEDMiddle_H__

#include "PCF8551A.h"
#include "config.h"
#include "string.h"
#include "math.h"


//******************************************************************************************

#define PCF8551A_ADD_W  		0x70		//PCF8551A写地址

#define PCF8551A_REG_BASE		0x00		//命令Register基地址
#define PCF8551A_DATA_BASE 	0x04		//显示Register基地址

#define PCF8551A_RET    		0x2B		//PCF8551A软件复位
#define PCF8551A_CTR    		0x04		//PCF8551A内设配置字节
#define PCF8551A_CTR1   		0x01		//PCF8551A显示配置字节1
#define PCF8551A_CTR2   		0x00		//PCF8551A小时配置字节2

//******************************************************************************************


//****************************************************************************************************

extern unsigned char Display_Buffer1[24];	//显示缓存1
extern unsigned char Display_Buffer2[24];	//显示缓存2

//****************************************************************************************************


void Pcf8551Init(void);
void Pcf8551_IO_Init(void);
void Pcf8551_All_ON(void);
void Pcf8551_All_OFF(void);

void DisplayGasSpeed(float Speed,BOOL Flag);
void DisplayTmp_Press(float Tmp, float Press);
void DisplayWorkData(unsigned long int Num_H,float Num_L,BOOL GBFlag,BOOL VolFlag,BOOL FaultFlag);

void Test(void);

//显示符号相关的定义

#define SHOW_M3H()						Display_Buffer2[19] |= 0x04
#define CLR_M3H()							Display_Buffer2[19] &= 0xFB

#define SHOW_LowVol()					Display_Buffer2[15] |=0x04 
#define CLR_LowVol()					Display_Buffer2[15] &= 0xFB

#define SHOW_K()							Display_Buffer2[16] |= 0x01
#define CLR_K()								Display_Buffer2[16] &= 0xFE

#define SHOW_FAULT()					Display_Buffer2[15] |= 0x10
#define CLR_FAULT()						Display_Buffer2[15] &= 0xEF

#define SHOW_T()							Display_Buffer2[15] |= 0x40
#define CLR_T()								Display_Buffer2[15] &= 0xBF

#define SHOW_GKSPEED()				Display_Buffer2[18] |= 0x01
#define CLR_GKSPEED()					Display_Buffer2[18] &= 0xFE

#define SHOW_BKSPEED()				Display_Buffer2[18] |= 0x04
#define CLR_BKSPEED()					Display_Buffer2[18] &= 0xFB

#define SHOW_GKM3()						Display_Buffer2[18] |= 0x40
#define CLR_GKM3()						Display_Buffer2[18] &= 0xBF

#define SHOW_SPEEDPOINT()			Display_Buffer2[19] |= 0x01
#define CLR_SPEEDPOINT()			Display_Buffer2[19] &= 0xFE

#define SHOW_GKPOINT()				Display_Buffer2[2] |= 0x04
#define CLR_GKPOINT()					Display_Buffer2[2] &= 0xFB

#define SHOW_GK()							Display_Buffer1[0] |= 0x04
#define CLR_GK()							Display_Buffer1[0] &= 0xFB

#define SHOW_BK()							Display_Buffer1[1] |= 0x01
#define CLR_BK()							Display_Buffer1[1] &= 0xFE

#define SHOW_MINUS()					Display_Buffer1[0] |= 0x01
#define CLR_MINUS()						Display_Buffer1[0] &= 0xFE

#define SHOW_TMPPOINT()				Display_Buffer1[15] |= 0x10
#define CLR_TMPPOINT()				Display_Buffer1[15] &= 0xEF

#define SHOW_TMP()						Display_Buffer1[0] |= 0x40
#define CLR_TMP()							Display_Buffer1[0] &= 0xBF

#define SHOW_PRESSPOINT()			Display_Buffer1[16] |= 0x10
#define CLR_PRESSPOINT()			Display_Buffer1[16] &= 0xEF

#define SHOW_KPA()						Display_Buffer1[1] |= 0x40	
#define CLR_KPA()							Display_Buffer1[1] &= 0xBF	

#define SHOW_BKPOINT()				Display_Buffer1[3] |= 0x02
#define CLR_BKPOINT()					Display_Buffer1[3] &= 0xFD

#define SHOW_BKM3()						Display_Buffer1[2] |= 0x20
#define CLR_BKM3()						Display_Buffer1[2] &= 0xDF

#define SHOW_PERCENT()				Display_Buffer1[2] |= 0x04
#define CLR_PERCENT()					Display_Buffer1[2] &= 0xFB

#endif
