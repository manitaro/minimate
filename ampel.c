// LEDs
const byte LED_RED    = 3;
const byte LED_YELLOW = 18;
const byte LED_GREEN  = 21;
// Knöpfe
const byte BUTTON     = 22;

byte r = 0;
bool lastButtonState = false;
ulong lastButtonTime = 0;

// Initialisierung beim Start
void setup() {
  // PINs am ESP32 richtig einstellen
  pinMode(LED_RED   , OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN , OUTPUT);
  pinMode(BUTTON    , INPUT);
  Serial.begin(115200);

  Serial.println("Ampel startet ...");

  for (byte i=0; i<255; i++) {
    green(i);
    delay(2);
  }
  for (byte i=0; i<255; i++) {
    yellow(i);
    delay(2);
  }
  for (byte i=0; i<255; i++) {
    red(i);
    delay(2);
  }
  lastButtonState = digitalRead(BUTTON);
  lastButtonTime = millis();
  Serial.println("Ampel bereit");
}

// Ich wiederhole mich immer und immer und immer
void loop() {
  red(200 + (millis() / 20) % 100);
  yellow(200 + (millis() / 20) % 100);
  green(200 + (millis() / 20) % 100);

  bool isPressed = digitalRead(BUTTON);

  if (isPressed != lastButtonState) {
    if (!isPressed) {
      uint diff = millis() - lastButtonTime;
      if (diff <= 50) {

        Serial.println("Fehler");
      } else if (diff <= 400) {
        ampelProg();

        Serial.println("kurz gedrückt");
      } else if (diff <= 2000) {

        Serial.println("lang gedrückt");
        hellProg();
      } else {

        Serial.println("zu lang gedrückt");
      }
    }
    lastButtonTime = millis();
    lastButtonState = isPressed;
  }
  if (isPressed) {
    return;
  }

}

void ampelProg() {
  red(255);
  yellow(0);
  green(0);
  delay(1000);
  red(0);
  yellow(255);
  green(0);
  delay(1000);
  red(0);
  yellow(0);
  green(255);
  delay(5000);
  red(0);
  yellow(255);
  green(0);
  delay(1000);
  red(255);
  yellow(0);
  green(0);
  delay(1000);
}

void hellProg() {
  red(255);
  yellow(255);
  green(255);
  delay(10000);
}

void red(byte value) {
  analogWrite(LED_RED, value);
}

void yellow(byte value) {
  analogWrite(LED_YELLOW, value);
}

void green(byte value) {
  analogWrite(LED_GREEN, value);
}
