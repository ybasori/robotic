#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create PCA9685 instance
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// PWM frequency for servos
#define PWM_FREQ 50

// Servo pulse width range (for most servos)
#define SERVO_MIN  102  // ~1 ms pulse (0 degrees)
#define SERVO_MAX  512  // ~2 ms pulse (180 degrees)


void setup() {
  Serial.begin(115200);
  Serial.println("PCA9685 Servo Sweep");

  pwm.begin();
  pwm.setPWMFreq(PWM_FREQ);
  delay(10);
}

void loop() {

  for(uint8_t i=0; i<=16; i++){
    // Move to 0 degrees
    setServoAngle(i, 0);
    Serial.println("Moving to 0°");
  }
  delay(1000);

  
  for(uint8_t i=0; i<=16; i++){
    // Move to 0 degrees
    setServoAngle(i, 90);
    Serial.println("Moving to 90°");
  }
  delay(1000);

  
  for(uint8_t i=0; i<=16; i++){
    // Move to 0 degrees
    setServoAngle(i, 180);
    Serial.println("Moving to 180°");
  }
  delay(1000);

}


void setServoAngle(uint8_t channel, float angle) {
  // Map angle (0-180) to pulse (SERVOMIN-SERVOMAX)
  uint16_t pulse = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  pwm.setPWM(channel, 0, pulse);
}
