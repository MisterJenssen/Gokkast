const int buttonPin = 2;     // the number of the button pin
const int lightPin =  13;    // the number of the light pin

int buttonState = 0;         // variable for reading the pushbutton status

void setup() 
{
  // initialize the light pin as an output:
  pinMode(lightPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // starting serial communication
  Serial.begin(9600);
}

void loop() 
{
  // read the state of the button value:
  buttonState = digitalRead(buttonPin);

  // check if the button is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) 
  {
    // turn light on:
    digitalWrite(lightPin, HIGH);    
  } 
  else 
  {
    // turn light off:
    digitalWrite(lightPin, LOW);
  }

  // print the state of the button to the serial port
  Serial.print("buttonstate: ");
  Serial.println(buttonState);
  
  // delay for testing purposes, so the serial port
  //  isn't spammed with messages
  delay(500);
}
