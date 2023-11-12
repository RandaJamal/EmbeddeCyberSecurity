/*
 * register.h
 *
 *  Created on: Oct 17, 2023
 *      Author: Lenovo
 */

#ifndef REGISTER_H_
#define REGISTER_H_

#include "STD_TYPES.h"


  #define PORTA_REG      *((volatile u8int_t*) 0x3b)
  #define DDRA_REG   *((volatile u8int_t*) 0x3a)
  #define PINA_REG       *((volatile u8int_t*) 0x39)


  #define PORTB_REG        *((volatile u8int_t*) 0x38)
  #define DDRB_REG    *((volatile u8int_t*) 0x37)
  #define PINB_REG        *((volatile u8int_t*) 0x36)


  #define PORTC_REG      *((volatile u8int_t*) 0x35)
  #define DDRC_REG     *((volatile u8int_t*) 0x34)
  #define PINC_REG        *((volatile u8int_t*) 0x33)


  #define PORTD_REG       *((volatile u8int_t*) 0x32)
  #define DDRD_REG     *((volatile u8int_t*) 0x31)
  #define PIND_REG        *((volatile u8int_t*) 0x30)










#endif
