/************************************************************************
* Rafael Corsi   - Insper
* rafael.corsi@insper.edu.br
*
* Computação Embarcada
*
* 10-PIO-INTERRUPCAO
*
* [ref] http://www.atmel.com/Images/Atmel-42142-SAM-AT03258-Using-Low-Power-Mode-in-SAM4E-Microcontroller_Application-Note.pdf
* [ref] https://www.eecs.umich.edu/courses/eecs373/labs/refs/M3%20Guide.pdf
************************************************************************/


#include "asf.h"
#include "conf_clock.h"
#include "Driver/pio_insper.h"
#include "Driver/pmc_insper.h"


/************************************************************************/
/* Defines                                                              */
/************************************************************************/

/**
 * LEDs da SAME70
 */
#define LED_PIO_ID				ID_PIOC
#define LED_PIO					PIOC
#define LED_PIN					8
#define LED_PIN_MASK			(1<<LED_PIN)

/**
 * LEDs 1 da OLED1 Xplained Pro
 */
#define LED_PIO_ID_1			ID_PIOA
#define LED_PIO_1				PIOA
#define LED_PIN_1				0
#define LED_PIN_MASK_1			(1<<LED_PIN_1)


/**
 * LEDs 2 da OLED1 Xplained Pro
 */
#define LED_PIO_ID_2			ID_PIOC
#define LED_PIO_2				PIOC
#define LED_PIN_2				30
#define LED_PIN_MASK_2			(1<<LED_PIN_2)

/**
 * LEDs 3 da OLED1 Xplained Pro
 */
#define LED_PIO_ID_3			ID_PIOB
#define LED_PIO_3				PIOB
#define LED_PIN_3				2
#define LED_PIN_MASK_3			(1<<LED_PIN_3)

/**
 * Botão da SAME70
 */
#define BUT_PIO_ID				ID_PIOA
#define BUT_PIO					PIOA
#define BUT_PIN					11
#define BUT_PIN_MASK			(1 << BUT_PIN)
#define BUT_DEBOUNCING_VALUE	79


/**
 * Botão 1 da OLED1 Xplained Pro
 */
#define BUT_PIO_ID_1			ID_PIOD
#define BUT_PIO_1				PIOD
#define BUT_PIN_1				28
#define BUT_PIN_MASK_1			(1 << BUT_PIN_1)
//#define BUT_DEBOUNCING_VALUE_1		// à definir


/**
 * Botão 2 da OLED1 Xplained Pro
 */
#define BUT_PIO_ID_2			ID_PIOC
#define BUT_PIO_2				PIOC
#define BUT_PIN_2				31
#define BUT_PIN_MASK_2			(1 << BUT_PIN_2)
//#define BUT_DEBOUNCING_VALUE_2		// à definir


/**
 * Botão 3 da OLED1 Xplained Pro
 */
#define BUT_PIO_ID_3			ID_PIOA
#define BUT_PIO_3				PIOA
#define BUT_PIN_3				19
#define BUT_PIN_MASK_3			(1 << BUT_PIN_3)
//#define BUT_DEBOUNCING_VALUE_3		// à definir




/************************************************************************/
/* prototype                                                             */
/************************************************************************/
void led_init(int estado);
void but_init(void);
void but_Handler();
void but_Handler_1();
void but_Handler_2();
void but_Handler_3();

/************************************************************************/
/* Interrupçcões                                                        */
/************************************************************************/

void but_Handler(){
    /*
     *  limpa interrupcao do PIO
     */
    uint32_t pioIntStatus;
    pioIntStatus =  pio_get_interrupt_status(BUT_PIO);
    
   /**
    *  Toggle status led da SAME70
    */
   if(pio_get_output_data_status(LED_PIO, LED_PIN_MASK))
    pio_clear(LED_PIO, LED_PIN_MASK);
   else
    pio_set(LED_PIO,LED_PIN_MASK);
    
}


void but_Handler_1(){
    /*
     *  limpa interrupcao do PIO
     */
    uint32_t pioIntStatus;
    pioIntStatus =  pio_get_interrupt_status(BUT_PIO_1);
    
   /**
    *  Toggle status led 1 da OLED1 Xplained Pro
    */
   if(pio_get_output_data_status(LED_PIO_1, LED_PIN_MASK_1))
    pio_clear(LED_PIO_1, LED_PIN_MASK_1);
   else
    pio_set(LED_PIO_1,LED_PIN_MASK_1);

   /**
    *  Toggle status led da SAME70
    */
	if(pio_get_output_data_status(LED_PIO, LED_PIN_MASK))
    pio_clear(LED_PIO, LED_PIN_MASK);
   else
    pio_set(LED_PIO,LED_PIN_MASK);
    
}

void but_Handler_2(){
    /*
     *  limpa interrupcao do PIO
     */
    uint32_t pioIntStatus;
    pioIntStatus =  pio_get_interrupt_status(BUT_PIO_2);
    
   /**
    *  Toggle status led 2 da OLED1 Xplained Pro
    */
   if(pio_get_output_data_status(LED_PIO_2, LED_PIN_MASK_2))
    pio_clear(LED_PIO_2, LED_PIN_MASK_2);
   else
    pio_set(LED_PIO_2,LED_PIN_MASK_2);
	
   /**
    *  Toggle status led da SAME70
    */
	if(pio_get_output_data_status(LED_PIO, LED_PIN_MASK))
    pio_clear(LED_PIO, LED_PIN_MASK);
   else
    pio_set(LED_PIO,LED_PIN_MASK);
    
}


void but_Handler_3(){
    /*
     *  limpa interrupcao do PIO
     */
    uint32_t pioIntStatus;
    pioIntStatus =  pio_get_interrupt_status(BUT_PIO_3);
    
   /**
    *  Toggle status led 3 da OLED1 Xplained Pro
    */
   if(pio_get_output_data_status(LED_PIO_3, LED_PIN_MASK_3))
    pio_clear(LED_PIO_3, LED_PIN_MASK_3);
   else
    pio_set(LED_PIO_3,LED_PIN_MASK_3);
    
   /**
    *  Toggle status led da SAME70
    */
	if(pio_get_output_data_status(LED_PIO, LED_PIN_MASK))
    pio_clear(LED_PIO, LED_PIN_MASK);
   else
    pio_set(LED_PIO,LED_PIN_MASK);
	
}


/************************************************************************/
/* Funções	                                                            */
/************************************************************************/

/**
 * @Brief Inicializa o pino do LED
 */
void led_init(int estado){
	
	/**
	 * @Brief Inicializa o pino do LED da SAME70
	 */
    pmc_enable_periph_clk(LED_PIO_ID);
    pio_set_output(LED_PIO, LED_PIN_MASK, 1, 0, 0 );
	
	/**
	 * @Brief Inicializa o pino do LED 1 da OLED1 Xplained Pro
	 */
	pmc_enable_periph_clk(LED_PIO_ID_1);
    pio_set_output(LED_PIO_1, LED_PIN_MASK_1, 1, 0, 0 );
	
	
	/**
	 * @Brief Inicializa o pino do LED 2 da OLED1 Xplained Pro
	 */	
	pmc_enable_periph_clk(LED_PIO_ID_2);
    pio_set_output(LED_PIO_2, LED_PIN_MASK_2, 1, 0, 0 );


	/**
	 * @Brief Inicializa o pino do LED 3 da OLED1 Xplained Pro
	 */
	pmc_enable_periph_clk(LED_PIO_ID_3);
    pio_set_output(LED_PIO_3, LED_PIN_MASK_3, 1, 0, 0 );
};

/**
 * @Brief Inicializa o pino do BUT
 *  config. botao em modo entrada enquanto 
 *  ativa e configura sua interrupcao.
 */
void but_init(void){
	
	/**
	 * Botão da SAME70
	 */
	
    /* config. pino botao em modo de entrada */
    pmc_enable_periph_clk(BUT_PIO_ID);
    pio_set_input(BUT_PIO, BUT_PIN_MASK, PIO_PULLUP | PIO_DEBOUNCE);
  
	/* config. interrupcao em borda de descida no botao do kit */
	/* indica funcao (but_Handler) a ser chamada quando houver uma interrupção */
	pio_enable_interrupt(BUT_PIO, BUT_PIN_MASK);
	pio_handler_set(BUT_PIO, BUT_PIO_ID, BUT_PIN_MASK, PIO_IT_FALL_EDGE, but_Handler);
			    
	/* habilita interrupçcão do PIO que controla o botao */
	/* e configura sua prioridade                        */
	NVIC_EnableIRQ(BUT_PIO_ID);
	NVIC_SetPriority(BUT_PIO_ID, 1);
	
	/**
	 * Botão 1 da OLED1 Xplained Pro
	 */

    /* config. pino botao em modo de entrada */
    pmc_enable_periph_clk(BUT_PIO_ID_1);
    pio_set_input(BUT_PIO_1, BUT_PIN_MASK_1, PIO_PULLUP | PIO_DEBOUNCE);	
	
	/* config. interrupcao em borda de subida no botao do kit */
	/* indica funcao (but_Handler) a ser chamada quando houver uma interrupção */
	pio_enable_interrupt(BUT_PIO_1, BUT_PIN_MASK_1);
	pio_handler_set(BUT_PIO_1, BUT_PIO_ID_1, BUT_PIN_MASK_1, PIO_IT_RISE_EDGE, but_Handler_1);
			    
	/* habilita interrupçcão do PIO que controla o botao */
	/* e configura sua prioridade                        */
	NVIC_EnableIRQ(BUT_PIO_ID_1);
	NVIC_SetPriority(BUT_PIO_ID_1, 1);
				
	/**
	 * Botão 2 da OLED1 Xplained Pro
	 */

    /* config. pino botao em modo de entrada */
    pmc_enable_periph_clk(BUT_PIO_ID_2);
    pio_set_input(BUT_PIO_2, BUT_PIN_MASK_2, PIO_PULLUP | PIO_DEBOUNCE);
	
	/* config. interrupcao em borda de descida no botao do kit */
	/* indica funcao (but_Handler) a ser chamada quando houver uma interrupção */
	pio_enable_interrupt(BUT_PIO_2, BUT_PIN_MASK_2);
	pio_handler_set(BUT_PIO_2, BUT_PIO_ID_2, BUT_PIN_MASK_2, PIO_IT_FALL_EDGE, but_Handler_2);
			    
	/* habilita interrupçcão do PIO que controla o botao */
	/* e configura sua prioridade                        */
	NVIC_EnableIRQ(BUT_PIO_ID_2);
	NVIC_SetPriority(BUT_PIO_ID_2, 1);
				
	/**
	 * Botão 3 da OLED1 Xplained Pro
	 */

    /* config. pino botao em modo de entrada */
    pmc_enable_periph_clk(BUT_PIO_ID_3);
    pio_set_input(BUT_PIO_3, BUT_PIN_MASK_3, PIO_PULLUP | PIO_DEBOUNCE);
	
	/* config. interrupcao em borda de subida e descida no botao do kit */
	/* indica funcao (but_Handler) a ser chamada quando houver uma interrupção */
	pio_enable_interrupt(BUT_PIO_3, BUT_PIN_MASK_3);
	pio_handler_set(BUT_PIO_3, BUT_PIO_ID_3, BUT_PIN_MASK_3, PIO_IT_RE_OR_HL, but_Handler_3);
		
	/* habilita interrupçcão do PIO que controla o botao */
	/* e configura sua prioridade                        */
	NVIC_EnableIRQ(BUT_PIO_ID_3);
	NVIC_SetPriority(BUT_PIO_ID_3, 1);
		
	}



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
	/* Inicializao I/OS                                                     */
	/************************************************************************/
	led_init(1);
    but_init();

	/************************************************************************/
	/* Super loop                                                           */
	/************************************************************************/
	while(1){
       /* entra em modo sleep */
       pmc_sleep(SLEEPMGR_SLEEP_WFI);
	
}

}
