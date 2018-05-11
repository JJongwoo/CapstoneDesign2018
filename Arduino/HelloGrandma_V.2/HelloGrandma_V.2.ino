/*
    한성대 캡스톤 디자인
    망고스틴 조 - Hello, Grandma

    측정값만 보내도록 수정된 코드
*/

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

int sensorValue[7] = {0,};
//되는 번호 0,1,2,3,4,5,12,13,14,15,16
//순서는 16, 5, 4, 14, 12, 13, //0//, 2
const int dirPin_LivingRoom =         16;  // 적외선 센서 핀 번호 (거실)
const int dirPin_Bathroom =           5;  // 적외선 센서 핀 번호 (화장실)
const int sonaPin_Bathroom_echo =     13;  // 초음파 센서 핀 번호 (거실-화장실) 에코(input)
const int sonaPin_Bathroom_trig =     12;  // 초음파 센서 핀 번호 (거실-화장실) 트리거(output)
const int sonaPin_Outside_echo =      14;  // 초음파 센서 핀 번호 (거실-현관) 에코(input)
const int sonaPin_Outside_trig =      4;  // 초음파 센서 핀 번호 (거실-현관) 트리거(output)
const int buttonPin =                 15; // SOS 버튼 핀 번호 (거실)
//const int vibePin =                   O; // 진동(낙상감지) 아날로그 핀 번호 (거실)

const char* ssid     = "jongwoohot";      // 공유기 ID
const char* password = "whddntkfkdgo";      // 공유기 비밀번호

const char* host = "192.168.43.51";       // 서버 IP
const char* streamId   = "....................";
const char* privateKey = "....................";

void setup() {
  //ESP.wdtDisable();
  pinMode(dirPin_LivingRoom, INPUT);
  pinMode(dirPin_Bathroom, INPUT);
  pinMode(sonaPin_Bathroom_echo, INPUT);
  pinMode(sonaPin_Bathroom_trig, OUTPUT);
  pinMode(sonaPin_Outside_echo, INPUT);
  pinMode(sonaPin_Outside_trig, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(0, INPUT);
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println(); 
  Serial.print("Connecting to ");
  Serial.println(ssid);
 // ESP.Disable();
  if(!WiFi.getAutoConnect()){

    WiFi.begin(ssid, password);
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {                        /// Loop 시작
 
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort=8080;
  Serial.println(host);
  Serial.println(httpPort);
  
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  // We now create a URI for the request
  String url = "/helloGrandma/savestatus2";
 
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  long duration, detectValue;
  
  sensorValue[0] = digitalRead(dirPin_LivingRoom);  // 적외선 센서 - 거실
  sensorValue[1] = digitalRead(dirPin_Bathroom);    // 적외선 센서 - 화장실

  digitalWrite(sonaPin_Bathroom_trig,LOW);      // 거실 Trig에서 신호 송신 (초음파 쏘기)
  delayMicroseconds(2);                         // 2us 정도 유지
  digitalWrite(sonaPin_Bathroom_trig,HIGH);     // 거실 Trig 신호 송신 정지
  delayMicroseconds(10);                        // 10us 정도 유지
  digitalWrite(sonaPin_Bathroom_trig,LOW);      // 거실 Trig에서 신호 송신 (초음파 쏘기)
  duration = pulseIn(sonaPin_Bathroom_echo,HIGH);// Echo pin: HIGH->Low 간격을 측정
  detectValue = duration * 17 / 1000;
  sensorValue[3] = (int)detectValue;             // 초음파 센서 - 거실
  
  digitalWrite(sonaPin_Outside_trig,LOW);       // 현관 Trig에서 신호 송신 (초음파 쏘기)
  delayMicroseconds(2);                         // 2us 정도 유지
  digitalWrite(sonaPin_Outside_trig,HIGH);      // 현관 Trig 신호 송신 정지
  delayMicroseconds(10);                        // 10us 정도 유지
  digitalWrite(sonaPin_Outside_trig,LOW);       // 현관 Trig에서 신호 송신 (초음파 쏘기)
  duration = pulseIn(sonaPin_Outside_echo,HIGH);// Echo pin: HIGH->Low 간격을 측정
  detectValue = duration  * 17 / 1000;
  sensorValue[2] = (int)detectValue;             // 초음파 센서 - 현관
  
  sensorValue[4] = analogRead(0);                // 충격감지 센서 - 거실
  //sensorValue[5] = analogRead(1);                // 충격감지 센서 - 화장실
  
  sensorValue[6] = digitalRead(buttonPin);       // 버튼 센서

  
  String jsondata = "";
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["id"] = "jwkim";
  root["dir1Value"] = sensorValue[0];
  root["dir2Value"] = sensorValue[1];
  root["sona1Value"] = sensorValue[2];
  root["sona2Value"] = sensorValue[3];
  root["shock1Value"] = sensorValue[4];
//  root["shock2Value"] = sensorValue[5];
  root["buttonValue"] = sensorValue[6];


  root.printTo(jsondata);
  Serial.println(jsondata);              // 측정한 센서 값 전송.
  
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n");
  client.print("User-Agent: Arduino\r\n");
  client.print("Content-Type: application/json\r\n");
  client.print("Content-Length: ");
  client.println(jsondata.length());
  client.println();
  client.println(jsondata);
  client.print("Connection: close\r\n\r\n");
  
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 4000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }

  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()==0){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  
  delay(1000);
}


