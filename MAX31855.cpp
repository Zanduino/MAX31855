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
** Overloaded method begin() prepares communications with the MAX31855. If called with one parameter which        **
** represents the chip-select pin then hardware SPI is used, otherwise 3 parameters define the software SPI pins  **
** SPI to be used.  Since the MAX31855 is a 1-way device, there is no practical way to check for a device, so the **
** begin() is set to always return success                                                                        **
*******************************************************************************************************************/
bool MAX31855_Class::begin(const uint8_t chipSelect) {                        // Start using hardware SPI         //
  _cs = chipSelect;                                                           // Copy value for later use         //
  pinMode(_cs, OUTPUT);                                                       // Make the chip select pin output  //
  digitalWrite(_cs, HIGH);                                                    // High means ignore master         //
  SPI.begin();                                                                // Initialize SPI communication     //
  return true;                                                                // Always return success            //
} // of method begin()                                                        //----------------------------------//
bool MAX31855_Class::begin(const uint8_t chipSelect,                          // Start using software SPI         //
                           const uint8_t miso,                                //                                  //
                           const uint8_t sck) {                               //                                  //
  _cs   = chipSelect; _miso = miso; _sck  = sck;                              // Store SPI pins                   //
  pinMode(_cs, OUTPUT);                                                       // Make the chip select pin output  //
  digitalWrite(_cs, HIGH);                                                    // High means ignore master         //
  pinMode(_sck, OUTPUT);                                                      // Make system clock pin output     //
  pinMode(_miso, INPUT);                                                      // Make master-in slave-out input   //
  return true;                                                                // Always return success            //
} // of method begin()                                                        //                                  //
/*******************************************************************************************************************
** Method fault() returns the last fault code from the MAX31855                                                   **
*******************************************************************************************************************/
uint8_t MAX31855_Class::fault() {                                             // Get fault state                  //
  return _errorCode;                                                          // return internal variable         //
} // of method fault()                                                        //                                  //
/*******************************************************************************************************************
** Method readRaw() returns the 32 bits of raw data from the MAX31855 device                                      **
*******************************************************************************************************************/
int32_t MAX31855_Class::readRaw() {                                           // Get readings                     //
  int32_t dataBuffer = 0;                                                     //                                  //
  digitalWrite(_cs,LOW);                                                      // Tell MAX31855 that it is active  //
  delayMicroseconds(SPI_DELAY_MICROSECONDS);                                  // Give device time to respond      //
  if(_sck==0) {                                                               // If we are using HW SPI branch    //
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));          // Start transaction at 4MHz MSB    //
    dataBuffer   = SPI.transfer(0);                                           // Read a byte                      //
    dataBuffer <<= 8;                                                         // Shift over left 8 bits           //
    dataBuffer  |= SPI.transfer(0);                                           // Read a byte                      //
    dataBuffer <<= 8;                                                         // Shift over left 8 bits           //
    dataBuffer  |= SPI.transfer(0);                                           // Read a byte                      //
    dataBuffer <<= 8;                                                         // Shift over left 8 bits           //
    dataBuffer  |= SPI.transfer(0);                                           // Read a byte                      //
    SPI.endTransaction();                                                     // Terminate SPI transaction        //
  } else {                                                                    //                                  //
    digitalWrite(_sck, LOW);                                                  // Toggle the system clock low      //
    delayMicroseconds(SPI_DELAY_MICROSECONDS);                                // Give device time to respond      //
    for(uint8_t i=0;i<32;i++) {                                               // Loop for each bit to be read     //
      digitalWrite(_sck, LOW);                                                // Toggle the system clock low      //
      delayMicroseconds(SPI_DELAY_MICROSECONDS);                              // Give device time to respond      //
      dataBuffer <<= 1;                                                       // Shift over 1 bit                 //
      if (digitalRead(_miso)) dataBuffer |= 1;                                // set rightmost bit if true        //
      digitalWrite(_sck, HIGH);                                               // Toggle the system clock high     //
      delayMicroseconds(SPI_DELAY_MICROSECONDS);                              // Give device time to respond      //
    } // of read each bit from software SPI bus                               //                                  //
  } // of if-then-else we are using HW SPI                                    //                                  //
  digitalWrite(_cs,HIGH);                                                     // MAX31855 no longer active        //
  _errorCode = dataBuffer & B111;                                             // Set fault code bits              //
  return dataBuffer;                                                          // Return data                      //
} // of method readRaw()                                                      //                                  //
/*******************************************************************************************************************
** Method readProbe() returns the probe temperature. The temperature is returned in milli-degrees Celsius so that **
** no floating point needs to be used and no precision is lost                                                    **
*******************************************************************************************************************/
int32_t MAX31855_Class::readProbe() {                                         // Get readings                     //
  int32_t dataBuffer = readRaw();                                             // Read the raw data into variable  //
  if (dataBuffer & B111) dataBuffer = INT32_MAX;                              // if error bits set then return err//
  else {                                                                      //                                  //
    dataBuffer = dataBuffer >> 18;                                            // remove unused ambient values     //
    if(dataBuffer & 0x2000) dataBuffer |= 0xFFFE000;                          // 2s complement bits if negative   //
    dataBuffer *= 250;                                                        // Sensitivity is 0.25°C            //
  } // of if we have an error                                                 //                                  //
  return dataBuffer;                                                          // Return appropriate code          //
} // of method readProbe()                                                    //                                  //
/*******************************************************************************************************************
** Method readAmbient() returns the probe temperature. The temperature is returned in milli-degrees Celsius so    **
** that no floating point needs to be used and no precision is lost                                               **
*******************************************************************************************************************/
int32_t MAX31855_Class::readAmbient() {                                       // Get readings                     //
  int32_t dataBuffer = readRaw();                                             // Read the raw data into variable  //
  if (dataBuffer & B111) dataBuffer = INT32_MAX;                              // if error bits set then return err//
  else {                                                                      //                                  //
    dataBuffer = (dataBuffer&0xFFFF)>>4;                                      // remove probe & fault values      //
    if(dataBuffer & 0x2000) dataBuffer |= 0xFFFF000;                          // 2s complement bits if negative   //
    dataBuffer = dataBuffer*625/10;                                           // Sensitivity is 0.0625°C          //
  } // of if we have an error                                                 //                                  //
  return dataBuffer;                                                          // Return appropriate code          //
} // of method readAmbient()                                                  //                                  //
