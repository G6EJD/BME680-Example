# BME680-Example

Using the BME680 to measure temperature, pressure, humidity and air quality
The sensor is used to get so-called Gas Resistance and then an Air Quality Index (IAQ) is determined from a combination of the readings of humidity and gas content of the air.
The index comprises up to 25% for the humidity contribution and 75% for the gas contribution.
Very low or high humidity is considered to result in an uncomfortable environment, with 40% being optimal. Therefore the humidity contribution to the IAQ is derived from a value that is 0 when RH is 0 and rises to 25% at 40% RH, above 40% RH the value falls to 0 at 100% RH, so in summary the RH quality scores peaks at 40% RH and falls to 0 either side of that value, with the final value scaled between 0 and 25%.
For Gas it has been assumed that normal breathable air with no pollutants (adverse gases) corresponds to the sensors highest output of 300,000 ohms. The sensor outputs a Gas resistance value ranging from a low of 50,000 to a high of 500,000 and beyond. A linear relationship is assumed and the output scaled accordingly between 0 and 75%.
The result of humidity and gas indexes is a qualitative and a so-called IAQ - Indoor Air Quality index value scaled from 0-100% (where 100% is good). This is then scaled to 0-500 where a 500 value is bad and descriptive values applied in stages from good to hazardous air quality.
There is no definitive (ISO Standard method for calculating an IAQ.
(c) d.l.bird 2017 all rights reserved and as per the MIT licence agreements listed in all my software.
