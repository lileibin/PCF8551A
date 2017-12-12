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

static unsigned char ack;//Ӧ��

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
void StartI2c(void)
{
  DAT_O;
  CLK_O;
  delay_us(1);

  DAT_H;//������ʼ�����������ź�
  delay_us(1);

  CLK_H;
  delay_us(1);//��ʼ��������ʱ�����4.7us,��ʱ
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  DAT_L;//������ʼ�ź�
  delay_us(1);//��ʼ��������ʱ�����4��s
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK_L;//ǯסI2C���ߣ�׼�����ͻ��������
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
void StopI2c(void)
{
  DAT_O;
  CLK_O;
  delay_us(1);

  DAT_L;//���ͽ��������������ź�
  delay_us(1);

  CLK_H;//���ͽ���������ʱ���ź�
  delay_us(1);//������������ʱ�����4��s
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  DAT_H;//����I2C���߽����ź�
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
void SendByte(unsigned char c)
{
  unsigned char BitCnt;

  DAT_O;
  CLK_O;
  delay_us(1);

  for(BitCnt=0; BitCnt<8; BitCnt++)//Ҫ���͵����ݳ���Ϊ8λ
  {
    if(c&0x80)
      DAT_H;//�жϷ���λ
    else
      DAT_L;

    c<<=1;
    delay_us(1);

    CLK_H;//��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
    delay_us(1);
    delay_us(1);//��֤ʱ�Ӹߵ�ƽ���ڴ���4��s*/
    delay_us(1);
    delay_us(1);
    delay_us(1);

    CLK_L;
  }

  delay_us(1);
  delay_us(1);

  DAT_H;//8λ��������ͷ������ߣ�׼������Ӧ��λ
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
    ack=1;//�ж��Ƿ���յ�Ӧ���ź�

  CLK_L;
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
unsigned char RcvByte(void)
{
  unsigned char retc;
  unsigned char BitCnt;

  retc=0;

  DAT_O;
  CLK_O;
  delay_us(1);

  DAT_H;//��������Ϊ���뷽ʽ
  DAT_I;
  delay_us(1);

  for(BitCnt=0; BitCnt<8; BitCnt++)
  {
    delay_us(1);

    CLK_L;//��ʱ����Ϊ�ͣ�׼����������λ
    delay_us(1);
    delay_us(1);//ʱ�ӵ͵�ƽ���ڴ���4.7��s
    delay_us(1);
    delay_us(1);
    delay_us(1);

    CLK_H;//��ʱ����Ϊ��ʹ��������������Ч
    delay_us(1);
    delay_us(1);

    retc=retc<<1;

    if(DAT_D)
      retc=retc+1;//������λ,���յ�����λ����retc��

    delay_us(1);
    delay_us(1);
  }

  CLK_L;   
  delay_us(1);
  delay_us(1);

  return(retc);
}

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
void AckI2c(unsigned char a)
{
  DAT_O;
  CLK_O;
  delay_us(1);

  if(a==0)
    DAT_L;//�ڴ˷���Ӧ����Ӧ���ź�
  else
    DAT_H;

  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK_H;
  delay_us(1);//ʱ�ӵ͵�ƽ���ڴ���4��s
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK_L;//��ʱ���ߣ�ǯסI2C�����Ա��������
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
unsigned char ISendStr(unsigned char sla, unsigned char rla,unsigned char *s, unsigned char no)
{
  unsigned char i;

  StartI2c();//��������
  SendByte(sla);//����������ַ
  if(ack==0)
    return(0);

  SendByte(rla);//���������ӵ�ַ
  if(ack==0)
    return(0);

  for(i=0; i<no; i++)
  {
    SendByte(*s);//��������
    if(ack==0)
      return(0);

    s++;
  }

  StopI2c();//��������

  return(1);
}

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
unsigned char IRcvStr(unsigned char sla, unsigned char *suba, unsigned char *s, unsigned char subano, unsigned char no)
{
  unsigned char i;

  StartI2c();//��������
  SendByte(sla);//����������ַ

  if(ack==0)
    return(0);

  for(i=0; i<subano; i++)
  {
    SendByte(*suba);//���������ӵ�ַ
 
    if(ack==0)return(0);
      suba++;
  }

  StartI2c();
  SendByte(sla+1);

  if(ack==0)
    return(0);

  for(i=0; i<no-1; i++)
  {  
    *s=RcvByte();//��������
    AckI2c(0);//���;ʹ�λ
 
    s++;
  }

  *s=RcvByte();
  AckI2c(1);//���ͷ�Ӧλ
  StopI2c();//��������

  return(1);
}

//****************************************************************************************************************************************

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
void StartI2c2(void)
{
  DAT2_O;
  CLK2_O;
  delay_us(1);

  DAT2_H;//������ʼ�����������ź�
  delay_us(1);

  CLK2_H;
  delay_us(1);//��ʼ��������ʱ�����4.7us,��ʱ
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  DAT2_L;//������ʼ�ź�
  delay_us(1);//��ʼ��������ʱ�����4��s
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK2_L;//ǯסI2C���ߣ�׼�����ͻ��������
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
void StopI2c2(void)
{
  DAT2_O;
  CLK2_O;
  delay_us(1);

  DAT2_L;//���ͽ��������������ź�
  delay_us(1);

  CLK2_H;//���ͽ���������ʱ���ź�
  delay_us(1);//������������ʱ�����4��s
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  DAT2_H;//����I2C���߽����ź�
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
void SendByte2(unsigned char c)
{
  unsigned char BitCnt;

  DAT2_O;
  CLK2_O;
  delay_us(1);

  for(BitCnt=0; BitCnt<8; BitCnt++)//Ҫ���͵����ݳ���Ϊ8λ
  {
    if(c&0x80)
      DAT2_H;//�жϷ���λ
    else
      DAT2_L;

    c<<=1;
    delay_us(1);

    CLK2_H;//��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
    delay_us(1);
    delay_us(1);//��֤ʱ�Ӹߵ�ƽ���ڴ���4��s*/
    delay_us(1);
    delay_us(1);
    delay_us(1);

    CLK2_L;
  }

  delay_us(1);
  delay_us(1);

  DAT2_H;//8λ��������ͷ������ߣ�׼������Ӧ��λ
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
    ack=1;//�ж��Ƿ���յ�Ӧ���ź�

  CLK2_L;
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
unsigned char RcvByte2(void)
{
  unsigned char retc;
  unsigned char BitCnt;

  retc=0;

  DAT2_O;
  CLK2_O;
  delay_us(1);

  DAT2_H;//��������Ϊ���뷽ʽ
  DAT_I;
  delay_us(1);

  for(BitCnt=0; BitCnt<8; BitCnt++)
  {
    delay_us(1);

    CLK2_L;//��ʱ����Ϊ�ͣ�׼����������λ
    delay_us(1);
    delay_us(1);//ʱ�ӵ͵�ƽ���ڴ���4.7��s
    delay_us(1);
    delay_us(1);
    delay_us(1);

    CLK2_H;//��ʱ����Ϊ��ʹ��������������Ч
    delay_us(1);
    delay_us(1);

    retc=retc<<1;

    if(DAT2_D)
      retc=retc+1;//������λ,���յ�����λ����retc��

    delay_us(1);
    delay_us(1);
  }

  CLK2_L;   
  delay_us(1);
  delay_us(1);

  return(retc);
}

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
void AckI2c2(unsigned char a)
{
  DAT2_O;
  CLK2_O;
  delay_us(1);

  if(a==0)
    DAT2_L;//�ڴ˷���Ӧ����Ӧ���ź�
  else
    DAT2_H;

  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK2_H;
  delay_us(1);//ʱ�ӵ͵�ƽ���ڴ���4��s
  delay_us(1);
  delay_us(1);
  delay_us(1);
  delay_us(1);

  CLK2_L;//��ʱ���ߣ�ǯסI2C�����Ա��������
  delay_us(1);
  delay_us(1);
}

/*******************************************************************************
* ��    �ƣ�
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
*******************************************************************************/
unsigned char ISendStr2(unsigned char sla, unsigned char rla,unsigned char *s, unsigned char no)
{
  unsigned char i;

  StartI2c2();//��������
  SendByte2(sla);//����������ַ
  if(ack==0)
    return(0);

  SendByte2(rla);//���������ӵ�ַ
  if(ack==0)
    return(0);

  for(i=0; i<no; i++)
  {
    SendByte2(*s);//��������
    if(ack==0)
      return(0);

    s++;
  }

  StopI2c2();//��������

  return(1);
}

