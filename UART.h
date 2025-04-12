#ifndef _UART
#define _UART
#include <avr/io.h>
void UART_Ini(uint8_t com, uint16_t baudrate, uint8_t size, uint8_t parity, uint8_t stop);//Inicializar el UART
char UART_getchar(uint8_t com); //Funcion para obtener el caracter
void UART_gets(char *str, uint8_t com); //FUNCION PARA OBTENER TODOS LOS DATOS DE GETCHAR EN UNA CADENA
void UART_putchar(char dato, uint8_t com); //Funcion para mostrar el caracter al teclear 
void UART_puts(char *str, uint8_t com); //Imprime la cadena
uint8_t UART0_available(void);//FUNCION PARA SABER SI LA CADENA ESTA LLENA O NO
void ITOA(char *str, uint16_t input, uint8_t base); //convierte numeros a cadena
uint16_t ATOI(char *str); //convierte cadena a numero
void gotoxy(uint8_t com, uint8_t x, uint8_t y); //posiciona el texto en una posicion de la consola
void setColor(uint16_t color);//FUNCION DE SECUENCIA DE ESCAPE PARA CAMBIAR COLOR DE TEXTO
void clrscr(uint8_t com); //limpia la pantalla
enum color{NEGRO = 30, ROJO, VERDE, AMARILLO, AZUL, MAGENTA, CIAN, BLANCO};
#endif
