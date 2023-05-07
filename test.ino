long initialValues[4] = {0, 0, 0, 0};
int inputPins[4] = {5, 6, 7, 8};
int outputPin = 9;

void setup()
{
  Serial.begin(115200);

  pinMode(9, OUTPUT);
  for (int i = 0; i < 4; i++)
  {
    pinMode(inputPins[i], INPUT);
  }

  readSensorValues(initialValues);
}

void loop()
{
  delay(300);
  long currentValues[4] = {0, 0, 0, 0};
  readSensorValues(currentValues);
  for (int i = 0; i < 4; i++)
  {
    Serial1.print(i);
    Serial1.print(": ");
    Serial1.print(currentValues[i]);
    Serial1.print(", ");
  }
  Serial1.println("");
}

void readSensorValues(long *target)
{
  for (int i = 0; i < 24; i++)
  {
    digitalWrite(9, 1);
    delayMicroseconds(1);
    digitalWrite(9, 0);
    delayMicroseconds(1);
    for (int j = 0; j < 4; j++)
    {
      target[j] = (target[j] << 1) | (digitalRead(inputPins[j]));
    }
  }
  for (int j = 0; j < 4; j++)
  {
    target[j] = target[j] ^ 0x800000;
  }
}
