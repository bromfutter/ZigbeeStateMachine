/*
 * hardware.c
 *
 *  Created on: Jul 3, 2017
 *      Author: nick
 */
#include "main.h"
#define PULL_UP     1
#define PULL_DOWN   2

void Init(void)
{
    initExternalClock();

    // Configure Button
    setPinInterrupt(
            GPIO_PORT_P1,
            GPIO_PIN2,
            PULL_UP,
            GPIO_HIGH_TO_LOW_TRANSITION);

/*
    P1DIR &= ~BIT2;                         // input
    P1OUT |= BIT2;                          // Configure P1.2 as pulled-up
    P1REN |= BIT2;                          // P1.3 pull-up register enable
    P1IES |= BIT2;                          // P1.3 Hi/Low edge
    P1IE  |= BIT2;                           // P1.3 interrupt enabled
    P1IFG &= ~BIT2;                         // P1.3 IFG cleared
*/
    // Configure LED2
    P4OUT &= ~BIT0;                          // Configure P4.0 as output
    P4DIR |= BIT0;

    /*
     * Disable the GPIO power-on default high-impedance mode to activate
     * previously configured port settings
     */
    PMM_unlockLPM5();

    configureUART();

    __enable_interrupt();
}

void initExternalClock(void)
{
    //Set P4.1 and P4.2 as Function Input.
    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P4,
            GPIO_PIN1 + GPIO_PIN2,
            GPIO_PRIMARY_MODULE_FUNCTION
            );

    //Set external clock frequency to 32.768 KHz
    CS_setExternalClockSource(32768);
    //Set ACLK=XT1
    CS_initClockSignal(CS_ACLK,CS_XT1CLK_SELECT,CS_CLOCK_DIVIDER_1);
    //Start XT1 with no time out
    CS_turnOnXT1(CS_XT1_DRIVE_0);
    //Set SMCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_SMCLK,CS_DCOCLKDIV_SELECT,CS_CLOCK_DIVIDER_1);
    //Set MCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_MCLK,CS_DCOCLKDIV_SELECT,CS_CLOCK_DIVIDER_1);
}

void configureUART (void)
{
    // Configure UART pins
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P1,
        GPIO_PIN0 + GPIO_PIN1,
        GPIO_PRIMARY_MODULE_FUNCTION
        );

    //Configure UART
    //SMCLK = 1MHz, Baudrate = 9600
    //UCBRx = 104, UCBRFx = 0, UCBRSx = 0xD6, UCOS16 = 0
    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
    param.clockPrescalar = 104;
    param.firstModReg = 0;
    param.secondModReg = 0xD6;
    param.parity = EUSCI_A_UART_NO_PARITY;
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
    param.uartMode = EUSCI_A_UART_MODE;
    param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    if(STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A0_BASE, &param))
    {
        return;
    }

    EUSCI_A_UART_enable(EUSCI_A0_BASE);

    EUSCI_A_UART_clearInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);

    // Enable USCI_A0 RX interrupt
    EUSCI_A_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);      // Enable interrupt
}

void Tx_byte(void)
{
    static uint8_t TXData = 0;
    uint8_t zigbeePkt[] = {0x7E, 0x00, 0x02, 0x8A, 0x00, 0x75};

    if(TXData == 5) TXData = 0;

    for(TXData = 0; TXData < sizeof(zigbeePkt); TXData++)
    {
        // Load data onto buffer
        EUSCI_A_UART_transmitData(EUSCI_A0_BASE, zigbeePkt[TXData]);
    }

    // Load data onto buffer
    //EUSCI_A_UART_transmitData(EUSCI_A0_BASE, zigbeePkt[TXData++]);
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
void setPinInterrupt(uint8_t selectedPort, uint16_t selectedPins, uint8_t selectedResistor, uint8_t edgeSelect)
{
    if(selectedPort < 3)
    {
        GPIO_setAsInputPin(selectedPort,selectedPins);

        if(selectedResistor == PULL_UP)
        {
            GPIO_setAsInputPinWithPullUpResistor(selectedPort, selectedPins);
        }
        else    // Pull down resistor selected
        {
            GPIO_setAsInputPinWithPullDownResistor(selectedPort, selectedPins);
        }

        GPIO_selectInterruptEdge(selectedPort,selectedPins,edgeSelect);

        GPIO_enableInterrupt(selectedPort,selectedPins);

        GPIO_clearInterrupt(selectedPort, selectedPins);
    }
}
// end of hardware.c
