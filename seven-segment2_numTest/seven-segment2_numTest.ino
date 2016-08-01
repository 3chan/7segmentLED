/* clearAll関数：全桁・全セグメントへの入力をリセットする
 * numLighting関数：引数で受け取った数値を7セグ上で光らせる
 * 
 * 未実装：桁ごとの表示, 小数点の使用 (しないかも)
 */

const int anode[] = {11, 7, 4, 2, 1, 10, 5, 3};
const int cathode[] = {12, 9, 8, 6};
int cnt;


void setup() {
  for (int i=0; i<8; i++) pinMode(anode[i], OUTPUT);
  for (int j=0; j<4; j++) pinMode(cathode[j], OUTPUT);
  cnt = 0;
}


void loop() {
  clearAll();  // 表示リセット
  delay(250);

  numLighting(cnt);
  for (int i=0; i<4; i++) digitalWrite(cathode[i], LOW);  // 表示する数値のインクリメント
  if (8 < cnt) cnt = 0;
  else cnt++;
  delay(250);
}


void clearAll() {
  for (int i=0; i<4; i++) digitalWrite(cathode[i], HIGH);  // 全桁を非表示にする
  for (int j=0; j<8; j++) digitalWrite(anode[j], LOW);  // 全セグメントの表示をオフにする
}


void numLighting(int num) {
  if (6 < num || num == 1 || num == 3) {  // 1, 3, 7, 8, 9
    digitalWrite(anode[1], HIGH);
    digitalWrite(anode[2], HIGH);
    if (num == 1) return;
    digitalWrite(anode[0], HIGH);
    if (num == 7) return;
    digitalWrite(anode[3], HIGH);
    digitalWrite(anode[6], HIGH);
    if (num == 3) return;
    digitalWrite(anode[5], HIGH);
    if (num == 9) return;
    digitalWrite(anode[4], HIGH);  // 8を表示
  }
  else if (num == 0) {  // 0
    for (int i=0; i<6; i++) digitalWrite(anode[i], HIGH);
  }
  else if (num == 2) {  // 2
    digitalWrite(anode[0], HIGH);
    digitalWrite(anode[1], HIGH);
    digitalWrite(anode[3], HIGH);
    digitalWrite(anode[4], HIGH);
    digitalWrite(anode[6], HIGH);
  }
  else if (num == 4) {  // 4
    digitalWrite(anode[1], HIGH);
    digitalWrite(anode[2], HIGH);
    digitalWrite(anode[5], HIGH);
    digitalWrite(anode[6], HIGH);
  }
  else {  // 5, 6
    digitalWrite(anode[0], HIGH);
    digitalWrite(anode[2], HIGH);
    digitalWrite(anode[3], HIGH);
    digitalWrite(anode[5], HIGH);
    digitalWrite(anode[6], HIGH);
    if (num == 5) return;
    digitalWrite(anode[4], HIGH);  // 6を表示
  }
  return;
}
