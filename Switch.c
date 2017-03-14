// Switch.c
// Runs on LM3S811
// Provide functions that initialize a GPIO as an input pin and 
// allow reading of a positive logic switch.
// Use bit-banded I/O.
// Jonathan Valvano
// July 11, 2011

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to the Arm Cortex M3",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2011
   Example 2.3, Program 2.9, Figure 2.30

 Copyright 2011 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// positive logic switch connected to PD5

#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define PD5                     (*((volatile unsigned long *)0x40007080))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOD      0x00000008  // port D Clock Gating Control

#define PD5 (*((volatile unsigned long *)0x40007080))
void Switch_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000008;  // 1) activate clock for Port D
  delay = SYSCTL_RCGC2_R;        // allow time for clock to settle
  GPIO_PORTD_DIR_R &= ~0x20;     // 2) set direction register
  GPIO_PORTD_AFSEL_R &= ~0x20;   // 3) regular port function
  GPIO_PORTD_DEN_R |= 0x20;      // 4) enable digital port
}
unsigned long Switch_Input(void){ 
  return PD5;      // 0x20 if pressed, 0x00 if not pressed
}

//debug code
// debug hardware, LED on PC5
#define GPIO_PORTC_DATA_R       (*((volatile unsigned long *)0x400063FC))
#define GPIO_PORTC_DIR_R        (*((volatile unsigned long *)0x40006400))
#define GPIO_PORTC_DEN_R        (*((volatile unsigned long *)0x4000651C))
#define SYSCTL_RCGC2_GPIOC      0x00000004  // port C Clock Gating Control
#define PC5 (*((volatile unsigned long *)0x40006080))
int main(void){
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;// activate port C
  Switch_Init();            // initialize PD5 and make it input
  GPIO_PORTC_DIR_R |= 0x20; // make PC5 output (PC5 built-in LED)
  GPIO_PORTC_DEN_R |= 0x20; // enable digital I/O on PC5
  while(1){
    if(Switch_Input()){
      PC5 = 0x20;  // turn on LED if switch pressed
    } else{
      PC5 = 0x00;  // turn off LED if switch not pressed
    }
  }
}
