const int dirPin_LivingRoom =         2;  // 적외선 센서 핀 번호 (거실)
const int dirPin_Bathroom =           3;  // 적외선 센서 핀 번호 (화장실)
const int sonaPin_Bathroom_echo =     4;  // 초음파 센서 핀 번호 (거실-화장실) 에코(input)
const int sonaPin_Bathroom_trig =     5;  // 초음파 센서 핀 번호 (거실-화장실) 트리거(output)
const int sonaPin_Outside_echo =      6;  // 초음파 센서 핀 번호 (거실-현관) 에코(input)
const int sonaPin_Outside_trig =      7;  // 초음파 센서 핀 번호 (거실-현관) 트리거(output)
const int buttonPin =                 10; // SOS 버튼 핀 번호 (거실)

int rotateRound;

void setup() {
  // put your setup code here, to run once:
  pinMode(dirPin_LivingRoom, INPUT);
  pinMode(dirPin_Bathroom, INPUT);
  pinMode(sonaPin_Bathroom_echo, INPUT);
  pinMode(sonaPin_Bathroom_trig, OUTPUT);
  pinMode(sonaPin_Outside_echo, INPUT);
  pinMode(sonaPin_Outside_trig, OUTPUT);
  pinMode(buttonPin, INPUT);

  rotateRound = 0;
  
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(3000);
  sensorCheck();
}

void sensorCheck() {
  int sensorValue[7] = {0,};
  long duration, detectValue;
  
  sensorValue[0] = digitalRead(dirPin_LivingRoom);  // 적외선 센서 - 거실
  sensorValue[1] = digitalRead(dirPin_Bathroom);    // 적외선 센서 - 화장실

  digitalWrite(sonaPin_Bathroom_trig,HIGH);      // 거실 Trig에서 신호 송신 (초음파 쏘기)
  delayMicroseconds(10);                           // 10us 정도 유지
  digitalWrite(sonaPin_Bathroom_trig,LOW);       // 거실 Trig 신호 송신 정지

  duration = pulseIn(sonaPin_Bathroom_echo,HIGH);// Echo pin: HIGH->Low 간격을 측정
  detectValue = duration / 29 / 2 * 100;         // 측정 단위를 centimeter로 변경하고 x 100
  sensorValue[2] = (int)detectValue;             // 초음파 센서 - 거실

   digitalWrite(sonaPin_Outside_trig,HIGH);       // 현관 Trig에서 신호 송신 (초음파 쏘기)
   delayMicroseconds(10);
   digitalWrite(sonaPin_Outside_trig,LOW);        // 현관 Trig 신호 송신 정지

  duration = pulseIn(sonaPin_Outside_echo,HIGH); // Echo pin: HIGH->Low 간격을 측정
  detectValue = duration / 29 / 2 * 100;         // 측정 단위를 centimeter로 변경 x 100
  sensorValue[3] = (int)detectValue;             // 초음파 센서 - 현관
  
  sensorValue[4] = analogRead(0); // 충격감지 센서 - 거실
  sensorValue[5] = analogRead(1); // 충격감지 센서 - 화장실
  
  sensorValue[6] = digitalRead(buttonPin);          // 버튼 센서

  rotateRound++;
  Serial.print(rotateRound);
  Serial.println("--------------------------------------");
  Serial.print("적외선1 센서값 : ");
  Serial.println(sensorValue[0]);
  Serial.print("적외선2 센서값 : ");
  Serial.println(sensorValue[1]);
  Serial.print("초음파1 센서값 : ");
  Serial.println(sensorValue[2]);
  Serial.print("초음파2 센서값 : ");
  Serial.println(sensorValue[3]);
  Serial.print("충격감지1 센서값 : ");
  Serial.println(sensorValue[4]);
  Serial.print("충격감지2 센서값 : ");
  Serial.println(sensorValue[5]);
  Serial.print("버튼 센서값 : ");
  Serial.println(sensorValue[6]);
}
