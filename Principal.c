#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "ServoMtr.h"
#define ARR2 1439
#define PSC2 0
#define IDX 6
#define Duree 20
int res=0;
int dc;
int res2=0;

int main ( void )
{
	int test = 0;
	
	//configuration du tim2 pour le codeur incrémental
	
	//activation du timer2 en prenant 
	MyTimer_Struct_TypeDef MTIM2={TIM2,ARR2,PSC2};
	
	//activation des pins PA0 et PA1 du GPIOA 
	MyGPIO_Struct_TypeDef MGPIOA0={GPIOA,0,In_Floating};//PA0 en floating input
	MyGPIO_Struct_TypeDef MGPIOA1={GPIOA,1,In_Floating};//PA1 en floating input
	//on utilise le PC6 pour lire l'index du codeur incremental
	MyGPIO_Struct_TypeDef MGPIOC6={GPIOC,6,In_Floating};//PC6 en floating input
	
	MyTimer_Base_Init(&MTIM2);
	MyGPIO_Init (&MGPIOA0) ;//PA0 en floating input
	MyGPIO_Init (&MGPIOA1) ;//PA1 en floating input
	MyGPIO_Init (&MGPIOC6) ;//PC6 en floating input
	//On met TIM2_SMCR à 011 pour compter dans Tl1 ainsi que dans Tl2
	TIM2->SMCR &= ~(0x07);
	TIM2->SMCR |=(0x03);
	
	Timer_PWM_Init(TIM3,Duree,1);
	Init_SERVOMTR();
	
	while(test == 0){
		test = (GPIOC->IDR	& (0x01<<IDX));
	}
	
	TIM2->CNT=0;//on reset le CNT car on est à l'origine
	
	while (1){
		res=(TIM2->CNT)/4;//on lit l'angle obtenu
		dc=Calcul_DutyCycle_SERVOMTR(res);
		Timer_PWM_DutyCycle_Fix(TIM3,dc,1);
		res2=TIM3->CCR3;
	}
}
