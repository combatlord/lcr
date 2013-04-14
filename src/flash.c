

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "flash.h"

void eep_unlock(void)               //����eep���
{
   FLASH->CR1 |= 0x01;
   do
   {
    FLASH->DUKR=EEPMASS1;                        //��1��Կ  
    FLASH->DUKR=EEPMASS2;                        //��2��Կ
   }
   while(!(FLASH->IAPSR&0x08));                  //�ȴ����ܾ���         
}

/**
  *****************************************************************
  * @brief flash write byte
  * @par Parameters: address
  * @par Parameters: data
  * @retval void None
  * @par Required preconditions: None
  *****************************************************************
  */
void Write_Byte (unsigned int address,unsigned char Data)
{   
    FLASH->DUKR = 0xAE;
    FLASH->DUKR = 0x56;
    FLASH->CR2 = 0x00;
    FLASH->NCR2 = 0xFF;
    *((u8*)address) = Data;
    FLASH->IAPSR = (u8)(~0x08);
}

/*
��ȡeep
unsigned char *data   �����������ݷŽ�ָ��p
unsigned char len  ������ȡ�����ݸ���
unsigned short eep_addr д�뿪ʼ��ַ
*/
void eep_word_read(u8 *data,u8 len,u16 eep_addr)
{
      u8 *eep=(u8*)eep_addr;
      u8  j;
      for(j=0; j<len;j++)
      {
          *data=*eep;            
          eep++;
          data++;
      }
}
/*
unsigned char *data  Ҫд���������Դ
unsigned char len  д��������������˴��������4���ֽڣ��������������
unsigned short eep_addr д�뿪ʼ��ַ
*/
void eep_word_write(u8 *data,u8 len,u16 eep_addr)
{
  u8 *eep=(u8*)eep_addr;
  u8  j;
  eep_unlock();
  for(j=0;j<len;j++)
   {
      *eep=*data;
       data++;
       eep++;
       EEPROM_WaitForLastOperation();
    }
   EEP_PROG_OFF;         
}


