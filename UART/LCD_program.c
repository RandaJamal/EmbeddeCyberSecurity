/*
 * LCD_program.c
 *
 *  Created on: Oct 24, 2023
 *      Author: Lenovo
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "LCD_int.h"
#include "LCD_config.h"

#include "init.h"
#include "register.h"
#include "config.h"



void CLCD_voidCommand(u8int_t copy_u8Command)
{
	/*Set RS pin low for command*/
	DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,PIN_LOW);
	/*Set RW pin Low to write*/
	//DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN ,PIN_LOW);

	/*Send command to data pins */
	DIO_SetPinValue(PORT_B,PIN_0,GET_BIT(copy_u8Command,4));
	DIO_SetPinValue(PORT_B,PIN_1,GET_BIT(copy_u8Command,5));
	DIO_SetPinValue(PORT_B,PIN_2,GET_BIT(copy_u8Command,6));
	DIO_SetPinValue(PORT_B,PIN_4,GET_BIT(copy_u8Command,7));

	/*Send enable pulse*/
	DIO_SetPinValue(PORT_A,PIN_2 ,PIN_HIGH);
	_delay_ms(2);
	DIO_SetPinValue(PORT_A,PIN_2,PIN_LOW);
	_delay_ms(5);

	DIO_SetPinValue(PORT_B,PIN_0,GET_BIT(copy_u8Command,0));
	DIO_SetPinValue(PORT_B,PIN_1,GET_BIT(copy_u8Command,1));
	DIO_SetPinValue(PORT_B,PIN_2,GET_BIT(copy_u8Command,2));
	DIO_SetPinValue(PORT_B,PIN_4,GET_BIT(copy_u8Command,3));



	/*Send enable pulse*/
	DIO_SetPinValue(PORT_A,PIN_2 ,PIN_HIGH);
	_delay_ms(2);
	DIO_SetPinValue(PORT_A,PIN_2 ,PIN_LOW);
	_delay_ms(5);

}
void CLCD_voidSendData(u8int_t copy_u8Data)
{
	/*Set RS pin high for data*/
	DIO_SetPinValue(PORT_A,PIN_3,PIN_HIGH);

	/*Set RW pin LOW to write*/
	//DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,PIN_LOW);
	/*SEND DATA ONLY ON FOR BITS*/
	DIO_SetPinValue(PORT_B,PIN_0,GET_BIT(copy_u8Data,4));
	DIO_SetPinValue(PORT_B,PIN_1,GET_BIT(copy_u8Data,5));
	DIO_SetPinValue(PORT_B,PIN_2,GET_BIT(copy_u8Data,6));
	DIO_SetPinValue(PORT_B,PIN_4,GET_BIT(copy_u8Data,7));


	/*Send enable pulse*/
	DIO_SetPinValue(PORT_A,PIN_2,PIN_HIGH);
	_delay_ms(2);
	DIO_SetPinValue(PORT_A,PIN_2,PIN_LOW);
	_delay_ms(5);

	DIO_SetPinValue(PORT_B,PIN_0,GET_BIT(copy_u8Data,0));
	DIO_SetPinValue(PORT_B,PIN_1,GET_BIT(copy_u8Data,1));
	DIO_SetPinValue(PORT_B,PIN_2,GET_BIT(copy_u8Data,2));
	DIO_SetPinValue(PORT_B,PIN_4,GET_BIT(copy_u8Data,3));




	/*Send enable pulse*/
	DIO_SetPinValue(PORT_A,PIN_2,PIN_HIGH);
	_delay_ms(2);
	DIO_SetPinValue(PORT_A,PIN_2,PIN_LOW);
	_delay_ms(5);

}
void CLCD_voidInit(void)
{
	/*set pin rs,rw,e->output*/
	DIO_INIT(PORT_A,PIN_3,PIN_OUTPUT);
	//DIO_INIT(PORT_A,CLCD_RW_PIN,PIN_OUTPUT);
	DIO_INIT(PORT_A,PIN_2,PIN_OUTPUT);
	/*set data port as output*/

	DIO_SetPortDirection(PORT_B,PORT_OUT);
	/*delay for more than 30 ms */
	_delay_ms(40);
	CLCD_voidCommand(0x33);
	CLCD_voidCommand(0x32);
	/*Function set command:2 lines(N)=1,,,5*8 font size (f=0)*/
	CLCD_voidCommand(0x28);
	_delay_ms(1);
	/*Display ON/OFF control:Display enable D=1,cursor disable,C=0,NO Blink cursorB=0*/
	CLCD_voidCommand(0x0c);

	_delay_ms(2);
	/*RETURN HOME*/
	CLCD_voidCommand(0x02);
	_delay_ms(1);

	/*Clear display*/
	CLCD_voidCommand(0x01);
}
void CLCD_GoTOXY(u8int_t copy_u8Xpos,u8int_t copy_u8Ypos)
{
	u8int_t Local_u8Address;
	/*Location at first line*/
	if(copy_u8Xpos==0)//ifx==0->adress=y
	{
		Local_u8Address=(copy_u8Ypos);

	}

	/*Location at second line*/
/*x->.row(0,1,2,3), y-> col(0...19*/
	else if(copy_u8Xpos==1)
	{
		Local_u8Address=(0x40+copy_u8Ypos);
	}

	else if(copy_u8Xpos==2)
	{
		Local_u8Address=(0x14+copy_u8Ypos);
	}

	else if(copy_u8Xpos==3)
	{
		Local_u8Address=(0x54+copy_u8Ypos);
	}


	/*Set DDRAM address in Address Counter */
	//128->for address counter
	CLCD_voidCommand(Local_u8Address+0x80);
}
void CLCD_voidSendString(u8int_t* String)
{
	u8int_t Counter=0;
	while(String[Counter]!='\0')
	{
		CLCD_voidSendData(String[Counter]);
		Counter++;
	}
}
void CLCD_voidWriteNumber(u32 copy_u32Number)
{
	u8int_t Local_u8Digit;
	u8int_t Local_u8Counter=0;
	s8 Local_u8Counter2;
	static u8int_t Local_ArrayOfChar[10]={'0','1','2','3','4','5','6','7','8','9'};
	static u8int_t Local_ArrayOfDigits[10];

	if(copy_u32Number==0)
	{
		CLCD_voidSendData(Local_ArrayOfChar[0]);
	}
	else
	{

		while(copy_u32Number>0)
		{
			Local_u8Digit=copy_u32Number%10;
			copy_u32Number=copy_u32Number/10;
			Local_ArrayOfDigits[Local_u8Counter]=Local_ArrayOfChar[Local_u8Digit];
			Local_u8Counter++;
		}

		for(Local_u8Counter2=Local_u8Counter-1;Local_u8Counter2>=0;Local_u8Counter2--)
		{
			CLCD_voidSendData(Local_ArrayOfDigits[Local_u8Counter2]);
		}
	}
}
void write_special_character(u8int_t *pattern_ARR, u8int_t position,u8int_t x_pos, u8int_t y_pos )
{
	/*calculate cgram adress whose block 8 bytes*/
	CLCD_voidCommand(0x40+(position * 8));
/*write pattern into cgram*/
	for(int i=0;i<8;i++)
	{
		CLCD_voidSendData(pattern_ARR[i]);
	}

	/*go to ddram to display pattern*/
CLCD_GoTOXY(x_pos,y_pos);
CLCD_voidSendData(position);

}
void CLCD_Void_LCDClear(void)
{
    CLCD_voidCommand(0x01);
}
