/*******************************************************************************************************************
** Example program for measuring temperatures using the MAX31855 Cold-Junction Compensated Thermocouple-to-digital**
** converter.                                                                                                     **
** The MAX31855 datasheet is located at https://datasheets.maximintegrated.com/en/ds/MAX31855.pdf and describes   **
** the relatively simple interface.  The MAX31855 uses SPI to communicate and only outputs data. It writes a      **
** sentences of 32 bits which include devices failure information and the ambient temperature as well as the      **
** thermocouple probe temperature in degrees Celsius.                                                             **
**                                                                                                                **
** The most recent version of the MAX31855 library is available at https://github.com/SV-Zanshin/MAX31855 and the **
** documentation of the library as well as example programs are described in the project's wiki pages located at  **
** https://github.com/SV-Zanshin/MAX31855/wiki.                                                                   **
**                                                                                                                **
** This example is simple in that it displays the ambient and probe temperatures every 5 seconds and flags any    **
** errors that the device raises.                                                                                 **
**                                                                                                                **
** This program is free software: you can redistribute it and/or modify it under the terms of the GNU General     **
** Public License as published by the Free Software Foundation, either version 3 of the License, or (at your      **
** option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY     **
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   **
** GNU General Public License for more details. You should have received a copy of the GNU General Public License **
** along with this program.  If not, see <http://www.gnu.org/licenses/>.                                          **
**                                                                                                                **
** Vers.  Date       Developer           Comments                                                                 **
** ====== ========== =================== ======================================================================== **
** 1.0.0  2017-08-12 Arnd@SV-Zanshin.Com Finished, first release                                                  **
** 1.0.0a 2017-08-11 Arnd@SV-Zanshin.Com Initial coding                                                           **
**                                                                                                                **
*******************************************************************************************************************/
#include <MAX31855.h>                                                         // Include MAX31855 Sensor library  //
#include <DSFamily.h>                                                         // Include the DS-Family library    //
/*******************************************************************************************************************
** Declare all program constants                                                                                  **
*******************************************************************************************************************/
const uint32_t SERIAL_SPEED            = 115200;                              // Set the baud rate for Serial I/O //
const uint8_t  SPI_CHIP_SELECT         =      2;                              // Chip-Select PIN for SPI          //
const uint8_t  ONE_WIRE_PIN            =     10;                              // 1-Wire communications pin        //
const uint8_t  SPI_MISO                =   MISO;                              // Master-In, Slave-Out PIN for SPI //
const uint8_t  SPI_SYSTSEM_CLOCK       =    SCK;                              // System Clock PIN for SPI         //
/*******************************************************************************************************************
** Declare global variables and instantiate classes                                                               **
*******************************************************************************************************************/
MAX31855_Class   MAX31855;                                                    // Create an instance of MAX31855   //
DSFamily_Class   oneWire(ONE_WIRE_PIN);                                       // Create a 1-Wire microlan on pin  //
/*******************************************************************************************************************
** Method Setup(). This is an Arduino IDE method which is called upon boot or restart. It is only called one time **
** and then control goes to the main loop, which loop indefinately.                                               **
*******************************************************************************************************************/
void setup() {                                                                // Arduino standard setup method    //
  Serial.begin(SERIAL_SPEED);                                                 // Start serial port at Baud rate   //
  #ifdef  __AVR_ATmega32U4__                                                  // If this is a 32U4 processor, then//
    delay(3000);                                                              // wait 3 seconds for the serial    //
  #endif                                                                      // interface to initialize          //
  Serial.println(F("Starting software SPI demo program for MAX31855"));       //                                  //
  Serial.print(F("Initializing MAX31855 sensor\n"));                          //                                  //
  /******************************************************                     //                                  //
  ** Uncomment out either the hardware or software SPI **                     //                                  //
  ** call, depending upon which you are going to use.  **                     //                                  //
  ******************************************************/                     //                                  //
  while (!MAX31855.begin(SPI_CHIP_SELECT)) {                                  // Hardware SPI for MAX31855        //
//while (!MAX31855.begin(SPI_CHIP_SELECT,SPI_MISO,SPI_SYSTSEM_CLOCK)) {       // Software SPI for MAX31855        //
    Serial.println(F("Unable to start MAX31855. Waiting 3 seconds."));        // Show error text                  //
    delay(3000);                                                              // wait three seconds               //
  } // of loop until device is located                                        //                                  //
 Serial.println();                                                            //                                  //
 Serial.print("Found ");
 oneWire.ScanForDevices();
 Serial.print(oneWire.ThermometersFound);
 Serial.println(" 1-Wire thermometers.");
} // of method setup()                                                        //                                  //
/*******************************************************************************************************************
** This is the main program for the Arduino IDE, it is an infinite loop and keeps on repeating.                   **
*******************************************************************************************************************/
void loop() {                                                                 //                                  //
  int32_t ambientTemperature = MAX31855.readAmbient();                        // retrieve die ambient temperature //
  int32_t probeTemperature   = MAX31855.readProbe();                          // retrieve thermocouple probe temp //
  uint8_t faultCode          = MAX31855.fault();                              // retrieve any error codes         //
  if(faultCode) {                                                             // Display error code when present  //
    Serial.print("Fault code ");                                              //                                  //
    Serial.print(faultCode);                                                  //                                  //
    Serial.println(" returned.");                                             //                                  //
  } else {                                                                    //                                  //
    Serial.print(millis()/1000);                                              //                                  //
    Serial.print(",");                                                        //                                  //
    Serial.println((float)probeTemperature/1000,3);                           //                                  //
//    Serial.print(",");                                                        //                                  //
//    Serial.println((float)oneWire.ReadDeviceTemp(0)*0.0625,3);
  } // of if-then-else an error occurred                                      //                                  //
  oneWire.DeviceStartConvert(0);
  delay(1000);                                                                //                                  //
} // of method loop()                                                         //----------------------------------//
