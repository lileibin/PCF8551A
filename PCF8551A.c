/*******************************************************************************
*                              PCF8551 Drivers
*
* File      	: PCF8551A.c
* Version   	: V1.00
* By        	: 
*
* For       	: PCF8551A
*
* Description :
*
* Date        : 2017.1.20
*******************************************************************************/
#include "PCF8551A.h"

static unsigned char ack;//应答

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
void StartI2c(void)
{
  DAT_O;
  CLK_O;
  delay_us(1);

  DAT_H;//发送起始条件的数据信号
  delay_us(1);

  CLK_H;
  delay_us(1);//起始条件建立时间大于4.7us,延时
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  DAT_L;//发送起始信号
  delay_us(1);//起始条件锁定时间大于4μs
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK_L;//钳住I2C总线，准备发送或接收数据
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
void StopI2c(void)
{
  DAT_O;
  CLK_O;
  delay_us(1);

  DAT_L;//发送结束条件的数据信号
  delay_us(1);

  CLK_H;//发送结束条件的时钟信号
  delay_us(1);//结束条件建立时间大于4μs
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  DAT_H;//发送I2C总线结束信号
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
void SendByte(unsigned char c)
{
  unsigned char BitCnt;

  DAT_O;
  CLK_O;
  delay_us(1);

  for(BitCnt=0; BitCnt<8; BitCnt++)//要传送的数据长度为8位
  {
    if(c&0x80)
      DAT_H;//判断发送位
    else
      DAT_L;

    c<<=1;
    delay_us(1);

    CLK_H;//置时钟线为高，通知被控器开始接收数据位
    delay_us(1);
    delay_us(1);//保证时钟高电平周期大于4μs*/
    delay_us(1);
    delay_us(1);
    delay_us(1);

    CLK_L;
  }

  delay_us(1);
  delay_us(1);

  DAT_H;//8位发送完后释放数据线，准备接收应答位
  delay_us(1);
  delay_us(1);

  CLK_H;
  DAT_I;
  delay_us(1);
  delay_us(1);
  delay_us(1);

  if(DAT_D)
    ack=0;
  else
    ack=1;//判断是否接收到应答信号

  CLK_L;
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
unsigned char RcvByte(void)
{
  unsigned char retc;
  unsigned char BitCnt;

  retc=0;

  DAT_O;
  CLK_O;
  delay_us(1);

  DAT_H;//置数据线为输入方式
  DAT_I;
  delay_us(1);

  for(BitCnt=0; BitCnt<8; BitCnt++)
  {
    delay_us(1);

    CLK_L;//置时钟线为低，准备接收数据位
    delay_us(1);
    delay_us(1);//时钟低电平周期大于4.7μs
    delay_us(1);
    delay_us(1);
    delay_us(1);

    CLK_H;//置时钟线为高使数据线上数据有效
    delay_us(1);
    delay_us(1);

    retc=retc<<1;

    if(DAT_D)
      retc=retc+1;//读数据位,接收的数据位放入retc中

    delay_us(1);
    delay_us(1);
  }

  CLK_L;   
  delay_us(1);
  delay_us(1);

  return(retc);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
void AckI2c(unsigned char a)
{
  DAT_O;
  CLK_O;
  delay_us(1);

  if(a==0)
    DAT_L;//在此发出应答或非应答信号
  else
    DAT_H;

  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK_H;
  delay_us(1);//时钟低电平周期大于4μs
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK_L;//清时钟线，钳住I2C总线以便继续接收
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
unsigned char ISendStr(unsigned char sla, unsigned char rla,unsigned char *s, unsigned char no)
{
  unsigned char i;

  StartI2c();//启动总线
  SendByte(sla);//发送器件地址
  if(ack==0)
    return(0);

  SendByte(rla);//发送器件子地址
  if(ack==0)
    return(0);

  for(i=0; i<no; i++)
  {
    SendByte(*s);//发送数据
    if(ack==0)
      return(0);

    s++;
  }

  StopI2c();//结束总线

  return(1);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
unsigned char IRcvStr(unsigned char sla, unsigned char *suba, unsigned char *s, unsigned char subano, unsigned char no)
{
  unsigned char i;

  StartI2c();//启动总线
  SendByte(sla);//发送器件地址

  if(ack==0)
    return(0);

  for(i=0; i<subano; i++)
  {
    SendByte(*suba);//发送器件子地址
 
    if(ack==0)return(0);
      suba++;
  }

  StartI2c();
  SendByte(sla+1);

  if(ack==0)
    return(0);

  for(i=0; i<no-1; i++)
  {  
    *s=RcvByte();//发送数据
    AckI2c(0);//发送就答位
 
    s++;
  }

  *s=RcvByte();
  AckI2c(1);//发送非应位
  StopI2c();//结束总线

  return(1);
}

//****************************************************************************************************************************************

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
void StartI2c2(void)
{
  DAT2_O;
  CLK2_O;
  delay_us(1);

  DAT2_H;//发送起始条件的数据信号
  delay_us(1);

  CLK2_H;
  delay_us(1);//起始条件建立时间大于4.7us,延时
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  DAT2_L;//发送起始信号
  delay_us(1);//起始条件锁定时间大于4μs
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK2_L;//钳住I2C总线，准备发送或接收数据
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
void StopI2c2(void)
{
  DAT2_O;
  CLK2_O;
  delay_us(1);

  DAT2_L;//发送结束条件的数据信号
  delay_us(1);

  CLK2_H;//发送结束条件的时钟信号
  delay_us(1);//结束条件建立时间大于4μs
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  DAT2_H;//发送I2C总线结束信号
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
void SendByte2(unsigned char c)
{
  unsigned char BitCnt;

  DAT2_O;
  CLK2_O;
  delay_us(1);

  for(BitCnt=0; BitCnt<8; BitCnt++)//要传送的数据长度为8位
  {
    if(c&0x80)
      DAT2_H;//判断发送位
    else
      DAT2_L;

    c<<=1;
    delay_us(1);

    CLK2_H;//置时钟线为高，通知被控器开始接收数据位
    delay_us(1);
    delay_us(1);//保证时钟高电平周期大于4μs*/
    delay_us(1);
    delay_us(1);
    delay_us(1);

    CLK2_L;
  }

  delay_us(1);
  delay_us(1);

  DAT2_H;//8位发送完后释放数据线，准备接收应答位
  delay_us(1);
  delay_us(1);

  CLK2_H;
  DAT_I;
  delay_us(1);
  delay_us(1);
  delay_us(1);

  if(DAT2_D)
    ack=0;
  else
    ack=1;//判断是否接收到应答信号

  CLK2_L;
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
unsigned char RcvByte2(void)
{
  unsigned char retc;
  unsigned char BitCnt;

  retc=0;

  DAT2_O;
  CLK2_O;
  delay_us(1);

  DAT2_H;//置数据线为输入方式
  DAT_I;
  delay_us(1);

  for(BitCnt=0; BitCnt<8; BitCnt++)
  {
    delay_us(1);

    CLK2_L;//置时钟线为低，准备接收数据位
    delay_us(1);
    delay_us(1);//时钟低电平周期大于4.7μs
    delay_us(1);
    delay_us(1);
    delay_us(1);

    CLK2_H;//置时钟线为高使数据线上数据有效
    delay_us(1);
    delay_us(1);

    retc=retc<<1;

    if(DAT2_D)
      retc=retc+1;//读数据位,接收的数据位放入retc中

    delay_us(1);
    delay_us(1);
  }

  CLK2_L;   
  delay_us(1);
  delay_us(1);

  return(retc);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
void AckI2c2(unsigned char a)
{
  DAT2_O;
  CLK2_O;
  delay_us(1);

  if(a==0)
    DAT2_L;//在此发出应答或非应答信号
  else
    DAT2_H;

  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK2_H;
  delay_us(1);//时钟低电平周期大于4μs
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK2_L;//清时钟线，钳住I2C总线以便继续接收
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* 名    称：
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
*******************************************************************************/
unsigned char ISendStr2(unsigned char sla, unsigned char rla,unsigned char *s, unsigned char no)
{
  unsigned char i;

  StartI2c2();//启动总线
  SendByte2(sla);//发送器件地址
  if(ack==0)
    return(0);

  SendByte2(rla);//发送器件子地址
  if(ack==0)
    return(0);

  for(i=0; i<no; i++)
  {
    SendByte2(*s);//发送数据
    if(ack==0)
      return(0);

    s++;
  }

  StopI2c2();//结束总线

  return(1);
}

