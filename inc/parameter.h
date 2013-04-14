
#ifndef __PARAMETER_H
#define __PARAMETER_H
/* Includes ------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define AUTORELOAD	0x1999	//sampling period definition (trigg period)
#define NUMB_SAMP	8       //number of samples for SW filtering
#define PEAK_FILTER	8	//  floating spot fall speed filter
#define AD_STAB		20	//  AD stabilization [TIM1 increments] (~10us)

#define MAXTASKS        8
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

//���尴��
#define KEY_GPIO_PORT  (GPIOE)
#define KEY_GPIO_PINS  (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6)
#define KEY_MENU     GPIO_PIN_1    
#define KEY_FRQ      GPIO_PIN_2
#define KEY_REDUCE   GPIO_PIN_5
#define KEY_PLUS     GPIO_PIN_6

//�����������
#define MODE_R	     0
#define MODE_C       1
#define MODE_L       2

//Ƶ��ѡ�� 
#define SEL_100      0
#define SEL_1K       1	 
#define SEL_7K8      2

//����Ƶ�ʿ��ƶ˿�
#define FRQ_GPIO_PORT  (GPIOA)
#define FRQ_GPIO_PINS  (GPIO_PIN_4 | GPIO_PIN_5)
#define FRQ_100 	{GPIO_WriteLow(FRQ_GPIO_PORT, GPIO_PIN_4); \
								GPIO_WriteHigh(FRQ_GPIO_PORT,GPIO_PIN_5); }
#define FRQ_1K  {GPIO_WriteLow(FRQ_GPIO_PORT, GPIO_PIN_4); \
								GPIO_WriteLow(FRQ_GPIO_PORT,GPIO_PIN_5); }
#define FRQ_7K8 {GPIO_WriteHigh(FRQ_GPIO_PORT, GPIO_PIN_4); \
								GPIO_WriteLow(FRQ_GPIO_PORT,GPIO_PIN_5); }

//����ѡ�� 
#define RNG_40       0
#define RNG_1K       1	 
#define RNG_10K      2
#define RNG_100K     3

//�������̿���
#define RANGE_GPIO_PORT  (GPIOC)
#define RANGE_GPIO_PINS  (GPIO_PIN_5 | GPIO_PIN_6)
#define RANGE_40  {GPIO_WriteLow(RANGE_GPIO_PORT, GPIO_PIN_5); \
								GPIO_WriteLow(RANGE_GPIO_PORT,GPIO_PIN_6); }
#define RANGE_1K   {GPIO_WriteLow(RANGE_GPIO_PORT, GPIO_PIN_5); \
								GPIO_WriteHigh(RANGE_GPIO_PORT,GPIO_PIN_6); }
#define RANGE_10K   {GPIO_WriteHigh(RANGE_GPIO_PORT, GPIO_PIN_5); \
								GPIO_WriteLow(RANGE_GPIO_PORT,GPIO_PIN_6); }
#define RANGE_100K   {GPIO_WriteHigh(RANGE_GPIO_PORT, GPIO_PIN_5); \
								GPIO_WriteHigh(RANGE_GPIO_PORT,GPIO_PIN_6); }

//�������濪��
#define GAIN_GPIO_PORT (GPIOD)
#define GAIN_GPIO_PINS (GPIO_PIN_5 | GPIO_PIN_6 )
#define GAIN_1 {GPIO_WriteLow(GAIN_GPIO_PORT, GPIO_PIN_5); \
								GPIO_WriteLow(GAIN_GPIO_PORT,GPIO_PIN_6); }
#define GAIN_3 {GPIO_WriteLow(GAIN_GPIO_PORT, GPIO_PIN_5); \
								GPIO_WriteHigh(GAIN_GPIO_PORT,GPIO_PIN_6); }				
#define GAIN_9 {GPIO_WriteHigh(GAIN_GPIO_PORT, GPIO_PIN_5); \
								GPIO_WriteLow(GAIN_GPIO_PORT,GPIO_PIN_6); }								
#define GAIN_27 {GPIO_WriteHigh(GAIN_GPIO_PORT, GPIO_PIN_5); \
								GPIO_WriteHigh(GAIN_GPIO_PORT,GPIO_PIN_6); }

//ADC����
#define ADC_GPIO_PORT  (GPIOB)
#define ADC_INPUT  GPIO_PIN_3

#define ADC_TIM_PORT   (GPIOC)
#define ADC_TIM_PIN   GPIO_PIN_1


#endif
