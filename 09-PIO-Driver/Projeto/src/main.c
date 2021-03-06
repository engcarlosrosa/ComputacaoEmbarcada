/************************************************************************
* Rafael Corsi   - Insper
* rafael.corsi@insper.edu.br
*
* Computa��o Embarcada
*
* 09-PIO-DRIVER
************************************************************************/


#include "asf.h" //Atmel Software Framework (ASF) exemplos de aplica��es para o kit SAM E70
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
#define LED_PIO         PIOC // 0x400E1200 � 0x400E1400
#define LED_PIN		    8
#define LED_PIN_MASK    (1<<LED_PIN)

/**
 * Bot�o
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
/* Fun��es	                                                            */
/************************************************************************/

/**
 * @Brief Inicializa o pino do LED
 */
void led_init(int estado){
	_pmc_enable_periph_clock(LED_PIO_ID);					// Ativa o clock no periferico					  (ID do perif�rico)
	
	_pio_set_output(LED_PIO, LED_PIN_MASK, 1, 0);	/** Configura os pinos do controlador de PIO como output (p_pio Pointer to a PIO instance, 
															* ul_mask Bitmask indicating which pin(s) to configure, ul_default_level Default level on the pin(s),
															* ul_pull_up_enable Indicates if the pin shall have its pull-up activated.
															*/
};

/**
 * @Brief Inicializa o pino do BUT
 */
void but_init(void){
	_pmc_enable_periph_clock(BUT_PIO_ID);					// Ativa o clock no periferico					  (ID do perif�rico)
	_pio_set_input(BUT_PIO, BUT_PIN_MASK, PIO_PULLUP /*| PIO_DEGLITCH */ | PIO_DEBOUNCE );
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
		/*
		* @Brief Verifica constantemente o status do bot�o
		* 1 : n�o apertado
		* 0 : apertado
		*/
		
	    if(_pio_get_output_data_status(BUT_PIO, BUT_PIN_MASK)){ //Pin Data Status Register
			_pio_clear( LED_PIO, LED_PIN_MASK);	//Clear Output Data Register
        }
		else{
			 _pio_set(LED_PIO, LED_PIN_MASK); //Set Output Data Register
        }
	};
}


