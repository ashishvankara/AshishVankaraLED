const int LEDPin = 6;
const int interruptPin = 3;
int button_state = 0;
int PWM = 255;
int PWM_Modulation= 0;
int blink_frequency = 2;

//float volt = 0;
void setup() {
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), buttonPress, RISING);
  pinMode(LEDPin,OUTPUT);

}

void loop() {
  
    switch(button_state){
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
      PWM_Modulation = int(PWM/2);
      analogWrite(LEDPin, PWM_Modulation);
    break;
    case 4:
    // Least Bright
      PWM_Modulation = int(PWM/4);
      analogWrite(LEDPin, PWM_Modulation);
    case 5:
    // Flashing @ 2Hz
      blinking();
    break;
  }

}

void buttonPress()
{
  
  if(button_state>=5){
    button_state=0;
  }
  else{
    button_state++; 
  }
  
}

void blinking(){
  
  //Blink LED at x Hz
  int delay_time = (500/blink_frequency);
  digitalWrite(LEDPin, HIGH);
  delay(delay_time);
  digitalWrite(LEDPin, LOW);
  delay(delay_time);
  
}

  
