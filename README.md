# RPPicoTFT-ILI9341-ImageBuffer-C
Fork for the RPIPicoTFT2.4 (TFT ILI9341) with image buffers in C 
  
> RPIPicoTFT2.4 by [jondurrant](https://github.com/jondurrant/RPIPicoTFT2.4)   

I ran the following code on the RP2350B (RP Pico 2)   

For an implementation in CPP - check out [RPPicoTFT-ILI9341-ImageBuffer-CPP](https://github.com/AaryanPanigrahi/RPPicoTFT-ILI9341-ImageBuffer-CPP)  
  
## Usage
### Writing to the buffer  
While old funcionality is the same as the library linked above, I added the convinience of writing pixels directly to the buffer  
  
for a uint16_t - RGB565 colour value   
__**PIX(x,y)**__ = colour  

Added "**ILI9341_setScreenColour**" that updates the entire screen to 'colour'

## Changes  
- Instead of the class header "__ILI9341__", added a suffix "**ILI9341_**" to funtion names  
    All the class parameters are accessible through static global variables instead  
  
- Writes to an image buffer instead of the TFT directly to increase flexibility of use   
    "Overwriting" a spot on the TFT glitched it out. A tft->clear then re-writing the same data was a waste of computation  
  
- Use of multicore/pipelined proccessing allowing higher FPS    
    Can update the TFT on one core, and write to the buffer on another. Avoids race conditions  
  
## Potential Changes  
- Update SPI over DMA to free up an entire core  
    Can potentially allow for a 'pre' image buffer, where you can update a main buffer for screen scrolls, while a intermediate buffer holds new data to be written to the main buffer   
  
---

## Feedback  
> My usecase <ins>required</ins> the use of C. Would've been great to know before I started this endeavour  
  
This library was re-written hastily to work on a project. Please feel free to reach out in case something doesn't work. I will try my best to fix it asap  
