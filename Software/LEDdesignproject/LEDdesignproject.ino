//Initialize pins
const int LEDPin = 6;
const int interruptPin = 3;

//Initialize constants
int button_state = 1;
int PWM = 255;
int blink_frequency = 2;
int PWM_Modulation= 0;

//Initialize blink variables
unsigned long previousTime = 0;
const long interval = int(500/blink_frequency); 
int LEDState = LOW;

//Initialize debouncing variables
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 200;

void setup() 
{
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), buttonPress, RISING);
  pinMode(LEDPin,OUTPUT);

}

void loop() 
{
    //Serial.println(button_state);  
    switch(button_state)
    {
      case 1:
      // OFF
        PWM_Modulation = int(PWM*0);
        analogWrite(LEDPin, PWM_Modulation);
      break;
      
      case 2:
      // Brightest
        PWM_Modulation = int(PWM*1);
        analogWrite(LEDPin, PWM_Modulation);
      break;
      
      case 3:
      // Intermediate Brightness
        PWM_Modulation = int(PWM/4);
        analogWrite(LEDPin, PWM_Modulation);
      break;
      
      case 4:
      // Least Bright
        PWM_Modulation = int(PWM/16);
        analogWrite(LEDPin, PWM_Modulation);
      break;
      
      case 5:
      // Flashing @ 2Hz
        blinking();
      break;
      
  }

}

void buttonPress()
{
  if((millis() - lastDebounceTime) > debounceDelay)
  {
    lastDebounceTime = millis();
    if(button_state>=5)
    {
      button_state=1;
    }
    else
    {
      button_state++; 
    }
  }
}

void blinking()
{

  unsigned long currentTime = millis();
  if (currentTime - previousTime >= interval)
  {
    previousTime = currentTime;
    if (LEDState == LOW) 
    {
      LEDState = HIGH;
    } 
    else 
    {
      LEDState = LOW;
    }
    digitalWrite(LEDPin, LEDState);
  }
  
}

  
