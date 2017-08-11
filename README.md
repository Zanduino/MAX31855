# MAX31855 library

 - - - W o r k   i n   p r o g r e s s - - -   
 
<img src="https://github.com/SV-Zanshin/BME280/blob/master/Images/sensors_pinout.jpg" width="175" align="right"/> *Arduino* library for using the [Bosch BME280](https://www.bosch-sensortec.com/bst/products/all_products/bme280) sensor which senses temperature, humidity and pressure. Since the package is quite small and difficult to breadboard with, the [Adafruit BME280 Breakout](https://www.adafruit.com/product/2652) board was used for development.

A complete description of the BME280 sensor can be found in the [BME280 Datasheet](https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280_DS001-11.pdf) while the [Adafruit BME280 tutorial](https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout) describes additional board information.

## Sensing

### Temperature sensing
The BME280 measures temperatures between -40°C and 85°C with a full accuracy range between 0°C and +65°C. The accuracy is ±0.5°c with a full resolution of 0.01°C. Since the temperature sensor in the small package is tied to the PCB board on which it is soldered placed and has some self-heating as well the temperature reading will usually be above ambient.

A detailed library description and further details are available at the [GitHub MAX31855 Wiki](https://github.com/SV-Zanshin/MAX31855/wiki)

![Zanshin Logo](https://www.sv-zanshin.com/r/images/site/gif/zanshinkanjitiny.gif) <img src="https://www.sv-zanshin.com/r/images/site/gif/zanshintext.gif" width="75"/>
