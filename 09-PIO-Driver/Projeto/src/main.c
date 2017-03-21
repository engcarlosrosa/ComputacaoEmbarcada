/************************************************************************
* Rafael Corsi   - Insper
* rafael.corsi@insper.edu.br
*
* Computação Embarcada
*
* 09-PIO-DRIVER
************************************************************************/


#include "asf.h" //Atmel Software Framework (ASF) exemplos de aplicações para o kit SAM E70
#include "conf_clock.h"
#include "driver/pmc_insper.h"
#include "driver/pio_insper.h"

/************************************************************************/
/* Defines                                                              */
/************************************************************************/

/**
 * LEDs
 */
#define LED_PIO_ID		ID_PIOC // 12
#define LED_PIO         PIOC // 0x400E1200 à 0x400E1400
#define LED_PIN		    8
#define LED_PIN_MASK    (1<<LED_PIN)

/**
 * Botão
 */
#define BUT_PIO_ID      ID_PIOA // 10
#define BUT_PIO         PIOA // 0x400E0E00 a 0x400E1000
#define BUT_PIN		    11
#define BUT_PIN_MASK    (1 << BUT_PIN)
#define BUT_DEBOUNCING_VALUE  79

/************************************************************************/
/* prototype                                                             */
/************************************************************************/
void led_init(int estado);
void but_init(void);

/************************************************************************/
/* Funções	                                                            */
/************************************************************************/

/**
 * @Brief Inicializa o pino do LED
 */
void led_init(int estado){
	_pmc_enable_periph_clock(LED_PIO_ID);					// Ativa o clock no periferico					  (ID do periférico)
	
	_pio_set_output(LED_PIO, LED_PIN_MASK, 1, 0);	/** Configura os pinos do controlador de PIO como output (p_pio Pointer to a PIO instance, 
															* ul_mask Bitmask indicating which pin(s) to configure, ul_default_level Default level on the pin(s),
															* ul_pull_up_enable Indicates if the pin shall have its pull-up activated.
															*/
};

/**
 * @Brief Inicializa o pino do BUT
 */
void but_init(void){
	_pmc_enable_periph_clock(BUT_PIO_ID);					// Ativa o clock no periferico					  (ID do periférico)
	BUT_PIO->PIO_ODR	 = BUT_PIN_MASK;					// Desativa saída do registrador                  (Output DISABLE register)
	BUT_PIO->PIO_PER	 = BUT_PIN_MASK;					// Ativa controle do pino no PIO no registrador   (PIO ENABLE register)
	BUT_PIO->PIO_PUER	 = BUT_PIN_MASK;					// Ativa pull-up no PIO no registrador            (PullUp ENABLE register)
	BUT_PIO->PIO_IFER	 = BUT_PIN_MASK;					// Ativa debouncing
	BUT_PIO->PIO_IFSCER  = BUT_PIN_MASK;					// Ativa clock periferico
	BUT_PIO->PIO_SCDR	 = BUT_DEBOUNCING_VALUE;			// Configura a frequencia do debouncing
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
	/*
	WDT: Watchdog Timer;
	WDT_MR: Watchdog Timer Mode Register;
	WDT_MR_WDDIS: reprogram the WDT to meet the maximum watchdog period
	 the application requires;
	*/
	WDT->WDT_MR = WDT_MR_WDDIS; /*WDT_MR: Watchdog Timer Mode Register*/

	/************************************************************************/
	/* Inicializao I/OS                                                     */
	/************************************************************************/

	led_init(1);
    but_init();

	/************************************************************************/
	/* Super loop                                                           */
	/************************************************************************/

	while(1){
		/**
		* @Brief Verifica constantemente o status do botão
		* 1 : não apertado
		* 0 : apertado
		*/
	    if(BUT_PIO->PIO_PDSR & (BUT_PIN_MASK)){ /*Pin Data Status Register*/
			LED_PIO->PIO_CODR = LED_PIN_MASK; /*Clear Output Data Register*/
        }
		else{
			LED_PIO->PIO_SODR = LED_PIN_MASK; /*Set Output Data Register*/
        }
	};
}


