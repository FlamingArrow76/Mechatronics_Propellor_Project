#include <MotorLib.h>	//Uses the corresponding header file which creates the class used to define the following functions. 

MOTOR::MOTOR(int Pin1, int Pin2, int PinWM, int PinStandBy)	//Declares MOTOR class with pin numbers. 
{	
  A01 = Pin1; 		//Sets the following variables to be equal to the current state of the pins. 
  A02 = Pin2;		//Named after the pins used on the motor controller. 
  PWMA = PinWM;
  STBY = PinStandBy;

  pinMode(A01, OUTPUT);		//Turns all necessary pins on the controller to be outputs. 
  pinMode(A02, OUTPUT);		//This allows them to be set high/low. 
  pinMode(PWMA, OUTPUT);
  pinMode(STBY, OUTPUT);
}

void MOTOR::Spin(int Analog, float Time)	//Function that makes the motor rotate. Takes an analog input between 0-255 
{						//and a time in milliseconds that the motor will run for. 
  digitalWrite(STBY, HIGH);		//Sets the standby pin to be high. 
  if (Analog >= 0)			
  {
  Up(Analog);  			//A positive input will cause the propellor to go up. 
  }
  else
  {
  Down(-Analog);		//A negative input will cause the propellor to go down. 
  }
  delay(Time);			//Cause a delay using 'time'. 
}

void MOTOR::Halt(float Time)	//Function to make motor stop, takes time input.
{
  digitalWrite(A01, HIGH);	//Sets both pins to be HIGH
  digitalWrite(A02, HIGH);	
  analogWrite(PWMA,0);		//Gives analog signal of 0, motor won't move. 
  delay(Time);			//Runs for 'time' milliseconds. 
}

void MOTOR::Up(int Analog)	//Private function used by Spin() to make propellor go up, takes analog input. 
{
  digitalWrite(A01, LOW);	//Sets pins 1 and 2 high/low to control direction. 
  digitalWrite(A02, HIGH);
  analogWrite(PWMA, Analog);	//Gives analog signal to set speed. 
}


void MOTOR::Down(int Analog)	//Same as Up but states of pins A01 and A02 are reversed to change direction. 
{
  digitalWrite(A01, HIGH);
  digitalWrite(A02, LOW);
  analogWrite(PWMA, Analog);
}
