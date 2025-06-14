#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create PCA9685 instance
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// PWM frequency for servos
#define PWM_FREQ 50

// Servo pulse width range (for most servos)
#define SERVO_MIN  102  // ~1 ms pulse (0 degrees)
#define SERVO_MAX  512  // ~2 ms pulse (180 degrees)




uint8_t WAIST = 7;

uint8_t HIP_JOINT_LEFT = 8;
uint8_t THIGH_LEFT = 9;
uint8_t CALV_LEFT = 10;
uint8_t ANKLE_LEFT = 11;

uint8_t HIP_JOINT_RIGHT = 12;
uint8_t THIGH_RIGHT = 13;
uint8_t CALV_RIGHT = 14;
uint8_t ANKLE_RIGHT = 15;


bool oneTime = true;

void setup() {
  Serial.begin(115200);
  Serial.println("PCA9685 Servo Sweep");

  pwm.begin();
  pwm.setPWMFreq(PWM_FREQ);
  delay(10);
}

void loop() {

// if(oneTime){
//   oneTime = false;
//   animateStandUp();
  // delay(1000);
// }

  // animateStand();
  // delay(1000);

  // animateSquad();
  // delay(1000);

  // normalizeTo90Degrees();
  // delay(1000);

  
    setServoAngle(WAIST, 0);
  delay(1000);
    setServoAngle(WAIST, 90);
  delay(1000);
    setServoAngle(WAIST, 180);
  delay(1000);



}

// NOT AVAILABLE ON 0 DEGREES
// HIP_JOINT_LEFT, THIGH_LEFT, CALV_RIGHT, ANKLE_LEFT,  


// NOT AVAILABLE ON 180 DEGREES
// HIP_JOINT_RIGHT, THIGH_RIGHT, CALV_LEFT, ANKLE_RIGHT,

void animateStandUp(){
  Serial.println("Stand Up");
    setServoAngle(HIP_JOINT_RIGHT, 90);
    setServoAngle(HIP_JOINT_LEFT, 90);

    setServoAngle(THIGH_RIGHT, 90);
    setServoAngle(THIGH_LEFT, 90);

    setServoAngle(CALV_RIGHT, 90);
    setServoAngle(CALV_LEFT, 90);

    setServoAngle(ANKLE_RIGHT, 0);
    setServoAngle(ANKLE_LEFT, 180);

    
  delay(1000);

    setServoAngle(HIP_JOINT_RIGHT, 90);
    setServoAngle(HIP_JOINT_LEFT, 90);

    setServoAngle(THIGH_RIGHT, 0);
    setServoAngle(THIGH_LEFT, 180);

    setServoAngle(CALV_RIGHT, 180);
    setServoAngle(CALV_LEFT, 0);

    setServoAngle(ANKLE_RIGHT, 0);
    setServoAngle(ANKLE_LEFT, 180);

  delay(1000);

  
    setServoAngle(HIP_JOINT_RIGHT, 90);
    setServoAngle(HIP_JOINT_LEFT, 90);

    setServoAngle(THIGH_RIGHT, 0);
    setServoAngle(THIGH_LEFT, 180);

    setServoAngle(CALV_RIGHT, 180);
    setServoAngle(CALV_LEFT, 0);

    setServoAngle(ANKLE_RIGHT, 90);
    setServoAngle(ANKLE_LEFT, 90);

  delay(1000);
  
    setServoAngle(HIP_JOINT_RIGHT, 0);
    setServoAngle(HIP_JOINT_LEFT, 180);

    setServoAngle(THIGH_RIGHT, 0);
    setServoAngle(THIGH_LEFT, 180);

    setServoAngle(CALV_RIGHT, 180);
    setServoAngle(CALV_LEFT, 0);

    setServoAngle(ANKLE_RIGHT, 0);
    setServoAngle(ANKLE_LEFT, 180);
  delay(1000);
  
    setServoAngle(HIP_JOINT_RIGHT, 0);
    setServoAngle(HIP_JOINT_LEFT, 180);

    setServoAngle(THIGH_RIGHT, 90);
    setServoAngle(THIGH_LEFT, 90);

    setServoAngle(CALV_RIGHT, 90);
    setServoAngle(CALV_LEFT, 90);

    setServoAngle(ANKLE_RIGHT, 0);
    setServoAngle(ANKLE_LEFT, 180);
}

void animateSquad(){

  Serial.println("Squad");
  
    setServoAngle(HIP_JOINT_RIGHT, 0);
    setServoAngle(HIP_JOINT_LEFT, 180);
  
    setServoAngle(THIGH_RIGHT, 0);
    setServoAngle(THIGH_LEFT, 180);

    setServoAngle(CALV_RIGHT, 180);
    setServoAngle(CALV_LEFT, 0);

    setServoAngle(ANKLE_RIGHT, 0);
    setServoAngle(ANKLE_LEFT, 180);
  
}

void animateStand(){
  Serial.println("Stand");
  
    setServoAngle(HIP_JOINT_RIGHT, 0);
    setServoAngle(HIP_JOINT_LEFT, 180);
  
    setServoAngle(THIGH_RIGHT, 90);
    setServoAngle(THIGH_LEFT, 90);

    setServoAngle(CALV_RIGHT, 90);
    setServoAngle(CALV_LEFT, 90);

    setServoAngle(ANKLE_RIGHT, 0);
    setServoAngle(ANKLE_LEFT, 180);
  
}


void normalizeTo90Degrees(){
  Serial.println("Normalize to 90 Degrees");
  for(uint8_t i=0; i<16; i++){
    setServoAngle(i, 90);
  }
}


void setServoAngle(uint8_t channel, float angle) {
  // Map angle (0-180) to pulse (SERVOMIN-SERVOMAX)
  uint16_t pulse = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  pwm.setPWM(channel, 0, pulse);
}
