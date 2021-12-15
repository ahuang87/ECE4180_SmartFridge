#include "mbed.h"  //
#include "uLCD_4DGL.h" //
#include "Motor.h" //
#include "neopixel.h"
#include <ctime>            //SRAND Random Seed Generator. 
#include "Speaker.h"        //Spekaer

#include "XNucleo53L0A1.h"
#include <stdio.h>

#define I 0x008000 //GREEN
#define _ 0x000000 //BLACK

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

Serial pc(USBTX,USBRX);                                 //Not used in this program


 
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
//Right side MotorDriver: GND to Bottom Barrel Jack, PWMB to Pin22, BIN2 to Pin17, BIN1 to PIN18, STBY to VCC, AIN1 to PIN19, AIN2 to PIN20,PWMA to Pin21.
//Left Side MotorDriver: GND to GND, BO1 to RED1, BO2 to BLACK1, AO2 to BLACK2, AO1 to RED2, VCC to VCC, VM to Top Barrel JAck. 
Motor m1(p21, p19, p20); // pwm(PWMA), fwd(AIN1), rev(AIN2)
Motor m2(p22, p18, p17); // pwm(PWMB), fwd, rev
//Speaker mySpeaker(p23);

static XNucleo53L0A1 *board=NULL;
uLCD_4DGL uLCD(p13, p14, p29);                      //uLCD delcaration
 
int main()
{
    Speaker mySpeaker(p23);
    bool doorstatus = false;
    bool playsound = false; 
    int status;
    uint32_t distance;
    DevI2C *device_i2c = new DevI2C(VL53L0_I2C_SDA, VL53L0_I2C_SCL);
    /* creates the 53L0A1 expansion board singleton obj */
    board = XNucleo53L0A1::instance(device_i2c, A2, D8, D2);
    shdn = 0; //must reset sensor for an mbed reset to work
    wait(0.1);
    shdn = 1;
    wait(0.1);
    /* init the 53L0A1 board with default values */
    status = board->init_board();
    while (status) {
        pc.printf("Failed to init board! \r\n");
        status = board->init_board();
    }
    
    uLCD.color(WHITE);
    uLCD.locate(1,15);
    uLCD.printf("Door Closed!!");
    
    
    
    time_t startTime;                                   //Start time for timerbar
    startTime = time(0);
    time_t timeElapsed = time(0)-startTime;             //Elpased time for timerbar
    uLCD.filled_rectangle(0, 0, 127, 2, I);             //Timerbar delcaration.
    
    bool soundoff = false;
    
    //loop taking and printing distance
    while (1) {
        
        m1.speed(1.0);
        //m2.speed(1.0); //fan dont work
        
        //Temp Reading:
        float tempC, tempF; 
        tempC = myTMP36.read(); 
        //convert to degrees F 
        tempF = (9.0*tempC)/5.0 + 32.0; 
        //print current temp 
        uLCD.color(WHITE);
        uLCD.locate(1,1);
        uLCD.printf("%5.2f C %5.2f F \n\r", tempC, tempF);
        wait(.1);
        uLCD.color(BLACK); 
        uLCD.locate(1,1);
        uLCD.printf("%5.2f C %5.2f F \n\r", tempC, tempF);
        wait(0.1);
        
       
        
        if (distance > 130)
        {
            
        
            uLCD.cls();
            uLCD.color(WHITE);
            uLCD.locate(1,15);
            uLCD.printf("Door Open!!");
            wait(0.5  );
            uLCD.cls();
            DigitalIn(DATA_PIN, PullDown);
            // An alternative is to connect an external pull-down resistor.
            DigitalIn(DATA_PIN, PullDown);
            // The pixel array control class.
            neopixel::PixelArray array(DATA_PIN);
            // Declare array/buffer of type Pixel.
            uint16_t numPixels = 6;
            neopixel::Pixel pixels[numPixels];
            // Use buffer method of updating pixels.
            pixels[0].red = 255;
            pixels[0].green = 255;
            pixels[0].blue = 255;
    
            pixels[1].red = 255;
            pixels[1].green = 255;
            pixels[1].blue = 255;
    
            pixels[2].red = 255;
            pixels[2].green = 255;
            pixels[2].blue = 255;
    
            pixels[3].red = 255;
            pixels[3].green = 255;
            pixels[3].blue = 255;
    
            pixels[4].red = 255;
            pixels[4].green = 255;
            pixels[4].blue = 255;
    
            pixels[5].red = 255;
            pixels[5].green = 255;
            pixels[5].blue = 255;
    
            pixels[6].red = 255;
            pixels[6].green = 255;
            pixels[6].blue = 255;
            
            array.update(pixels, numPixels); // led lighting       
            doorstatus = true; 
            playsound=true;
       
            
        }
        
        status = board->sensor_centre->get_distance(&distance);
        if (status == VL53L0X_ERROR_NONE) {
            pc.printf("D=%ld mm\r\n", distance);
        }
 
        //LCD status showing door closed.
        if ((doorstatus == true) && (distance < 130))
            {
                uLCD.cls();
                uLCD.color(WHITE);
                uLCD.locate(1,15);
                uLCD.printf("Door Closed!!");
                doorstatus = false;
            }
        if ((playsound == true) && (distance > 130) && (soundoff ==false))
            {
                mySpeaker.PlayNote(500.0, 0.5, 0.5);
                playsound= false; 
                soundoff = true;
                
            }
            
            
        //turns Lights Off
        if ((distance < 130) && (doorstatus ==false))
        {
            
            DigitalIn(DATA_PIN, PullDown);
            // An alternative is to connect an external pull-down resistor.
            DigitalIn(DATA_PIN, PullDown);
            // The pixel array control class.
            neopixel::PixelArray array(DATA_PIN);
            // Declare array/buffer of type Pixel.
            uint16_t numPixels = 6;
            neopixel::Pixel pixels[numPixels];
            // Use buffer method of updating pixels.
            pixels[0].red = 0;
            pixels[0].green = 0;
            pixels[0].blue = 0;
    
            pixels[1].red = 0;
            pixels[1].green = 0;
            pixels[1].blue = 0;
    
            pixels[2].red = 0;
            pixels[2].green = 0;
            pixels[2].blue = 0;
    
            pixels[3].red = 0;
            pixels[3].green = 0;
            pixels[3].blue = 0;
    
            pixels[4].red = 0;
            pixels[4].green = 0;
            pixels[4].blue = 0;
    
            pixels[5].red = 0;
            pixels[5].green = 0;
            pixels[5].blue = 0;
    
            pixels[6].red = 0;
            pixels[6].green = 0;
            pixels[6].blue = 0;
            
            array.update(pixels, numPixels); // led lighting   
            soundoff = false; 
        }
      
    }     
}