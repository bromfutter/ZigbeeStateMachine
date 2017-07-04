/*
 * main.h
 *
 *  Created on: Jul 2, 2017
 *      Author: nick
 */
#ifndef MAIN_H_
#define MAIN_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "driverlib.h"

#define RING_BUF_SZ     256

typedef volatile struct ringBufS
{
    uint8_t buf[RING_BUF_SZ];
    int8_t  head;
    int8_t  tail;
    int8_t  count;
} ringBufS;

void handle_state_INIT(void);
void handle_state_WAIT_FOR_INPUT(void);
void handle_state_TX_DIGI (void);
void handle_state_RX_DIGI (void);
void (*do_state)(void);

//******************************************************************************
// hardware functions
//******************************************************************************
void Init(void);
void initExternalClock(void);
uint8_t configureUART (void);
void Tx_byte(void);
void setPinInterrupt(uint8_t selectedPort, uint16_t selectedPins, uint8_t selectedResistor, uint8_t edgeSelect);

//******************************************************************************
// buffer functions
//******************************************************************************
int8_t Check_Digi_Pkt(ringBufS *_this);
void Process_Digi_Pkt(ringBufS *_this, uint8_t * data);
void ringBufS_init (ringBufS *_this);
uint8_t ringBufS_empty (ringBufS *_this);
uint8_t ringBufS_full (ringBufS *_this);
uint8_t ringBufS_get (volatile ringBufS *_this);
void ringBufS_put (volatile ringBufS*_this, const uint8_t c);
void ringBufS_flush (volatile ringBufS *_this, const uint8_t clearBuffer);
unsigned int modulo_inc (const unsigned int value, const unsigned int modulus);
unsigned int modulo_dec (const unsigned int value, const unsigned int modulus);

//******************************************************************************
// Global Structs
//******************************************************************************
extern ringBufS rx_buffer;
extern ringBufS tx_buffer;

#endif /* MAIN_H_ */
