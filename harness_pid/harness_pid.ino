#include <PID_v1.h>

// PID motor position control.

#include <PID_v1.h>
#define pot      A0                     // motor position potentiomter
#define res      A1                     // resistance potentiometer
#define pwm      9                       
#define dir      7

double kp = 7 , ki = 1.5 , kd = 0.01;            // modify for optimal performance
double input = 0, output = 0, setpoint = 0;
long temp;
PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);  // if motor will only run at full speed try 'REVERSE' instead of 'DIRECT'

void setup() {
  pinMode(pwm, OUTPUT);                  
  pinMode(dir, OUTPUT);                  
  TCCR1B = TCCR1B & 0b11111000 | 1;                   // set 31KHz PWM to prevent motor noise
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(100);
  myPID.SetOutputLimits(-200, 200);
  Serial.begin (115200);                              // for debugging
}

void loop() {
  setpoint = map(analogRead(res), 0, 1023, 204, 878);      // modify to fit motor and encoder characteristics, potmeter connected to A0
  input = analogRead(pot) ;                           // data from motor position pot
  Serial.print("resistance: ");                      // monitor motor position
  Serial.print(setpoint);
  Serial.print(" position: ");
  Serial.println(input);
  myPID.Compute();                                    // calculate new output
  pwmOut(output);                                     // drive motor
}

void pwmOut(int out) {                                // to H-Bridge board
  if (out > 0) {
    analogWrite(pwm, out);                             // drive motor CCW
    digitalWrite(dir, LOW);
  }
  else {
    analogWrite(pwm, abs(out));
    digitalWrite(dir, HIGH);                        // drive motor CW
  }
}
