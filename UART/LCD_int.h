/*
 * LCD_int.h
 *
 *  Created on: Oct 24, 2023
 *      Author: Lenovo
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_
#include "STD_TYPES.h"



void CLCD_voidCommand(u8int_t copy_u8Command);
void CLCD_voidSendData(u8int_t copy_u8Data);
void CLCD_voidInit(void);
void CLCD_GoTOXY(u8int_t copy_u8Xpos,u8int_t copy_u8Ypos);
void CLCD_voidSendString(u8int_t * String);
void CLCD_voidWriteNumber(u32 copy_u32Number);
void write_special_character(u8int_t *pattern_ARR, u8int_t position,u8int_t x_pos, u8int_t y_pos );
void CLCD_Void_LCDClear(void);





#endif
