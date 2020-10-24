#ifndef __TIMER_H
#define __TIMER_H
#include "common.h"



void TIM1_Int_Init(u16 arr, u16 psc);
void TIM1_PWM_Init(u16 arr,u16 psc);

void TIM2_Int_Init(u16 arr, u16 psc);
void TIM2_PWM_Init(u16 arr, u16 psc);

void TIM3_Int_Init(u16 arr, u16 psc);
void TIM3_PWM_Init(u16 arr, u16 psc);

void TIM4_Int_Init(u16 arr, u16 psc);
void TIM4_PWM_Init(u16 arr, u16 psc);

//void TIM5_Int_Init(u16 arr, u16 psc);
//void TIM5_PWM_Init(u16 arr, u16 psc);

//void TIM6_Int_Init(u16 arr, u16 psc);

//void TIM7_Int_Init(u16 arr, u16 psc);


#endif
