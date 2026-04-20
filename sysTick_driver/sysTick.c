/*
 * sysTick.c
 *
 *  Created on: Jun 17, 2023
 *      Author: hp
 */


#include"sysTick.h"
#include<stdlib.h>

static systickCbf_t appcbf;

 void systick_start(void)
{
//systick->CR=start
}

 void systick_stop(void)
 {
	 //systick->CR=stop
 }

 void systick_setPeriodMs(uint8_t periodMs)
 {
	 //systick->reload=periomMs*tickTime
 }

  void systick_setCbf(systickCbf_t cbf)
  {
	  if (cbf!=NULL)
	  {
		 appcbf=cbf;
	  }
  }

 void systick_handler(void)
 {
	 if(appcbf)
	 {
		 appcbf();
	 }
 }
