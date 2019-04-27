#include "SensorManager.hpp"

SensorManager::SensorManager(){
   __IdToType = (unsigned char *)malloc((size_t)(SENSOR_MANAGER_TAB_SIZE*sizeof(unsigned char)));
   for (unsigned char i = 0; i<SENSOR_MANAGER_TAB_SIZE; i++){
      __IdToType[i] = 0;
   }
}

void SensorManager::registerNewSensor(unsigned char pinId, SensorType type){
	__IdToType[pinId] = type;
}

double SensorManager::readSensorData(unsigned char pinId){
  int IRvalue = this->readRawSensorData(pinId, DEFAULTPRECISIONLEVEL);
  double voltage = 3.3*(IRvalue/1024.0);

   // If voltage out of bounds
  if(voltage > 2.7)
    voltage = 2.7;
  if(voltage < 0.2)
    voltage = 0.2;

  double r = (voltage*0.0415 - 0.00375); // formula randomly found by experiments :)
  double measuredDistance = ((1.0/r) - 0.42)*10;

  return measuredDistance;
}

int SensorManager::readRawSensorData(unsigned char pinId, unsigned char measureCount){
	if (__IdToType[pinId] == SHARP){
    int sum = 0;
    for(unsigned char i = 0; i<measureCount; i++){
			sum += analogRead(pinId);
      delay(3);
    }
    return (int) (sum/((1.0)*measureCount));
	}else if(__IdToType[pinId] == LASER_CLASS_2){
    return digitalRead(pinId);
  }
	return 0;

}

bool SensorManager::detectObject(unsigned char pinId, double thresholdDistance){
  if (__IdToType[pinId] == SHARP){
    double measuredDistance = this->readSensorData(pinId);

    if(measuredDistance < thresholdDistance)
      return true;
    else
      return false;

  }

  return false;
}
