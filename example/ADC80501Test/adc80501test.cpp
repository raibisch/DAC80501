
#include <Arduino.h>

/*************************************************************
 Example for DAC80501
**************************************************************/

// initialise vspi with default pins
// SCLK = 18, MISO = 19, MOSI = 23, SS = 5
// ...or custom pins
#define SPI1_SCK  7  // Clock
#define SPI1_MISO 8  // fuer dac nur dummy def
#define SPI1_MOSI 6  // Master Output Slave Input
#define SPI1_CS   9  // Chip-Select

#include "Dac80501.h"
Dac80501 dac;

void setup() 
{
  // default clock=2MHz
  // dac.setClockSpeed(30000000); // maximum tested for 80501
  // dac.setClockSpeed(100000); // min. tested for 80501
  
  dac.begin(&SPI,SPI1_SCK,SPI1_MISO,SPI1_MOSI,SPI1_CS);
  //dac.setREG4_DivGain(SET4_DIV2,SET4_GAIN1);
}

#define DAC_SAW

uint16_t i=0;
void loop() 
{
#ifdef DAC_SAW
  // saw-wave signal
  i= i +256;
  dac.writeDAC(i);
#else
  // fast square signal
  dac.writeDAC(0);
  dac.writeDAC(0xffff);
#endif
}
