void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);   
  // wait for 2 seconds
  delay(2000);           
  // turn the LED off by making the voltage LOW            
  digitalWrite(LED_BUILTIN, LOW);    
  // wait for 2 seconds
  delay(2000);                       
}
