#include <TimerOne.h>

// Constants
const int frequencyPotPin = A1;  // Analog pin for frequency control potentiometer
const int dutyCyclePotPin = A0;  // Analog pin for duty cycle control potentiometer
const int outputPin = 9;         // Digital pin for the PWM output

// Variables
int frequencyPotValue = 0;    // Variable to store frequency potentiometer value
int dutyCyclePotValue = 0;    // Variable to store duty cycle potentiometer value
long frequency = 1000;        // Initial frequency in Hz
int dutyCycle = 511;          // Initial duty cycle (50% of 1023)
int frequencyPrev = 0;        // Previous frequency value for hysteresis
int dutyCyclePrev = 0;        // Previous duty cycle value for hysteresis
const int hysteresisRange = 10; // Hysteresis deadband range

void setup() {
  pinMode(outputPin, OUTPUT);
  Timer1.initialize(1000000 / frequency);  // Initialize Timer1 with the period in microseconds
  Timer1.pwm(outputPin, dutyCycle);        // Set initial PWM duty cycle
}

void loop() {
  // Read frequency potentiometer value with hysteresis
  int frequencyPotRead = analogRead(frequencyPotPin);
  if (abs(frequencyPotRead - frequencyPrev) > hysteresisRange) {
    frequencyPrev = frequencyPotRead;
    frequency = map(frequencyPotRead, 0, 1023, 50, 5000);  // Map potentiometer value to frequency range (50 Hz to 5000 Hz)
    Timer1.setPeriod(1000000 / frequency);  // Update Timer1 period based on the new frequency
  }

  // Read duty cycle potentiometer value with hysteresis
  int dutyCyclePotRead = analogRead(dutyCyclePotPin);
  if (abs(dutyCyclePotRead - dutyCyclePrev) > hysteresisRange) {
    dutyCyclePrev = dutyCyclePotRead;
    dutyCycle = dutyCyclePotRead;  // Map potentiometer value directly to duty cycle (0 to 1023)
    Timer1.pwm(outputPin, dutyCycle);  // Update PWM duty cycle
  }
}
