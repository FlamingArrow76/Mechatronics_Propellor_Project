#include <Arduino.h>	//Arduino library to include basic C functions. 

class MOTOR	//Creates a class to store parameters for motor driver.
{		//Parameters are the pin used. 
 
 public:	//Public functions can be used by the class anytime.   
     
    MOTOR(int Pin1, int Pin2, int PinMW, int PinStandBy);
	//Function to set up the pins used.
	//These are used to change the inputs/outputs of each pin, which determines the behaviour of the motor.   

    void Spin(int Analog, float Time);
	//Function to get the motor spinning. 
	//Uses the private functions below to control direction. 
	//Takes analog value between 0-255, spins for 'Time' number of milliseconds. 

    void Halt(float Time);
	//Method to stop the motor, runs for 'Time' number of milliseconds. 

 private:	//Private functions can only be usd by the public functions. 
       int A01, A02, PWMA, STBY;  //Declares variables for functions (see .cpp file)
       void Up(int Analog);	  //Function to spin propellor to go up, takes analog input between 0-255. 
       void Down(int Analog);     //Function to spin propellor to go down, takes analog input between 0-255. 

};
