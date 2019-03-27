 #include "stm32f10x.h"
 #include "IO.h"
 #include "VR.h"
 #include "LCD.h"
 #include "clock.h"
 
// think of user input as 3x3 grid
// horizontal
#define left       (uint16_t)0x3    // 0011
#define straight   (uint16_t)0x2    // 0010
#define right      (uint16_t)0x1    // 0001

// vertical
#define top       (uint16_t)0xC    // 1100
#define middle    (uint16_t)0x8    // 1000
#define bottom    (uint16_t)0x4    // 0100
 
 // SWITCH AND LED I/O FUNCTIONS
 
 void send(uint16_t position)
{
	GPIOA->BSRR = position << 9;
	
}

void led_IO_init (void)
{
    //Enable peripheral clocks for various ports and subsystems
    //Bit 4: Port C Bit3: Port B Bit 2: Port A
    RCC->APB2ENR |=  RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN ;

    //Set the config and mode bits for Port C bit 9 and 8 so they will
    // be push-pull outputs (up to 50 MHz)
    GPIOC->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_MODE8 ;
    GPIOC->CRH &= ~GPIO_CRH_CNF9 & ~GPIO_CRH_CNF8 ;
/* LED Configuration */
// Configuration Port A 9-12 - output 50 MHz, general. purpose i/o 
	 GPIOA->CRH |=   GPIO_CRH_MODE9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12 ;
   GPIOA->CRH &=  ~GPIO_CRH_CNF9 & ~GPIO_CRH_CNF10 & ~GPIO_CRH_CNF11 & ~GPIO_CRH_CNF12 ;
	
	// LCD SCREEN MODE AND CONFIGURATION SET UP CONFIGURED "LOW"
	// RS , R/W, ENABLE (E) 
		GPIOB->CRL |=   GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE5;
		GPIOB->CRL &=   ~GPIO_CRL_CNF0 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF5;
	// DB0 TO DB7
		GPIOC->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE2 | GPIO_CRL_MODE3 | GPIO_CRL_MODE4 | GPIO_CRL_MODE5 |GPIO_CRL_MODE6 | GPIO_CRL_MODE7; 
		GPIOC->CRL &= ~GPIO_CRL_CNF0 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF2 & ~GPIO_CRL_CNF3 & ~GPIO_CRL_CNF4 & ~GPIO_CRL_CNF5  & ~GPIO_CRL_CNF6 & ~GPIO_CRL_CNF7;
	
}

/* Switch Configuration */ 
	// SW1_1-2 input Port A 6-7 - input, floating
	// SW1_3-4 Port C 10-11 - input, floating 
	// SW2 Port B 8 - input, floating 
	// SW3 Port B 9 - input, floating
	// SW4 Port C 12 - input, floating 
	// SW5 Port A 5 - input, floating
	// ** These are all set by default ** //



void led_switch_operate(void)
{
	// SW2 => LED9
	// SW3 => LED10
	// SW4 => LED11
	// SW5 => LED12
		if ( ( (GPIOC->IDR & GPIO_IDR_IDR8) == 0) ){
			     move_forward();
		}
		else if ( (GPIOC->IDR & GPIO_IDR_IDR9) == 0 ) {
			      turn_right();
		}
		else if ( (GPIOC->IDR & GPIO_IDR_IDR10) == 0 ) {
			         turn_left();
		}
		
		
			else if ( (GPIOC->IDR & GPIO_IDR_IDR11) == 0 ) {
			           move_backward();
		}
		else {
			stop();
		}
}
	
void move_forward()
{
	
		 //GPIOA->ODR = ~GPIO_ODR_ODR9;  
	
	// before we enter the loop we are making sure all the leds are off		
		GPIOA->BSRR = GPIO_BSRR_BR8 | GPIO_BSRR_BR9 | GPIO_BSRR_BR10 |GPIO_BSRR_BR11 |GPIO_BSRR_BR12;
	
		send(straight);
	  send(top);
		 		
	
		         
}

void turn_right()
{
	
			              	
	//GPIOA->ODR = ~GPIO_ODR_ODR10;
	
	//before we enter the loop we are making sure all the leds are off		
		GPIOA->BSRR = GPIO_BSRR_BR8 | GPIO_BSRR_BR9 | GPIO_BSRR_BR10 |GPIO_BSRR_BR11 |GPIO_BSRR_BR12;
	
		send(right);
	  send(middle);
			
            
}

void turn_left()
{
	        	
//	    GPIOA->ODR = ~GPIO_ODR_ODR11;   
	
	//before we enter the loop we are making sure all the leds are off		
		GPIOA->BSRR = GPIO_BSRR_BR8 | GPIO_BSRR_BR9 | GPIO_BSRR_BR10 |GPIO_BSRR_BR11 |GPIO_BSRR_BR12;
	
		send(left);
	  send(middle);
			 	

		        
              
}

void move_backward()
{ 	       
	
//	    GPIOA->ODR = ~GPIO_ODR_ODR12;    
	
	//before we enter the loop we are making sure all the leds are off		
		GPIOA->BSRR = GPIO_BSRR_BR8 | GPIO_BSRR_BR9 | GPIO_BSRR_BR10 |GPIO_BSRR_BR11 |GPIO_BSRR_BR12;
	
		send(straight);
	  send(bottom);
  		 		 
}
	
void stop()
{
//GPIOA->ODR |= GPIO_ODR_ODR9 | GPIO_ODR_ODR10 | GPIO_ODR_ODR11 | GPIO_ODR_ODR12;	
//GPIOB->ODR |= GPIO_ODR_ODR10 | GPIO_ODR_ODR11 | GPIO_ODR_ODR12| GPIO_ODR_ODR13;	
	
	//before we enter the loop we are making sure all the leds are off		
		GPIOA->BSRR = GPIO_BSRR_BR8 | GPIO_BSRR_BR9 | GPIO_BSRR_BR10 |GPIO_BSRR_BR11 |GPIO_BSRR_BR12;
	
		send(straight);
	  send(middle);
}
void ON()
	{
		
	if ( ( (GPIOC->IDR & GPIO_IDR_IDR7) == 0) ){
			     GPIOC->ODR ^= GPIO_ODR_ODR9;
}
}	
void OFF()
	{
	if ( ( (GPIOC->IDR & GPIO_IDR_IDR7) == 0) ){
			    GPIOC->ODR ^= GPIO_ODR_ODR9;
		
}	
}


