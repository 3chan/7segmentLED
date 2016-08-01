const int anode[] = {11, 7, 4, 2, 1, 10, 5, 3};
const int cathode[] = {12, 9, 8, 6};

void setup() {
  for (int i=0; i<8; i++) pinMode(anode[i], OUTPUT);
  for (int i=0; i<4; i++) pinMode(cathode[i], OUTPUT);
}

void loop() {
  for (int i=0; i<4; i++) digitalWrite(cathode[i], LOW);
  //digitalWrite(anode[0], HIGH);
  for (int i=0; i<8; i++) digitalWrite(anode[i], HIGH);
}
