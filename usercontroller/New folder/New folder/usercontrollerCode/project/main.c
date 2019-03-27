
// the foloing sites are being used as reference
///https://github.com/annem/ADXL362
//AN4509 Application Note
//ADXL362 Datasheet
///Lab SPI form ENEL 387
//Header filer
#include "stm32f10x.h"
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>     
#include <math.h>


// think of user input as 3x3 grid
// horizontal
#define left              (uint16_t)0x3    // 0011
#define straight    (uint16_t)0x2    // 0010
#define right             (uint16_t)0x1    // 0001

// vertical
#define top         (uint16_t)0xC    // 1100
#define middle    (uint16_t)0x8    // 1000
#define bottom    (uint16_t)0x4    // 0100

void Configclk(void);

//-----functions used for the SPI communication accelerometer------------------------------------
void configure_SPI2(void);    //To configure SPI 2 for the accelerometer
void config_ADXL362 (void);        //To configure Accelerometer Adxl 362
void SPI2_write (uint8_t byte);        //To write one byte to SPI
int8_t SPI2_read (void);            //To read one byte from SPI communication
void beginMeasure (void);                //Take the reading from the accelemroeter
void SPI2writeOneRegister  (uint8_t, uint8_t);    //To write one register to to either read or wright
int8_t SPI2readOneRegister(uint8_t);        //To read one register from SPI
void send(uint16_t position);// send the vaule for the led to be turned on
//------------------------------------------------------------------

void delay (unsigned int x)
{
    int i=0;
    for(i = 0; i< x ;i++);    
}

void Configclk(void)//confiuring the GPIOs and clock
{
  RCC->APB1ENR |=  RCC_APB1ENR_SPI2EN; //turns ON clock for SPI2
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN |RCC_APB2ENR_IOPCEN |RCC_APB2ENR_IOPAEN; //turning on the clokcs GPIO port B, A and C

 
    //for led on PA8, PA9, PA10, PA11
    //GPIOA->CRH = 0x00003333;    // output push/pull for dirving leds
    GPIOA->CRH = 0x00007777;    // output open/dtain for interface encoder
    
    GPIOB->CRH = 0xB4B3FF8F;    // PB9, PB12, PB13, PB14, PB15 for accelerometer
    
    
}

void configure_SPI2(void)//configures SPI2
{
    SPI2->CR1 = 0x31C;
    SPI2->CR2 = 0x0;
    GPIOB->BSRR = GPIO_BSRR_BS12;     //makes the NSS pin high
    SPI2->CR1 |= 0x0040;        //enables SPI2
}

    // fixed code
void config_ADXL362 (void)//configures accelerometer
{
        uint8_t POWER_CTL_reg;//address is 0x2D conating the measuring mode
        uint8_t g_range = (0x13);// after reading the g value set it to 8g range selected    //read FILTER_CTL register from Accelerometer // 0x2C is filter ctrl register and its  bits 6 & 7 are used to set the  g
        SPI2writeOneRegister(0x2C, g_range);//sets the g range to +/- 8g by writing its value to power crtl register.
      g_range = SPI2readOneRegister(0x2C);// read the valur form the accelremotere
    POWER_CTL_reg = SPI2readOneRegister(0x2D);    //read power_ctl register to measure the chnage in g
    POWER_CTL_reg = POWER_CTL_reg | (0x04);    // auto sleep mode on so when meauser taken make the accelerometer sleep
    SPI2writeOneRegister(0x2D, POWER_CTL_reg);    // setup auto mode
    beginMeasure();// make it in measuring mode

    delay(100);//delays for the system to get settle for the next reading
}

//Write one bytes to from spi to Accelerometer
void SPI2_write (uint8_t byte)
{
        while (!(SPI2->SR & SPI_SR_TXE )){};        
        SPI2->DR = byte;
}

//Read bytes from the accelerometer
int8_t SPI2_read (void)
{
        uint8_t read_byte;
    while (!(SPI2->SR & SPI_SR_RXNE )){};
        read_byte = SPI2->DR;
    
        return read_byte;    
}


//this function is used to tell the accerelmtoter that we want to write the comad to and red the data
void SPI2writeOneRegister  (uint8_t  regAddress, uint8_t regValue)
{
        uint8_t byte_1;
        GPIOB->BRR = GPIO_BRR_BR12;//NSS set to low
    
        SPI2_write(0x0A);    // write instruction command form datasheet
        byte_1 =SPI2_read();
    
        SPI2_write(regAddress);
        byte_1 =SPI2_read();
    
        SPI2_write(regValue);
        byte_1 =SPI2_read();

        GPIOB->BSRR = GPIO_BSRR_BS12;//make the NSS set to high for the next step
}

//this function will tell the accelremoetr that we will read the data from the accerelometer
int8_t SPI2readOneRegister(uint8_t regAddress)
{
        int8_t regValue = 0;
        uint8_t byte_1;
        GPIOB->BRR = GPIO_BRR_BR12;//NSS set to low
 
        SPI2_write(0x0B);    // read instruction from the datasheet
        byte_1 =SPI2_read();

        SPI2_write(regAddress);
        byte_1 =SPI2_read();
    
        SPI2_write(0x00);
        regValue =SPI2_read();
    
        GPIOB->BSRR = GPIO_BSRR_BS12;//make the NSS set to high for the next step

        return regValue;
}


void send(uint16_t position)
{
    GPIOA->BSRR = position << 8;// used to trun the leds on and off
    
}



//This function starts measurment mode for reading the change in axis rotation
void beginMeasure (void)
{
        uint8_t temp = SPI2readOneRegister(0x2D);
        uint8_t tempwrite = temp | 0x02;
        SPI2writeOneRegister(0x2D, tempwrite);
           
 
}

int main (void)
{
 
    Configclk();// to config the clock and register being used in the project
    configure_SPI2();        //To configure SPI2 for the user controller
  config_ADXL362();//To configure Accelerometer
    
                
            int8_t xdata ; // axis
            int8_t ydata ;
            int8_t zdata ;
        

    
    while (1)
    {
        
    //    xdata = SPI2readOneRegister (0x01);
             xdata =  SPI2readOneRegister(0x08);// reading the register x
             ydata = SPI2readOneRegister(0x09);//  reading the register y
             zdata = SPI2readOneRegister(0x0a);//  reading the register z
            
            GPIOA->BSRR = GPIO_BSRR_BR8 | GPIO_BSRR_BR9 | GPIO_BSRR_BR10 |GPIO_BSRR_BR11;// just top make sure before we enetr the loop we are making sure all the leds are off
        
        
        
        
         //forward
         if(xdata >30 && xdata <55)
         {
             send(top);   
            
         }
         else if(xdata >=-35 && xdata <= 30)
         {
            send(middle);
         }
         else if (xdata >-55 && xdata <-35)  
         {
             send(bottom);
         }
         else
         {
             send(middle);// out of bounce
             send(straight);
             continue;
         }
        
         //backwards
        if(ydata >30 && ydata <55)
         {
             send(left);   
             GPIOA->BSRR = GPIO_BSRR_BS8 | GPIO_BSRR_BS10;
            // position = 0x3;
            
         }
         else if(ydata >=-35 && ydata <= 30)
         {
            send(straight);
         }
         else if (ydata >-55 && ydata <-35)  
         {
             send(right);
         }
         else
         {
             send(middle);// out of bounce
             send(straight);
             continue;
         }
        
        
        
        
        
        
}
    
}


