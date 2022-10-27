#include "TIMER.h"
void (*pFunc)(void);

/************************
FONCTIONS GENERALES
************************/

// 	Activation Clock TIMER
void Timer_Active_Clock (TIM_TypeDef *Timer){
	
	if (Timer == TIM1) {
		(RCC->APB2ENR)|= RCC_APB2ENR_TIM1EN; //Clock TIMER1
	}
	else if (Timer == TIM2) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM2EN; //Clock TIMER2
	}
	else if (Timer == TIM3) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM3EN; //Clock TIMER3
	}
	else if (Timer == TIM4) {
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM4EN; //Clock TIMER4
	}	

}


// Initialisation TIMER (NEW: ARR et PSC automatique pour une durée déterminée)
void Timer_Init(TIM_TypeDef *Timer, float Duree){
	
		int Psc;
		int Arr;
		//int Total;
		Timer_Active_Clock(Timer);
		
	  // Calcul de ARR et PSC
		//Total = 72000000*Duree; 
		
		Psc = 35;     
		Arr = ((72 * Duree) / (Psc + 1)-1); 
		
		
		Timer->PSC = Psc;
		Timer->ARR = Arr;

}


// Activation de l'interruption TIMER
void Timer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void (*IT_function)(void)){
	Timer->DIER |= 0x01; //demande d'interruption au debordement de timer
	pFunc = IT_function;
	if (Timer == TIM1){
		NVIC_EnableIRQ((IRQn_Type)(25));
		NVIC_SetPriority((IRQn_Type)(25),Prio);
	}
	else if (Timer == TIM2)
	{
		NVIC_EnableIRQ((IRQn_Type)(28)); 
		NVIC_SetPriority((IRQn_Type)(28),Prio);  //IP(28)=(Prio<<4)
	}
	else if (Timer == TIM3)
	{
		NVIC_EnableIRQ((IRQn_Type)(29));
		NVIC_SetPriority((IRQn_Type)(29),Prio);
	}
	else
	{
		NVIC_EnableIRQ((IRQn_Type)(30));
		NVIC_SetPriority((IRQn_Type)(30),Prio);
	}
}


void TIM1_IRQHandler(void) 
{
	TIM1->SR &= ~(0x01); 
	if(pFunc != 0) (*pFunc)();
}

void TIM2_IRQHandler(void) // la matérielle appelle cette fonction automatiquement
{
	TIM2->SR &= ~(0x01); //reset le flag				on ajoute un point d'arret ici et si le compteur depasse, le programme revient ici
	if(pFunc != 0) (*pFunc)();
}

void TIM3_IRQHandler(void) 
{
	TIM3->SR &= ~(0x01); 
	if(pFunc != 0) (*pFunc)();
}

void TIM4_IRQHandler(void) 
{
	TIM4->SR &= ~(0x01); 
	if(pFunc != 0) (*pFunc)();
}

/************************
           PWM
************************/


//	Initialisation PWM du Timer
void Timer_PWM_Init(TIM_TypeDef *Timer, float Duree, int Channel){
	//int Duree = (1000/(Frequence_PWM_kHz)); // Duree en micro secondes 
 	Timer_Init(Timer, Duree);
	switch (Channel) {
		
			 case 1:
			 	// On utilise le PWM en mode 1 
			  Timer->CCMR1 &= ~(6 << 4);  
			  Timer->CCMR1 |= (6 << 4);  //  CCMR1-> OC1M = 110
				Timer->CCER &= ~(0 << 0);
				Timer->CCER |= (1 << 0);  // Open channel 1, active OC1
		    //Initialisation de la PWM d'un Duty Cycle de 0%
				Timer->CCR1=0;  // Reset CCR1
				break;
			 
			 case 2:
				 
			  Timer->CCMR1 &= ~(6 << 12); 
			  Timer->CCMR1 |= (6 << 12);  //  CCMR1-> OC2M = 110
				Timer->CCER &= ~(0 << 4);
				Timer->CCER |= (1 << 4); // Open channel 2, active OC2
		    
				Timer->CCR2=0; // Reset CCR2
				break;
			 
			 case 3:

			  Timer->CCMR2 &= ~(6 << 4); 
			  Timer->CCMR2 |= (6 << 4);  //  CCMR2-> OC1M = 110
				Timer->CCER &= ~(0 << 8);
				Timer->CCER |= (1 << 8); // Open channel 3, active OC3

				Timer->CCR3=0; // Reset CCR3
				break;
			 
			 case 4:

			  Timer->CCMR2 &= ~(6 << 12); 
			  Timer->CCMR2 |= (6 << 12); //  CCMR2-> OC2M = 110
				Timer->CCER &= ~(0 << 12);
				Timer->CCER |= (1 << 12); // Open channel 4, active OC4

				Timer->CCR4=0; // Reset CCR4
				break;
			 
			 default:

				 break;
		 
 }
	// Enable bit MOE 
	Timer->BDTR |= (0x1 << 15);
	
}


//	 Fixer la le rapport cyclique de la PWM 
void Timer_PWM_DutyCycle_Fix(TIM_TypeDef *Timer, int Duty_Cycle, int Channel){
     int Arr;
     if ((Duty_Cycle <= 100) && (Duty_Cycle >= 0)) {
			 
       Arr = Timer->ARR;
			 
			 switch (Channel) {
				 case 1:
                     Timer->CCR1 = (Arr*Duty_Cycle)/100;
				     break;

				 case 2:
                     Timer->CCR2 = (Arr*Duty_Cycle)/100;
				     break;

				 case 3:
                     Timer->CCR3 = (Arr*Duty_Cycle)/100;
				     break;

				 case 4:
                     Timer->CCR4 = (Arr*Duty_Cycle)/100;
				     break;
			 }
     }
 }


