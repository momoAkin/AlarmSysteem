//Declareren
const int AlarmLed = 8;
const int RedLED = 11;
const int GreenLED = 9;
const int inputPin = A0;
const int inputPin1 = A1;
const int inputPin2 = A2;
const int inputPin3 = A4;
const int inputPin4 = A5;

const int AlarmSpeaker = 7;
const int armButton = 10;

boolean isArmed = true;
boolean isTriggered = false;
int buttonVal = 0;
int prev_buttonVal = 0;
int reading = 0;
int reading1 = 0;
int reading2 = 0;
int reading3 = 0;
int reading4 = 0;

int threshold = 0;


const int lowrange = 2000;
const int highrange = 4000;

void setup() {

  pinMode(AlarmLed, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(armButton, INPUT);
  digitalWrite(AlarmLed, HIGH);
  delay(500);
  digitalWrite(AlarmLed, LOW);

  Kalibreren();
  setArmedState();
}

void loop() {


  reading = analogRead(inputPin);
  reading1 = analogRead(inputPin1);
  reading2 = analogRead(inputPin2);
  reading3 = analogRead(inputPin3);
  reading4 = analogRead(inputPin4);
//kijken of dat het alarm systeem is ingeschakel/uitgeschakeld

  int buttonVal = digitalRead(armButton);
  if ((buttonVal == HIGH) && (prev_buttonVal == LOW)) {
    setArmedState();
    delay(500);
  }

  if ((isArmed) && (reading < threshold)) {
    isTriggered = true;
  }
if ((isArmed) && (reading1 < threshold)) {
    isTriggered = true;
  }
if ((isArmed) && (reading2 < threshold)) {
    isTriggered = true;
  }
if ((isArmed) && (reading3 < threshold)) {
    isTriggered = true;
  }
if ((isArmed) && (reading4 < threshold)) {
    isTriggered = true;
  }
//Als de sensor is getriggerd gaat het alarm af (speaker+led)

  if (isTriggered) {

    for (int i = lowrange; i <= highrange; i++)
    {
      tone (AlarmSpeaker, i, 250);
    }

    for (int i = highrange; i >= lowrange; i--)
    {
      tone (AlarmSpeaker, i, 250);
    }


    digitalWrite(AlarmLed, HIGH);
    delay(50);
    digitalWrite(AlarmLed, LOW);
    delay (50);

  }

  delay(20);
}

void setArmedState() {
//het alarm systeem aan/uitschakelen
  if (isArmed) {
    digitalWrite(GreenLED, HIGH);
    digitalWrite(RedLED, LOW);
    isTriggered = false;
    isArmed = false;
  } else {
    digitalWrite(GreenLED, LOW);
    digitalWrite(RedLED, HIGH);
    tone(AlarmSpeaker, 220, 125);
    delay(200);
    tone(AlarmSpeaker, 196, 250);
    isArmed = true;
  }
}

void Kalibreren() {
//tijdens de start controleren of lazer wordt gezien + kleine intro tijdens het aansluiten aan stroom

  int sample = 0;
  int baseline = 0;
  const int min_diff = 200;
  const int sensitivity = 50;
  int success_count = 0;

  digitalWrite(RedLED, LOW);
  digitalWrite(GreenLED, LOW);

  for (int i = 0; i < 10; i++) {
    sample += analogRead(inputPin);
    digitalWrite(GreenLED, HIGH);
    delay (50);
    digitalWrite(GreenLED, LOW);
    delay (50);
  }

  do
  {
    sample = analogRead(inputPin);

    if (sample > baseline + min_diff) {
      success_count++;
      threshold += sample;

      digitalWrite(GreenLED, HIGH);
      delay (100);
      digitalWrite(GreenLED, LOW);
      delay (100);
    } else {
      success_count = 0;
      threshold = 0;
    }

  } while (success_count < 3);

  threshold = (threshold / 3) - sensitivity;

  tone(AlarmSpeaker, 196, 250);
  delay(200);
  tone(AlarmSpeaker, 220, 125);
}
