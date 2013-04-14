//==========================================================================
//  ESR���������� V2.0
//  ��ΰ ������ 2012.10
//==========================================================================
//==========================================================================
#define uchar unsigned char
#define uint  unsigned int
#define ulong  unsigned long
#include <reg52.h>

//==========================================================================
// ��Ŀ��LCD1602 ������������
// ���Ҫ�㣺
//     LCD1602 �������ٶ���������Ƭ�����е��ٶȿ죬���������Ϊ�ٶȲ�
//     ƥ����ɵ���ʧ�ܡ���ˣ�����֮ǰӦ׼ȷ����lcd_delay() ��ʱ����
//     ׼ȷ����ʱ���������������ע���е�Ҫ����Ӧ����ѭ������ÿ����
//     ���������ʱ�������������ֲ�ָ��ָ�У�ͬʱ�����㹻��ʱ��������
// Ӳ�����ӣ�
//     ������Ҫ9���ߣ���Դ��2����7���ź��ߡ��ź�����������еĽӿڶ��塣
//     ��ע���LCD1602�ȶԵĵ��ڣ���������ʾ��
// ��ƣ���ΰ,������,2010.12
//==========================================================================
sbit lcd_RS = P0^5; //�����������λ,0����1����
sbit lcd_RW = P0^6; //��дλ,0д1��
sbit lcd_EN = P0^4; //ʹ��λ,�½��ش���
sbit lcd_D4 = P0^3; //���ݶ˿�D4
sbit lcd_D5 = P0^2; //���ݶ˿�D5
sbit lcd_D6 = P0^1; //���ݶ˿�D6
sbit lcd_D7 = P0^0; //���ݶ˿�D7
//==========================================================================
void lcd_delay(int n){ //LCDר����ʱ����
  //32MHz��Ƶ�£�Լѭ��3000���ӳ�1����
  int i,j;
  if(n<0)    { for(i=0;i< 20;i++); return; } //10us
  if(n== 0)  { for(i=0;i<100;i++); return; } //50us
  for(;n;n--){ for(j=0;j<2000;j++);        } //n����
}
//==========================================================================
void lcd_B(char f, uchar c, char t){ //��������ʽ�ӿ�LCD��7����
  //f=0д������, f=1дRAM����, f=2����ַ�����æ��, f=3��RAM����
  lcd_EN = 0;
  lcd_RS = f%2;
  lcd_RW = f/2%2;
  //�������λ
  lcd_D4 = c & 16;
  lcd_D5 = c & 32;
  lcd_D6 = c & 64;
  lcd_D7 = c & 128;
  lcd_EN = 1;  lcd_delay(-1);  lcd_EN = 0; //ʹ������
  if(f==4) { lcd_delay(t); return; }
  //�������λ
  lcd_D4 = c & 1;
  lcd_D5 = c & 2;
  lcd_D6 = c & 4;
  lcd_D7 = c & 8;
  lcd_EN = 1;  lcd_delay(-1);  lcd_EN = 0; //ʹ������
  lcd_delay(t);  //��ͬ������,��Ӧʱ�䲻ͬ,����������Ҫ2ms
}
//==========================================================================
void lcd_init(){ //LCD1602 ��ʼ��
  //��������ģʽ������9�����裬��ʼ�������ʱ�ϳ���Լ65ms��ʱ�޲��ɼ�
  lcd_delay(20); //����lcd֮ǰ����ʱ����15ms��ֱ��VDD����4.5V
  lcd_B(4, 0x30, 9); //��8��ģʽ,����ʱ����4.1ms
  lcd_B(4, 0x30, 5); //��8��ģʽ,����ʱ����100us
  lcd_B(4, 0x30, 5); //��8��ģʽ,�ֲ���δָ����ʱ
  lcd_B(4, 0x20, 5); //��������ģʽ
  lcd_B(0, 0x28, 5); //����ģʽ˫����ʾ
  lcd_B(0, 0x0C, 5); //����ʾ��
  lcd_B(0, 0x80, 5); //RAMָ�붨λ
  lcd_B(0, 0x01, 5); //������������ʼ��LCD
}
//==========================================================================
//=========================�������ܳ��ú���=================================
void lcd_cls()         { lcd_B(0, 0x01+0, 2);  } //����
void lcd_cur0()        { lcd_B(0, 0x0C+0, 0);  } //���ع��
void lcd_goto1(uchar x){ lcd_B(0, 0x80+x, 0);  } //����DDRAM��ַ,��1��xλ
void lcd_goto2(uchar x){ lcd_B(0, 0xC0+x, 0);  } //����DDRAM��ַ,��2��xλ
void lcd_putc(uchar d) { lcd_B(1, 0x00+d, 0);  } //�ַ����
void lcd_puts(uchar *s){ for(; *s; s++) lcd_B(1,*s,0); } //�ִ����
//==============�ַ���ʾ����====================
#define digW 4 //������ʾλ����
void lcd_puti(int a,char w){ //������ʾ������
  char i=0, s[5] = {' ',' ',' ',' ',' '};
  if(a<0) { a=-a; lcd_puts("-"); }
  else    lcd_puts(" ");
  do{
   s[i++] = a%10+48;
   a /= 10;
  }while(a);
  for(;w;w--) lcd_putc(s[w-1]);
}
void lcd_putf(float a,char n,char w){ //���������n�Ǳ���С����λ��,w�����ֿ��
 char i,g,fi=0;
 long b,c=1;
 if(a<0) { lcd_putc('-'); a = -a; }
 else    { lcd_putc(' '); }
 for(i=0;i<n;i++) a *= 10;
 for(i=1;i<w;i++) c *= 10;
 b = a;
 for(i=0;i<w;i++){
  g = b/c;
  b -= g*c;
  c /= 10;
  if(g>9||g<0) g='*'-48;
  if(i == w-n ) lcd_putc('.');
  if(!g && !fi && i<w-n-1) { lcd_putc(' '); continue; }
  lcd_putc(g+48);
  fi = 1;
 }
 if(!n) lcd_putc(' '); //��С����Ĳ�����ʾ���
}

//==========================================================================
//===============================��ʱ����===================================
void delay(uint loop) { uint i; for(i=0;i<loop;i++); } //��ʱ����
void delay2(uint k)   { for(;k>0;k--) delay(10000);  } //����ʱ,k=100��Լ��Ӧ1��

//==========================================================================
//=================================ADת��===================================
sfr P1ASF = 0x9D;     //��P1��Ϊģ��ڼĴ���(ʹ��),��λ��Ϊ1����Ч
sfr ADC_CONTR = 0xBC; //A/Dת�����ƼĴ���
sfr ADC_res   = 0xBD; //A/Dת������Ĵ���
sfr ADC_resl  = 0xBE; //A/Dת������Ĵ���

void set_channel(char channel){
 P1ASF = 1<<channel;
 ADC_CONTR = channel+128; //���λ�ǵ�Դ����,��3λͨ��ѡ��
 delay(1); //�״δ򿪵�ԴӦ�ӳ٣�ʹ�����ȶ�
}
uint getAD2(){
 ADC_CONTR |= 0x08;             //00001000,��ADC_START=1����A/D ת��
 while ( !(ADC_CONTR & 0x10) ); //�ȴ�A/Dת������(ADC_FLAG==0)
 ADC_CONTR &= 0xE7;             //11100111,��ADC_FLAG=0����������, ��ADC_START=0�ر�A/D ת��
 return ADC_res*4 + ADC_resl;
}
/*
uchar get_AD(){
 ADC_CONTR |= 0x08;             //00001000,��ADC_START=1����A/D ת��
 while( !(ADC_CONTR & 0x10) );  //�ȴ�A/Dת������(ADC_FLAG==0)
 ADC_CONTR &= 0xE7;             //11100111,��ADC_FLAG=0����������, ��ADC_START=0�ر�A/D ת��
 return ADC_res;
}
*/


//==========================================================================
//==================================EEPROWƫ��==============================
sfr IAP_data  = 0xC2;
sfr IAP_addrH = 0xC3;
sfr IAP_addrL = 0xC4;
sfr IAP_cmd   = 0xC5;
sfr IAP_trig  = 0xC6;
sfr IAP_contr = 0xC7;
/********************
д�ֽ�ʱ�����Խ�ԭ�������е�1��Ϊ0���޷���0��Ϊ1��ֻ��ʹ�ò������0��Ϊ1
Ӧע�⣬��������Ὣ������������
*********************/
int eepEn = 0;
void saEEP(){ //������EEP����
 if(eepEn==12345) IAP_trig = 0x5A;  //����5A
 if(eepEn==12345) IAP_trig = 0xA5;  //����5A����A5��������
 IAP_cmd = 0;      //�ر������
 IAP_contr = 0;    //��EEPROM������
 IAP_trig = 0;
 IAP_addrL = 255; //���ö�ȡ��ַ�ĵ��ֽڣ���ַ�ı����Ҫ����
 IAP_addrH = 255; //���ö�ȡ��ַ�ĸ��ֽڣ���ַ�ı����Ҫ����
}
uchar readEEP(uint k){ //��ȡ
 IAP_addrL = k;    //���ö�ȡ��ַ�ĵ��ֽڣ���ַ�ı����Ҫ����
 IAP_addrH = k>>8; //���ö�ȡ��ַ�ĸ��ֽڣ���ַ�ı����Ҫ����
 IAP_contr = 0x81; //���õȴ�ʱ�䣬1MHz����ȡ7��2M����ȡ6��3Mȡ5��6Mȡ4��12Mȡ3��20Mȡ2��24Mȡ1��30Mȡ0��ǰ��1��ʾ��IAP
 IAP_cmd = 1;      //��ȡֵ1��дȡ2������ȡ3������ʱ�������ֽ���������ߥ��
 saEEP(); //����������
 return IAP_data;
}
void writeEEP(uint k, uchar da){ //д��
 IAP_data = da;    //��������
 IAP_addrL = k;    //���ö�ȡ��ַ�ĵ��ֽڣ���ַ�ı����Ҫ����
 IAP_addrH = k>>8; //���ö�ȡ��ַ�ĸ��ֽڣ���ַ�ı����Ҫ����
 IAP_contr = 0x81; //���õȴ�ʱ�䣬1MHz����ȡ7��2M����ȡ6��3Mȡ5��6Mȡ4��12Mȡ3��20Mȡ2��24Mȡ1��30Mȡ0��ǰ��1��ʾ��IAP
 IAP_cmd = 2;      //��ȡֵ1��дȡ2������ȡ3������ʱ�������ֽ���������ߥ��
 saEEP(); //����������
}
void eraseEEP(uint k){ //����
 IAP_addrL = k;    //���ö�ȡ��ַ�ĵ��ֽڣ���ַ�ı����Ҫ����
 IAP_addrH = k>>8; //���ö�ȡ��ַ�ĸ��ֽڣ���ַ�ı����Ҫ����
 IAP_contr = 0x81; //���õȴ�ʱ�䣬1MHz����ȡ7��2M����ȡ6��3Mȡ5��6Mȡ4��12Mȡ3��20Mȡ2��24Mȡ1��30Mȡ0��ǰ��1��ʾ��IAP
 IAP_cmd = 3;      //��ȡֵ1��дȡ2������ȡ3������ʱ�������ֽ���������ߥ��
 saEEP(); //����������
}


xdata struct Ida{
 int x0;  //����ʱ�̵�72kHz��㣬0��
 int y0;  //����ʱ�̵�72kHz��㣬270��
 int z0;  //����ʱ�̵�6kHz��㣬270��
 int d0;  //����ʱ�̵�ǰ��ֱ��ƫ��
 char Vp; //����У׼��
 char J0; //��λУ׼��
 char J1; //��λУ׼��2
 char Cm; //�����У׼
 int a0;  //72k,90������,L
 int b0;  //03k,90������,L
 int g0;  //ֱ�����,L
 int a1;  //20ŷ����Ĳ���翹,L����������
 int b1;  //20ŷ����Ĳ���翹,L����������
 int c1;  //ֱ�����������AD���ƫ��(��L������)
} cs;

void cs_RW(char rw){
 uchar i,*p = &cs;
 const int offs=512;
 if(rw){
  eraseEEP(offs);
  for(i=0;i<sizeof(cs);i++) writeEEP(i+offs,p[i]);
 }else{
  for(i=0;i<sizeof(cs);i++) p[i]=readEEP(i+offs);
 }
}
//==============�����������ź�====================
//PCA��ؼĴ���
sfr CMOD = 0xD9;   //��Դѡ����Ƶ�
sfr CH = 0xF9;     //PCA�ļ�����
sfr CL = 0xE9;     //PCA�ļ�����
sfr CCON = 0xD8;   //PCA���ƼĴ���
sfr CCPAM0 = 0xDA; //PCAģ��0����ģʽ�Ĵ���
sfr CCPAM1 = 0xDB; //PCAģ��1����ģʽ�Ĵ���
sfr CCAP0L = 0xEA; //ģ��0����Ĵ�����λ
sfr CCAP0H = 0xFA; //ģ��0����Ĵ�����λ

sbit PPCA  = IP^7;   //PCA���ж����ȼ�����
sbit CCF0  = CCON^0; //PCA��ģ��0�жϱ�־
sbit CCF1  = CCON^1; //PCA��ģ��1�жϱ�־
sbit CR = CCON^6;    //PCA������ʹ��

void PWM_init(){ //��PCA��ΪPWM
  CMOD = 0;   //0000 0010 ����Դѡ��,��Դȡfosc/2, 0000 0000��fosc
  CL = CH = 0;
  CCAP0L = CCAP0H = 128; //ռ�ձ�Ϊ50%
  CCPAM0=0x42;//0100 0010,PCA��ģ��0����ΪPWMģʽ,���ж�
  //CCPAM0=0x53;//0101 0011,PCA��ģ��0����ΪPWMģʽ,���жϣ��½����ж�
  //PPCA = 1;   //�����ж�
  CR = 1;   //��ʼ����
  //EA = 1;     //�����ж�
}


//==========================================================================
//==================================ESR������===============================
//==========================================================================
sfr P1M1=0x91; //P1�˿����üĴ���
sfr P1M0=0x92; //P1�˿����üĴ���
sfr P0M1=0x93; //P0�˿����üĴ���
sfr P0M0=0x94; //P0�˿����üĴ���
sfr P2M1=0x95; //P2�˿����üĴ���
sfr P2M0=0x96; //P2�˿����üĴ���
sfr P3M1=0xB1; //P3�˿����üĴ���
sfr P3M0=0xB2; //P3�˿����üĴ���
sfr WAKE_CLKO = 0x8F;
sfr AUXR = 0x8E;
sfr BRT = 0x9C;


sbit pt0=P3^4;  //�����ź����
sbit pt1=P3^5;  //�����źſ���
sbit DCo=P1^6;  //ֱ���ź����
sbit pwk=P2^0;  //��Դ���ؿ�
sbit pwK=P2^1;  //��Դ���ؿ�2
xdata uchar menu=0,menu2=0; //�˵�����



//==============ESR����====================
ulong nn = 0; //ʱ�������
uchar nn2 = 0;

//=====�ɱ��ʱ�ӷ�����======
//ÿ���һ�˼�����TL0��TL1��װ��������÷����������˼���������������������������2*(256-THx)��
//THxȡ128�����������2*(256-128)=256��������256��ʱ������
uchar XW=0;
void feqInit(){
  WAKE_CLKO |= 0x07; //����T0 T1 BRT��������ʱ��,�������˷ŵ�Դ
  TMOD = 0x22;  //T0��T1������8λ�Զ���װ
  AUXR |= 0x80; //T0������1T
  AUXR |= 0x40; //T1������1T
  AUXR |= 0x04; //���������ʷ�����������1T
  TH0 = 128;    //��T0Ƶ����
  TH1 = 128;    //��T1Ƶ����
  BRT = 156;    //��BTRƵ��
  TL0 = 0;      //�ó���Ϊ0
  TL1 = 0;      //�ó���Ϊ0(TR1������ʱ4���ڣ����Բ���4��)
  AUXR |= 0x10; //����BRT,P1.0�����
  TCON |= 0x50; //����T0��T1,T0��T1�ֱ���P3.4��P3.5���,ͬʱ��1����.�����TR0=1,TR1=1,��1TʱTL1Ӧ����4��.
}
void setXW(uchar xw,uchar bc){ //xwΪ�������(360�ȶ�Ӧ256��),bc��������(72kHz��4��)
  uint m = 256-TH0;            //�����ڵļ���ֵ
  uint n = (m*xw+64)/128+bc;   //�任Ϊ����ƫ����,��TR1��TR0����������4������ʱ���������Ȳ���4��
  XW = xw;
  TR0 = 0, TR1 = 0;     //��ͣ����
  pt0 = 0, pt1 = n/m%2; //ͬ����ദ��
  TL0 = 0, TL1 = n % m; //����λ��
  TCON |= 0x50; //TR0��TR1ͬʱ��1����T0��T1.�����TR0=1,TR1=1;��1TʱbcӦ����4��
}
void setFeq(char k,uchar w){ //����Ƶ��,w����λ
  if(k==4){ //ֱ���������ʹ��
	P3M1 |= 0x10, P3M0 &= ~0x10; //P3.4��Ϊ�����
    P1M0 |= 0x40, P1M1 &= ~0x40; //P1.6��Ϊ�����
	TR0 = TR1 = 0; //ֹͣ������
    pt1 = 1; //P3.5��·
	DCo = 1; //����ֱ��Դ
	return;
  }
  //�����迹����ʹ��
  P1M1 |= 0x40, P1M0 &= ~0x40; //P1.6��Ϊ�����
  P3M0 |= 0x10, P3M1 &= ~0x10; //P3.4��Ϊ�����
  if(k==0){ AUXR |=  0x80;  AUXR |=  0x40;  TH0=128, TH1=128; } //1Tģʽ, ��Ϊ˫72kHz
  if(k==1){ AUXR &= ~0x80;  AUXR &= ~0x40;  TH0=0,   TH1=0;   } //12Tģʽ,��Ϊ˫3kHZ
  if(k==2){ AUXR |=  0x80;  AUXR |=  0x40;  TH0=128, TH1=0;   } //1Tģʽ, �ź�Դ72kHz���첨��36kHz
  if(k==3){ AUXR |=  0xC0;  TH0=128; TR0=1; TR1=pt1=0; return;} //1Tģʽ, �ź�Դ72kHz���첨��0Hz
  setXW(w,0);
}
uint getAD10() { //������
 //ÿ��ȡ���ٶ�Ϊ2.48��
 int i;
 long c = 0;
 for(i=0;i<500;i++) c += getAD2();
 c = (c+25)/50;
 return c;
}
void putCx(float C){ //��ʾ���ݣ�ռ��LCD��7�ַ�
  char xs = 0;
  float d=C;
  if(d<0) d = -d;
  if(d>=10000) { lcd_puts(" OL    "); return; }
  if(d<10000) xs = 0;
  if(d<1000)  xs = 1;
  if(d<100)   xs = 2;
  if(d<10)    xs = 3;
  lcd_putf(C,xs,4);
  lcd_puts("u");
}
void putRx(float R,char n,char *dw){ //�������͵�λ,��������ʾ���衢���
  lcd_putf(R,n,4);
  lcd_puts(dw);
}
void putNx(char *Lb,int a,char n){ //�������
  lcd_puts(Lb);
  lcd_puti(a,n);
}

int Vx,Vy,Vz,Vd; //Vd�����ֱ��Ư��
float Vpp=52500,Vbat; //Vpp�źŵ�ѹ,Vbat��ص�ѹ
char Ha=0;
void ESRcalc(char jiao, char ha){
 const Bn = 3; //ʱ����
 char n = nn%(Bn*8);
 int v,vx,vy,vz,vd;
 float R=0,C=0,C2=0,e;
 if(n%Bn) return;
 n /= Bn;
 v = getAD10();
 if(n==0){ //��õ�Դ��ѹ
   set_channel(2); delay(10); Vpp  = getAD10()*8.05*(1+0.001*cs.Vp); //���źŵ�ѹ
   set_channel(7); delay(10); Vbat = getAD2()*0.00954;               //����ص�ѹ
   set_channel(1);
 }
 if(ha==0){ //������
   if(n==0){ Vd = v; setFeq(0,  0); return; } //������ֱ��,��Ϊ72kHz,0��
   if(n==1){ Vx = v; setFeq(0,192); return; } //���x���ѹ,��72kHz,270��
   if(n==2){ Vy = v; setFeq(1,192); return; } //���y���ѹ,�õ�Ƶ,270��
   if(n==3){ Vz = v; setFeq(2,  0);         } //��Ƶ���y���ѹ,��Ϊ�����Ƶ�� 
   vd = Vd - cs.d0;
   vx = Vx - cs.x0 - vd;
   vy = Vy - cs.y0 - vd;
   vz = Vz - cs.z0 - vd + cs.Cm;
   e = 1.0*vy/Vpp; e = e*(1+e*e*1.7);
   C = 14.05/8/104/e;     //��������ʽ (T/8)*(A/vy)/R,�������ֱ��������260ŷ��ֱ������20k��Ҫ����0.9%
   v = vy*(1.333*e + 0.005*cs.J1*e - 0.001*cs.J0);//������������,����ϵ����1.333��ʵ�����1.38�ȽϺ�
   R = 1.0*(vx-v)/(Vpp-vx)*104; //�������
   if(Vz<9800){ //��Ƶ������
     e = vz/Vpp; e = e*(1+e*e*1.7);
     C2 = 14.05/8/104/e*24;
   }
   if(jiao==0){ //������ʾ
    if(Vx>9800||Vy>9800){ //���������
      lcd_goto1(0); lcd_puts("Overflow        ");
      lcd_goto2(0); lcd_puts("C<120n or R>18R ");
      return;
    }
    lcd_goto1(0); lcd_puts("R=");  putRx(R,2,"\xF4"); putRx(Vbat,2,"V");//�������͵�ص�ѹ
    lcd_goto2(0); lcd_puts("C=");  putCx(C);          putCx(C2);        //�������
   }
   if(jiao==1) { //������ʾ
    lcd_goto1(0); putNx("D=",cs.d0,4); putNx(" d=",vd,5); //���ֱ��
    lcd_goto2(0); putNx("X=",cs.x0,4); putNx(" x=",vx,5); //��ʾVx
   }
   if(jiao==2) { //������ʾ
    lcd_goto1(0); putNx("Y=",cs.y0,4); putNx(" y=",vy,5); //��ʾVy
    lcd_goto2(0); putNx("Z=",cs.z0,4); putNx(" z=",vz,5); //��ʾVz
   }
   //У׼��ʾ���
   if(jiao==4){ //�����У׼,�������72k����3kHz����Զ������Ч�����ã����˹�У׼���������ơ�
    lcd_goto1(0); lcd_puts("C=");  putCx(C2);
    lcd_goto2(0); putNx("Cm=",cs.Cm,5);
   }
   if(jiao>=5) { lcd_goto1(0); lcd_puts("R=");  putRx(R,2,"\xF4"); } //�������
   if(jiao==5) { lcd_goto2(0); putNx("Vp=",cs.Vp,5);  }  //VpУ׼���
   if(jiao==6) { lcd_goto2(0); putNx("J0=",cs.J0,5);  }  //J0У׼���
   if(jiao==7) { lcd_goto2(0); putNx("J1=",cs.J1,5);  }  //J1У׼���
 }
 if(ha==1){ //����
   if(n==0){ Vd = v; setFeq(4, 0); return; } //������ֱ��,��Ϊ72kHz,90��
   if(n==1){ Vx = v; setFeq(0,64); return; } //��ֱ������
   if(n==2){ Vy = v; setFeq(1,64); return; } //���y���ѹ,�õ�Ƶ,90��
   if(n==3){ Vz = v; setFeq(3, 0); return; } //��Ƶ���y���ѹ,��Ϊ�����Ƶ�� 
   vd = Vd - cs.g0;
   vy = Vy - cs.a0 - vd;
   vz = Vz - cs.b0 - vd;
   vx = Vx + cs.c1;  if(vx<0) vx = 0; vx = vx*2/3; //�õ�ֱ������,��λ��0.01ŷ,ʵ���ϲ��220R����ֱ������Ĳ���,��Ϊ�������С��220R�ɺ����ԣ���vx����������

   vy -= cs.a1*(vx/2000.0); //cs.a1��20ŷ��Ӧ�ĵ翹ƫ��,72kHz
   vz -= cs.b1*(vx/2000.0); //cs.b1��20ŷ��Ӧ�ĵ翹ƫ��,3kHz

   e = 354.0/Vpp;
   if(jiao==0){ //��ʾ�����
    lcd_goto1(0); lcd_puts("72k L ="); if(Vy>9800) lcd_puts("Over     "); else putRx(e*vy*(1+0.00020*vx)     , 2,"uH "); //72kHz���
    lcd_goto2(0); lcd_puts("03k L ="); if(Vz>9800) lcd_puts("Over     "); else putRx(e*vz*(1+0.00014*vx)*24.3, 0,"uH "); //��Ƶ����
   }
   if(jiao==1){ //������ʾ
    lcd_goto1(0); lcd_puts("Ind    ");
	putNx("DCR=",vx,4);
    lcd_goto2(0); putNx("G=",cs.g0,4); putNx(" g=",vd,5); //���ֱ��
   }
   if(jiao==2){ //������ʾ
    lcd_goto1(0); putNx("A=",cs.a0,4); putNx(" a=",vy,5); //��ʾVa
    lcd_goto2(0); putNx("B=",cs.b0,4); putNx(" b=",vz,5); //��ʾVb
   }
 }
}

void shortCls(){ //��·����
 if(Ha&&Vx>2500&&Vx<3000){ //��в����ĵ����������,�����׼20R������������
  uchar i;
  cs.a1 = Vy-cs.a0, cs.b1 = Vz-cs.b0;
  lcd_cls(); lcd_puts("Measure AD zeor.");
  setFeq(4,0);
  DCo=0, cs.c1=0;
  for(i=0;i<200;i++){ //ÿѭ��Լ1msʱ��
    DCo = ~DCo;	delay(100); //����ռ�ձ�Ϊ1:10�ķ���
    DCo = ~DCo;	delay(900);
	if(i>=190) cs.c1 += getAD2(); //����ѹ,�������5%ʱ�����ѹ�������ϵĵ�ѹ����һ���ı������ã����getAD2()ռ�õ�ʱ����ȻӰ��ռ�ձȣ����Զ�ֵ׼ȷ��Ӱ���С
  }
  DCo=1, cs.c1 = 275 - cs.c1; //ÿ1ŷ150��,20//220=18.3,1/10��Ϊ1.83ŷ��Ӧ275��
  lcd_goto2(0); putNx("c1=",cs.c1,4);
  cs_RW(1); //����
  lcd_goto2(0); lcd_puts("Ind cleared.");
  delay2(100);
  return;
 }
 if(Ha) cs.g0 = Vd, cs.a0 = Vy, cs.b0 = Vz;             //�㡢72kHz(90��)��3kHz(90��) ��в���
 else   cs.d0 = Vd, cs.y0 = Vy, cs.z0 = Vz, cs.x0 = Vx; //�㡢72kHz(0��)�� 72kHz(270��)��3kHz(270��) ���ݲ���
 cs_RW(1); //����
 lcd_cls();
 lcd_puts("Zero... OK");
 delay2(100);
 Ha = (Ha+1)%2;
}

main(){
 uchar kn=0,key=0,keya=0,keyb=0; //������Ӧ����
 pwk = 0; //�򿪵�Դ
 //�˿ڳ�ʼ��
 P1M0 = 0x09;    //P1.0 P1.3��Ϊ�����
 P1M1 = 0x86;    //10000110 P1.1 P1.2 P1.7��Ϊ���迹
 P3M0 = 0x30;    //00110000 P3.4��Ϊ�����(T0���),P3.5��Ϊ��©
 P3M1 = 0x20;    //00100000
 P2M0 = 0x02;    //P2.1��Ϊ�����
 P2M1 = 0x02;    //P2.1��Ϊ�����

 feqInit();
 PWM_init();

 delay2(5);    //�ȴ���ѹ��Դ��ѹ����
 lcd_init();   //��ʼ��LCD
 lcd_cur0();   lcd_puts("ESR V2.0");   //���ع�겢��ʾƬ��
 lcd_goto2(0); lcd_puts("XJW Putian,2012"); //��ʾ����
 delay2(200);  lcd_cls(); //������ʱ
 eepEn= 12345;
 cs_RW(0);   //��EEPROM

 set_channel(1); //����ADת��ͨ��

 while(1){
  nn++;
  if(nn%100==0) nn2++; //�ػ���ʱ��,nn2ÿ����Լ3.0��
  if(nn2==200) pwk = 1; //�ص�Դ
  if(pwK){ //�ػ���
    delay(20000); //�ȴ������ȶ�
    while(pwK);	lcd_cls();	lcd_puts("Power off ..."); //���������ʾ׼���ػ��ź�
    for(kn=0;1;kn++){//��ʱ�������ٹػ���������ڼ�power���ذ����򲻹ػ���������LC�л�
	  if(kn==240) pwk = 1; //�ػ�
	  lcd_goto2(0); lcd_puti(kn/20,3);
	  if(pwK) { kn=0; break; } //power�ذ�������
	  delay(20000);
	}
    delay(20000); //�ȴ������ȶ�
    while(pwK); Ha = (Ha+1)%2;  //�������LC�л�����
    nn2 = 0; //�а����������ػ���ʱ����0
  }
  //ɨ�����
  key=0;  keya=keyb;  keyb=(~P3)&(128+64+8);
  if(keya){
   if(!keyb){ //������
     if(kn>2)  key = keya;   //�̰�
     if(kn>40) key = keya+1; //����,Լ1��2��
     kn = 0;
	 nn2 = 0; //�а����������ػ���ʱ����0
   }
   else kn += kn<255?1:0;
  }
  //�˵�ϵͳ
  if(key==128){ //�˵���
	lcd_cls();
	if(++menu>4) menu=0;
  }
  if(key==129){ //�������
   cs_RW(1);
   lcd_cls();
   lcd_puts("saved OK");
   delay2(100);
  }
  if(menu==0){ //��ʾESR
    static char jia=0; //��ʾ�����л�
    ESRcalc(jia,Ha);
	if(key==64) shortCls(); //��·����
	if(key==8) jia++, jia %= 3;
  }
  if(menu==1){ //VpУ׼
    ESRcalc(5,0);
    if(key==64) cs.Vp++;
    if(key==8)  cs.Vp--;
  }
  if(menu==2){ //J0У׼
    ESRcalc(6,0);
    if(key==64) cs.J0++;
    if(key==8)  cs.J0--;
  }
  if(menu==3){ //J1У׼
    ESRcalc(7,0);
    if(key==64) cs.J1++;
    if(key==8)  cs.J1--;
  }
  if(menu==4){ //CmУ׼
    ESRcalc(4,0);
    if(key==64) cs.Cm++;
    if(key==8)  cs.Cm--;
  }
  delay(20000);
 }//while end
}
//==========================================================================

