/**************************************************************************
* Rafael Corsi   - Insper 
* rafael.corsi@insper.edu.br        
*
* Computa��o Embarcada
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
 * Bot�o
 */ 
#define BUT_PIO_ID		10
#define BUT_PIO         PIOA
#define BUT_PIN			11
#define BUT_PIN_MASK	(1<<BUT_PIN)

/************************************************************************/
/* Prototipa��o                                                        */
/************************************************************************/
void ledConfig();

/************************************************************************/
/* Fun��es	                                                            */
/************************************************************************/

/**
 * @Brief Inicializa o pino do LED
 */
void ledConfig(){
	/************************************************************************/
	/* 3. Ativa clock no PIO Configura��o do PMC	                          */
	/************************************************************************/

	/**
	* Perif�rico : PMC
	* @Brief Peripheral Clock Enable Register
	* O PMC � o perif�rico respons�vel pelo controle de energia dos
	* demais perif�ricos.
	* Inicializamos aqui o clock do perif�rico PIO C.
	*/
	PMC->PMC_PCER0 = (1<<LED_PIO_ID);

	/************************************************************************/
	/* PIO				                                                          */
	/************************************************************************/

	/**
	* Perif�rico : PIO C
	* @Brief Output Enable Register
	* Configuramos o pino como sa�da
	*/
	PIOC->PIO_OER = (1 << 8);
	

	/**
	* Perif�rico : PIO C
	* @Brief Peripheral Enable Register
	* Fazemos com que o controle do pino seja realizado pelo PIO
	* e n�o por outro perif�rico
	*/
	PIOC->PIO_PER = (1 << 8);

	/**
	* Perif�rico : PIO  
	* @Brief Clear/Set Output Data Register
	* Aqui controlamos o valor da sa�da desse pino
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
	* @Brief Diferente de um c�digo comum que executa em um pc, no uC deve estar
	* sempre executando um c�digo, por isso utilizamos esse loop infingir.
	*/
};

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
int main(void)
{

	/************************************************************************/
	/* Inicializa��o b�sica do uC                                           */
	/************************************************************************/
	sysclk_init();
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	/************************************************************************/
	/* Inicializa perifericos                                               */
	/************************************************************************/
	// Configura LED em modo sa�da
	ledConfig();
	
	// Configura botao
	PMC ->PMC_PCER0 = (1<<10);	// Ativa o clock do PIO que controla o bot�o no PMC
	PIOA ->PIO_PER = (1<<11);	// Ativa o PIO para controlar o pino do bot�o
	PIOA ->PIO_ODR = (1<<11);	// Desativa o buffer de sa�da
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


