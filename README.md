# BME680-Example
Using the BME680 to measure temperature, pressure, humdity and air quality

The sensor is uses to get so-called Gas Reistance and then an Air Quality index is determined from humidity and gas content of the air.

The index is comprised of 25% for the humidity contribution and 75% for the gas contributions.

Very low humidity gives a score of 0 rising to 25% at 40% which is considered to be an optimium humidity level and then the humidity value falls again until it reache 0 at 100% rH.

For Gas an restance value of 50,000 is assumed to be a bad enviroment and 300,000 good.

The result of humdidity and gas indexes is the so-called IAQ - Indoor Air Quality (in this case relative) index scaledfrom 0-100% (100% is good) to 0-500 where 500 is bad and then descriptive values are displayed.

