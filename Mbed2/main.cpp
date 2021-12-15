//File offers bluetooth feature to turn on and off cooling fan. 

#include "mbed.h"
#include "rtos.h"
#include "Motor.h"
#include <stdio.h>

//Wiring:
//NEOLED: + to 5V, G to GND, In to Pin 5
//LCD: 5V to 5V, RX to Pin14, TX to Pin13, GND to GND, RES to PIN29
//Barrel Jack: Closet to input(on left) to GND on MotorDriver. Furthest Away to PWMA on Power Driver. 
//Right side MotorDriver: GND to Bottom Barrel Jack, PWMB to Pin22, BIN2 to Pin17, BIN1 to PIN18, STBY to VCC, AIN1 to PIN19, AIN2 to PIN20,PWMA to Pin21.
//Left Side MotorDriver: GND to GND, BO1 to RED1, BO2 to BLACK1, AO2 to BLACK2, AO1 to RED2, VCC to VCC, VM to Top Barrel JAck. 


DigitalOut shdn(p26); // TOF distance sensor
//I2C sensor pins
#define VL53L0_I2C_SDA   p28
#define VL53L0_I2C_SCL   p27

// This must be an SPI MOSI pin.
#define DATA_PIN p5   //Neopixel

DigitalOut myled(LED1);
Mutex uLCD_mutex;
Serial blue(p9,p10);
Serial pc(USBTX,USBRX);                                 //Not used in this program

Motor m1(p21, p19, p20); // pwm, fwd, rev
Motor m2(p22, p18, p17); // pwm, fwd, rev
float speed =1.0f;  //For controlling fan speed.
bool doorstatus = false;
Semaphore one_slot(1);


//Setup a new class for TMP36 sensor 
class TMP36 
{ 
public: 
    TMP36(PinName pin); 
    TMP36(); 
    float read(); 
private: 
//class sets up the AnalogIn pin 
    AnalogIn _pin; 
}; 
  
TMP36::TMP36(PinName pin) : _pin(pin) {} //This is an initializer list ... more to come in class  
// _pin(pin) means pass pin to the AnalogIn constructor  
  
float TMP36::read() 
{ 
//convert sensor reading to temperature in degrees C 
    return ((_pin.read()*3.3)-0.500)*100.0; 
//read() function returns a normalized value of the voltage from 0 to 1 as a float 
} 
 
//instantiate new class to set p15 to analog input  
//to read and convert TMP36 sensor's voltage output 
 
TMP36 myTMP36(p15); 

void stopfan(void const *args)
{
    char bnum=0;
    while(true) {
        uLCD_mutex.lock();
        if (blue.getc()=='!') {
            if (blue.getc()=='B') { //button data packet
                bnum = blue.getc(); //button number { //checksum OK?
                if((bnum == '1')) {
                    speed =0;
                }
            }
        }
        uLCD_mutex.unlock();
        Thread::wait(.1*1000);
    }
}

void startfan(void const *args)
{
    char bnum=0;
    while(true) {
        uLCD_mutex.lock();
        if (blue.getc()=='!') {
            if (blue.getc()=='B') { //button data packet
                bnum = blue.getc(); //button number { //checksum OK?
                if((bnum == '2')) {
                    speed =1.0f;
                }
            }
        }
        uLCD_mutex.unlock();
        Thread::wait(.1*1000);
    }
}



int main()
{
 
    
      Thread thread1(stopfan);
      Thread thread2(startfan);



    while(1) {
        m1.speed(speed);
        
        myled = 1;
        Thread::wait(1000.0*0.2);
        myled = 0;
        Thread::wait(1000.0*0.2);
    }
}

