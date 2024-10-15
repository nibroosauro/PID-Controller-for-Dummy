//HEADING BNO USING HEADING/YAW EULER ANGLE
//NOTE PENTING!!!
//EULER SENSITIF BGT SAMA GERAKAN PITCH ROLL NYA, BAKAL NGARUH KE BACAAN HEADING
//KALAU MAU COBA, POSISI BNO HARUS SELALU NEMPEL DI PERMUKAAN BIAR GA GANGGU KE HEADING

// Possible vector values can be:
// - VECTOR_ACCELEROMETER - m/s^2
// - VECTOR_MAGNETOMETER  - uT
// - VECTOR_GYROSCOPE     - rad/s
// - VECTOR_EULER         - degrees
// - VECTOR_LINEARACCEL   - m/s^2
// - VECTOR_GRAVITY       - m/s^2

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//PIN MOTOR
int pinMotor1A = 3;
int pinMotor1B = 2;
int pinMotor2A = 8;
int pinMotor2B = 9;
int pinMotor3A = 7;
int pinMotor3B = 6;
int pinMotor4A = 5;
int pinMotor4B = 4;

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055();
bool pembacaanPertama = true;
float eulerX, eulerY, eulerZ, refValue, heading;

//variables for PID control
float target = 0;
float error = 0;
float integral = 0;
float derivative = 0;
float last_error = 0;

float angle = 0;

float Kp = 7;
float Ki = 0.005;
float Kd = 0;

float motor1Speed;
float motor2Speed;
float motor3Speed;
float motor4Speed;

float wheelradius = 9.6;  // dummy variable

void setup(void) {
  pinMode(pinMotor1A, OUTPUT);
  pinMode(pinMotor1B, OUTPUT);
  pinMode(pinMotor2A, OUTPUT);
  pinMode(pinMotor2B, OUTPUT);
  pinMode(pinMotor3A, OUTPUT);
  pinMode(pinMotor3B, OUTPUT);
  pinMode(pinMotor4A, OUTPUT);
  pinMode(pinMotor4B, OUTPUT);

  Serial.begin(115200);
  Serial.println("Orientation Sensor Raw Data Test");
  Serial.println("");

  /* Initialise the sensor */
  if (!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1)
      ;
  }

  bno.setExtCrystalUse(true);
  bno.setMode(adafruit_bno055_opmode_t::OPERATION_MODE_NDOF);
  delay(500);
}

void loop(void) {
  while (millis() < 3000) {
    SetMotor(pinMotor1A, pinMotor1B, 0);
    SetMotor(pinMotor2A, pinMotor2B, 0);
    SetMotor(pinMotor3A, pinMotor3B, 0);
    SetMotor(pinMotor4A, pinMotor4B, 0);
  }

  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  /* Display the floating point data */
  eulerX = euler.x();  //heading = berputar searah sumbu z 0 to 360 // INI YANG BAKAL DIPAKE
  eulerY = euler.y();  //roll = beprutar searah sumbu y -90 to -90
  eulerZ = euler.z();  //pitch = berputar searah sumbu x +180 to -180

  heading = eulerX;

  if (heading > 180) {
    heading -= 360;
  } else if (heading < -180) {
    heading += 360;
  }

  error = target - heading;         // proportional
  integral = integral + error;      // integral
  derivative = error - last_error;  // derivative

  angle = (error * Kp) + (integral * Ki) + (derivative * Kd);

  // Limit angle to ensure it stays within acceptable bounds


  // Calculate inverse kinematics using vx, vy, and rotate
  // Replace the following placeholder values with actual values or calculations
  float vx = 50;         // Placeholder value
  float vy = 0;          // Placeholder value
  float rotate = angle;  // Use the angle calculated by PID as the rotation speed

  InverseKinematic(vx, vy, rotate);

  Serial.print("heading: ");
  Serial.print(heading);
  Serial.print("  error: ");
  Serial.print(error);
  Serial.print("  angle:");
  Serial.print(angle);
  Serial.print("  integral: ");
  Serial.print(integral);
  Serial.print("  derivatif: ");
  Serial.print(derivative);
  Serial.print("  motor1: ");
  Serial.print(motor1Speed);
  Serial.print("  motor2: ");
  Serial.print(motor2Speed);
  Serial.print("  motor3: ");
  Serial.print(motor3Speed);
  Serial.print("  motor4: ");
  Serial.println(motor4Speed);

  // Apply motor speeds calculated from inverse kinematics
  SetMotor(pinMotor1A, pinMotor1B, motor1Speed);
  SetMotor(pinMotor2A, pinMotor2B, motor2Speed);
  SetMotor(pinMotor3A, pinMotor3B, motor3Speed);
  SetMotor(pinMotor4A, pinMotor4B, motor4Speed);

  // Update last error for derivative term calculation
  last_error = error;

  delay(BNO055_SAMPLERATE_DELAY_MS);
}


void setHeadingRef() {
  if (pembacaanPertama) {
    // Lakukan pembacaan sensor pertama kali
    if (eulerX != eulerY && eulerZ != eulerX && eulerY != eulerZ) {
      refValue = eulerX;
      Serial.print("Nilai referensi: ");
      Serial.println(refValue);
      // Set variabel pembacaanPertama menjadi false agar pembacaan hanya dilakukan sekali
      pembacaanPertama = false;
    }
  }
}

void InverseKinematic(float vx, float vy, float wr) {
  // float pi = 3.14159;
  // float angle_deg1 = 30;
  // float angle_rad1 = angle_deg1*pi/180;
  motor1Speed = (vx * cos((3 * PI) / 4) + vy * sin((3 * PI) / 4) + wr / 4);  // wheelradius) * (60 / (2 * PI)); //m/s to rpm per motor
  motor2Speed = (vx * cos((5 * PI) / 4) + vy * sin((5 * PI) / 4) + wr / 4);  // wheelradius) * (60 / (2 * PI));
  motor3Speed = (vx * cos((7 * PI) / 4) + vy * sin((7 * PI) / 4) + wr / 4);  // wheelradius) * (60 / (2 * PI));
  motor4Speed = (vx * cos((1 * PI) / 4) + vy * sin((1 * PI) / 4) + wr / 4);  // wheelradius) * (60 / (2 * PI));
}

void SetMotor(int motorPin1, int motorPin2, float speed) {
  int abs_speed = abs(static_cast<int>(speed));  // Cast to int before using map
  int mappedSpeed = abs_speed;                   //map(abs_speed, 0, 100, 0, 100);
  if (speed > 0) {
    analogWrite(motorPin1, mappedSpeed);
    analogWrite(motorPin2, 0);
  } else {
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, mappedSpeed);
  }
}