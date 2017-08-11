/*******************************************************************************************************************
** MAX31855 class method definitions. See the header file for program details and version information             **
**                                                                                                                **
** This program is free software: you can redistribute it and/or modify it under the terms of the GNU General     **
** Public License as published by the Free Software Foundation, either version 3 of the License, or (at your      **
** option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY     **
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   **
** GNU General Public License for more details. You should have received a copy of the GNU General Public License **
** along with this program.  If not, see <http://www.gnu.org/licenses/>.                                          **
**                                                                                                                **
*******************************************************************************************************************/
#include "MAX31855.h"                                                         // Include the header definition    //
                                                                              //----------------------------------//
MAX31855_Class::MAX31855_Class()  {}                                          // Empty & unused class constructor //
MAX31855_Class::~MAX31855_Class() {}                                          // Empty & unused class destructor  //
/*******************************************************************************************************************
** Method begin starts communications with the device. It is overloaded to allow for either hardware or software  **
** SPI to be used.                                                                                                **
*******************************************************************************************************************/
bool MAX31855_Class::begin(const uint8_t chipSelect,                          // Start using software SPI         //
                           const uint8_t miso,                                //                                  //
                           const uint8_t sck) {                               //                                  //
  _cs   = chipSelect; _miso = miso; _sck  = sck;                              // Store SPI pins                   //
  digitalWrite(_cs, HIGH);                                                    // High means ignore master         //
  pinMode(_cs, OUTPUT);                                                       // Make the chip select pin output  //
  pinMode(_sck, OUTPUT);                                                      // Make system clock pin output     //
  pinMode(_miso, INPUT);                                                      // Make master-in slave-out input   //

  return false;                                                               // return failure if we get here    //
} // of method begin()                                                        //                                  //
/*******************************************************************************************************************
** Method getData() returns the ambient and probe temperatures as well as any error codes. There are 3 possible   **
** errors which are mutually exclusive, the return codes possible are:                                            **
** 1 - No Thermocouple detected                                                                                   **
** 2 - Short-Circuit to GND                                                                                       **
** 3 - Short-Circuit to VCC                                                                                       **
** In order to avoid floating-point math, the temperatures are returned in thousandths of degress Celsius, so a   **
** temperature of 24.3450 degrees is returned as 24345                                                            **
*******************************************************************************************************************/
uint8_t getData(int16_t &ambientTemp, int16_t &probeTemp) {                   // Get readings                     //

} // of method getData()                                                      //                                  //