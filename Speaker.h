#include "mbed.h"
// new class to play a note on Speaker based on PwmOut class
class Speaker
{
public:
    Speaker(PinName pin) : _pin(pin) {
// _pin(pin) means pass pin to the Speaker Constructor
    }
// class method to play a note based on PwmOut class
    void PlayNote(float frequency, float duration, float volume) {
        _pin.period(1.0/frequency);
        _pin = volume/2.0;
        wait(duration);
        _pin = 0.0;
    }
 
private:
// sets up specified pin for PWM using PwmOut class 
    PwmOut _pin;
};
 
// Speaker test program - earlier euro police style siren now using new class method
//
// can also be used to play a song, if you have the notes and durations
// for musical note frequencies see http://en.wikipedia.org/wiki/Piano_key_frequencies