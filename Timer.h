#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"

/************************
FONCTIONS GENERALES
************************/

// 	Activation Clock TIMER
void Timer_Active_Clock (TIM_TypeDef *Timer);


// Initialisation TIMER (NEW: ARR et PSC automatique pour une durée déterminée)
void Timer_Init(TIM_TypeDef *Timer, float Duree_us );


// Activation de l'interruption TIMER
void Timer_Active_IT( TIM_TypeDef *Timer, char Prio, void (*IT_function) (void) );


// Allumer TIMER
#define Timer_Start(Timer) 	(Timer->CR1 |= ( 1 << 0))


// Eteindre TIMER
#define Timer_Stop(Timer)    (Timer->CR1 &= ~( 1 << 0))

/************************
           PWM
************************/


//	Initialisation PWM du Timer
void Timer_PWM_Init(TIM_TypeDef *Timer, float Frequence_PWM_kHz, int Channel);


//	 Fixer la le rapport cyclique de la PWM 
void Timer_PWM_DutyCycle_Fix(TIM_TypeDef *Timer, int Duty_Cycle, int Channel);



#endif