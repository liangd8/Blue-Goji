#define cell1 A5  // Analog input pin that the potentiometer is attached to
#define cell2 A4
#define cell3 A0
#define cell4 A3
int F1 =0, F2=0, F3=0, F4=0, CoMX=0, CoMY=0,CF2, CF3,CF4, CF1;
int a = 100; 
int b = 100;


//Load Cell 4 max value 240, min 80 Voltage 6.1
//Load Cell 3 max value 130, min 20 Voltage 5.9
//Load Cell 2 max value 272, min 113 Voltage 5.9
//Load Cell 1 max value 64, min 17 Voltage 5.7

//139
//21
//184
//27

void setup() {
  // put your setup code here, to run once:
  pinMode(cell1,INPUT);
  pinMode(cell2,INPUT);
  pinMode(cell3,INPUT);
  pinMode(cell4,INPUT);
  Serial.begin(9600); 
}
void loop() {
  // put your main code here, to run repeatedly:
  F1 = analogRead(cell1);
  F2 = analogRead(cell2)/2;
  F3 = analogRead(cell3);
  F4 = analogRead(cell4);

// CoMX = (a/2)*(F2-F1+F3-F4)/(F1+F2+F3+F4);
// CoMY = (b/2)*(F2+F1-F3-F4)/(F1+F2+F3+F4);
  
  CF1 = map(F1, 17, 64, 1, 30);
  CF2 = map(F2, 113, 272, 1, 30);
  CF3 = map(F3, 20, 247, 1, 30);
  CF4 = map(F4, 80, 136, 1, 30);
  
 //CoMX = (a/2)*(CF2-CF1+CF3-CF4)/(CF1+CF2+CF3+CF4);
 // CoMY = (b/2)*(CF2+CF1-CF3-CF4)/(CF1+CF2+CF3+CF4);
  
  char buffer[80];
  sprintf(buffer, "Cell#1: %d; Cell#2: %d; Cell#3: %d; Cell#4 %d; CoM: %d,%d", F1, F2, F3, F4, CoMX, CoMY);
  Serial.println(buffer); 
// char debuffer[80];
// sprintf(debuffer, "Cell 1: %d, Cell 2: %d, Cell 3: %d, Cell 4: %d", F1, F2, F3, F4);
 Serial.println(buffer);
  delay(800);
}
