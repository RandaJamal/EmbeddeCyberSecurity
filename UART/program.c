/*
 * program.c
 *
 *  Created on: Oct 17, 2023
 *      Author: Lenovo
 */


#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include "register.h"
#include "init.h"
#include "config.h"


u8int_t  DIO_INIT  (u8int_t PortName, u8int_t PinNum,u8int_t Direction)
{
	u8int_t Local_u8ERRStatus=OK;

	if(PinNum>=0 && PinNum<=7)
	{
		if(Direction == PIN_INPUT)
		{

			switch(PortName)
			{


			case(PORT_A):  CLR_BIT(DDRA_REG,PinNum);break;
			case(PORT_B): CLR_BIT(DDRB_REG,PinNum);break;
			case(PORT_C): CLR_BIT(DDRC_REG,PinNum);break;
			case(PORT_D):CLR_BIT(DDRD_REG,PinNum);break;

			default: Local_u8ERRStatus=NOK;
			break;
			}

		}

		else if(Direction == PIN_OUTPUT)
		{
			switch(PortName)
			{


			case(PORT_A): SET_BIT(DDRA_REG,PinNum);break;
			case(PORT_B): SET_BIT(DDRB_REG,PinNum);break;
			case(PORT_C): SET_BIT(DDRC_REG,PinNum);break;
			case(PORT_D):SET_BIT(DDRD_REG,PinNum);break;
			default: Local_u8ERRStatus=NOK;
			break;
			}
		}

		else
		{
			Local_u8ERRStatus=NOK;
		}
	}
	else
	{
		Local_u8ERRStatus=NOK;
	}



	return Local_u8ERRStatus;

}
u8int_t  DIO_SetPinValue (u8int_t PortName, u8int_t PinNum,u8int_t Value)
{
	u8int_t ErrorState=OK ;

	if(PinNum>=0 && PinNum<=7 )
	{
		if(Value== PIN_HIGH)
		{

			switch(PortName){

			case (PORT_A): SET_BIT(PORTA_REG,PinNum);break;
			case (PORT_B): SET_BIT(PORTB_REG,PinNum);;break;
			case (PORT_C): SET_BIT(PORTC_REG,PinNum);break;
			case (PORT_D): SET_BIT(PORTD_REG,PinNum);break;
			default:break;

			}
		}
		if(Value== PIN_LOW)
		{

			switch(PortName){

			case (PORT_A): CLR_BIT(PORTA_REG,PinNum);break;
			case (PORT_B): CLR_BIT(PORTB_REG,PinNum);;break;
			case (PORT_C): CLR_BIT(PORTC_REG,PinNum);break;
			case (PORT_D): CLR_BIT(PORTD_REG,PinNum);break;
			default:ErrorState=NOK;break;

			}
		}
		else
		{
			ErrorState =NOK;
		}

	}
	else
	{
		ErrorState=NOK;
	}



	return ErrorState;
}
u8int_t DIO_ReadPin (u8int_t PortName, u8int_t PinNum, u8int_t *Value)
{
	u8int_t ErrorState=OK;

	if(PinNum>=0 && PinNum<=7)
	{
		switch(PortName){

		case PORT_A:    *Value=GET_BIT(PINA_REG,PinNum);break;
		case PORT_B:    *Value=GET_BIT(PINB_REG,PinNum);break;
		case PORT_C:    *Value=GET_BIT(PINC_REG,PinNum);break;
		case PORT_D:    *Value=GET_BIT(PIND_REG,PinNum);break;
		default:ErrorState=NOK;break;

		}
	}
	else
	{
		ErrorState=NOK;
	}
	return ErrorState;
}

u8int_t TogglePin(u8int_t PortId,u8int_t PinId)
{
	u8int_t ErrorState=OK;
	switch(PortId){
	case PORT_A: SET_BIT(DDRA_REG,PinId);TOG_BIT(PORTA_REG,PinId);break;
	case PORT_B: SET_BIT(DDRB_REG,PinId);TOG_BIT(PORTB_REG,PinId);break;
	case PORT_C: SET_BIT(DDRC_REG,PinId);TOG_BIT(PORTC_REG,PinId);break;
	case PORT_D: SET_BIT(DDRD_REG,PinId);TOG_BIT(PORTD_REG,PinId);break;
	default:ErrorState=NOK;break;

	}
	return ErrorState;
}

u8int_t DIO_SetPortDirection(u8int_t PortId, u8int_t PortDir)
{
	u8int_t ErrState=OK;
	if(PortDir == PORT_IN)
	{
		switch(PortId){
		case PORT_A: DDRA_REG=PORT_IN;break;
		case PORT_B: DDRA_REG=PORT_IN;break;
		case PORT_C: DDRA_REG=PORT_IN;break;
		case PORT_D: DDRA_REG=PORT_IN;break;
		default:ErrState=NOK;break;

		}
	}
	else if (PortDir == PORT_OUT)
	{
		switch(PortId){
		case PORT_A: DDRA_REG=PORT_OUT;break;
		case PORT_B: DDRA_REG=PORT_OUT;break;
		case PORT_C: DDRA_REG=PORT_OUT;break;
		case PORT_D: DDRA_REG=PORT_OUT;break;
		default:ErrState=NOK;break;

		}
	}

	else
	{
		ErrState=NOK;
	}
	return ErrState;
}
u8int_t DIO_SetPortValue(u8int_t PortId, u8int_t PortVal)
{
	u8int_t ErrorState=OK;
	if(PortVal == PORT_HIGH)
	{
		switch(PortId){
		case PORT_A: PORTA_REG=PORT_HIGH;break;
		case PORT_B: PORTB_REG=PORT_HIGH;break;
		case PORT_C: PORTC_REG=PORT_HIGH;break;
		case PORT_D: PORTD_REG=PORT_HIGH;break;
		default:ErrorState=NOK;break;

		}


	}
	else if (PortVal == PORT_LOW)
	{
		switch(PortId){
		case PORT_A: PORTA_REG=PORT_LOW;break;
		case PORT_B: PORTB_REG=PORT_LOW;break;
		case PORT_C: PORTC_REG=PORT_LOW;break;
		case PORT_D: PORTD_REG=PORT_LOW;break;
		default:ErrorState=NOK;break;

		}


	}
	else
	{
		ErrorState=NOK;
	}
	return ErrorState;

}
