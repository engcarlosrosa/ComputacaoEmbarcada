#include "pio_insper.h"

/**
 * \brief Configure one or more pin(s) of a PIO controller as outputs, with
 * the given default value. 
 * 
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask indicating which pin(s) to configure.
 * \param ul_default_level Default level on the pin(s).
 * \param ul_pull_up_enable Indicates if the pin shall have its pull-up
 * activated.
 */
void _pio_set_output(	Pio *p_pio, 
                    	const uint32_t ul_mask,
		       	const uint32_t ul_default_level,
		       	const uint32_t ul_pull_up_enable){
					   
			   
	p_pio->PIO_PER = ul_mask;
	p_pio->PIO_OER = ul_mask;
	if(ul_default_level){
		p_pio->PIO_SODR = ul_mask;
	} else{
		p_pio->PIO_CODR = ul_mask;
	}
					   /*
					   PMC->PMC_PCER0    = (1<<LED_PIO_ID);
					   LED_PIO->PIO_PER  = LED_PIN_MASK;
					   LED_PIO->PIO_OER  = LED_PIN_MASK;
					   if (!estado)
					   {LED_PIO->PIO_CODR = LED_PIN_MASK;  
					   } 
					   else
					   { LED_PIO->PIO_SODR = LED_PIN_MASK;
					   }
					   */
					   
					   
 }
 