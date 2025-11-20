#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/spi.h"
#include "Ili9341.h"
#include "ili9341hw.h"

#define PIN_SDI     19
#define PIN_CS      17
#define PIN_SCK     18
#define PIN_DC      16
#define PIN_nRESET  20
#define PIN_SDO     36
#define PIN_LED     13

void core1_main(void);

void core1_main(void) {
    sleep_ms(10);
    init_imageBuffer();         // Initialize the imageBuffer

    // Constantly Init the Image Buffer
    for (;;) {
        ILI9341_writeImageBuffer();
        sleep_us(30);
    }
}

int main(void) {
    stdio_init_all();
    sleep_ms(2000); 

    // Init the TFT display
    ili9341_init(spi0,
                90 * MHz,
                PIN_SDO,		//SDO(MISO)
                PIN_CS, 		//CS
                PIN_SCK,		//SCK
                PIN_SDI,		//SDI(MOSI)
                PIN_nRESET,  	//RESET
                PIN_DC,			//DC/RS 
                PIN_LED,     
                true);      

    // Launch writing the image buffer on core 1
    multicore_launch_core1(core1_main); 
    
    // Write Test Colours on Screen
    ili9341_test();            
    sleep_ms(3000);

    //ili9341_clear();  
    // OR
	ILI9341_setScreenColour(TFT_BLACK);         

    // Draw A Small Rectangle
    ili9341_drawRect(120, 100, 20, 20, TFT_BLUE);
    sleep_ms(3000);

    {
        uint16_t color = ili9341_RGBto16bit(0xE0, 0x30, 0x3F); 
        ili9341_putStr("Hello", 20, 20, color, TFT_WHEAT);     
    }

    return 0;
}
