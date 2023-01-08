/*
 * Copyright (c) 2022 by J. Goldmann raibisch@gmail.com
 * Arduino library for DAC80501
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 2.1,
 * as published by the Free Software Foundation.
 */

#include <Arduino.h>
#include <SPI.h>
#include "DAC80501.h"


/**
 * @brief Construct a new Dac80501 object - not needed by Arduino but for complete class. does not do anything.
 * 
 */
DAC80501::DAC80501()
{
}

/*-----------------------------
destructor for class, not needed by Arduino but for complete class. Calls Arduino end function
*/
DAC80501::~DAC80501()
{
  spi_port->end();
}


/**
 * @brief write 2x 8bit bytes to a command register
 * 
 * @param command dac register No
 * @param b1      HIGH-byte
 * @param b2      LOW-byte
 */
void DAC80501::writeREG(uint8_t command, uint8_t b1, uint8_t b2)
{
  digitalWrite(DacCsPin,HIGH);
  delay(1);
  digitalWrite(DacCsPin,LOW);
  delayMicroseconds(1);
  spi_port->write(command);
  spi_port->write(b1);
  spi_port->write(b2);
  delay(1);
  digitalWrite(DacCsPin,HIGH);
}

/**
 * @brief  Set Divider and Gain -  
           default Divider: SET4_DIV2 = 0x01
 * @param div  div=1->SET4_DIV1  
 *             div=2->SET4_DIV2
 * @param gain gain=1->SET4_GAIN1  
 *             gain=2->SET4_GAIN2
 */
void DAC80501::setREG4_DivGain(uint8_t div, uint8_t gain)
{
   writeREG(REG4_DIVGAIN, div , gain); 
}

/**
 * @brief soft reset for DAC
 */
void DAC80501::setREG5_Reset()
{
   writeREG(REG5_RESET, 0b00000000 ,0b00001010); // Soft Reset
}


/**
 * @brief write analog value to output register
 * @param data 16bit analog output value
 */
void DAC80501::writeDAC(uint16_t data)
{
  digitalWrite(DacCsPin,LOW);
  spi_port->write(REG8_DAC);
  spi_port->write16(data);
  digitalWrite(DacCsPin,HIGH);
}

/**
 * @brief Set SPI speed (call bevor "begin" to change default 2MHz)
 *        
 * @param cspeed value in Hz
 */
void DAC80501::setClockSpeed(uint32_t cspeed)
{
  spi_clock_speed = cspeed;
}

/**
 * @brief init SPI, prepare I/O and start DAC80501
 * 
 * @param port    SPI-Port
 * @param clk_pin Clock-Pin
 * @param miso_pin MISO-Pin (only dummy)
 * @param mosi_pin MOSI-Pin
 * @param cs_pin   ChipSelect-Pin
 */
void DAC80501::begin(SPIClass *port, uint8_t clk_pin, uint8_t miso_pin, uint8_t mosi_pin, uint8_t cs_pin)
{
  DacCsPin = cs_pin;
  spi_port = port;
  pinMode(cs_pin, OUTPUT); // CS output
  digitalWrite(DacCsPin,HIGH);
  delay(1);
  port->begin(clk_pin, miso_pin, mosi_pin,cs_pin); //SCLK, MISO, MOSI, SS
  SPISettings settings(spi_clock_speed, SPI_MSBFIRST, SPI_MODE2);
  port->beginTransaction(settings);
  delay(1);
  setREG5_Reset();
  setREG4_DivGain(SET4_DIV2, SET4_GAIN2); // div=2 gain=2
}


/**
 * @brief Class end (mostly not needed)
 * 
 */
void DAC80501::end()
{
  spi_port->end();
}

