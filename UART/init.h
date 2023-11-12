/*
 * init.h
 *
 *  Created on: Oct 17, 2023
 *      Author: Lenovo
 */

#ifndef INIT_H_
#define INIT_H_

#include "STD_TYPES.h"
//all driver funcs prototypes

u8int_t  DIO_INIT  (u8int_t PortName, u8int_t PinNum,u8int_t Direction) ; //done
u8int_t  DIO_SetPinValue (u8int_t PortName, u8int_t PinNum,u8int_t Value) ; //done
u8int_t DIO_ReadPin (u8int_t PortName, u8int_t PinNum, u8int_t *Value);//done
u8int_t DIO_TOGLE (u8int_t PortName, u8int_t PinNum,u8int_t Value);//done



u8int_t DIO_SetPortValue(u8int_t PortId, u8int_t PortVal);//done
u8int_t DIO_SetPortDirection(u8int_t PortId, u8int_t PortDir);//done





u8int_t DIO_ReadPort(u8int_t PortId, u8int_t *reading);

// read by variable
u8int_t DIO_GetPinValue(u8int_t u8PortIdCopy, u8int_t u8PinIdCopy);


#endif
