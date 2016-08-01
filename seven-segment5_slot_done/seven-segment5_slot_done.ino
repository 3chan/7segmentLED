/* clearAll関数：全桁・全セグメントへの入力をリセットする
 *  
 * numLighting関数：引数で受け取った数値 (一ケタ) を7セグ上で光らせる
 * num2display関数：引数で受け取った4桁以下の数値を7セグ上で光らせる (ダイナミック点灯)
 * num2display_関数：引数で受け取った4桁以下の数値を7セグ上で光らせる (ダイナミック点灯ではない)
 * 
 * 注意：「0」は「-」として表示
 */

const int anode[] = {11, 7, 4, 2, 1, 10, 5, 3};
const int cathode[] = {12, 9, 8, 6};

const int segment[11][8]={{HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW , LOW},
                          {LOW , HIGH, HIGH, LOW , LOW , LOW , LOW , LOW},
                          {HIGH, HIGH, LOW , HIGH, HIGH, LOW , HIGH, LOW},
                          {HIGH, HIGH, HIGH, HIGH, LOW , LOW , HIGH, LOW},
                          {LOW , HIGH, HIGH, LOW , LOW , HIGH, HIGH, LOW},
                          {HIGH, LOW , HIGH, HIGH, LOW , HIGH, HIGH, LOW},
                          {HIGH, LOW , HIGH, HIGH, HIGH, HIGH, HIGH, LOW},
                          {HIGH, HIGH, HIGH, LOW , LOW , LOW , LOW , LOW},
                          {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},
                          {HIGH, HIGH, HIGH, HIGH, LOW , HIGH, HIGH, LOW},
                          {LOW , LOW , LOW , LOW , LOW , LOW , HIGH, LOW}};  // 横バー

int noDigits[4] = {10, 10, 10, 10};
int testDigits[4] = {4, 3, 2, 1};
int digits[4];
int luckyNum;
unsigned long startMillis[2];


void setup() {
  for (int i=0; i<8; i++) pinMode(anode[i], OUTPUT);
  for (int j=0; j<4; j++) pinMode(cathode[j], OUTPUT);
  pinMode(13, INPUT);  // タクトスイッチを接続
  randomSeed(analogRead(0));  // シード値をアナログピン(未接続)の入力値から取る
  clearAll();
}


void loop() {
  if (digitalRead(13) == HIGH) {
    int cnt = 0;
    initDigits();
    luckyNum = random(10);  // 当たり数字を決定

    for (int i=3; 0<i; i--) {   // 千～十の位に当たり数字を順に表示
      digits[i] = luckyNum;
      displayWdelay(150, digits, false);
    }

    for (int j=-2; j<2; j++) {  // 一の位を焦らしつつ表示
      digits[0] = luckyNum + j;
      if (digits[0] < 0) {  // マイナスの値の例外処理
        digits[0] += 10;
      }
      else if (digits[0] == 10) {  // バーは非表示に設定
        digits[0] = 0;
      }
      displayWdelay(150 + (200 * cnt++), digits, false);  // "焦らしつつ"
    }
    
    displayWdelay(1500, digits, true);
  }
  else num2display_(noDigits);
}


void displayWdelay(int ms, int dig[], boolean flashing) {
  if (!flashing) {
    startMillis[0] = millis();
    while (millis() - startMillis[0] < ms) {
      num2display_(dig);
    }
  }
  else {
    startMillis[1] = millis();
    while (millis() - startMillis[1] < ms) {
      displayWdelay(180, dig, false);
      displayWdelay(180, noDigits, false);
    }
  }
}


void initDigits() {
  for (int i=0; i<4; i++) digits[i] = 10;
}


void clearAll() {
  for (int i=0; i<4; i++) digitalWrite(cathode[i], HIGH);  // 全桁を非表示にする
  for (int j=0; j<8; j++) digitalWrite(anode[j], LOW);  // 全セグメントの表示をオフにする
}


//void num2display(int num) {
//  for (int i=0; i<4; i++) {  // 各桁の値を取得
//    digits[i] = num % 10;
//    num = num / 10;
//
//    // ここからダイナミック点灯
//    clearAll();
//    for (int j=0; j<4; j++) digitalWrite(cathode[j],(i==j? LOW : HIGH));
//    numLighting(digits[3-i]);
//    delay(5);  // (桁切り替え後 - 表示する値切り替え) 間の遅延分delayが必要
//  }
//}


void num2display_(int dig[]) {
  // 4桁 => 各桁の値を取得する過程をスロットでは必要ないため省略
  // ダイナミック点灯では不具合があるので通常点灯を実装
  for (int i=0; i<4; i++) {
    numLighting(dig[3-i]);
    digitalWrite(cathode[i], LOW);
    clearAll();
  }
}


void numLighting(int num) {
  for(int i=0;i<8;i++)digitalWrite(anode[i], segment[num][i]);
  return;
}
