//******************************************************************************
//
//  @info: Zigbee Operating System
//
//
//******************************************************************************
#include "main.h"

ringBufS rx_buffer = { };
ringBufS tx_buffer = { };
uint8_t data[RING_BUF_SZ] = {0};
static uint8_t *dataPtr;

int main(void)
{
    // stop watchdog
    WDT_A_hold(WDT_A_BASE);

    dataPtr = &data[0];

    // Do not forget to initialize me!!!
    do_state = handle_state_INIT;
    while(1)
    {
        do_state();
    }
}

//******************************************************************************
//                                   STATES
//******************************************************************************
//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
void handle_state_INIT(void)
{
    Init();
    do_state = handle_state_WAIT_FOR_INPUT;
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
void handle_state_WAIT_FOR_INPUT(void)
{
    // Enter LPM3, interrupts enabled
    //__bis_SR_register(LPM3_bits|GIE);
    if(rx_buffer.count >= 3)
    {
        // large enough packet to start validating
        do_state = handle_state_RX_DIGI;
    }
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
void handle_state_TX_DIGI (void)
{
    Tx_byte();
    do_state = handle_state_WAIT_FOR_INPUT;
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
void handle_state_RX_DIGI (void)
{
    Process_Digi_Pkt(&rx_buffer, dataPtr);
}
