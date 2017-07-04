/*
 * interrupts.c
 *
 *  Created on: Jul 4, 2017
 *      Author: nick
 */
#include "main.h"
//******************************************************************************
//
//This is the USCI_A0 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A0_VECTOR)))
#endif
void EUSCI_A0_ISR(void)
{
    uint8_t RXData = 0;

    __bic_SR_register_on_exit(LPM3_bits);
    switch(__even_in_range(UCA0IV,USCI_UART_UCTXCPTIFG))
    {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:
        RXData = EUSCI_A_UART_receiveData(EUSCI_A0_BASE);
        ringBufS_put (&rx_buffer, (uint8_t)RXData);
        break;
    case USCI_UART_UCTXIFG: break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
    }
}


//******************************************************************************
//
// Port 1 interrupt service routine
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else
#error Compiler not supported!
#endif
{
    P1IFG &= ~BIT2;                         // Clear P1.2 IFG
    P4OUT ^= BIT0;                      // Toggle P4.0 using exclusive-OR
    do_state = handle_state_TX_DIGI;
    //__bic_SR_register_on_exit(LPM3_bits);   // Exit LPM3
}




