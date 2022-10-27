#ifndef GPIO_H
#define GPIO_H

#include "stm32f10x.h"

#define In_Analog 0x00
#define In_Floating 0x01
#define In_PullDown 0x02
#define In_PullUp 0x02
#define Out_Ppull 0x00
#define Out_OD 0x01
#define AltOut_Ppull 0x02
#define AltOut_OD 0x03
#define InputMode 0x00
#define OutputMode_10MHz 0x01
#define OutputMode_2MHz 0x02
#define OutputMode_50MHz 0x03


// GPIO Initialisation et choix de la Config et Mode
void MyGPIO_Init (GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf, char GPIO_Mode ) ;


// Lire la broche : renvoie 0 ou autre chose different de 0
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ; 


// Mettre la broche à 1
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ; 


// Mettre la broche à 0
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;


// Faire clignotter la borche 
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ; 


#endif