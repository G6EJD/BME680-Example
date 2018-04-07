

BME680 IAQ Example

Using the BME680 to measure temperature, pressure, humidity and air quality.

The sensor is used to obtain the so-called Gas Resistance and then calculate an Index of Air Quality (IAQ) from a combination of readings of humidity and the gas content of the air, optionally temperature could be added too.

The index is a function of humidity which contributes up to 25% and gas concentrations that contributes up to 75%. See slide1.jpg for details of the IAQ index formulation. 

In this current version only Humidity and Gas concentrations are used for the index, but adding temperature woudl be straightforward on the basis that temepratures that are too high (for humans) or too low add to the overal Air Quality index along with Humidity and Gas concetrations.

The index is comprised of two parts, up to 25% is determined by Humidity levels and the remaining 75% by Gas concentrations. 

Humidity is universally accepted as being optimal when it is 40% within a reading range of 0 to 100%. At 40% humidity the index contribution will be 0%, but at a Humidity reading of 0%, the contribution increases to 25% and similarly at 100% it contributes 25% to the index. See Slide1 for details.

Gas concentrations for normal breathable air with no pollutants (no adverse gases) corresponds to the sensors highest output of 50,000 ohms or more. The sensor normally outputs a Gas resistance value ranging from a low of 50ohm to a high of 50,000ohm and beyond. A linear relationship is assumed and the output scaled accordingly between 0 and 75% for the range 50-50,000 ohms.

The result of combining humidity and gas indexes is a qualitative and so-called IAQ - Indoor Air Quality index value scaled from 0-100% (where 100% is good) and this is then scaled again from 0-500 where a 500 value is bad and descriptive values then applied in stages from good to hazardous air quality.

There is no definitive (ISO Standard) method for calculating an IAQ.

(c) d.l.bird 2018 all rights reserved and as per the Licence agreements listed in my software.

This IAQ and the ideas and concepts is Copyright (c) David Bird 2018. All rights to this IAQ and software are reserved.
 Any redistribution or reproduction of any part or all of the contents in any form is prohibited other than the following:
 1. You may print or download to a local hard disk extracts for your personal and non-commercial use only.
 2. You may copy the content to individual third parties for their personal use, but only if you acknowledge the author David Bird as the source of the material.
 3. You may not, except with my express written permission, distribute or commercially exploit the content.
 4. You may not transmit it or store it in any other website or other form of electronic retrieval system for commercial purposes.
The above copyright ('as annotated') notice and this permission notice shall be included in all copies or substantial portions of the IAQ index and Software and where the software use is visible to an end-user.
