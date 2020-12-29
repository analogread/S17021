//https://github.com/adafruit/Adafruit_Si7021#include "Adafruit_Si7021.h"
#include "Adafruit_Si7021.h"
#define LED 3
float Humidity;
float Temperature;
bool enableHeater = false;
uint8_t loopCnt = 0;

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Si7021 test!");

  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true);
  }

  Serial.print("Found model ");
  switch (sensor.getModel()) {
    case SI_Engineering_Samples:
      Serial.print("SI engineering samples"); break;
    case SI_7013:
      Serial.print("Si7013"); break;
    case SI_7020:
      Serial.print("Si7020"); break;
    case SI_7021:
      Serial.print("Si7021"); break;
    case SI_UNKNOWN:
    default:
      Serial.print("Unknown");
  }
  Serial.print(" Rev(");
  Serial.print(sensor.getRevision());
  Serial.print(")");
  Serial.print(" Serial #"); Serial.print(sensor.sernum_a, HEX); Serial.println(sensor.sernum_b, HEX);
}

void loop() {
  Humidity = sensor.readHumidity();
  Temperature = sensor.readTemperature();

  Serial.print("Humidity:    ");
  Serial.print(Humidity);
  Serial.print("\tTemperature: ");
  Serial.print(Temperature);


  if(Temperature >=35){
    digitalWrite(LED,HIGH);
    Serial.print(" :เปิดไฟ \n");
    }
  else{
    digitalWrite(LED,LOW);
    Serial.print(" :ปิดไฟ \n");
    }
  delay(250);

  // Toggle heater enabled state every 30 seconds
  // An ~1.8 degC temperature increase can be noted when heater is enabled
  if (++loopCnt == 30) {
    enableHeater = !enableHeater;
    sensor.heater(enableHeater);
    Serial.print("Heater Enabled State: ");
    if (sensor.isHeaterEnabled()) {
      Serial.print("ENABLED ( ");
      Serial.print(enableHeater);
      Serial.print(" )\n");

    }
    else {
      Serial.print("DISABLED ( ");
      Serial.print(enableHeater);
      Serial.print(" )\n");
      loopCnt = 0;

    }
  }


}
