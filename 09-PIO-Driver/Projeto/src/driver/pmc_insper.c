/**
 * @file pmc_insper.h
 * @author Rafael Corsi
 * @date 22/3/2016
 * @brief Funções para configurar o PMC do SAME70
 */


/**
 * inclui o head do pmc
 */
#include "pmc_insper.h"

uint32_t _pmc_enable_periph_clock(uint32_t ID){
    /**
     * @brief Existem dois registradores que configuram
     * os clocks dos perifericos, é necessário testarmos
     * antes para saber em qual deve ser salvo.
     *
     * O ID máximo para o PMC_PCER0 é 32
     */
    if(ID< 32){
		/**
		* PMC_PCER0: PMC Peripheral Clock Enable Register 0
		* Mal-sucedido
		*/
        PMC->PMC_PCER0 = (1 << ID); 
		return(0);
    }
    else{
		/**
		* PMC_PCER1: PMC Peripheral Clock Enable Register 1
		* Bem-sucedido
		*/
        PMC->PMC_PCER1 = (1 << ID); 
		return(1);
    }

    /**
     * @brief qual seria a situação que retornariamos 1 ?
	 * Deveríamos retornar 1, quando ID é 32, em PMC_PCER1.
     */
    return(0);
}

uint32_t _pmc_disable_periph_clock(uint32_t ID){
    /**
     * @brief Existem dois registradores que configuram
     * os clocks dos perifericos, é necessário testarmos
     * antes para saber em qual deve ser salvo.
     *
     * O ID máximo para o PMC_PCER0 é 32
     */
    if(ID< 32){
		/**
		*PMC_PCDR0: PMC Peripheral Clock Disable Register 0;
		* Mal-sucedido;
		*/
        PMC->PMC_PCDR0 = (1 << ID);
		return(0);
    }
    else{
		/**
		*PMC_PCDR1: PMC Peripheral Clock Disable Register 1;
		*Bem-sucedido;
		*/
        PMC->PMC_PCDR1 = (1 << ID);
		return(1);
    }

    /**
     * @brief qual seria a situação que retornariamos 1 ?
	 * Deveríamos retornar 1, quando ID é 32, em PMC_PCDR1.
     */
    return(0);
}

