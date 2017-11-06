# BME680-Example
Using the BME680 to measure temperature, pressure, humdity and air quality

The sensor is used to get so-called Gas Resistance and then an Air Quality Index (IAQ) is determined from a combination of the readings of humidity and gas content of the air.

The index comprises upto 25% for the humidity contribution and 75% for the gas contribution.

Very low or high humidity is considered to result in an uncomfortable environment, with 40% being optimal. Therefore the humidity contribution to the IAQ is derived from a value that is 0 when RH is 0 and rises to 25% at 40% RH, above 40% RH the value falls to 0 at 100% RH, so in summary the RH quality scores peaks at 40% RH and falls to 0 either side of that value, with the final value scaled between 0 and 25%.

For Gas it has been assumed that normal breathable air with no pollutants (adverse gases) corresponds to the sesnors highest output of 300,000 ohms. The sensor outputs a Gas resistance value ranging from alow of 50,000 to a high of 300,000 and beyond. A linear relationship is assumed and the output scaled between 0 and 75%.

The result of humdity and gas indexes is a qualative and so-called IAQ - Indoor Air Quality index value scaled from 0-100% (100% is good) and then this is scaled to 0-500 where 500 is bad and descriptive values are displayed from good to hazardous air quality.

There is no definitive (ISO Standardj method for calculating an IAQ.

(c) d.l.bird 2017 all rights reserved and as per the MIT licence agrrements listed in all my software.

