/*
 * Copyright (c) 2019 by generationmake bernhard@generationmake.de
 * Arduino library for Electronic Assembly Dog Graphic Display DOGM132-5, DOGM128-6, DOGL128-6 and DOGS102-6 (controller ST7565 and UC1701)
 *
 * based on the work by:
 * Copyright (c) 2014 by ELECTRONIC ASSEMBLY <technik@lcd-module.de>
 * EA DOG Graphic (ST7565R) software library for arduino.
 * (see git log for modifications)
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 2.1,
 * as published by the Free Software Foundation.
 */

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
