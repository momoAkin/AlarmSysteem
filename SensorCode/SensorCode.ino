//Declareren
int trigger = 12;
int echo = 13;
int speakerPin = 3;
int  led1 = 7;
int  led2 = 8;
int  led3 = 9;
const int lowrange = 2000;
const int highrange = 4000;

void setup() {
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 1) / 29.1;
  duration = pulseIn(echo, LOW);
  Serial.print(distance);
  Serial.println("cm");
  delay(10);
//door de afstand in tegeven wordt er bepaald op welke afstand de alarm mag afgaan
  if ((distance <= 50))
  {
    for (int i = 0; i <= 10; i++)
    {
      for (int i = lowrange; i <= highrange; i++)
      {
        tone (speakerPin, i, 250);
      }
      for (int i = highrange; i >= lowrange; i--)
      {
        tone (speakerPin, i, 250);
      }
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      delay (50);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
  }
  else if (distance > 50)
  {
    digitalWrite(speakerPin, LOW);
  }
}
