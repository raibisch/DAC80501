#  DAC80501 Library

This is a library for the TI DAC80501 16bit digital analog converter
(until now only the SPI bus connection is supported by this lib)

## Helpful Infos
https://e2e.ti.com/support/data-converters-group/data-converters/f/data-converters-forum/968246/dac80501-spi
https://www.ti.com/product/DAC80501


## Author
Juergen Goldmann

## Licence
GNU Lesser General Public License v3 (LGPL-3.0)

## Download and Installation
To download click the DOWNLOAD ZIP button, rename the uncompressed folder Dac80501. Check that the ADC80501 folder contains Dac80501.cpp and Dac80501.h

### Arduino IDE
Place the Dac80501 library folder your arduinosketchfolder/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the IDE.

### Platform IO
Add in 'platform.ini' (no need to download before)
```
lib_deps =
  https://github.com/raibisch/adc80501
```

# Remark for Software-Design 
MOSI signal was not used, because of one way data transfer from slave to master, but defined as 'dummy' pin in CPU.
Tested with ESP32, ESP-S2 and ESP-S3
### Define
```
Dac80501 dac;
```
### Init
```
// default clock=2MHz
dac.setClockSpeed(10000000); // 10MHz
dac.begin(&SPI,SPI1_SCK,SPI1_MISO,SPI1_MOSI,SPI1_CS);
// default div=2 gain=1
dac.setREG4_DivGain(SET4_DIV2,SET4_GAIN2);
``` 
### Write Value to DAC
```
 dac.writeDAC(0xffff);
``` 

# Remark for Hardware-Design
In some cases the spi data transfer does not work. I have good results with a 330 Ohm resistor in the 'SCLK' and 'MISO' (and CS) line to reduce signal reflections.
