# MAX31855 library
<img src="https://github.com/SV-Zanshin/MAX31855/blob/master/Images/Digilent_Pmod_TC1.png" width="175" align="right"/> *Arduino* library for using the [Maxim Integrated MAX31855](https://www.maximintegrated.com/en/products/analog/sensors-and-sensor-interface/MAX31855.html) cold-junction compensated thermocouple to digital sensor.

### Temperature sensing
The MAX31855 uses SPI and, when selected, sends a 4 byte buffer which can be decoded to show faults, the ambient die-temperature (cold-junction) and the thermocouple temperature. It does not have any settings or data input, making the library simple.  Temperatures are returned in degrees Celsius and in accuracy of the thermocouple temperature ±0.2°C over a range from -200°C to 700°C depending on thermocouple type. The K-Type thermocouple used for developing this library gives a range of -73°C to 482°C.
The ambient temperature is affected by die and board temperature and will generally be above actual ambient room temperature.

A detailed library description and further details are available at the [GitHub MAX31855 Wiki](https://github.com/SV-Zanshin/MAX31855/wiki)

![Zanshin Logo](https://www.sv-zanshin.com/r/images/site/gif/zanshinkanjitiny.gif) <img src="https://www.sv-zanshin.com/r/images/site/gif/zanshintext.gif" width="75"/>
