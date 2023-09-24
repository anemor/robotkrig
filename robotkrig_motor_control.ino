#define LED_BUILTIN 2

#define enA 12
#define in1 14
#define in2 27
#define in3 26
#define in4 25
#define enB 33

// out3 = hvit = motor +
// out4 = rød = motor -


int yAxis=0;
int xAxis=0;
int channel_A=0;
int channel_B=1;
int motorSpeedA = 50;
int motorSpeedB = 100;

const int freq = 5000;
const int resolution = 14;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  delay(10); 
  // pinMode(enA, OUTPUT);
  // pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  ledcAttachPin(enA, channel_A);
  ledcAttachPin(enB, channel_B);
  ledcSetup(channel_A, freq, resolution);
  ledcSetup(channel_B, freq, resolution);

}

void loop() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Moving Forward");
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  delay(2000);
  motorSpeedA = 100;
  motorSpeedB = 255;
  
  
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  delay(1000);
  // PWM TESTING
  // for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
  //   ledcWrite(channel_A, dutyCycle);
  //   delay(15);
  // }

  // // decrease the LED brightness
  // for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
  //   ledcWrite(channel_A, dutyCycle);   
  //   delay(15);
  // }


  //int xAxis = analogRead(A0); // Read Joysticks X-axis
  //int yAxis = analogRead(A1); // Read Joysticks Y-axis
  
  // if(yAxis<255){
  //   yAxis++;
  // }
  // Y-axis used for forward and backward control
  /*if (yAxis < 0) {
    // Set Motor A backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, -255, 0, 0, 255);
    motorSpeedB = map(yAxis, -255, 0, 0, 255);
  }*/
  // Set Motor A forward
  // digitalWrite(in1, LOW);
  // digitalWrite(in2, HIGH);
  // // Set Motor B forward
  // digitalWrite(in3, LOW);
  // digitalWrite(in4, HIGH);
  // if (yAxis > 0) {
  //   // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
  //   motorSpeedA = map(yAxis, 0, 255, 0, 255);
  //   motorSpeedB = map(yAxis, 0, 255, 0, 255);
  //   //Mapping for vår kontroller går fra -128 til 127!
  // }
  // // If joystick stays in middle the motors are not moving
  // else {
  //   motorSpeedA = 0;
  //   motorSpeedB = 0;
  // }
  // if(yAxis>250 && xAxis<250){
  //   xAxis++;
  // }

  // // X-axis used for left and right control
  // if (xAxis < 125) {
  //   // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
  //   int xMapped = map(xAxis, 0, 125, 0, 255);
  //   // Move to left - decrease left motor speed, increase right motor speed
  //   motorSpeedA = motorSpeedA - xMapped;
  //   motorSpeedB = motorSpeedB + xMapped;
  //   // Confine the range from 0 to 255
  //   if (motorSpeedA < 0) {
  //     motorSpeedA = 0;
  //   }
  //   if (motorSpeedB > 255) {
  //     motorSpeedB = 255;
  //   }
  // }
  
  // if (xAxis > 125) {
  //   // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
  //   int xMapped = map(xAxis, 125, 250, 0, 255);
  //   // Move right - decrease right motor speed, increase left motor speed
  //   motorSpeedA = motorSpeedA + xMapped;
  //   motorSpeedB = motorSpeedB - xMapped;
  //   // Confine the range from 0 to 255
  //   if (motorSpeedA > 255) {
  //     motorSpeedA = 255;
  //   }
  //   if (motorSpeedB < 0) {
  //     motorSpeedB = 0;
  //   }
  // }
  // // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  // if (motorSpeedA < 50) {
  //   motorSpeedA = 0;
  // }
  // if (motorSpeedB < 50) {
  //   motorSpeedB = 0;
  // }
  
  // analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  // analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  // ledcWrite(channel_A, motorSpeedA);
  // ledcWrite(channel_B, motorSpeedB);

  // delay(30);
}
