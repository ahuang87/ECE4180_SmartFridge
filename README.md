# ECE4180_SmartFridge
# Smart Fridge Prototype 
# Created by: Andy Huang, Aman Patel


#Description: 
This project is a smart fridge prototype. This smart fridge prototype was created using a small 13-inch toolbox which models a fridge with its opening door, this small toolbox also allows users to store things inside it like a fridge would. The smart fridge prototype uses two brushless dc fan to provide cooling. Located inside the smart fridge is a temperature sensor which reads temperature readings and displays it live to an lcd screen located on the outside of the smart fridge door. This feature lets the user know what the given temperature inside the fridge is.   

#Video Demo:

Link: 


#Components: 

mbed NXP LPC1768

uLCD-144-G2 

Breakout Boards (x3)

Pololu md08a Motor Driver

Temperature Sensor - TMP36

Gdt Brushless DC Fan (x2)

DC Barrel Power Jack/Connector

5V Power Supply

13-Inch Toolbox

RGB Smart Neopixel (x6)

VL53LOX ToF Distance Sensor




#Wiring:

NEOPIXEL: + to 5V, G to GND, In to Pin 5

LCD: 5V to 5V, RX to Pin14, TX to Pin13, GND to GND, RES to PIN29

Barrel Jack: Closet to input(on left) to GND on MotorDriver. Furthest Away to PWMA on Power Driver.

Right side MotorDriver: GND to Bottom Barrel Jack, PWMB to Pin22, BIN2 to Pin17, BIN1 to PIN18, STBY to VCC, AIN1 to PIN19, AIN2 to PIN20,PWMA to Pin21.

Left Side MotorDriver: GND to GND, BO1 to RED1, BO2 to BLACK1, AO2 to BLACK2, AO1 to RED2, VCC to VCC, VM to Top Barrel Jack. 


#Check Code to Try Smart Fridge Demo: 
