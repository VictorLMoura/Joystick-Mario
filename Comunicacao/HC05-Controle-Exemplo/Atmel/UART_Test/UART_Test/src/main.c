/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <string.h>
#include <string.h>
#include "conf_board.h"
#include "conf_example.h"
#include "conf_uart_serial.h"

#define BUT_PIO_ID			  ID_PIOB
#define BUT_PIO				  PIOB
#define BUT_PIN				  2u
#define BUT_PIN_MASK			  (1 << BUT_PIN)

#define BUT2_PIO_ID			  ID_PIOA
#define BUT2_PIO				  PIOA
#define BUT2_PIN				  3u
#define BUT2_PIN_MASK			  (1 << BUT2_PIN)

#define BUT3_PIO_ID			  ID_PIOC
#define BUT3_PIO				  PIOC
#define BUT3_PIN				  13u
#define BUT3_PIN_MASK			  (1 << BUT3_PIN)

#define BUT4_PIO_ID			  ID_PIOC
#define BUT4_PIO				  PIOC
#define BUT4_PIN				  13u
#define BUT4_PIN_MASK			  (1 << BUT4_PIN)


// Descomente o define abaixo, para desabilitar o Bluetooth e utilizar modo Serial via Cabo
//#define DEBUG_SERIAL


#ifdef DEBUG_SERIAL
#define UART_COMM USART1
#else
#define UART_COMM USART0
#endif

void BUT_init(void);
void BUT2_init(void);
void BUT3_init(void);
void BUT4_init(void);



volatile Bool conected;
volatile long g_systimer = 0;

/**
* @Brief Inicializa o pino do BUT
*/
void BUT_init(void){
	/* config. pino botao em modo de entrada */
	pmc_enable_periph_clk(BUT_PIO_ID);
	pio_set_input(BUT_PIO, BUT_PIN_MASK, PIO_PULLUP | PIO_DEBOUNCE);

	/* config. interrupcao em borda de descida no botao do kit */
	/* indica funcao (but_Handler) a ser chamada quando houver uma interrupção */
	//pio_enable_interrupt(BUT_PIO, BUT_PIN_MASK);
	//pio_handler_set(BUT_PIO, BUT_PIO_ID, BUT_PIN_MASK, PIO_IT_FALL_EDGE, Button_callback);

	/* habilita interrupçcão do PIO que controla o botao */
	/* e configura sua prioridade                        */
	//NVIC_EnableIRQ(BUT_PIO_ID);
	//NVIC_SetPriority(BUT_PIO_ID, 1);
};

void BUT2_init(void){
	/* config. pino botao em modo de entrada */
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pio_set_input(BUT2_PIO, BUT2_PIN_MASK, PIO_PULLUP | PIO_DEBOUNCE);

	/* config. interrupcao em borda de descida no botao do kit */
	/* indica funcao (but_Handler) a ser chamada quando houver uma interrupção */
	//pio_enable_interrupt(BUT_PIO, BUT_PIN_MASK);
	//pio_handler_set(BUT_PIO, BUT_PIO_ID, BUT_PIN_MASK, PIO_IT_FALL_EDGE, Button_callback);

	/* habilita interrupçcão do PIO que controla o botao */
	/* e configura sua prioridade                        */
	//NVIC_EnableIRQ(BUT_PIO_ID);
	//NVIC_SetPriority(BUT_PIO_ID, 1);
};

void BUT3_init(void){
	/* config. pino botao em modo de entrada */
	pmc_enable_periph_clk(BUT3_PIO_ID);
	pio_set_input(BUT3_PIO, BUT3_PIN_MASK, PIO_PULLUP | PIO_DEBOUNCE);

	/* config. interrupcao em borda de descida no botao do kit */
	/* indica funcao (but_Handler) a ser chamada quando houver uma interrupção */
	//pio_enable_interrupt(BUT_PIO, BUT_PIN_MASK);
	//pio_handler_set(BUT_PIO, BUT_PIO_ID, BUT_PIN_MASK, PIO_IT_FALL_EDGE, Button_callback);

	/* habilita interrupçcão do PIO que controla o botao */
	/* e configura sua prioridade                        */
	//NVIC_EnableIRQ(BUT_PIO_ID);
	//NVIC_SetPriority(BUT_PIO_ID, 1);
};

void BUT4_init(void){
	/* config. pino botao em modo de entrada */
	pmc_enable_periph_clk(BUT4_PIO_ID);
	pio_set_input(BUT4_PIO, BUT4_PIN_MASK, PIO_PULLUP | PIO_DEBOUNCE);

	/* config. interrupcao em borda de descida no botao do kit */
	/* indica funcao (but_Handler) a ser chamada quando houver uma interrupção */
	//pio_enable_interrupt(BUT_PIO, BUT_PIN_MASK);
	//pio_handler_set(BUT_PIO, BUT_PIO_ID, BUT_PIN_MASK, PIO_IT_FALL_EDGE, Button_callback);

	/* habilita interrupçcão do PIO que controla o botao */
	/* e configura sua prioridade                        */
	//NVIC_EnableIRQ(BUT_PIO_ID);
	//NVIC_SetPriority(BUT_PIO_ID, 1);
};
struct ili9488_opt_t g_ili9488_display_opt;
static void configure_lcd(void){
	/* Initialize display parameter */
	g_ili9488_display_opt.ul_width = ILI9488_LCD_WIDTH;
	g_ili9488_display_opt.ul_height = ILI9488_LCD_HEIGHT;
	g_ili9488_display_opt.foreground_color = COLOR_CONVERT(COLOR_WHITE);
	g_ili9488_display_opt.background_color = COLOR_CONVERT(COLOR_WHITE);

	/* Initialize LCD */
	ili9488_init(&g_ili9488_display_opt);
}

void draw_screen(void) {
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_WHITE));
	ili9488_draw_filled_rectangle(0, 0, ILI9488_LCD_WIDTH-1, ILI9488_LCD_HEIGHT-1);
}

void SysTick_Handler() {
	g_systimer++;
}


void config_console(void) {
	usart_serial_options_t config;
	config.baudrate = 9600;
	config.charlength = US_MR_CHRL_8_BIT;
	config.paritytype = US_MR_PAR_NO;
	config.stopbits = false;
	usart_serial_init(USART1, &config);
	usart_enable_tx(USART1);
	usart_enable_rx(USART1);
}

void usart_put_string(Usart *usart, char str[]) {
	usart_serial_write_packet(usart, str, strlen(str));
}

int usart_get_string(Usart *usart, char buffer[], int bufferlen, int timeout_ms) {
	long timestart = g_systimer;
	uint32_t rx;
	uint32_t counter = 0;
	
	while(g_systimer - timestart < timeout_ms && counter < bufferlen - 1) {
		if(usart_read(usart, &rx) == 0) {
			//timestart = g_systimer; // reset timeout
			buffer[counter++] = rx;
		}
		//if(g_systimer - timestart < timeout_ms){
			//conected = false;
		//}
	}
	buffer[counter] = 0x00;
	return counter;
}

void usart_send_command(Usart *usart, char buffer_rx[], int bufferlen, char buffer_tx[], int timeout) {
	usart_put_string(usart, buffer_tx);
	usart_get_string(usart, buffer_rx, bufferlen, timeout);
}

void usart_log(char* name, char* log) {
	usart_put_string(USART1, "[");
	usart_put_string(USART1, name);
	usart_put_string(USART1, "] ");
	usart_put_string(USART1, log);
	usart_put_string(USART1, "\r\n");
}

void hc05_config_server(void) {
	usart_serial_options_t config;
	config.baudrate = 9600;
	config.charlength = US_MR_CHRL_8_BIT;
	config.paritytype = US_MR_PAR_NO;
	config.stopbits = false;
	usart_serial_init(USART0, &config);
	usart_enable_tx(USART0);
	usart_enable_rx(USART0);
	
	 // RX - PB0  TX - PB1 
	 pio_configure(PIOB, PIO_PERIPH_C, (1 << 0), PIO_DEFAULT);
	 pio_configure(PIOB, PIO_PERIPH_C, (1 << 1), PIO_DEFAULT);
}

int hc05_server_init(void) {
	char buffer_rx[128];
	usart_send_command(USART0, buffer_rx, 1000, "AT", 1000);
	usart_send_command(USART0, buffer_rx, 1000, "AT", 1000);	
	usart_send_command(USART0, buffer_rx, 1000, "AT+NAMEServer", 1000);
	usart_log("hc05_server_init", buffer_rx);
	usart_send_command(USART0, buffer_rx, 1000, "AT", 1000);
	usart_send_command(USART0, buffer_rx, 1000, "AT+PIN0000", 1000);
	usart_log("hc05_server_init", buffer_rx);
	
	conected = true;
}

void send_command(char c[512]){
		char eof = 'X';

	while(!usart_is_tx_ready(UART_COMM));
	usart_write(UART_COMM, c[0]);
	while(!usart_is_tx_ready(UART_COMM));
	usart_write(UART_COMM, c[1]);
	while(!usart_is_tx_ready(UART_COMM));
	usart_write(UART_COMM, eof);
}

void printa_conectado(){
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_WHITE));
	ili9488_draw_filled_rectangle(0,370,400,500);
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_BLACK));
	char buff5[32];
	sprintf(buff5, "Controle ativado");
	ili9488_draw_string(45, 395, buff5);
}
void printa_desconectado(){
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_WHITE));
	ili9488_draw_filled_rectangle(0,370,400,500);
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_BLACK));
	char buff5[32];
	sprintf(buff5, "Controle Desconectado");
	ili9488_draw_string(45, 395, buff5);
}

int main (void)
{
	//board_init();
	sysclk_init();
	board_init();  /* Initialize board */
	configure_lcd();
	draw_screen();
	delay_init();
	SysTick_Config(sysclk_get_cpu_hz() / 1000); // 1 ms
	config_console();
	
	/* Configura os botões */
	BUT_init();
	BUT2_init();
	BUT3_init();
	BUT4_init();
	
	conected = false;
	printa_desconectado();

	
	#ifndef DEBUG_SERIAL
	usart_put_string(USART1, "Inicializando...\r\n");
	usart_put_string(USART1, "Config HC05 Server...\r\n");
	hc05_config_server();
	hc05_server_init();
	#endif
	
	char button[4];
	char header;
	char buffer[1024];
	
	while(1) {
		if(conected == true){
			printa_conectado();
		}
		else{
			printa_desconectado();
		}
		
		if(!pio_get(BUT_PIO, PIO_INPUT, BUT_PIN_MASK)) {
			send_command("A1");
		} else {
			send_command("A0");
		}
		
		if(!pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIN_MASK)) {
			send_command("B1");
		} else {
			send_command("B0");
		}
		
		if(!pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIN_MASK)) {
			send_command("C1");
		} else {
			send_command("C0");
		}
		
	}
}
