/* 	Moves the robot forward a specified distance at a specified motor speed.
* 	Each full rotation of the wheel moves the robot roughly 17.6 cm.
* 	Motor encoders monitor the rotations and hence the distance to move.
* 	@param distanceCM - the distance in cm to move.
* 	@param motorSpeed - the motor speed, 0 - 100.Negative for reverse.
* 	@author Alexis Barltrop
*/
void moveDistance(int distanceCM,int motorSpeed){
	float distancePerRotation = 17.6; // distance in cm.
	float noRotations = ((float)distanceCM)/(distancePerRotation);
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[rightMotor] = 0;
	while (abs(nMotorEncoder[leftMotor])<(noRotations*360)){
		motor[leftMotor] = motorSpeed;
		motor[rightMotor] = motorSpeed;
	}
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

/* 	Rotates the robot clockwise.
*  	Wheels move in opposite direction so that the robot turns on the spot.
*  	Number of ticks per degree callibrated with 90 degree turn.
*  	Has related function turnAntiClockwise.
*  	@param turndegree - the number of degrees to rotate the robot sideways
*  	@author Alexis Barltrop
*/
void turnClockwise(int turndegree){
	float ticksPerDegree = ((float)160)/90;
	int noEncoderTicks = ((float)turndegree)*ticksPerDegree;
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;

	while(nMotorEncoder[leftMotor]<noEncoderTicks&&nMotorEncoder[rightMotor]>-noEncoderTicks){
		motor[leftMotor] = 50;
		motor[rightMotor]= -50;
	}
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

/* 	Rotates the robot anticlockwise.
*  	See related function turnClockwise.
*  	@param turndegree - the number of degrees to rotate the robot
*  	@author Alexis Barltrop
*/
void turnAntiClockwise(int turndegree){
	float ticksPerDegree = 160/90;
	int noEncoderTicks = ((float)turndegree) / ticksPerDegree;
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
	// setMotorSyncEncoder(leftTouchSensor, rightTouchSensor, 1, noEncoderTicks, -1);

	while(nMotorEncoder[rightMotor]<noEncoderTicks&&nMotorEncoder[leftMotor]>-noEncoderTicks){
		motor[leftMotor] = -50;
		motor[rightMotor]= 50;
	}
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

/* 	Correct Direction Method for Sonar
* 	Method for Sonar Detection Direction Correction.
* 	Rotates robot in steps of 30 degrees, taking a distance measurement
* 	with the sonar sensor at each step.
* 	Rotates to face the closest object based on these measurements.
*/
void correctDirection(){
	// Creates array containing distance measurments.
	int rotate = 0;
	int count = 0;
	int step = 30;
	int size = 360/step;
	int distanceArray[12];
	while (rotate < 360){
		turnClockwise(step);
		wait1Msec(100);
		distanceArray[count]= SensorValue[sonarSensor];
		wait1Msec(100);
		rotate =rotate+step;
		count++;
	}
	turnClockwise(step);

	// Finds location of minimum distance in array.
	int minimumDistance;
	int location = 0;
	minimumDistance = distanceArray[0];
	for ( int i = 1 ; i <size ; i++ ){
		if ( distanceArray[i] < minimumDistance ){
			minimumDistance = distanceArray[i];
			location = i;
		}
	}

	// Creates array containing turning directions.
	int directionArray[12];
	for (int i = 0; i<(size); i++) {
		directionArray[i] = 0 + (i*step);
	}

	// Turns to face closest object.
	int rotationError = 10;
	turnClockwise(directionArray[location]+rotationError);
}

/**
* Mathematical equation used for line correction.
* See comments for task PathCorrectionAlongBlackAndWhiteTiles.
* Equation is an absolute function designed to have a maximum of one,
* and to intercept the x-axis at the WHITETHRESHOLD and BLACKTHRESHOLD.
* @author Alexis Barltrop
*/
float magicFunction(){
	int xShift = (BLACKTHRESHOLD+WHITETHRESHOLD)/2;
	int slope = xShift-BLACKTHRESHOLD;
	float y = 1 - (abs((float)(SensorValue[colorSensor] - xShift) / slope));
	return y;
}

/**
* Used to turn 90 degrees after tile count in part one is complete.
* Reuses the mathematical function from path correction to determine if,
* and how much the robot is on the grey line.
* Should rotate slighty more if on grey, less if on black or white tile.
*/
void turnNinetyCorrectly(){
	turnClockwise(90+30*magicFunction());
}

/**
* Following functions return true if sensor is reading values corresponding to the relevant tile.
* WHITETHRESHOLD and BLACKTHRESHOLD are declared before main task in program file.
*/
bool isWhite(){
	return (SensorValue[colorSensor]> WHITETHRESHOLD);
}

bool isBlack(){
	return (SensorValue[colorSensor]< BLACKTHRESHOLD);
}

bool isGrey(){
	return (SensorValue(colorSensor) > BLACKTHRESHOLD && SensorValue(colorSensor) < WHITETHRESHOLD);
}

bool isBlackOrWhite(){
	return (SensorValue(colorSensor) < BLACKTHRESHOLD || SensorValue(colorSensor) > WHITETHRESHOLD);
}
