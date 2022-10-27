#include "SERVOMTR.h"


//Initialisation du Servomoteur
// Sortie PWN -> PA8
//PA8 -> Output Alternate function push-pull
void Init_SERVOMTR(void){
	
     MyGPIO_Init(GPIOA,8,AltOut_Ppull,OutputMode_10MHz);
     Timer_PWM_Init(TIM3,20000,1);
     Timer_Start(TIM3);
	   
}




//Calcul du rapport cyclique pour varier l'angle de rotation du Servomoteur
int Calcul_DutyCycle_SERVOMTR(int Angle_Vent) {

	int Duty_Cycle;
	

	if (Angle_Vent <= 45)  {
        Duty_Cycle = 5;
   }
   if (Angle_Vent > 45 && Angle_Vent < 68) {
		Duty_Cycle = 6; 
	}
	if (Angle_Vent >= 68 && Angle_Vent < 90) {
		Duty_Cycle = 7; 
	}
	if (Angle_Vent >= 90 && Angle_Vent < 113) {
		Duty_Cycle = 8; 
	}
   if (Angle_Vent >= 113 && Angle_Vent < 135) {
		Duty_Cycle = 9; 
	}
	if (Angle_Vent >= 135 && Angle_Vent < 225) {
		Duty_Cycle = 10; 
	}
	if (Angle_Vent >= 225 && Angle_Vent < 248) {
		Duty_Cycle = 9; 
	}
	if (Angle_Vent >= 248 && Angle_Vent < 270) {
		Duty_Cycle = 8; 
	}
   if (Angle_Vent >= 270 && Angle_Vent < 293) {
		Duty_Cycle = 7; 
	}
	if (Angle_Vent >= 293 && Angle_Vent < 315) {
		Duty_Cycle = 6; 
	}
	if (Angle_Vent >= 315)  {
        Duty_Cycle = 5;
   }
	
	
	return Duty_Cycle;
}
	
