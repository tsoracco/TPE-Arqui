#include <interruptions.h>
#include <driverVideo.h>
#include <keyboardDriver.h>
#include <driverKeyboard.h>
#include <mouseDriver.h>
#include <naiveConsole.h>


static int i = 0;
char *video = (char *) 0xB8000;

#pragma pack(push)
#pragma pack(1)

typedef struct { 
	uint16_t offset_l; //bit 0..15
	uint16_t selector;
	uint8_t zero_l;
	uint8_t attrs;
	uint16_t offset_m; //16..31
	uint32_t offset_h; //32..63
	uint32_t zero_h;
} IDTEntry_t;

#pragma pack(pop)

static IDTEntry_t* IDT = (IDTEntry_t*) 0x0;


void iSetHandler(int index, uint64_t handler) {
	IDT[index].offset_l = (uint16_t) handler & 0xFFFF;
	IDT[index].offset_m = (uint16_t) (handler >> 16) & 0xFFFF;
	IDT[index].offset_h = (uint32_t) (handler >> 32) & 0xFFFFFFFF;
	
	IDT[index].selector = 0x08;
	IDT[index].zero_l = 0;
	
	IDT[index].attrs = 0x8E;
	IDT[index].zero_h = 0;	
	
}

typedef void (*handler_t) (void);

void tickHandler() {
	//video[i++] = i;	

}

void keyboardHandler(){
	keyboard_handler(); // lo de abajo funciona pero imprime con unos espacios raros q la verdad ni idea asique hay q arreglarlo
	// addToBuffer();
	// char aux=get_char();
	// printChar(aux);
	// //testfoo();
}

void mouseHandler(){
	//testfoo();
	mouse_handle();

}

void syscallHandler(){

}


handler_t handlers[] = {tickHandler, keyboardHandler, mouseHandler, syscallHandler}; // vector con todas las interrupciones que vamos a usar

void irqDispatcher(int irq){ //le pasamos el numero de interrupcion y nos lleva al handler adecuado
	handlers[irq]();
}