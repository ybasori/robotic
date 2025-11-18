const int S1 = 23;
const int S2 = 22;
const int S3 = 21;
const int S4 = 19;
const int S5 = 18;
const int CLP = 17;
const int NEAR= 4;

void setup() {
  Serial.begin(115200);
  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);
  pinMode(S3, INPUT_PULLUP);
  pinMode(S4, INPUT_PULLUP);
  pinMode(S5, INPUT_PULLUP);
  pinMode(CLP, INPUT_PULLUP);
  pinMode(NEAR, INPUT_PULLUP); // if NEAR is active-low, this is fine
}

void loop() {
  // reading: 0 = black (line) on many boards; invert if yours is opposite
  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s3 = digitalRead(S3);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);
  int clp= digitalRead(CLP);
  int near= digitalRead(NEAR);

  Serial.print(s1); Serial.print(' ');
  Serial.print(s2); Serial.print(' ');
  Serial.print(s3); Serial.print(' ');
  Serial.print(s4); Serial.print(' ');
  Serial.print(s5); Serial.print("  CLP:");
  Serial.print(clp); Serial.print(" NEAR:");
  Serial.println(near);

  delay(100);
}
