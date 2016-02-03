int MAX = 1024;
float B = 3435;
float T0 = 298.15;
float R0 = 10.0;
float R1 = 0.98;
float TARGET = 65.0;


void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(12, HIGH);
  delay(1000);

  float temperature = getTemperature(analogRead(0));
  cookWithLove(temperature);
  Serial.println(temperature);

  digitalWrite(12, LOW);
  delay(9000);
}

float getTemperature(int analogInput) {
  Serial.println(analogInput);
  float r = calcResistance(analogInput);
  float t = calcTemperature(r);
  return t;
}

float calcResistance(int input) {
  return R1 * (MAX - input) / input;
}

float calcTemperature(float resistance) {
  float k = 1 / (log(resistance / R0) / B + (1 / T0));
  return k - 273.15;
}

void cookWithLove(float temperature) {
  //  なんとなくLEDをチカチカさせる
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);

  if (temperature < TARGET) {
    digitalWrite(2, HIGH);
    digitalWrite(13, HIGH);
  } else if (temperature > TARGET)  {
    digitalWrite(2, LOW);
    digitalWrite(13, LOW);
  }
}

