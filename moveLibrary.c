/* Moves the robot forward a specified distance at a specified motor speed
 * Uses encoders to monitor rotations and circumference of tire to
 * calculate the number of rolls to cover the distance.
 * @param distanceCM - the distance in cm to move.
 * @param motorSpeed - the motor speed, 0 - 100.Negative for reverse.
 * @author Alexis Barltrop
 */
void moveDistance(int distanceCM,int motorSpeed)
	{
		float noRotations = ((float)distanceCM)/(17.6);
		nMotorEncoder[motorB] = 0;
		nMotorEncoder[motorC] = 0;
		while (nMotorEncoder[motorB]<(noRotations*360)){
		motor[motorB]=motorSpeed;
		motor[motorC]=motorSpeed;
		}
	}

	/* Rotates the robot clockwise x number of degrees.
	*  Keeps one wheel still and moves the other to action rotation
	*  Has related function turnAntiClockwise
	*  @param turndegree - the number of degrees to rotate the robot sideways
	*  @author	Alexis Barltrop
	*/
	void turnClockwise(int turndegree)
	{
	int ticksPerQuarterTurn = 160;
	int noEncoderTicks = ((float)turndegree/90)*ticksPerQuarterTurn;

		nMotorEncoder[motorB] = 0;
		nMotorEncoder[motorC] = 0;
		while(nMotorEncoder[motorB]<noEncoderTicks&&nMotorEncoder[motorC]>-noEncoderTicks)
		{
			motor[motorB] = 50;
			motor[motorC]= -50;
		}
	motor[motorB] = 0;
	motor[motorC] = 0;

	}

	/* Rotates the robot anticlockwise x number of degrees.
	*  Keeps one wheel still and moves the other to action rotation
	*  Has related function turnClockwise
	*  @param turndegree - the number of degrees to rotate the robot
	*  @author	Alexis Barltrop
	*/
	void turnAntiClockwise(int turndegree)
	{
		int ticksPerQuarterTurn = 160;
	int noEncoderTicks = ((float)turndegree/90)*ticksPerQuarterTurn;

		nMotorEncoder[motorB] = 0;
		nMotorEncoder[motorC] = 0;
		while(nMotorEncoder[motorC]<noEncoderTicks&&nMotorEncoder[motorB]>-noEncoderTicks)
		{
			motor[motorB] = -50;
			motor[motorC]= 50;
		}
	motor[motorB] = 0;
	motor[motorC] = 0;
	}
