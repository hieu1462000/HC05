#include "config.h"

float temp = 0;
char* display;

void Port_Config(){
    TRISD = 0x00;
    TRISC = 0x00;
    TRISB = 0x01;   // RB0 is input, pin interrupt
    PORTB = 0xFF;               
    
    INTEDG = 1;                 // Interrupt edge config bit (HIGH value means interrupt occurs every rising edge)
    INTE = 1;                   // IRQ (Interrupt request pin RB0) Interrupt Enable bit
    GIE = 1;                    // Global Interrupt Enable bit
}

void main(void) {  
    Port_Config();
    LCD_Init();
    ADC_Init();
    UART_Init();
    
    
   while(1){  
        
        if(RB1 == 1){ //chân RB1 lay lam bien de xac dinh interrupt
            LCD_Clear();
            temp =  ADC_Read(0) * 5/10;  // LM35 ouput to temperature
            display = ftoa(temp, 1);	 // Convert double to String
            LCD_Set_Cursor(1,1);		 
            LCD_Write_String("Temperature");
            LCD_Set_Cursor(2,1);
            LCD_Write_String(display);
            __delay_ms(5000);  
        }else{
            LCD_Clear();
            LCD_Set_Cursor(1,1);
            LCD_Write_String("  TURN_OFF_");
            __delay_ms(5000);  
        }
    }
    return;
}



void __interrupt() ISR(void){
	// RB0 interrupt
    if(INTF == 1 ){            
        RB1 = ~RB1;  
        INTF = 0;
        RCIF = 0;
    }
	
	// UART interrupt   
    if(RCIF == 1){
        RB1 = ~RB1;
        RCIF = 0;
    }
} 

