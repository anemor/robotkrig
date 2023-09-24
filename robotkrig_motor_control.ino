//The joystick values goes from (-127 to 128)

#include <PS4Controller.h>

#define enA 12
#define in1 14
#define in2 27
#define in3 26
#define in4 25
#define enB 33
#define enC 32
#define inC1 35
#define inC2 34

int yAxis=0;
int xAxis=0;
int channel_A=0;
int channel_B=1;
int channel_C=2;

const int freq = 5000;
const int resolution = 14;

void onConnect()
{
  Serial.println("Connected!.");
}

void onDisConnect()
{
  Serial.println("Disconnected!.");
  analogWrite(enA, 0); // Send PWM signal to motor A
  analogWrite(enB, 0); // Send PWM signal to motor B
  analogWrite(enC, 0); // Send PWM signal to weapon
}


void setup() {
  Serial.begin(115200);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  delay(10); 

  pinMode(enA, OUTPUT); //Merk litt andeledes fra når vi testet!!
  pinMode(enB, OUTPUT); //Merk litt andeledes fra når vi testet!!
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(inC1, OUTPUT);
  pinMode(inC2, OUTPUT);

  Serial.println("Ready.");
}

void loop() {
  //Read signals from joystick
  yAxis=PS4.LstickY();
  xAxis=PS4.LstickX();

  //Setter våpnetet fremover
  digitalWrite(inC1, LOW);
  digitalWrite(inC2, HIGH);

  // Y-axis used for forward and backward control
  //Burde vi legge rundt null lik null??
  if (yAxis < 0) {
    //NB!! må sjekke at in1, in2, in3, in4 blir koblet riktig for forward/backward
    // Set Motor A backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 0, -128, 0, 255);
    motorSpeedB = map(yAxis, 0, -128, 0, 255);
  }
  else if (yAxis > 0) {
    // Set Motor A forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 0, 127, 0, 255);
    motorSpeedB = map(yAxis, 0, 127, 0, 255);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  //X-axis used for left and right control
  //NB!! Burde vi legge inn en sperre på små verdier??
  if (xAxis < 0) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 0, -128, 0, 255);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 255) {
      motorSpeedB = 255;
    }
  }
  if (xAxis > 0) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 0, 127, 0, 255);
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  // NB!! Dette må sjekkes!! tester med 40 for nå
  if (motorSpeedA < 40) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 40) {
    motorSpeedB = 0;
  }

  if(PS4.Square()){
    motorSpeedC=255;
  }
  else {
    motorSpeedC=0;
  }

  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  analogWrite(enC, motorSpeedC); // Send PWM signal to weapon


}