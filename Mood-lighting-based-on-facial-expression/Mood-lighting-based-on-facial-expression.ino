// RGB LED 핀 정의 (아두이노 보드에 맞게 수정)
// int redPin1 = 2;
// int redPin2 = 3;
// int redPin3 = 4;

// int greenPin1 = 5;
// int greenPin2 = 6;
// int greenPin3 = 7;

// int bluePin1 = 8;
// int bluePin2 = 9;
// int bluenPin3 = 10;


void setup() {
  // 시리얼 통신 시작
  Serial.begin(9600);
  
  // LED 핀을 출력 모드로 설정
  for(int i = 2;i<=10;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
}

void loop() {
  // 시리얼로부터 데이터 수신
  if (Serial.available() > 0) {
    String emotion = Serial.readString();  // 받은 데이터를 문자열로 읽음

    // 감정에 따라 LED 색 변경
    if (emotion == "Happy") {
      // 빨간색 (Happy)

      for(int i = 2;i<=4;i++)
        digitalWrite(i, HIGH);

      for(int i = 5;i<=10;i++)
        digitalWrite(i, LOW);
    } 
    else if (emotion == "Sad") {
      // 파란색 (Sad)
      for(int i = 8;i<=10;i++)
        digitalWrite(i, HIGH);

      for(int i = 2;i<=7;i++)
        digitalWrite(i, LOW);
    } 
    else {
      // 초록색 (Neutral)
      for(int i = 2;i<=4;i++)
        digitalWrite(i, LOW);

      for(int i = 5;i<=7;i++)
        digitalWrite(i,HIGH);

      for(int i = 8;i<=10;i++)
        digitalWrite(i, LOW);
    }
  }
}
