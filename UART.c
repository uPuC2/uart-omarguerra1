#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "UART.h"
#define FOSC 1843200 //Puede usarse pero no lo usaremos
#define BAUD 9600 //Valor del BAUD
#define BAUD2 500000
#define SP1 1000000 //Valor resumido de la formula
#define SP2 2000000 //Valor resumido de la formula con la velocidad doble
#define STRLENGTH 10

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
//220 Y 101
//BOOK C  / 319 / 333 / 402

void UART_Ini(uint8_t com, uint16_t baudrate, uint8_t size, uint8_t parity, uint8_t stop){//INICIAMOS UART
	uint32_t MYUBRR = 0;
	if(com == 0){
		UCSR0A = 0; //Se puede inicializar la velocidad x2 aqui
		UCSR0B = (3 << TXEN0);//tx and rx enable
		if (parity == 1 || parity == 2){ // 1 PAR Y 2 IMPAR IGNORANDO 01 RESERVADO
			UCSR0C |= ((parity + 1) << UPM00) | ((stop - 1) << USBS0) | ((size - 5) << UCSZ00); 
		} //activamos el bit de paridad, de paro y de tam dependiendo de su com
		UCSR0C |= ((parity) << UPM00) | ((stop - 1 )<< USBS0) | ((size - 5) << UCSZ00);
		if (SP1%baudrate < SP2%baudrate){ //Si el SP1 es menor que SP2 se activa la velocidad normal
			UCSR0A &= ~(1 << U2X0); // Limpiar bit
			MYUBRR = (1000000/ baudrate)-1;
			UBRR0 = MYUBRR;
		}
		else{ //Si el SP2 es menor que SP1 se activa la velocidad doble
			UCSR0A |= (1 << U2X0);
			MYUBRR = (2000000/ baudrate)-1;
			UBRR0 = MYUBRR;
		}
		
	} 
	if(com == 1){
		UCSR1A = 0; //Se puede inicializar la velocidad x2 aqui
		UCSR1B = (3 << TXEN1);//tx and rx enable
		if (parity == 1 || parity == 2){ // 1 PAR Y 2 IMPAR IGNORANDO 01 RESERVADO
			UCSR1C |= ((parity + 1) << UPM10) | ((stop - 1) << USBS1) | ((size - 5) << UCSZ10); 
		} //activamos el bit de paridad, de paro y de tam dependiendo de su com
		UCSR1C |= ((parity) << UPM10) | ((stop - 1 )<< USBS1) | ((size - 5) << UCSZ10);
		if (SP1%baudrate < SP2%baudrate){ //Si el SP1 es menor que SP2 se activa la velocidad normal
			UCSR1A &= ~(1 << U2X1); // Limpiar bit
			MYUBRR = (1000000/ baudrate)-1;
			UBRR1 = MYUBRR;
		}
		else{ //Si el SP2 es menor que SP1 se activa la velocidad doble
			UCSR1A |= (1 << U2X1);
			MYUBRR = (2000000/ baudrate)-1;
			UBRR1 = MYUBRR;
		}
		
	} 
	if(com == 2){
		UCSR2A = 0; //Se puede inicializar la velocidad x2 aqui
		UCSR2B = (3 << TXEN2);//tx and rx enable
		if (parity == 1 || parity == 2){ // 1 PAR Y 2 IMPAR IGNORANDO 01 RESERVADO
			UCSR2C |= ((parity + 1) << UPM20) | ((stop - 1) << USBS2) | ((size - 5) << UCSZ20); 
		} //activamos el bit de paridad, de paro y de tam dependiendo de su com
		UCSR2C |= ((parity) << UPM20) | ((stop - 1 )<< USBS2) | ((size - 5) << UCSZ20);
		if (SP1%baudrate < SP2%baudrate){ //Si el SP1 es menor que SP2 se activa la velocidad normal
			UCSR2A &= ~(1 << U2X2); // Limpiar bit
			MYUBRR = (1000000/ baudrate)-1;
			UBRR2 = MYUBRR;
		}
		else{ //Si el SP2 es menor que SP1 se activa la velocidad doble
			UCSR2A |= (1 << U2X2);
			MYUBRR = (2000000/ baudrate)-1;
			UBRR2 = MYUBRR;
		}
		
	}
	if(com == 3){
		UCSR3A = 0; //Se puede inicializar la velocidad x2 aqui
		UCSR3B = (3 << TXEN3);//tx and rx enable
		if (parity == 1 || parity == 2){ // 1 PAR Y 2 IMPAR IGNORANDO 01 RESERVADO
			UCSR3C |= ((parity + 1) << UPM30) | ((stop - 1) << USBS3) | ((size - 5) << UCSZ30); 
		} //activamos el bit de paridad, de paro y de tam dependiendo de su com
		UCSR3C |= ((parity) << UPM30) | ((stop - 1 )<< USBS3) | ((size - 5) << UCSZ30);
		if (SP1%baudrate < SP2%baudrate){ //Si el SP1 es menor que SP2 se activa la velocidad normal
			UCSR3A &= ~(1 << U2X3); // Limpiar bit
			MYUBRR = (1000000/ baudrate)-1;
			UBRR3 = MYUBRR;
		}
		else{ //Si el SP2 es menor que SP1 se activa la velocidad doble
			UCSR3A |= (1 << U2X3);
			MYUBRR = (2000000/ baudrate)-1;
			UBRR3 = MYUBRR;
		}
		
	}

}

char UART_getchar(uint8_t com){//Configuracion getchar para habilitar el envio de informacion al MICRO
	if (com ==  0){
		while ( !( UCSR0A & (1 << RXC0)) ){
		}
		return UDR0;
	}
	else if (com ==  1){
		while ( !( UCSR1A & (1 << RXC1)) ){
		}
		return UDR1;
	}
	else if (com ==  2){
		while ( !( UCSR2A & (1 << RXC2)) ){
		}
		return UDR2;
	}
	else if (com ==  3){
		while ( !( UCSR3A & (1 << RXC3)) ){
		}
		return UDR3;
	}
	//agregar para com 2 y com 3 con jumper;
	return 0;

}

void UART_gets(char *str, uint8_t com){//RECIBE TODOS LOS GETCHAR EN UNA CADENA
	uint8_t index = 0; //CREAMOS UN INDICE
	char c;
	do{ //HAZ..
		c = UART_getchar(com); //ALMACENAMOS EL VALOR DE GETCHAR EN C
		if (c == 8 && index > 0){ //EN CASO DE HABER PRESIONADO BACKSPACE
			str[index] = '\0';
			index--;
			UART_putchar(8, com); //VERIFICACION DE OTRAS TECLAS EN LO QUE ESPERA OTRA RESPUESTA
			UART_putchar(' ', com);
			UART_putchar(8, com);
		}
		if (c != 8 && index <= STRLENGTH - 1){ //MIENTRAS C ES DIFERENTE DE BACKSPACE
			str[index] = c; //ALMACENAMOS C EN LA POSICION QUE ESTA APUNTANDO EL INDICE EN LA CADENA
			UART_putchar(c, com); //LLAMAMOS A PUTCHAR PARA MOSTRAR EL VALOR TECLEADO
			index++; //MOVEMOS EL INDICE DE POSICION
		}
		/*else{//EN CASO DE ESTAR PRESIONANDO LAS TECLAS DE DESPLAZAMIENTO HACIA ADENTRO
			UART_putchar(15, com);
		}*/
	}while(c != 13 ); //MIENTRAS NO PRESIONEMOS ENTER NO SE TERMINA EL GETS
	str[index-1] = '\0'; //SI PRESIONAMOS ENTER LE ENVIAMOS A AL INDICE EL CARACTER NULO PARA SABER DONDE TERMINAR
}

void UART_putchar(char data, uint8_t com){ //Configuracion putchar para transmitir informacion al UART
		if (com == 0){
			while ( !( UCSR0A & (1 << UDRE0)) ){
			}
			UDR0 = data;
		}
		else if (com == 1){
			while ( !( UCSR1A & (1 << UDRE1)) ){
			}
			UDR1 = data;
		}
		else if (com == 2){
			while ( !( UCSR2A & (1 << UDRE2)) ){
			}
			UDR2 = data;
		}
		else if (com == 3){
			while ( !( UCSR3A & (1 << UDRE3)) ){
			}
			UDR3 = data;
		}
}

void UART_puts(char *str, uint8_t com){ //Escribe toda la cadena
	while (*str != 0){
		UART_putchar(*str, com);
		str ++;
	}
}

void itoa( char *str, uint16_t input, uint8_t base){ //transformamos un numero a caracter
    int i = 0; //Usamos i para nuestros whiles
    if (base == 16){ //en caso de que sea base 16 se configura para transformar valores hexadecimales
        while (input != 0){ //mientras nuestro valor ingresado sea diferente de 0 se seguira imprimiendo
            if (input % base >= 10){ //Si el input es mayor a 10 se le suma 7 para obtener de A-F
                str[i++] = input % base + '0' + 7; //Almacenamos el valor en la cadena donde base equivale a 10 = decimal, 8 = octal, 2 = Binario
            }
            else { //En caso de que sea menor a 9 no se ocupa aumentar el valor
                str[i++] = input % base + '0'; 
            }
            input /= base;
            //printf(input);
        }
        for (int j = 0, k = i - 1; j < k; j++, k--) { //Acomodamos la cadena
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
        }
		str[i] = '\0'; 
        return 0;
    }
    while (input != 0){ //Se repite lo mismo pero para base 10, 8 y 2
        str[i++] = input % base + '0';
        input /= base;
    }
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
	str[i] = '\0'; 
}

uint16_t ATOI(char *str) { //Convertimos el caracter a numero
    uint8_t i = 0; //i para recorrer la cadena
    uint16_t dec = 0; //iniciamos dec en 0
    //uint8_t length = strlen(str); // Inicializamos length con la longitud de la cadena
	uint8_t length = 0; //colocamos la longitud en 0
	while (str[length] != '\0'){ //Mientras no lleguemos al caracter nulo al final de la cadena la seguimos recorriendo 
		length++; //Vamos obteniendo la longitud
	}
    while (i < length) { //Almacenamos los valores en base 10 en dec
		if (str[i] >= '0' && str[i] <= '9'){
			dec *= 10;
        	dec += str[i++] - '0';
		}
        else
			return 0;
    }
    return dec;
}

void clrscr(uint8_t com) {
    UART_puts("\033[H\033[2J", com); //Secuencia de escape para borrar la pantalla de la consola
}


void setColor(uint16_t color){ //SECUENCIA DE ESCAPE PARA CAMBIO DE COLOR
	char bufferC[6] = {0}; //COLOCAMOS EN 0 LA CADENA
	uint8_t com = 0;
	itoa(bufferC, color, 10); //MANDAMOS A LLAMAR EL ITOA PARA CONVERTIR ENTEROS A ALPHA
	UART_puts("\033[", com); //SECUENCIA DE ESCAPE
	UART_puts(bufferC, com);
	UART_puts("m", com);

}
void gotoxy(uint8_t com, uint8_t x, uint8_t y) {
	char bufferx[6] = {0}; //colocamos en 0 en cadena
	char buffery[6] = {0}; 
 	itoa(bufferx, x, 10); //convertimos a caracter para la secuencia de escape
	itoa(buffery, y, 10);
    UART_puts("\033[",com); //Primera parte de la secuencia de escape
	UART_puts(buffery,com); //Primera posicion
	UART_puts(";",com); //Separador de la secuencia
	UART_puts(bufferx,com); //Segunda posicion
	UART_puts("H",com); //Cerramos la secuencia
}
