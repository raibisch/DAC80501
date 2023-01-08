#ifndef DAC80501_H
#define DAC80501_H

#include <Arduino.h>
#include <SPI.h>

#define REG4_DIVGAIN  0x04
#define REG5_RESET    0x05
#define REG8_DAC      0x08

#define SET5_RESET 0x00A0

#define SET4_GAIN1 0x00
#define SET4_GAIN2 0x01
#define SET4_DIV1  0x00
#define SET4_DIV2  0x01



class DAC80501
{
  public:
    DAC80501 ();
    ~DAC80501 ();
    void begin(SPIClass *port, uint8_t clk_pin, uint8_t miso_pin, uint8_t mosi_pin, uint8_t cs_pin);
    void end ();
    
    void writeREG(uint8_t command, uint8_t b1, uint8_t b2);
    void setREG4_DivGain(uint8_t div, uint8_t gain);
    void setREG5_Reset();
    void writeDAC(uint16_t data);
    void setClockSpeed(uint32_t cspeed);
  private:
    uint8_t DacCsPin = 0;
    SPIClass *spi_port;
    uint32_t spi_clock_speed = 2000000;   
};

#endif /* DAC80501_H */
