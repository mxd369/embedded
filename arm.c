#include <stdio.h>        // Diamond braces for sys lib: Standard I/O
#include "uart.h"         // Quotes for user lib: UART lib
#include "tm4c123gh6pm.h" // define all the I/O port names for the TM4C123

int main(void) {
  UART_Init();  // call subroutine to initialize the uart 
  printf("This program calculates areas of square-shaped rooms\n");
}


//  declaration                    input            output
void Ritual(void);              // none             none 
char InChar(void);              // none             8-bit
void OutChar(char);             // 8-bit            none
short InSDec(void);             // none             16-bit
void OutSDec(short);            // 16-bit           none
char Max(char,char);            // two 8-bit        8-bit
int EMax(int,int);              // two 32-bit       32-bit
void OutString(char*);          // pointer to 8-bit none
char *alloc(int);               // 32-bit           pointer to 8-bit
int Exec(void(*fnctPt)(void));  // function pointer 32-bit




//declaring functions, alternative declarations

InitSCI();
char InChar(); 
void OutChar(char letter);
char UpCase(char letter);
InString(char *pt, unsigned int MaxSize);



extern void InitSCI(void); 
extern char InChar(void);  
extern void OutChar(char); 
extern char UpCase(char);  
extern void InString(char *, unsigned int);



int (*fp)(int);  // pointer to a function with input and output
int fun1(int input){
   return(input+1);    // this adds 1
};
int fun2(int input){
   return(input+2);    // this adds 2
};
void Setp(void){ int data;
   fp = &fun1;      // fp points to fun1
   data = (*fp)(5); // data=fun1(5);
   fp = &fun2;      // fp points to fun2
   data = (*fp)(5); // data=fun2(5);
};

