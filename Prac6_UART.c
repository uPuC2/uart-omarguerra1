#include <avr/io.h>
#include <string.h>
#include <inttypes.h>
#include "UART.h"

int main(void){
	char cad[20];
    char cadUart3[20];
	char cadc[20];
	UART_Ini(0,12345,8,1,2); //INICIAMOS EL UART
	UART_Ini(2,115200,8,0,1);
    UART_Ini(3,115200,8,0,1);
	//char cad[30] = " "; //CREAMOS LA CADENA 
	uint16_t num = 0; //CREAMOS NUM
	//uint8_t i = 0;
	while(1) {
		UART_getchar(0); //PRESIONAS LA TECLA
		clrscr(0); //LIMPIAMOS LA PANTALLA
		//
		gotoxy(0,2,2); //CAMBIAMOS LA POSICION
		setColor(AMARILLO); //Definirlo en UART.h
		UART_puts("Introduce un numero:",0); //IMPRIMIMOS EL MENSAJE
		//
		gotoxy(0,22,2); //MOVEMOS DE POSICION EL TEXTO
		setColor(VERDE); //Definirlo en UART.h
		UART_gets(cad, 0); //OBTENEMOS LA CADENA DE NUMEROS
		//
		UART_puts(cad, 2);
        UART_puts("\r", 2);
        UART_gets(cadUart3, 3);
        gotoxy(0,5,3);
        UART_puts(cadUart3, 0);
		//
		gotoxy(0,5,4); //MOVEMOS LA POSICION DEL TEXTO
		UART_puts(cad,0);
		num = atoi(cad); //MANDAMOS LA CADENA TRANSFORMADA DE ALPHA A ENTERO
		itoa(cad,num,16); //CONVERTIMOS  LA CADENA DE ENTERO A ALPHA CON HEX
		//
		gotoxy(0,5,5);
		setColor(AZUL); //Definirlo en UART.h
		UART_puts("Hex: ", 0); //COLOCAMOS EL MENSAJE
		UART_puts(cad, 0); //MOSTRAMOS EL VALOR DE LA CADENA
		itoa(cad,num,2); //LA TRANSFORMAMOS A ALPHA CON BIN
		//
		gotoxy(0,5,6); //MOVEMOS LA POSICION DEL TEXTO
		UART_puts("Bin: ",0); //COLOCAMOS EL MENSAJE
		UART_puts(cad,0); //MOSTRAMOS EL VALOR DE LA CADENA
		//i++;
	}
	return 0;

}
