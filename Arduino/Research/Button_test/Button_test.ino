const int buttonPin = 2;     // the number of the button pin
int buttonState = 0;         // variable for reading the button status

void setup() 
{
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // starting serial communication
  Serial.begin(9600);
}

void loop() 
{
  // read the state of the button value:
  buttonState = digitalRead(buttonPin);
  
  // print the state of the button to the serial port
  Serial.print("buttonstate: ");
  Serial.println(buttonState);

  // delay for testing purposes, so the serial port
  // isn't spammed with messages
  delay(500);
}
