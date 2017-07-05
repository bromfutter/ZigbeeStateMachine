/*
 * buffer.c
 *
 *  Created on: Jul 3, 2017
 *      Author: nick
 */
#include "main.h"

//******************************************************************************
//         name:    Process_Digi_Pkt
//  description:    determines is rx'd pkt is a valid zigbee api frame
//   parameters:    pointer to ringBufS structure
//      returns:    none
//******************************************************************************
void Process_Digi_Pkt(ringBufS *_this, uint8_t * data)
{
    uint8_t tempData = 0;
    static uint8_t valid = 0;
    static uint16_t length;

    for(;_this->count > 0; )
    {
        tempData = ringBufS_get(_this);

        if(tempData == 0x7E)
        {
            // valid packet
            valid = 1; //true
            //store pkt length
            tempData = ringBufS_get(_this); // byte 2
            length = *data << 8;
            *data = ringBufS_get(_this); // byte 3
            length = *data;
        }
        else if((valid == 1) && (length > 0))
        {
            *data = tempData;
            data++;
            length--;
        }
        else if((valid == 1) && (length == 0))
        {
            valid = 0;
        }
    }
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
void ringBufS_init (ringBufS *_this)
{
    uint16_t i = 0;
    /*****
      The following clears:
        -> buf
        -> head
        -> tail
        -> count
      and sets head = tail
    ***/
    //memset (_this, 0, sizeof (*_this));
    for(i = RING_BUF_SZ; i > 0; i--)
    {
       _this->buf[i] = 0;
    }
    _this->head = 0;
    _this->tail = 0;
    _this->count = 0;
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
uint8_t ringBufS_empty (ringBufS *_this)
{
    return (0==_this->count);
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
uint8_t ringBufS_full (ringBufS *_this)
{
    return (_this->count>=RING_BUF_SZ);
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
uint8_t ringBufS_get (volatile ringBufS *_this)
{
    int c;
    if (_this->count>0)
    {
      c = _this->buf[_this->tail];
      _this->tail = modulo_inc (_this->tail, RING_BUF_SZ);
      --_this->count;
    }
    else
    {
      c = -1;
    }
    return (c);
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
void ringBufS_put (volatile ringBufS *_this, const unsigned char c)
{
    if (_this->count < RING_BUF_SZ)
    {
      _this->buf[_this->head] = c;
      _this->head = modulo_inc (_this->head, RING_BUF_SZ);
      ++_this->count;
    }
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
void ringBufS_flush (volatile ringBufS *_this, const uint8_t clearBuffer)
{
  _this->count  = 0;
  _this->head   = 0;
  _this->tail   = 0;
  if (clearBuffer)
  {
    //memset (_this->buf, 0, sizeof (_this->buf));
  }
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
unsigned int modulo_inc (const unsigned int value, const unsigned int modulus)
{
    unsigned int my_value = value + 1;
    if (my_value >= modulus)
    {
      my_value  = 0;
    }
    return (my_value);
}

//******************************************************************************
//         name:
//  description:
//   parameters:
//      returns:
//******************************************************************************
unsigned int modulo_dec (const unsigned int value, const unsigned int modulus)
{
    unsigned int my_value = (0==value) ? (modulus - 1) : (value - 1);
    return (my_value);
}
// end of buffer.c
