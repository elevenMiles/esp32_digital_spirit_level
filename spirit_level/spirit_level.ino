// ESP32 Spirit Level
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

const int LED_PINS[] {26, 27, 14, 12, 13}; 
constexpr int LED_COUNT {sizeof(LED_PINS) / sizeof(int)};

float lightPosition {0.0f};
float offset {0.0f};
float brightDistance {0.5f};
float factor {0.2f};

int calculatePwm(float position, float light) 
{
  float distance {abs(position - light)};
  return constrain(static_cast<int>((-255.0f / brightDistance) * distance + 255.0f), 0, 255);
}

void setup() 
{
  Serial.begin(115200);

  for (int i {0}; i < LED_COUNT; ++i) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  Wire.begin(21, 22); 
  mpu6050.begin();
  
  Serial.println("Calibrating... Keep steady.");
  mpu6050.calcGyroOffsets(false);

  mpu6050.update();
  offset = (LED_COUNT - 1.0f) / 2.0f - mpu6050.getAngleX() * factor;
}

void loop() 
{
  static unsigned long previous_time_micros {0};
  unsigned long current_time_micros {micros()};
  float delta_time {(current_time_micros - previous_time_micros) / 1000000.0f};
  previous_time_micros = current_time_micros;

  mpu6050.update();

  float xAngle {mpu6050.getAngleX() * factor};

  lightPosition = xAngle + offset;
  lightPosition = constrain(lightPosition, 0.0f, static_cast<float>(LED_COUNT - 1.0f));

  for (int i {0}; i < LED_COUNT; ++i) {
    analogWrite(LED_PINS[i], calculatePwm(static_cast<float>(i), lightPosition));
  }

  delay(10);
}