 
#ifndef __PTASK_H
#define __PTASK_H

#include "parameter.h"
//#define MAXTASKS 8
 
#define lc_type  unsigned char
#define SEM unsigned int 

//volatile unsigned char timers[MAXTASKS];

/******************************************************
Micro    : PTH_BEGIN
Note     : �������������ں�����ʼ��
Updata   : 2012-12-14
*******************************************************/
#define PTH_BEGIN                                      \
    static lc_type _lc; switch(_lc){default: 

   
/******************************************************
Micro    : PTH_END
Note     : ��������,���ں��������
Updata   : 2012-12-07
*******************************************************/
#define PTH_END                 ;};  _lc=0; return 255;



//��ʱ�ȴ���tickets ���Ϊ250
#define WaitX(tickets) do {_lc=__LINE__+((__LINE__%256)==0); \
       	return tickets;} while(0); case __LINE__+((__LINE__%256)==0): 

//��ʱ���ĸ�ֵ�������������������࣬ԭ�ж�ʱ�����ֵĸ�ֵ�����Ǳ���ģ�����������Ȼ�����⣺��ѭ�����е�������Ϊѭ�����С�
#define RunTask(TaskName,TaskID) do { if (timers[TaskID]==0) \
   timers[TaskID]=TaskName();}  while(0);
//ǰ����������ȱ�ִ֤�� 
#define RunTaskA(TaskName,TaskID) { if (timers[TaskID]==0) \
	{timers[TaskID]=TaskName(); continue;} }  

#define CallSub(SubTaskName) do {lc_type currdt; WaitX(0); \
   currdt=SubTaskName(); if(currdt!=255) return currdt;} while(0);
 

#define UpdateTimers() {unsigned char i; for(i=MAXTASKS;i>0;i--) \
 {if((timers[i-1]!=0)&&(timers[i-1]!=255)) timers[i-1]--;}}

//��ʼ���ź���
#define InitSem(sem) sem=0;
//�ȴ��ź���
#define WaitSem(sem) do{ sem=1; WaitX(0); if (sem>0) return 1;} while(0);
//�ȴ��ź�����ʱ������� ��ʱ��tickets ���Ϊ0xFFFE
#define WaitSemX(sem,tickets)  do { sem=tickets+1; WaitX(0);  \
  if(sem>1){ sem--; return 1;} } while(0);
//�����ź���
#define SendSem(sem)  do {sem=0;} while(0);


#endif
