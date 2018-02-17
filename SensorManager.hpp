#ifndef PINCE
#define PINCE 1
#define SHARP ((unsigned char)1)

#include <Arduino.h>

class SensorManager{
	public:
 
   /**
    * The default constructor
    */
   SensorManager();
   
   /**
    * The advanced constructor
    */
   SensorManager(unsigned char inputPinMin, unsigned char inputPinMax);
   
	 /**
	  * Create a normalised var type SensorType
	  */
	 typedef unsigned char SensorType;
	
	 /**
	  * Register a new sensor
	  */
	 void registerNewSensor(unsigned char id, SensorType type);
	 
	 /**
	  * Return the output of the specified sensor with the default precision level
	  */
	 int readSensorData(unsigned char id);
   
   /**
    * Return the average value of the last <measureCount> output of the specified sensor 
    */
   int readSensorData(unsigned char id, unsigned char measureCount);
	 
	private:	//private stuff; don't try to modifie this! x)
   unsigned char *__IdToType;
};

#endif
