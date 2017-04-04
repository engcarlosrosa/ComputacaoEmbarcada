#include "asf.h"

/************************************************************************/
/* DEFINES                                                              */
/************************************************************************/

/**
 *  Informacoes para o RTC
 *  poderia ser extraida do __DATE__ e __TIME__
 *  ou ser atualizado pelo PC.
 */
#define YEAR        2017
#define MOUNTH      3
#define DAY         27
#define WEEK        13
#define HOUR        9
#define MINUTE      5
#define SECOND      0

/**
 * LEDs da SAME70
 */
#define LED_PIO_ID		ID_PIOC
#define LED_PIO         PIOC
#define LED_PIN		    8
#define LED_PIN_MASK    (1<<LED_PIN)

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
 * Botão
 */
#define BUT_PIO_ID      ID_PIOA
#define BUT_PIO         PIOA
#define BUT_PIN		    11
#define BUT_PIN_MASK    (1 << BUT_PIN)
#define BUT_DEBOUNCING_VALUE  79

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
/* VAR globais                                                          */
/************************************************************************/
volatile uint8_t flag_led0 = 0;
volatile uint8_t flag_led1 = 0;
volatile uint8_t flag_led2 = 0;
volatile uint8_t flag_led3 = 0;


/************************************************************************/
/* PROTOTYPES                                                           */
/************************************************************************/

void BUT_init(void);
void LED_init(int estado);
void TC0_init(void);
void TC1_init(void);
void TC2_init(void);
void TC3_init(void);
void RTC_init(void);
void pin_toggle(Pio *pio, uint32_t mask);

/************************************************************************/
/* Handlers                                                             */
/************************************************************************/

/**
 *  Handle Interrupcao botao 0
 */
static void Button0_Handler(uint32_t id, uint32_t mask)
{
			   tc_stop(TC0, 1);
	
}

/**
 *  Handle Interrupcao botao 1
 */
static void Button1_Handler(uint32_t id, uint32_t mask)
{
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

/**
 *  Handle Interrupcao botao 2
 */
static void Button2_Handler(uint32_t id, uint32_t mask)
{
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

/**
 *  Handle Interrupcao botao 3
 */
static void Button3_Handler(uint32_t id, uint32_t mask)
{
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

/**
 *  Interrupt handler for TC0 interrupt. 
 */
void TC0_Handler(void){
	volatile uint32_t ul_dummy;

    /****************************************************************
	* Devemos indicar ao TC que a interrupção foi satisfeita.
    ******************************************************************/
	ul_dummy = tc_get_status(TC0, 0);

	/* Avoid compiler warning */
	UNUSED(ul_dummy);

	/** Muda o estado do LED */
        pin_toggle(LED_PIO, LED_PIN_MASK);
}

/**
 *  Interrupt handler for TC0 interrupt. 
 */
void TC1_Handler(void){
	volatile uint32_t ul_dummy;

    /****************************************************************
	* Devemos indicar ao TC que a interrupção foi satisfeita.
    ******************************************************************/
	ul_dummy = tc_get_status(TC0, 1);

	/* Avoid compiler warning */
	UNUSED(ul_dummy);

	/** Muda o estado do LED */
        pin_toggle(LED_PIO_1, LED_PIN_MASK_1);
}

/**
 *  Interrupt handler for TC0 interrupt. 
 */
void TC2_Handler(void){
	volatile uint32_t ul_dummy;

    /****************************************************************
	* Devemos indicar ao TC que a interrupção foi satisfeita.
    ******************************************************************/
	ul_dummy = tc_get_status(TC0, 2);

	/* Avoid compiler warning */
	UNUSED(ul_dummy);

	/** Muda o estado do LED */
        pin_toggle(LED_PIO_2, LED_PIN_MASK_2);
}

/**
 *  Interrupt handler for TC0 interrupt. 
 */
void TC3_Handler(void){
	volatile uint32_t ul_dummy;

    /****************************************************************
	* Devemos indicar ao TC que a interrupção foi satisfeita.
    ******************************************************************/
	ul_dummy = tc_get_status(TC1, 0);

	/* Avoid compiler warning */
	UNUSED(ul_dummy);

	/** Muda o estado do LED */
        pin_toggle(LED_PIO_3, LED_PIN_MASK_3);
}

/**
 * \brief Interrupt handler for the RTC. Refresh the display.
 */
void RTC_Handler(void)
{
	uint32_t ul_status = rtc_get_status(RTC);

	/* Second increment interrupt */
	if ((ul_status & RTC_SR_SEC) == RTC_SR_SEC) {
	
		rtc_clear_status(RTC, RTC_SCCR_SECCLR);

	} else {
		/* Time or date alarm */
		if ((ul_status & RTC_SR_ALARM) == RTC_SR_ALARM) {
            
			/*Atualiza hora */ 
			uint32_t ano, mes, dia, hora, minuto, segundo;	
			
			rtc_get_time(RTC, &hora, &minuto, &segundo);
			rtc_get_date(RTC, &ano, &mes, &dia, NULL);

			/* incrementa minuto */
			minuto++;		   

	       /* configura alarme do RTC */
			rtc_set_date_alarm(RTC, 1, mes, 1, dia);
		    rtc_set_time_alarm(RTC, 1, hora, 1, minuto, 1, 0);

			/* inverte status led */
			flag_led0 ^= 1;

		   /* Ativa/desativa o TimerCounter */
		   if (flag_led0)
		   {
			   tc_start(TC0, 0);
		   }else{
			   tc_stop(TC0, 0);
		   }

			/* inverte status led 1*/
			flag_led1 ^= 1;

			/* Ativa/desativa o TimerCounter */
			if (flag_led1)
			{
				tc_start(TC0, 1);
				}else{
				tc_stop(TC0, 1);
			}
		   
		   			/* inverte status led 2 */
			flag_led2 ^= 1;

		   /* Ativa/desativa o TimerCounter */
		   if (flag_led2)
		   {
			   tc_start(TC0, 2);
		   }else{
			   tc_stop(TC0, 2);
		   }
		   
		   			/* inverte status led 3*/
			flag_led3 ^= 1;

		   /* Ativa/desativa o TimerCounter */
		   if (flag_led3)
		   {
			   tc_start(TC1, 0);
		   }else{
			   tc_stop(TC1, 0);
		   }
		   
			rtc_clear_status(RTC, RTC_SCCR_ALRCLR);
		}
	}
}


/************************************************************************/
/* Funcoes                                                              */
/************************************************************************/

/** 
 *  Toggle pin controlado pelo PIO (out)
 */
void pin_toggle(Pio *pio, uint32_t mask){
   if(pio_get_output_data_status(pio, mask))
    pio_clear(pio, mask);
   else
    pio_set(pio,mask);
}

/**
 * @Brief Inicializa o pino do BUT
 */
void BUT_init(void){
	
	/**
	* Botão da SAME70
	*/
	
    /* config. pino botao em modo de entrada */
    pmc_enable_periph_clk(BUT_PIO_ID);
    pio_set_input(BUT_PIO, BUT_PIN_MASK, PIO_PULLUP | PIO_DEBOUNCE);
    
    /* config. interrupcao em borda de descida no botao do kit */
    /* indica funcao (but_Handler) a ser chamada quando houver uma interrupção */
    pio_enable_interrupt(BUT_PIO, BUT_PIN_MASK);
    pio_handler_set(BUT_PIO, BUT_PIO_ID, BUT_PIN_MASK, PIO_IT_FALL_EDGE, Button0_Handler);
    
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
	pio_handler_set(BUT_PIO_1, BUT_PIO_ID_1, BUT_PIN_MASK_1, PIO_IT_FALL_EDGE, Button1_Handler);
			    
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
	pio_handler_set(BUT_PIO_2, BUT_PIO_ID_2, BUT_PIN_MASK_2, PIO_IT_FALL_EDGE, Button2_Handler);
			    
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
	pio_handler_set(BUT_PIO_3, BUT_PIO_ID_3, BUT_PIN_MASK_3, PIO_IT_FALL_EDGE, Button3_Handler);
		
	/* habilita interrupçcão do PIO que controla o botao */
	/* e configura sua prioridade                        */
	NVIC_EnableIRQ(BUT_PIO_ID_3);
	NVIC_SetPriority(BUT_PIO_ID_3, 1);
	
	
};

/**
 * @Brief Inicializa o pino do LED
 */
void LED_init(int estado){
	
	/**
	 * @Brief Inicializa o pino do LED da SAME70
	 */
    pmc_enable_periph_clk(LED_PIO_ID);
    pio_set_output(LED_PIO, LED_PIN_MASK, estado, 0, 0 );
	
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
 * Configura TimerCounter (TC0) para gerar uma interrupcao no canal 0-(ID_TC1) 
 * a cada 250 ms (4Hz)
 */
void TC0_init(void){   
    uint32_t ul_div;
    uint32_t ul_tcclks;
    uint32_t ul_sysclk = sysclk_get_cpu_hz();
    
    uint32_t channel = 0;
    
    /* Configura o PMC */
    pmc_enable_periph_clk(ID_TC0);    

    /** Configura o TC para operar em  4Mhz e interrupçcão no RC compare */
    tc_find_mck_divisor(4, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
    tc_init(TC0, channel, ul_tcclks | TC_CMR_CPCTRG);
    tc_write_rc(TC0, channel, (ul_sysclk / ul_div) / 4);

    /* Configura e ativa interrupçcão no TC canal 0 */
    NVIC_EnableIRQ((IRQn_Type) ID_TC0);
    tc_enable_interrupt(TC0, channel, TC_IER_CPCS);

    /* Inicializa o canal 0 do TC */
    tc_start(TC0, channel);
	//tc_stop(TC0, channel)
}

/**
 * Configura TimerCounter (TC0) para gerar uma interrupcao no canal 0-(ID_TC1) 
 * a cada 125 ms (8Hz)
 */
void TC1_init(void){   
    uint32_t ul_div;
    uint32_t ul_tcclks;
    uint32_t ul_sysclk = sysclk_get_cpu_hz();
    
    uint32_t channel = 1;
    
    /* Configura o PMC */
    pmc_enable_periph_clk(ID_TC1);    

    /** Configura o TC para operar em  8Mhz e interrupçcão no RC compare */
    tc_find_mck_divisor(8, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
    tc_init(TC0, channel, ul_tcclks | TC_CMR_CPCTRG);
    tc_write_rc(TC0, channel, (ul_sysclk / ul_div) / 8);

    /* Configura e ativa interrupçcão no TC canal 0 */
    NVIC_EnableIRQ((IRQn_Type) ID_TC1);
    tc_enable_interrupt(TC0, channel, TC_IER_CPCS);

    /* Inicializa o canal 1 do TC */
    tc_start(TC0, channel);
	//tc_stop(TC0, channel)
}

/**
 * Configura TimerCounter (TC0) para gerar uma interrupcao no canal 0-(ID_TC1) 
 * a cada 90.9 ms (11Hz)
 */
void TC2_init(void){   
    uint32_t ul_div;
    uint32_t ul_tcclks;
    uint32_t ul_sysclk = sysclk_get_cpu_hz();
    
    uint32_t channel = 2;
    
    /* Configura o PMC */
    pmc_enable_periph_clk(ID_TC2);    

    /** Configura o TC para operar em  8Mhz e interrupçcão no RC compare */
    tc_find_mck_divisor(11, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
    tc_init(TC0, channel, ul_tcclks | TC_CMR_CPCTRG);
    tc_write_rc(TC0, channel, (ul_sysclk / ul_div) / 11);

    /* Configura e ativa interrupçcão no TC canal 0 */
    NVIC_EnableIRQ((IRQn_Type) ID_TC2);
    tc_enable_interrupt(TC0, channel, TC_IER_CPCS);

    /* Inicializa o canal 2 do TC */
    tc_start(TC0, channel);
	//tc_stop(TC0, channel)
}


/**
 * Configura TimerCounter (TC1) para gerar uma interrupcao no canal 0-(ID_TC3) 
 * a cada 58.8 ms (17Hz)
 */
void TC3_init(void){   
    uint32_t ul_div;
    uint32_t ul_tcclks;
    uint32_t ul_sysclk = sysclk_get_cpu_hz();
    
    uint32_t channel = 0;
    
    /* Configura o PMC */
    pmc_enable_periph_clk(ID_TC3);    

    /** Configura o TC para operar em  8Mhz e interrupçcão no RC compare */
    tc_find_mck_divisor(17, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
    tc_init(TC1, channel, ul_tcclks | TC_CMR_CPCTRG);
    tc_write_rc(TC1, channel, (ul_sysclk / ul_div) / 17);

    /* Configura e ativa interrupçcão no TC canal 0 */
    NVIC_EnableIRQ((IRQn_Type) ID_TC3);
    tc_enable_interrupt(TC1, channel, TC_IER_CPCS);

    /* Inicializa o canal 2 do TC */
    tc_start(TC1, channel);
	//tc_stop(TC0, channel)
}

/**
 * Configura o RTC para funcionar com interrupcao de alarme
 */
void RTC_init(){
    /* Configura o PMC */
    pmc_enable_periph_clk(ID_RTC);
        
    /* Default RTC configuration, 24-hour mode */
    rtc_set_hour_mode(RTC, 0);

    /* Configura data e hora manualmente */
    rtc_set_date(RTC, YEAR, MOUNTH, DAY, WEEK);
    rtc_set_time(RTC, HOUR, MINUTE, SECOND);
	
	//rtc_get_time()

    /* Configure RTC interrupts */
    NVIC_DisableIRQ(RTC_IRQn);
    NVIC_ClearPendingIRQ(RTC_IRQn);
    NVIC_SetPriority(RTC_IRQn, 0);
    NVIC_EnableIRQ(RTC_IRQn);
    
    /* Ativa interrupcao via alarme */
    rtc_enable_interrupt(RTC,  RTC_IER_ALREN);   
    
}

/************************************************************************/
/* Main Code	                                                        */
/************************************************************************/
int main(void){
	/* Initialize the SAM system */
	sysclk_init();

	/* Disable the watchdog */
	WDT->WDT_MR = WDT_MR_WDDIS;

    /* Configura Leds */
    LED_init(0);
	
	/* Configura os botões */
	BUT_init();    
    
    /** Configura timer 0 */
    TC0_init();
	TC1_init();
	TC2_init();
	TC3_init();
    
    /** Configura RTC */
    RTC_init();

        /* configura alarme do RTC */    
        rtc_set_date_alarm(RTC, 1, MOUNTH, 1, DAY);
        rtc_set_time_alarm(RTC, 1, HOUR, 1, MINUTE+1, 1, SECOND);

          
	while (1) {
		/* Entra em modo sleep */
		
	}
}
