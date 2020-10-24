#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "common.h"


void uart_init(u32 bound);
void USART1_SendData(char Data);
void USART1_SendString(char* Data);
void USART1_Len_Send(u8 len, char* Data);


void uart2_init(u32 bound);
void USART2_SendData(char Data);
void USART2_SendString(char* Data);
void USART2_Len_Send(u8 len, char* Data);


void uart3_init(u32 bound);
void USART3_SendData(char Data);
void USART3_SendString(char* Data);
void USART3_Len_Send(u8 len, char* Data);

#endif




