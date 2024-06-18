#include <PWM.h>

// Define the pins for the potentiometers
const int freqPotPin = A0;
const int dutyPotPin = A1;

// Use pin 9 on the Nano for this example
const int outputPin = 9; // the pin that the LED is attached to

// Frequency range (10-10000 Hz)
const int minFreq = 10;
const int maxFreq = 10000;

// Duty cycle range (0-65535 for pwmWriteHR())
const uint16_t minDutyCycle = 0;
const uint16_t maxDutyCycle = 65535;

void setup() {
  InitTimersSafe(); // Initialize all timers except for 0, to save time keeping functions
  Serial.begin(9600);

  // Set an initial frequency
  int initialFreq = map(analogRead(freqPotPin), 0, 1023, minFreq, maxFreq);
  SetPinFrequency(outputPin, initialFreq); // Set initial frequency

  // Print initial frequency
  Serial.print("Initial Frequency: ");
  Serial.print(initialFreq);
  Serial.println(" Hz");
}

void loop() {
  // Read the values from the potentiometers
  int freqPotValue = analogRead(freqPotPin);
  int dutyPotValue = analogRead(dutyPotPin);

  // Map the potentiometer values to the desired frequency range
  int freqInput = map(freqPotValue, 0, 1023, minFreq, maxFreq);

  // Map the potentiometer values to the desired duty cycle range
  uint16_t dutyCycleInput = map(dutyPotValue, 0, 1023, minDutyCycle, maxDutyCycle);

  // Set the frequency and duty cycle
  SetPinFrequency(outputPin, freqInput);
  pwmWriteHR(outputPin, dutyCycleInput);

  // Print the values for debugging
  Serial.print("FREQ: ");
  Serial.print(freqInput);
  Serial.print(" Hz, DUTY: ");
  Serial.print(dutyCycleInput);
  Serial.print(" (raw: ");
  Serial.print(dutyPotValue);  // Print raw potentiometer value for duty cycle
  Serial.println(")");

  // Add a small delay to avoid too frequent updates
  delay(1000);
}
