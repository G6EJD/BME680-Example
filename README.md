# BME680-Example

Using the BME680 to measure temperature, pressure, humidity and air quality.

The sensor is used to get so-called Gas Resistance and then an Air Quality Index (IAQ) is determined from a combination of the readings of humidity and gas content of the air.

The index is comprised of contributions from humidity by up to 25% and gas concentrations by up to 75%.

The affect of humidity on the index is determined bby 40% being considered an ideal level, with 0% or 100% being considered to create an uncomfortable environment. Therefore the humidity contribution to the IAQ is derived from a value that is 0 when RH is 0 rising to 25% when hunidity is optimal at 40%, then above that, value falls to 0 at 100% RH. In summary, the RH quality scores peaks at 40% RH and falls to 0 either side of that value, with the final value scaled between 0 and 25%.

For Gas it has been assumed that normal breathable air with no pollutants (adverse gases) corresponds to the sensors highest output of 50,000 ohms or more. The sensor normally outputs a Gas resistance value ranging from a low of 50ohm to a high of 50,000ohm and beyond. A linear relationship is assumed and the output scaled accordingly between 0 and 75% for the range 50-50,000 ohms.

The result of humidity and gas indexes is a qualitative and a so-called IAQ - Indoor Air Quality index value, which is then scaled from 0-100% (where 100% is good). This is then scaled again from 0-500 where a 500 value is bad and descriptive values applied in stages from good to hazardous air quality.

There is no definitive (ISO Standard) method for calculating an IAQ.

(c) d.l.bird 2017 all rights reserved and as per the MIT licence agreements listed in all my software.
