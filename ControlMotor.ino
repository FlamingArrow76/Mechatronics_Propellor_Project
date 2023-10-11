#include <MotorLib.h>       //Library containing motor functions. 
#define AIN1 2              //Gives each pin a name depending on what 
#define AIN2 4              //part of the motor controller they're connected to. 
#define PWMA 5
#define STBY 9

MOTOR Propellor = MOTOR(AIN1, AIN2, PWMA, STBY);  //Creates a MOTOR class called propellor 
                                                  //containing pin names of motor controller. 
void setup() {
  pinMode(13, OUTPUT);  //Turns on LED on arduino board.    
  Serial.begin(9600);   //Sets bit rate for serial plotter/monitor.
}

void loop() {
  int t = 15;               //Time to run each function is 15 milliseconds
  int Analog;               //Declares variable used in for loop.
    for (Analog=0;Analog<=255;Analog++)   //Increments Analog up to 255 from 0. 
    {
     Propellor.Spin(Analog,t);      //Uses analog to power the motor. 
     Serial.println(Analog);        //Prints analog to the screen
    }
    for (Analog=255;Analog>=-255;--Analog)  //Same for loop but goes from 255 to -255.
    {                                       //This makes the propellor go from full speed upwards
     Propellor.Spin(Analog,t);              //to full speed downwards. 
     Serial.println(Analog);        //Prints analog to the screen
    }   
    for (Analog=-255;Analog<=0;Analog++)  //For loop going from full speed downwards back to 0 speed. 
    {
     Propellor.Spin(Analog,t);
     Serial.println(Analog);      //Prints analog to the screen
    }
    Propellor.Halt(1000);     //Motor pauses for a second. 

}
