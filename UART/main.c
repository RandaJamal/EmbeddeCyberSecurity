/*
 * main.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Lenovo
 */
#include "STD_TYPES.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <string.h>
#include "UART.h"
#include "init.h"
#include "register.h"
#include "config.h"
#include "LCD_int.h"
#include "LCD_config.h"
#include <util/delay.h>


// Function to initialize the random number generator
void initRandomSeed() {
	uint16_t seed = eeprom_read_word((uint16_t*) 0); // Read a seed from EEPROM
	if (seed == 0xFFFF) {
		seed = 42; // Default seed value if EEPROM is empty
		eeprom_write_word((uint16_t*) 0, seed); // Write the seed to EEPROM
	}
	srand(rand() ^ seed ); // Initialize the random number generator with the seed
}
unsigned int GenerateRandomHexNumber() {
	return rand();
	_delay_ms(100);
}


int main(void)
{
	static u8int_t flag=0;
	u8int_t data;
	char str[9];
	char request1[9]="3101AA00";
	char request2[9]="27010000";
	char request3[9]="27020000";


	u8int_t index =0;




	// Another number to concatenate

	DIO_INIT(PORT_D,PIN_1,PIN_OUTPUT); //TX PIN
	DIO_INIT(PORT_D,PIN_0,PIN_INPUT); //RX PIN
	DIO_INIT(PORT_C,PIN_1,PIN_OUTPUT);



	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init(9600);
	CLCD_voidInit();

	while(1)
	{
		initRandomSeed();
		unsigned int random_number = GenerateRandomHexNumber();

		char hex_string[5];
		snprintf(hex_string, sizeof(hex_string), "%04X", random_number);

				for(int i=0;i<4;i++)
				{
					request3[i+4]= (hex_string[i]+ 1);
				}
		for(int i=0;i<3; i++)
		{
			data=UART_recieveByte();  // receive from termianl
			_delay_ms(500);
			if(data == '\n' || index >= 8)
			{
				str[index]= '\0';
				unsigned int hexa_value;
				sscanf(str,"%8x",&hexa_value);
				index=0;

				strupr(str);
				strupr(request1);
				strupr(request3);



				if(strcmp(str,request1) == 0)
				{
					if(flag == 0)
					{
						CLCD_Void_LCDClear();
						CLCD_GoTOXY(0,1);
						CLCD_voidSendString("NRC 7F3135");
						_delay_ms(200);
					}
					else if(flag == 1)
					{
						CLCD_Void_LCDClear();
						CLCD_GoTOXY(0,1);
						CLCD_voidSendString("7101AA00");
						_delay_ms(200);
						CLCD_GoTOXY(1,1);
						CLCD_voidSendString("LED IS ON");
						DIO_SetPinValue(PORT_C,PIN_1,PIN_HIGH);


					}



				}

				else if(strcmp(str,request2) == 0)
				{
					CLCD_Void_LCDClear();
					CLCD_GoTOXY(0,1);
					CLCD_voidSendString("6701");
					_delay_ms(200);
					CLCD_GoTOXY(0,5);
					CLCD_voidSendString(hex_string);
					_delay_ms(200);
				}
				else if(strcmp(str,request3) == 0)
				{
					CLCD_Void_LCDClear();
					CLCD_GoTOXY(0,1);
					CLCD_voidSendString("6702");
					_delay_ms(200);
					CLCD_GoTOXY(1,1);
					CLCD_voidSendString("7F2735");

					flag=1;

				}
				else
				{
					CLCD_Void_LCDClear();
					CLCD_GoTOXY(0,1);
					CLCD_voidSendString("ERROR");
				}
				// Clear the buffer
				memset(str, 0, sizeof(str));
			}

			else
			{
				str[index]=data;
				index ++ ;
			}


		}



	}
	return 0;
}



