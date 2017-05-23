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
		}
	else{p_pio->PIO_CODR = ul_mask;
	}
	if (ul_pull_up_enable){
		p_pio->PIO_PUER = ul_mask;
		} 
	else{p_pio->PIO_PUDR = ul_mask;
	}
	/*Retirado do 08-PIO_INPUT*/
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
 
  void _pio_pull_up(	Pio *p_pio, 
								const uint32_t ul_mask, 
									const uint32_t ul_pull_up_enable){
	  if (ul_pull_up_enable)
	  {p_pio->PIO_PUER = ul_mask;					// Ativa pull-up no PIO no registrador            (PullUp ENABLE register)
	  }
	  else
	  {p_pio->PIO_PUDR = ul_mask;					// Desativa pull-up no PIO no registrador            (Pull-Up Disable Register)
	  }
  }
  
  void _pio_pull_down(Pio *p_pio, 
							const uint32_t ul_mask, 
								const uint32_t ul_pull_down_enable){
	  if (ul_pull_down_enable)
	  {p_pio->PIO_PPDER = ul_mask;					// Ativa pull-down no PIO no registrador            ( Pull-down Enable Register)
	  } 
	  else
	  {p_pio->PIO_PPDDR = ul_mask;					// Desativa pull-down no PIO no registrador            (Pull-down Disable Register)
	  }
  }
 
 void _pio_set_input( 	Pio *p_pio,
							 const uint32_t ul_mask,
									const uint32_t ul_attribute){
	/*
	BUT_PIO->PIO_ODR	 = BUT_PIN_MASK;			// Desativa saída do registrador                  (Output DISABLE register)
	BUT_PIO->PIO_PER	 = BUT_PIN_MASK;			// Ativa controle do pino no PIO no registrador   (PIO ENABLE register)
	BUT_PIO->PIO_PUER	 = BUT_PIN_MASK;			// Ativa pull-up no PIO no registrador            (PullUp ENABLE register)
	BUT_PIO->PIO_IFER	 = BUT_PIN_MASK;			// Ativa debouncing
	BUT_PIO->PIO_IFSCER  = BUT_PIN_MASK;			// Ativa clock periferico
	BUT_PIO->PIO_SCDR	 = BUT_DEBOUNCING_VALUE;	// Configura a frequencia do debouncing
	*/
	 p_pio->PIO_ODR = ul_mask;						// Desativa saída do registrador                  (Output DISABLE register)
	 p_pio->PIO_PER = ul_mask;						// Ativa controle do pino no PIO no registrador   (PIO ENABLE register)
	
	/*_pio_pull_up(p_pio, ul_mask, 1);*/
	
	_pio_pull_up(p_pio, ul_mask,
			 ul_attribute & PIO_PULLUP);			// Ativa pull-up no PIO no registrador            (PullUp ENABLE register)
	 if (ul_attribute & PIO_DEBOUNCE)
	 {p_pio->PIO_IFER = ul_mask;
		}											// Ativa debouncing
		
 }
 
	uint32_t _pio_get_output_data_status(const Pio *p_pio,
									 const uint32_t ul_mask){
	 if (p_pio->PIO_PDSR & ul_mask)					///Pin Data Status Register
	 {
		 return 1;						
	 } 
	 else
	 {
		 return 0;						
	 }
 }
 
/**
 * \brief Set a high output level on all the PIOs defined in ul_mask.
 * This has no immediate effects on PIOs that are not output, but the PIO
 * controller will save the value if they are changed to outputs.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
void _pio_set(   Pio *p_pio, 
                const uint32_t ul_mask){
					p_pio->PIO_SODR = ul_mask;
				}

/**
 * \brief Set a low output level on all the PIOs defined in ul_mask.
 * This has no immediate effects on PIOs that are not output, but the PIO
 * controller will save the value if they are changed to outputs.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
void _pio_clear( Pio *p_pio, 
                const uint32_t ul_mask){
					p_pio->PIO_CODR = ul_mask;
				}
