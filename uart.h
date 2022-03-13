void UART_Init(){
    // Baud rate configuration
    BRGH = 1;
    SPBRG = 25;
    // Enable Asynchronous Serial Port
    SYNC = 0;
    SPEN = 1;
    // Configure Rx-Tx pin for UART 
    TRISC6 = 1;
    TRISC7 = 1;
    // Configure interrupt
    RCIE = 1;
    PEIE = 1;
    // Enable data continous reception
    CREN = 1; 
}
    

uint8_t UART_Receive(){
    return RCREG;
}

