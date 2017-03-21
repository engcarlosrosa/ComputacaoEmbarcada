/**************************************************************************
* Rafael Corsi   - Insper 
* rafael.corsi@insper.edu.br        
*
* Computação Embarcada
*
* 08-PIO-ENTRADA
************************************************************************/


#include "asf.h"
#include "conf_clock.h"

/************************************************************************/
/* Defines                                                              */
/************************************************************************/

/**
 * LEDs
 */
#define LED_PIO_ID		ID_PIOC
#define LED_PIO         PIOC
#define LED_PIN			8
#define LED_PIN_MASK	(1<<LED_PIN) 

/**
 * Botão
 */ 
#define BUT_PIO_ID		10
#define BUT_PIO         PIOA
#define BUT_PIN			11
#define BUT_PIN_MASK	(1<<BUT_PIN)

/************************************************************************/
/* Prototipação                                                        */
/************************************************************************/
void ledConfig();

/************************************************************************/
/* Funções	                                                            */
/************************************************************************/

/**
 * @Brief Inicializa o pino do LED
 */
void ledConfig(){
	/************************************************************************/
	/* 3. Ativa clock no PIO Configuração do PMC	                          */
	/************************************************************************/

	/**
	* Periférico : PMC
	* @Brief Peripheral Clock Enable Register
	* O PMC é o periférico responsável pelo controle de energia dos
	* demais periféricos.
	* Inicializamos aqui o clock do periférico PIO C.
	*/
	PMC->PMC_PCER0 = (1<<LED_PIO_ID);

	/************************************************************************/
	/* PIO				                                                          */
	/************************************************************************/

	/**
	* Periférico : PIO C
	* @Brief Output Enable Register
	* Configuramos o pino como saída
	*/
	PIOC->PIO_OER = (1 << 8);
	

	/**
	* Periférico : PIO C
	* @Brief Peripheral Enable Register
	* Fazemos com que o controle do pino seja realizado pelo PIO
	* e não por outro periférico
	*/
	PIOC->PIO_PER = (1 << 8);

	/**
	* Periférico : PIO  
	* @Brief Clear/Set Output Data Register
	* Aqui controlamos o valor da saída desse pino
	* no caso especifico colocamos 0 (acende o LED)
	* O registrador :
	*   - PIO_SODR : coloca 1 nesse pino
	*	- PIO_CODR : coloca 0 nesse pino
	*/
	PIOC->PIO_CODR =  (1 << 8);
	
	/************************************************************************/
	/* Super loop                                                           */
	/************************************************************************/

	/**
	* @Brief Diferente de um código comum que executa em um pc, no uC deve estar
	* sempre executando um código, por isso utilizamos esse loop infingir.
	*/
};

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
int main(void)
{

	/************************************************************************/
	/* Inicialização básica do uC                                           */
	/************************************************************************/
	sysclk_init();
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	/************************************************************************/
	/* Inicializa perifericos                                               */
	/************************************************************************/
	// Configura LED em modo saída
	ledConfig();
	
	// Configura botao
	PMC ->PMC_PCER0 = (1<<10);	// Ativa o clock do PIO que controla o botão no PMC
	PIOA ->PIO_PER = (1<<11);	// Ativa o PIO para controlar o pino do botão
	PIOA ->PIO_ODR = (1<<11);	// Desativa o buffer de saída
	PIOA ->PIO_PUER = (1<<11);	// Ativa o pull-up
	PIOA ->PIO_IFER = (1<<11);
	/************************************************************************/
	/* Super loop                                                           */
	/************************************************************************/
	while(1){
	  if(PIOA ->PIO_PDSR & (1<<11) ){
		  PIOC ->PIO_SODR = (1<<8);
	  } else {
		  PIOC ->PIO_CODR = (1<<8);
	  }
	};
}


