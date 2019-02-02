/*! @file MAX31855.h

@mainpage Arduino Library Header to access the MAX31855 thermocouple 

@section MAX31855_intro_section Description

Class definition header for the Maxim MAX31855 Cold-Junction Compensated Thermocouple-to-digital converter. The 
MAX31855 datasheet is located at https://datasheets.maximintegrated.com/en/ds/MAX31855.pdf and describes the 
relatively simple interface.  The MAX31855 uses SPI to communicate and only outputs data. It writes a sentence
of 32 bits which include devices failure information and the ambient temperature as well as the thermocouple probe
temperature in degrees Celsius.\n\n

The most recent version of the MAX31855 library is available at https://github.com/SV-Zanshin/MAX31855 and the
documentation of the library as well as example programs are described in the project's wiki pages located at
https://github.com/SV-Zanshin/MAX31855/wiki \n\n

The MAX31855 is a specialized chip that uses SPI to send a sentence of 32 bits on demand. This contains the ambient
temperature and probe temperature in degrees Celsius as well as some status bits indicating fault conditions. It 
does not have any data inputs apart from checking the state of the CS pin.

@section MAX31855_License __**GNU General Public License v3.0**__
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

@section MAX31855author Author

Written by Arnd\@SV-Zanshin

@section MAX31855versions Changelog

Version| Date       | Developer                     | Comments
------ | ---------- | ----------------------------- | --------
1.0.4  | 2019-02-02 | https://github.com/SV-Zanshin | Issue #5 - Convert comments and style to Doxygen
1.0.2  | 2017-09-17 | https://github.com/SV-Zanshin | Issue #2 - Invalid values
1.0.1  | 2017-09-10 | https://github.com/SV-Zanshin | Added error return codes for begin(). Added reverse switch in
                                                      begin() and corrected speed issue and sporadic errors
1.0.0  | 2017-08-12 | https://github.com/SV-Zanshin | Ready for release
1.0.0a | 2017-08-11 | https://github.com/SV-Zanshin | Started coding
*/
#include "Arduino.h"
#include <SPI.h> // Standard SPI library
#ifndef MAX31855_h
  /*! Library guard variable to prevent multiple inclusions */
  #define MAX31855_h
  /*****************************************************************************************************************
  ** Declare constants used in the class                                                                          **
  *****************************************************************************************************************/
  const uint16_t SPI_DELAY_MICROSECONDS = 1000; ///< Wait time for SPI state changes
  const uint8_t  READING_RETRIES        =   64; ///< Number of retries for reading

/***************************************************************************************************************//*!
* @class   MAX31855_Class
* @brief    MAX31855 class for reading temperature information
*******************************************************************************************************************/
  class MAX31855_Class
  {
    public:
      MAX31855_Class();
      ~MAX31855_Class();
      bool    begin(const uint8_t cs,const bool reverse = false); // Start using hardware SPI
      bool    begin(const uint8_t cs, const uint8_t miso, const uint8_t sck, const bool reverse = false); // Soft SPI
      int32_t readProbe();       // Return probe temperature
      int32_t readAmbient();     // Return ambient/die temperature
      uint8_t fault();           // return any fault codes detected
    private:
      int32_t readRaw();         // Read 32 bits data from MAX31855
      uint8_t _cs,_miso,_sck;    ///< Store SPI pin values
      uint8_t _errorCode;        ///< MAX31855 fault code bits
      bool    _reversed = false; ///< Set to true if contacts reversed
  }; // of MAX31855 class definition
#endif
