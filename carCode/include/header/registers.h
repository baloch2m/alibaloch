#ifndef REGISTERS_H
#define REGISTERS_H
#include <stdint.h>

typedef uint32_t volatile * const reg32_t;
typedef uint16_t volatile * const reg16_t;

#define PERIPH_BASE           ((uint32_t)0x40000000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)

#define RCC_BASE    (AHBPERIPH_BASE + 0x1000)
#define RCC_APB2ENR (* (reg32_t)(RCC_BASE + 0x18))
#define RCC_APB1ENR	(* (reg32_t)(RCC_BASE 	+ 0x1C))
#define APB1RSTR 		(* (reg32_t)(RCC_BASE 	+ 0x10))

#define ADC1_BASE	  (APB2PERIPH_BASE + 0x2400)
#define ADC1_SR			(* (reg32_t)(ADC1_BASE 	+ 0x00))
#define ADC1_CR1		(* (reg32_t)(ADC1_BASE 	+ 0x04))
#define ADC1_CR2		(* (reg32_t)(ADC1_BASE 	+ 0x08))
#define ADC1_SMPR1	(* (reg32_t)(ADC1_BASE 	+ 0x0C))
#define ADC1_SQR3		(* (reg32_t)(ADC1_BASE 	+ 0x34))
#define ADC1_DR			(* (reg32_t)(ADC1_BASE 	+ 0x4C))


#define GPIOA_BASE 	((uint32_t) 0x40010800)
#define GPIOA_CRL 	(* (reg32_t)(GPIOA_BASE + 0x00))

#define GPIOB_BASE	(APB2PERIPH_BASE + 0x0C00)
#define GPIOB_CRL   (* (reg32_t)(GPIOB_BASE + 0x00))
#define GPIOB_ODR 	(* (reg32_t)(GPIOB_BASE + 0x0C))
#define GPIOB_CRH 	(* (reg32_t)(GPIOB_BASE + 0x04))
#define GPIOB_BSRR	(* (reg32_t)(GPIOB_BASE + 0x10))
#define GPIOB_BRR 	(* (reg32_t)(GPIOB_BASE + 0x14))

#define GPIOC_BASE	(APB2PERIPH_BASE + 0x1000)
#define GPIOC_CRL   (* (reg32_t)(GPIOC_BASE + 0x00))
#define GPIOC_ODR 	(* (reg32_t)(GPIOC_BASE + 0x0C))
#define GPIOC_CRH 	(* (reg32_t)(GPIOC_BASE + 0x04))
#define GPIOC_BSRR	(* (reg32_t)(GPIOC_BASE + 0x10))
#define GPIOC_BRR 	(* (reg32_t)(GPIOC_BASE + 0x14))
	
#define USART2_BASE ((uint32_t) PERIPH_BASE + 0x4400)
#define USART2_SR 	(* (reg32_t)(USART2_BASE + 0x00))
#define USART2_BRR 	(* (reg32_t)(USART2_BASE + 0x08))
#define USART2_CR1 	(* (reg32_t)(USART2_BASE + 0x0C))
#define USART2_DR 	(* (reg32_t)(USART2_BASE + 0x04))
	
#define TIM2_BASE PERIPH_BASE
#define TIM2_CR1 (* (reg32_t)(TIM2_BASE))
#define TIM2_CNT (* (reg32_t)(TIM2_BASE + 0x24))
#define TIM2_ARR (* (reg32_t)(TIM2_BASE + 0x2C))
#define TIM2_PSC (* (reg32_t)(TIM2_BASE + 0x28))
#define TIM2_SR	 (* (reg32_t)(TIM2_BASE + 0x10))
#define TIM2_DIER (* (reg32_t)(TIM2_BASE + 0x0C))
	
#define TIM4_BASE             ( (uint32_t)0x40000800 )
#define TIM4_CR1              (* (reg16_t)(TIM4_BASE + 0x00) )
#define TIM4_CR2              (* (reg16_t)(TIM4_BASE + 0x04) )
#define TIM4_SMCR             (* (reg16_t)(TIM4_BASE + 0x08) )
#define TIM4_CCMR1            (* (reg16_t)(TIM4_BASE + 0x18) )
#define TIM4_CCMR2            (* (reg16_t)(TIM4_BASE + 0x1c) )
#define TIM4_CCER             (* (reg16_t)(TIM4_BASE + 0x20) )
#define TIM4_PSC              (* (reg16_t)(TIM4_BASE + 0x28) )
#define TIM4_ARR              (* (reg16_t)(TIM4_BASE + 0x2c) )
#define TIM4_CCR1             (* (reg16_t)(TIM4_BASE + 0x34) )
#define TIM4_CCR2             (* (reg16_t)(TIM4_BASE + 0x38) )
#define TIM4_CCR3             (* (reg16_t)(TIM4_BASE + 0x3c) )
#define TIM4_CCR4             (* (reg16_t)(TIM4_BASE + 0x40) )
	
#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define ITM_BASE            (0xE0000000UL)                            /*!< ITM Base Address */
#define DWT_BASE            (0xE0001000UL)                            /*!< DWT Base Address */
#define TPI_BASE            (0xE0040000UL)                            /*!< TPI Base Address */
#define CoreDebug_BASE      (0xE000EDF0UL)                            /*!< Core Debug Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL) 
#define NVIC_ISER_SETENA_28 ((uint32_t)0x10000000)   /*!< bit 28 */
#define NVIC_ISER_SETENA_18 ((uint32_t)0x40000)  		 /*!< bit 18 */

#define NVIC_ISER		(* (reg32_t) NVIC_BASE)

void setupRegs(void);

#endif      
