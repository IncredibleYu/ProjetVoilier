#include "stm32f10x.h"
#include "MyTimer.h"

void (*p_function)(void);

void MyTimer_Base_Init( MyTimer_Struct_TypeDef * Timer )
{
	//on branche le timer
	
		if(Timer->Timer==TIM1)RCC->APB2ENR |=RCC_APB2ENR_TIM1EN;
		else if (Timer->Timer==TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		else if (Timer->Timer==TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		else RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
							
	//on fixe la période demandée
	Timer->Timer->ARR=Timer->ARR;
	Timer->Timer->PSC=Timer->PSC;
	//on active le compteur
	Timer->Timer->CR1|=0x01;
}

void MyTimer_Active_IT ( TIM_TypeDef * Timer , char Prio,void (*IT_function)(void)) 
{
	Timer->DIER|=0x01;//demande d'interruption au debordement de timer
	if (Timer==TIM1)
	{		NVIC_EnableIRQ((IRQn_Type)(25));
			NVIC_SetPriority((IRQn_Type)(25),Prio);
	}
	else if (Timer==TIM2) 
	{
		NVIC_EnableIRQ(28);
		NVIC_SetPriority(28,Prio);
	}
	else if (Timer==TIM3)
	{
		NVIC_EnableIRQ(29);
		NVIC_SetPriority(29,Prio);
	}
	else 
	{
		NVIC_EnableIRQ(30);
		NVIC_SetPriority(30,Prio);
		
	}
	
	p_function= IT_function;
	
}	

void TIM1_UP_IRQHandler(void)
{
	(*p_function) ();
	TIM1->SR&= ~(0x01);//remet le bit activé à 0
}

void TIM2_IRQHandler(void)
{
	(*p_function) ();
	TIM2->SR&= ~(0x01);//remet le bit activé à 0
}

void TIM3_IRQHandler(void)
{
	(*p_function) ();
	TIM3->SR&= ~(0x01);//remet le bit activé à 0
}

void TIM4_IRQHandler(void)
{
	(*p_function) ();
	TIM4->SR&= ~(0x01);//remet le bit activé à 0
}



