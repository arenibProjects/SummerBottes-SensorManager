#include "SensorManager.hpp"
#include <Arduino.h>

SensorManager* sensorManager;

void setup (){
  sensorManager = new SensorManager();
  sensorManager->registerNewSensor(A1, SHARP);
  Serial.begin(9600);
}

int tmp = 0;
void loop (){
  // Je fait du lissage
  tmp = (sensorManager->readSensorData(A1) + tmp)/2;
  Serial.println(tmp);
  delay(50);
}
