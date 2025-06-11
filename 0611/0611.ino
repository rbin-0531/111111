//MOTOR 腳位
const int IN1 = 2;     // 左馬達正轉
const int IN2 = 4;     // 左馬達反轉
const int IN3 = 6;     // 右馬達正轉
const int IN4 = 7;     // 右馬達反轉
const int ENA = 3;     // 左馬達使能（PWM）
const int ENB = 5;    // 右馬達使能（PWM）
//紅外線腳位
const int IRL = 8; //左紅
const int IRR = 9;  //右紅
//LED
const int LED_F = A0;//前進燈
const int LED_L = A1;//左轉燈
const int LED_R = A2;//右轉燈
const int LED_S = A3;//停止燈
//超音波SET
const int EC = 11;
const int TR = 10;
void setup() {
//SET輸入/出腳位
//MOTER
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 //紅外線
 pinMode(IRL, INPUT);
 pinMode(IRR, INPUT);
 //LED
 pinMode(LED_F, OUTPUT);
 pinMode(LED_L, OUTPUT);
 pinMode(LED_R, OUTPUT);
 pinMode(LED_S, OUTPUT);
 //超音波
 pinMode(EC, INPUT);
 pinMode(TR, OUTPUT);

 Serial.begin(9600);
 Serial.println("兄弟們要進城");
}
//主迴圈
void loop() {
  //避障優先
  long distance = getDistance();
  if (distance > 0 && distance < 15) {
    STOP();         // 停止車子
    delay(200);
    BACKWORD();     // 後退 0.5 秒
    delay(500);
    STOP();         // 短暫停止
    delay(200);
    RIGHT();        // 向右轉 0.4 秒
    delay(400);
    STOP();         // 短暫停
    delay(200);
    FORWORD();      // 繼續前進
    delay(400);     // 可視需求增加一小段前進距
    return;         // 避障完成後跳出本次 loop
    }
  
//讀取紅外線
    int l = digitalRead(IRL);
    int r = digitalRead(IRR);
    //黑線底 = LOW（有偵測到）
    //白底 = HIGH（沒偵測到）
    if (l == LOW && r == LOW) {
    Serial.println("直行"); 
    FORWORD();
  } else if (l == LOW && r == HIGH ) {
    Serial.println("右轉");
    RIGHT();
  } else if (l == HIGH && r == LOW) {
    Serial.println("左轉");
    LEFT();
  } else {
    Serial.println("停止");
    STOP();
    delay(500);
  }
  delay(20); // 控制迴圈速度

}
//指令
void FORWORD() {
  //前進
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  digitalWrite(LED_F, HIGH);
  digitalWrite(LED_L, LOW);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_S, LOW);
}
void RIGHT() {
  //右轉
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 0);
  digitalWrite(LED_F, LOW);
  digitalWrite(LED_L, LOW);
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_S, LOW);
}
void LEFT() {
  //左轉
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 0);
  analogWrite(ENB, 100);
  digitalWrite(LED_F, LOW);
  digitalWrite(LED_L, HIGH);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_S, LOW);
}
void STOP() {
  //停止
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(LED_F, LOW);
  digitalWrite(LED_L, LOW);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_S, HIGH);
}
void BACKWORD() {
  //後退
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 200);
}
long getDistance() {
  digitalWrite(TR, LOW);
  delayMicroseconds(2);
  digitalWrite(TR, HIGH);
  delayMicroseconds(10);
  digitalWrite(TR, LOW);

  long duration = pulseIn(EC, HIGH, 20000);  // 最長等待 20ms
  if (duration == 0) return -1;  // 沒收到回波，視為錯誤

  long distance = duration * 0.034 / 2;
  return distance;
}

 
