#  DAC80501 Arduino Library
[![GitHub version](https://img.shields.io/github/release/raibisch/DAC80501.svg)](https://github.com/raibisch/Dac80501/archive/refs/heads/master.zip)
[![License](https://img.shields.io/badge/license-EUPL1.2-green)](license/LICENSE.md)
[![donate](https://img.shields.io/badge/donate-PayPal-blue.svg)](https://www.paypal.com/paypalme/goldmannjuergen)

This is a library for the TI DAC80501 16bit digital analog converter
(until now only the SPI bus connection is supported by this lib)
## Helpful Infos
https://e2e.ti.com/support/data-converters-group/data-converters/f/data-converters-forum/968246/dac80501-spi

https://www.ti.com/product/DAC80501
## Author
Jürgen Goldmann
## Licence
[Licensed under the European Union Public License (EUPL)-1.2-or-later](https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12)

[why licensed under EUPL-1.2: it is compatible to GPL and compatible to EU-rights and regulations](https://joinup.ec.europa.eu/collection/eupl/join-eupl-licensing-community)

[compare different licences](https://joinup.ec.europa.eu/collection/eupl/solution/joinup-licensing-assistant/jla-find-and-compare-software-licenses)
## Download and Installation
To download click the DOWNLOAD ZIP button, rename the uncompressed folder Dac80501. Check that the Dac80501 folder contains DAC80501.cpp and DAC80501.h
### Arduino IDE
Place the Dac80501 library folder your arduinosketchfolder/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the IDE.
### Platform IO
Add in 'platform.ini' (no need to download before)
```
lib_deps =
  https://github.com/raibisch/dac80501
```
# Remark for Software-Design 
MOSI signal was not used, because of one way data transfer from slave to master, but defined as 'dummy' pin in CPU.
Tested with ESP32, ESP-S2 and ESP-S3 - may also (not tested) work with other arduino CPUs
### Define
```
DAC80501 dac;
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
