//RPP Helped by Copilot
//Arduino

unsigned long previous1 = millis(); // Timing for LED 1
unsigned long previous2 = millis(); // Timing for LED 2
unsigned long previous3 = millis(); // Timing for LED 3

bool state1 = false; // State for LED 1
bool state2 = false; // State for LED 2
bool state3 = false; // State for LED 3

void setup() {
  pinMode(13, OUTPUT); // LED 1
  pinMode(12, OUTPUT); // LED 2
  pinMode(11, OUTPUT); // LED 3
}

void loop() {
  unsigned long currentMillis = millis();

  // Control LED 1 (blinks every 500ms)
  if (currentMillis - previous1 >= 300) 
  {
    state1 = !state1; 
    digitalWrite(13, state1); 
    previous1 = currentMillis; 
  }

  // Control LED 2 (blinks every 2000ms)
  if (currentMillis - previous2 >= 2000) 
  {
    state2 = !state2; 
    digitalWrite(12, state2); 
    previous2 = currentMillis; 
  }
  // Control LED 3 (blinks every 1000ms)
  if (currentMillis - previous3 >= 1000) 
  {
    state3 = !state3;
    digitalWrite(11, state3);
    previous3 = currentMillis; 
  }
}