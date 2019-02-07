#define readEncoder bitRead(PIND,2)//faster than digitalRead()

const byte encoderPin = 2;//encoder output, digital pin

volatile long count = 0; //current number of total encoder counts
volatile long previousCount = 0; //current number of total encoder counts
volatile long intervalCount = 0; //current number of total encoder counts

long vel;
float pedalSpeed = 0; //RPM

unsigned long currentTime; 
unsigned long previousTime = 0;
const int interval = 1000; // One second

void isr() { //increment or decrement the encoder count if channel changes
    count ++; //increment
}


void calcSpeed() {
    intervalCount = count - previousCount;
    pedalSpeed = intervalCount/8 /interval * 60000; //Revolutions per millisec times 60000 millisec = RPM
    previousCount = count;
    previousTime = currentTime;
}

void setup() {
  pinMode(encoderPin, INPUT_PULLUP);  
  attachInterrupt(digitalPinToInterrupt(encoderPin), isr, HIGH); //encoder  initialization

}

void loop() {


  currentTime = millis();
  if (currentTime - previousTime >= interval) {calcSpeed();} //Every interval (1second right now), calculate speed

    
}
