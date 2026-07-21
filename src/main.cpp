#include <Arduino.h>
#include <Servo.h>

const int pot_pin = A0;
Servo servo;

unsigned long last_time;

void setup()
{
  Serial.begin(9600);
  servo.attach(6);
  servo.write(90); // Старт із зупинки
}

void loop()
{
  if (millis() - last_time >= 200)
  {
    last_time = millis();
    int rawVal = analogRead(pot_pin);

    // Масштабуємо 0..1023 у значення для 360° серво (0..180)
    int speed = map(rawVal, 0, 1023, 0, 180);

    // Мертва зона навколо 90 (центр ручки потенціометра)
    if (speed >= 85 && speed <= 95)
    {
      speed = 90; // Гарантована зупинка
    }

    servo.write(speed);
  }
}