#include "SensorManager.hpp"

SensorManager::SensorManager(){
   __IdToType = (unsigned char *)malloc((size_t)(8*sizeof(unsigned char)));
   for (unsigned char i = 0; i<8; i++){
      __IdToType[i] = 0;
   }
}

void SensorManager::registerNewSensor(unsigned char pinId, SensorType type){
	__IdToType[pinId] = type;
}

int SensorManager::readSensorData(unsigned char pinId){
  return this->readSensorData(pinId, 30);
}

int SensorManager::readSensorData(unsigned char pinId, unsigned char measureCount){
	if (__IdToType[pinId] == SHARP){
    int sum = 0;
    for(unsigned char i = 0; i<measureCount; i++){
			sum += analogRead(pinId);
    }
    return (int)sum/measureCount;
	}
	return 0;
	
}

bool SensorManager::detectObject(unsigned char pinId, double thresholdDistance){
  if (__IdToType[pinId] == SHARP){
    int IRvalue = this->readSensorData(pinId);
    
    if(IRvalue < 10)
      IRvalue = 10;
    
    double measuredDistance = ((67870.0 / (IRvalue - 3.0)) - 40.0); // formula randomly found on the net

    if(measuredDistance < thresholdDistance)
      return true;
    else
      return false;
    
  }

  return false;
}

