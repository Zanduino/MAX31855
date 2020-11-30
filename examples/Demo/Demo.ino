/*! @file Demo.ino

@section Demo_intro_section Description

Example program for measuring temperatures using the MAX31855 Cold-Junction Compensated Thermocouple-to-digital
converter.\n\n
The MAX31855 datasheet is located at https://datasheets.maximintegrated.com/en/ds/MAX31855.pdf and describes the
relatively simple interface.  The MAX31855 uses SPI to communicate and only outputs data. It writes a sentence of
32 bits which include devices failure information and the ambient temperature as well as the thermocouple probe 
temperature in degrees Celsius.\n\n

The most recent version of the MAX31855 library is available at https://github.com/SV-Zanshin/MAX31855 and the
documentation of the library as well as example programs are described in the project's wiki pages located at
https://github.com/SV-Zanshin/MAX31855/wiki \n\n

This example is simple in that it displays the ambient and probe temperatures every 5 seconds and flags any errors 
that the device raises.

@section Demolicense __**GNU General Public License v3.0**__

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

@section Demoauthor Author

Written by Arnd\@SV-Zanshin

@section Demoversions Changelog

Version | Date       | Developer  | Comments
------- | ---------- | ---------- | ---------------------------------------------------
1.0.2   | 2020-11-30 | mbouy974   | Corrected definition for Sofware SPI
1.0.1   | 2019-02-02 | SV-Zanshin | Issue #4 - Convert program comments and style to Doxygen
1.0.0   | 2017-08-12 | SV-Zanshin | Finished, first release
1.0.0a  | 2017-08-11 | SV-Zanshin | Initial coding
*/
#include <MAX31855.h> // Include MAX31855 Sensor library
/*******************************************************************************************************************
** Declare all program constants                                                                                  **
*******************************************************************************************************************/
const uint32_t SERIAL_SPEED     = 115200; ///< Set the baud rate for Serial I/O
const uint8_t  SPI_CHIP_SELECT  =      2; ///< Chip-Select PIN for SPI
const uint8_t  SPI_MISO         =   MISO; ///< Master-In, Slave-Out PIN for SPI
const uint8_t  SPI_SYSTEM_CLOCK =    SCK; ///< System Clock PIN for SPI

/*******************************************************************************************************************
** Declare global variables and instantiate classes                                                               **
*******************************************************************************************************************/
MAX31855_Class MAX31855; ///< Create an instance of MAX31855

/***************************************************************************************************************//*!
* @brief    Arduino method called once at startup to initialize the system
* @details  This is an Arduino IDE method which is called first upon boot or restart. It is only called one time
*           and then control goes to the main "loop()" method, from which control never returns
* @return   void
*******************************************************************************************************************/
void setup()
{
  Serial.begin(SERIAL_SPEED);
  #ifdef  __AVR_ATmega32U4__  // If this is a 32U4 processor, then wait 3 seconds for the interface to initialize
    delay(3000);
  #endif
  Serial.println(F("Starting software SPI demo program for MAX31855"));
  Serial.print(F("Initializing MAX31855 sensor\n"));
  /********************************************************************************************
  ** Uncomment out either the hardware or software SPI call, depending upon which is in use  **
  ********************************************************************************************/
  while (!MAX31855.begin(SPI_CHIP_SELECT))                           // Hardware SPI for MAX31855
//while (!MAX31855.begin(SPI_CHIP_SELECT,SPI_MISO,SPI_SYSTEM_CLOCK)) // Software SPI for MAX31855
  {
    Serial.println(F("Unable to start MAX31855. Waiting 3 seconds."));
    delay(3000);
  } // of loop until device is located
 Serial.println();
} // of method setup()

/***************************************************************************************************************//*!
* @brief    Arduino method for the main program loop
* @details  This is the main program for the Arduino IDE, it is an infinite loop and keeps on repeating.
* @return   void
*******************************************************************************************************************/
void loop()
{
  int32_t ambientTemperature = MAX31855.readAmbient(); // retrieve MAX31855 die ambient temperature
  int32_t probeTemperature   = MAX31855.readProbe();   // retrieve thermocouple probe temp
  uint8_t faultCode          = MAX31855.fault();       // retrieve any error codes
  if ( faultCode )                                     // Display error code if present
  {
    Serial.print("Fault code ");
    Serial.print(faultCode);
    Serial.println(" returned.");
  }
  else
  {
    Serial.print("Ambient Temperature is ");
    Serial.print((float)ambientTemperature/1000,3);
    Serial.println("\xC2\xB0""C");
    Serial.print("Probe Temperature is   ");
    Serial.print((float)probeTemperature/1000,3);
    Serial.println("\xC2\xB0""C\n");
  } // of if-then-else an error occurred
  delay(5000);
} // of method loop()
