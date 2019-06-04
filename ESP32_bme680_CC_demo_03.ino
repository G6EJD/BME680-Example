/*
    Calculate IAQ indices scaled 0-100% (100% is excellent) and 0-500 where 0 is excellent and 500 Hazardous
    The index is a hybrid of humidity and adverse gas content. See the Redme for further detaisl of the index.

    This software, the ideas and concepts is Copyright (c) David Bird 2019. All rights to this software are reserved.

    Any redistribution or reproduction of any part or all of the contents in any form is prohibited other than the following:
    1. You may print or download to a local hard disk extracts for your personal and non-commercial use only.
    2. You may copy the content to individual third parties for their personal use, but only if you acknowledge the author David Bird as the source of the material.
    3. You may not, except with my express written permission, distribute or commercially exploit the content.
    4. You may not transmit it or store it in any other website or other form of electronic retrieval system for commercial purposes.

    The above copyright ('as annotated') notice and this permission notice shall be included in all copies or substantial portions of the Software and where the
    software use is visible to an end-user.

    THE SOFTWARE IS PROVIDED "AS IS" FOR PRIVATE USE ONLY, IT IS NOT FOR COMMERCIAL USE IN WHOLE OR PART OR CONCEPT. FOR PERSONAL USE IT IS SUPPLIED WITHOUT WARRANTY
    OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHOR OR COPYRIGHT HOLDER BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    See more at http://www.dsbird.org.uk
*/
/****************************************************************************
  This is a library for the BME680 gas, humidity, temperature & pressure sensor
  Designed specifically to work with the Adafruit BME680 Breakout
  ----> http://www.adafruit.com/products/XXXX
  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C

float hum_weighting = 0.25; // so hum effect is 25% of the total air quality score
float gas_weighting = 0.75; // so gas effect is 75% of the total air quality score

int   humidity_score, gas_score;
float gas_reference = 2500;
float hum_reference = 40;
int   getgasreference_count = 0;
int   gas_lower_limit = 10000;  // Bad air quality limit
int   gas_upper_limit = 300000; // Good air quality limit

void setup() {
  Serial.begin(115200);
  Serial.println(F("BME680 test"));
  Wire.begin();
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  } else Serial.println("Found a sensor");

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320°C for 150 ms
  // Now run the sensor to normalise the readings, then use combination of relative humidity and gas resistance to estimate indoor air quality as a percentage.
  // The sensor takes ~30-mins to fully stabilise
  GetGasReference();
}

void loop() {
  Serial.println("Sensor Readings:");
  Serial.println("  Temperature = " + String(bme.readTemperature(), 2)     + "°C");
  Serial.println("     Pressure = " + String(bme.readPressure() / 100.0F) + " hPa");
  Serial.println("     Humidity = " + String(bme.readHumidity(), 1)        + "%");
  Serial.println("          Gas = " + String(gas_reference)               + " ohms\n");
  Serial.print("Qualitative Air Quality Index ");

  humidity_score = GetHumidityScore();
  gas_score      = GetGasScore();

  //Combine results for the final IAQ index value (0-100% where 100% is good quality air)
  float air_quality_score = humidity_score + gas_score;
  Serial.println(" comprised of " + String(humidity_score) + "% Humidity and " + String(gas_score) + "% Gas");
  if ((getgasreference_count++) % 5 == 0) GetGasReference();
  Serial.println(CalculateIAQ(air_quality_score));
  Serial.println("--------------------------------------------------------------");
  delay(2000);
}

void GetGasReference() {
  // Now run the sensor for a burn-in period, then use combination of relative humidity and gas resistance to estimate indoor air quality as a percentage.
  //Serial.println("Getting a new gas reference value");
  int readings = 10;
  for (int i = 1; i <= readings; i++) { // read gas for 10 x 0.150mS = 1.5secs
    gas_reference += bme.readGas();
  }
  gas_reference = gas_reference / readings;
  //Serial.println("Gas Reference = "+String(gas_reference,3));
}

String CalculateIAQ(int score) {
  String IAQ_text = "air quality is ";
  score = (100 - score) * 5;
  if      (score >= 301)                  IAQ_text += "Hazardous";
  else if (score >= 201 && score <= 300 ) IAQ_text += "Very Unhealthy";
  else if (score >= 176 && score <= 200 ) IAQ_text += "Unhealthy";
  else if (score >= 151 && score <= 175 ) IAQ_text += "Unhealthy for Sensitive Groups";
  else if (score >=  51 && score <= 150 ) IAQ_text += "Moderate";
  else if (score >=  00 && score <=  50 ) IAQ_text += "Good";
  Serial.print("IAQ Score = " + String(score) + ", ");
  return IAQ_text;
}

int GetHumidityScore() {  //Calculate humidity contribution to IAQ index
  float current_humidity = bme.readHumidity();
  if (current_humidity >= 38 && current_humidity <= 42) // Humidity +/-5% around optimum
    humidity_score = 0.25 * 100;
  else
  { // Humidity is sub-optimal
    if (current_humidity < 38)
      humidity_score = 0.25 / hum_reference * current_humidity * 100;
    else
    {
      humidity_score = ((-0.25 / (100 - hum_reference) * current_humidity) + 0.416666) * 100;
    }
  }
  return humidity_score;
}

int GetGasScore() {
  //Calculate gas contribution to IAQ index
  gas_score = (0.75 / (gas_upper_limit - gas_lower_limit) * gas_reference - (gas_lower_limit * (0.75 / (gas_upper_limit - gas_lower_limit)))) * 100.00;
  if (gas_score > 75) gas_score = 75; // Sometimes gas readings can go outside of expected scale maximum
  if (gas_score <  0) gas_score = 0;  // Sometimes gas readings can go outside of expected scale minimum
  return gas_score;
}
