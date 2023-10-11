#include <MPU6050_tockn.h>  //Libraries to find angle from IMU.
#include <Wire.h>           
#include <MotorLib.h>       //Library containing motor functions. 

MPU6050 mpu6050(Wire);      
#define AIN1 2              //Gives each pin a name depending on what 
#define AIN2 4              //part of the motor controller they're connected to. 
#define PWMA 5
#define STBY 9

const float KP = 0.22;      //Constants used for PID control. 
const float KI = 0.1;
const float KD = 0.12;
int PrevError = 0;           //Initially declares the previous error to be 0 (used in D). 

MOTOR Propellor = MOTOR(AIN1, AIN2, PWMA, STBY);  //Creates a MOTOR class called propellor 
                                                  //containing pin names of motor controller. 
void setup() {
  pinMode(13, OUTPUT);            //Turns on LED on arduino board. 
  Serial.begin(9600);             //Sets bit rate for serial plotter/monitor. 
  Wire.begin();                   
  mpu6050.begin();                //Sets up IMU.
  mpu6050.calcGyroOffsets(true);  //Finds the starting angle of the IMU. 
}

void loop() {
  mpu6050.update();               //Updates the position fo the IMU.
  int DesiredAngle = 0;           //Declares the angle to hover at to be 0. 
  float Angle = (mpu6050.getAngleX()) + 5; //Replaces AngleX with the new value. Has a bias of
                                            // +6 to offset the way the IMU being attached to the frame. 
  Serial.print("Angle : ");     
  Serial.println(Angle);         //Prints the angle to the serial monitor. 
  
//  delay(10);                    //Cause a short delay used in ID calculations.
  float TimeBetween = 0.01;     //TimeBetween represented in decimal form. 
  
  double Error = DesiredAngle - Angle;       //Calculates the difference between where the motor is and where it should be: the error. 
  //All terms are doubles to include negative signs. 
  double P = Error * KP;                               //Calculates P term.
  double SumError = SumError + (Error * TimeBetween);   //Calculates the sum of previous errors
  double I = SumError * KI;                             //Calculates I term.
  double D = ((Error - PrevError) / TimeBetween) * KD;  //Calculates D term.
    
  double Analog = P + I + D;            //Adds them together, PWM.
  PrevError = Error;                    //Current error becomes the previous error.
    
  float percent = 0.97;      
  float n = percent * 255;        //The base analog signal required to support the motor. 
  n = n + Analog;                 //The PID constants are added on top to change the power outputted by the motor.
  if (n > 255)
  { 
    n = 255;                      //Analog has a limit of 255 so anything greater is capped at 255. 
  }
  int t = 10;               
  Propellor.Spin(n,t);            //Spins the propellor upwards for 10 (t) milliseconds. 

  if (Angle < DesiredAngle)      //If propellor is too low, turn on the boards LED. 
  {
    digitalWrite(13,HIGH);
  }
  if (Angle > DesiredAngle)      //If propellor is too high, turn off the boards LED.
  {
    digitalWrite(13,LOW);
  }
}
