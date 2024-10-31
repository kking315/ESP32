int LED_BUILTIN[] = {5,17,16,4,0};
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  for(int i=0;i<5;i++)
    pinMode(LED_BUILTIN[i], OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for(int i=0;i<5;i++){
    digitalWrite(LED_BUILTIN[i], HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(100);                      // wait for a second
    digitalWrite(LED_BUILTIN[i], LOW);   // turn the LED off by making the voltage LOW
    //delay(100);                      // wait for a second
  }
}
