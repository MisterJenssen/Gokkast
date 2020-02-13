const int counterPin = 13;

void setup() 
{
  // initialize digital pin counterPin as an output.
  pinMode(counterPin, OUTPUT);
}

void loop() 
{
  // set counterPin output to high to change the number
  digitalWrite(counterPin, HIGH);
  // wait for a small amount of time to let the
  // mechanical parts move
  delay(10);
  // set counterPin output back to low
  digitalWrite(counterPin, LOW);
  // wait 2 seconds
  delay(2000);
}
