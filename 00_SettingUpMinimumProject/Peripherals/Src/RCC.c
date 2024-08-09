/*
 * RCC.c
 *
 *  Created on: Aug 8, 2024
 *      Author: Obviousfancy
 */

#include "RCC.h"
void RCC_HSE_Config(void)
{
  /*
   * Configuration parameters(for Maximum Speed 72 MHz) --> STM32F103 Clock Tree
   *
   * HSE(High Speed External Oscilator) = 8 MHz
   * PLL_Mul(Multiplexor PLL) = 9
   * USB Preescaler = 1
   * AHB Preescaler = 1
   * Cortex Preescaler(To Cortex System Timer) = 1
   * -->72 MHz System Clock
   *
   * APB1 preescaler = 2 --> 36 Mhz Peripheral Clocks,72 MHz Timer Clocks
   * APB2 preescaler = 1 --> 72 MHz for Peripheral and Timer Clocks
   * ADC Preescaler = 6 --> 12 Mhz
   */

  //PLL Configurations
  //PLL_Mul = 9(Page 102 Reference Manual)
  RCC->CFGR &= ~(0xFUL << 18);    //Clear bitfields [21-18]   basicamente ponemos en cero los bits del 18 asignandole a CFGR, recorriendolo 18 espacios, e invirtiendo los 1111 a ceros
  //RCC->CFGR &= ~(RCC_CFGR_PLLMULL);
  RCC->CFGR |= (7UL << 18);       //Asignamos 0111 a el multiplicador, con 7 hexadecimal que es 0111 con un or para cambiarlo de 0 a 1
  //USB PREESCALER TO 1.5
  RCC->CFGR &= ~(1UL << 22);      //Limpiamos a ceros el registro de el USB preescaler inviertiendo a cero el bit 22 del registro
  //RCC->CFGR &= ~(RCC_CFGR_USBPRE);    //Lo mismo de arriba pero dado por el fabricante (0x1UL << (22U))
  //RCC->CFGR |= (1UL << 22);             //

  /*HSE Oscillator*/
  //Enable HSE Oscillator (Page 99 of Reference Manual)
  RCC->CR |= (1UL << 16);                 //Encendemos el HSE oscillator
  //RCC->CR |= (RCC_CR_HSEON);              //Lo mismo pero con macros de stm32
  //Wait for it stabilize
  while((RCC->CR & (1UL <<17)) == 0){};          //Esperamos a que el CR tenga informacion y que el HSE este listo
  //while((RCC->CR & RCC_CR_HSERDY) == 0){};     //Lo mismo pero con macros

  //Select HSE as PLL Source
  //RCC->CR |= RCC_CFGR_PLLSRC;                 //Lo mismo de abajo pero con macros
  RCC->CR |= (1UL << 16);                         //Seleccionamos la fuente del PLL del oscilador externo

  //Enable PLL
  RCC->CR |= (1UL << 24);                        //Habilitamos el bit de encendido del PLL
  //RCC->CR |= RCC_CR_PLLON;

  //Wait for it stabilize
   while((RCC->CR & (1UL <<25)) == 0){};          //Esperamos a que el CR tenga informacion y que el PLL SE HAYA CONFIGURADO
   //while((RCC->CR & RCC_CR_PLLRDY) == 0){};     //Lo mismo pero con macros

   //Flash prefetch and wait state
   //2Waitstate = 72 Mhz
   FLASH->ACR &= ~(7UL << 0);                     //Establecemos a cero los bits de latencia de el wait state
   //FLASH->ACR &= ~(FLASH_ACR_LATENCY);          //Lo mismo pero con macros

   FLASH->ACR |= (1UL << 1);                      //Establecemos la latencia en 2 wait states
   //FLASH->ACR |= (FLASH_ACR_LATENCY_1);                      //Establecemos la latencia en 2 wait states

   //Enable Prefetch Buffer
   FLASH->ACR |= (1UL << 4);
   //FLASH->ACR |= (FLASH_ACR_PRFTBE);

   //Select PLL like main system clock
   RCC->CFGR &= ~ (3UL << 0);                   //Limpiamos el registro
   //RCC->CFGR &= ~(RCC_CFGR_SW);
   RCC->CFGR |= (2UL << 0);                     //Asignamos 1 al bit 1 con un recorrimiento desde el bit 0
   //RCC->CFGR |= RCC_CFGR_SW_1;

   //Wait for PLL to be the active clock source
   while((RCC->CFGR & (2UL << 2)) == 0){};      //Esperamos a que el reloj principal sea usado con el PLL
   //while((RCC->CFGR & RCC_CFGR_SWS_1) == 0){};

   //Peripherals clock setup
   //AHB Preescaler
   RCC->CFGR &= ~(0xFUL << 4);                  //Limpiamos el registro de el AHB Preescaler
   //RCC->CFGR &= ~(RCC_CFGR_HPRE);               //Con macros

   /*APB1 Preescaler*/
   RCC->CFGR &= ~(7UL << 8);                    //Limpiamos el registro de el APB1 Preescaler
   //RCC->CFGR &= ~(RCC_CFGR_PPRE1);
   RCC->CFGR |= (4UL << 8);                     //Dividimos por 2 el preescaler de APB1
   //RCC->CFGR |= (RCC_CFGR_PPRE1_2);           //Macros

   /*APB2 Preescaler*/

   RCC->CFGR &= ~(7UL << 11);                    //Limpiamos el registro de el APB2 Preescaler
   //RCC->CFGR &= ~(RCC_CFGR_PPRE2);

   /*ADC Preescaler*/
   RCC->CFGR &= ~(3UL << 14);                    //Limpiamos el registro a cero
   //RCC->CFGR &= ~(RCC_CFGR_ADCPRE);
   RCC->CFGR |= (2UL << 14);                     //Dividimos el preescaler del ADC en 6
   //RCC->CFGR |= (RCC_CFGR_ADCPRE_1);


}
