const int sensorPin = A0;
int sensorValue = 0;
int numReading = 5;

int pastValue = 0;
int dummy = 0;


int touch = 0;
int pastTouch = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  long total = 0;
  for (int i = 0; i < numReading; i++) {
    total += analogRead(sensorPin);
    delay(10);
  }
  int average = total / numReading / 4;
  average += 127;
  // Serial.print(average);
  // Serial.print(" ");
  if (average == 127) {
    touch = 0;
    // Serial.println("0");
    dummy = 0;
  } else if (average > pastValue) {
    // Serial.println("-");
    dummy -= 1;
  } else if (average < pastValue) {
    // Serial.println("+");
    dummy += 1;
  } else {
    touch = 1;
    dummy = 0;
  }

  if (dummy > 3) {
    Serial.println("+");
    dummy = 0;
  } else if (dummy < -3) {
    Serial.println("-");
    dummy = 0;
  }

  if(pastTouch == 1) {
    if (touch == 0) {
      Serial.println("Touch End");
      touch = 0;
    }
  }
  if (pastTouch == 0) {
    if (touch == 1) {
      Serial.println("Touch Start");
    }
  }

  pastTouch = touch;
  pastValue = average;
  delay(10);
}
