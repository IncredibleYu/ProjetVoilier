#include "GPIO.h"


void MyGPIO_Init ( GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf, char GPIO_Mode ) {
	
	// 	Clock Activation 
	if (GPIO == GPIOA) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPAEN;
	}
	else if (GPIO == GPIOB) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPBEN;
	}
	else if (GPIO == GPIOC) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPCEN;
	}
	else if (GPIO == GPIOD) {
		(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_APB2ENR_IOPDEN;
	}
	
	if (GPIO_Pin<8){
		GPIO->CRL ^= ~(0x0F) << GPIO_Pin;
		GPIO->CRL |= GPIO_Conf << GPIO_Pin;
	}
	else{
		GPIO->CRH ^= ~(0x0F) << GPIO_Pin;
		GPIO->CRH |= GPIO_Conf << GPIO_Pin;
	}
};

int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ){ // renvoie 0 ou autre chose different de 0 
	uint32_t testIDR;
	testIDR = GPIO->IDR & (0x01 << GPIO_Pin);
	if (testIDR == (0x01<<GPIO_Pin)){
		return 1;
	}
	else {
		return 0;
	}
}

void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->BSRR |= (0x01 << GPIO_Pin);
}
	
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->BRR |= (0x01 << GPIO_Pin);
}

void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	if ((GPIO->ODR & (1 << GPIO_Pin)) == (1<<GPIO_Pin))
			MyGPIO_Reset (GPIO , GPIO_Pin ) ;
	else
			MyGPIO_Set (GPIO , GPIO_Pin ) ;
}



