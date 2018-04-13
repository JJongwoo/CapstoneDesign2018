/*
    한성대 캡스톤 디자인
    망고스틴 조 - Hello, Grandma
*/



/* ------------------------------------------------------------------ */

#define INSIDE_MODE               1    // 모드 - 일상
#define OUTSIDE_MODE              2    // 모드 - 외출
#define SLEEP_MODE                3    // 모드 - 취침
#define NORMAL_STATUS             100  // 상태 - 정상
#define LONER_DANGER_STATUS       200  // 상태 - 위험(고독사 감지)
#define FALL_DANGER_STATUS        201  // 상태 - 위험(낙상 감지)
#define SOS_DANGER_STATUS         202  // 상태 - 위험(SOS 감지)
#define BATHROOM_ABNORMAL_STATUS  300  // 상태 - 이상(화장실 빈도 높음)
#define THEIF_ABNORMAL_STATUS     301  // 상태 - 이상(도둑 감지)

/* ------------------------------------------------------------------ */




/* ------------------------------------------------------------------ */

int debugMode =                       0;  // 테스트모드 번호 
// (0꺼짐/1적외선거실/2적외선화장실/3초음파화장실/4초음파거실/5충격감지거실/6충격감지화장실/7스위치/8고독사스택/9화장실스택)
bool debugShow =                    true; // 모드,스탯 정보 보여줄지 여부

int mode;                                 // 모드 번호
int stat;                                 // 상태 번호

int detectValue;                          // 측정 값
int lonerStack;                           // 고독사 스택 (일정 스택 이상 쌓이면 고독사 판정)
int bathroomAbnormalStack;                // 화장실 스택 (일정 스택 이상 쌓이면 건강 이상 판정)
bool isModeChangedOnce;                   // 모드 수정되었는가? (한번 변경 후 초음파 센서에서 벗어나야 모드값변경 가능)

const int lonerNormalStandard =       10; // 고독사 검사 기준 (일상)
const int lonerSleepStandard =        10; // 고독사 검사 기준 (취침)
const int sonaRangeStandard =         7;  // 출입 검사 기준
const int bathroomStackStandard =     20; // 출입 검사 기준

const int dirPin_LivingRoom =         2;  // 적외선 센서 (거실)
const int dirPin_Bathroom =           3;  // 적외선 센서 (화장실)
const int sonaPin_Bathroom_echo =     4;  // 초음파 센서 (거실-화장실) 에코(input)
const int sonaPin_Bathroom_trig =     5;  // 초음파 센서 (거실-화장실) 트리거(output)
const int sonaPin_Outside_echo =      6;  // 초음파 센서 (거실-현관) 에코(input)
const int sonaPin_Outside_trig =      7;  // 초음파 센서 (거실-현관) 트리거(output)
const int shockPin_LivingRoom =       8;  // 충격감지 센서 (거실)
const int shockPin_Bathroom =         9;  // 충격감지 센서 (화장실)
const int buttonPin =                 10; // SOS 버튼 (거실)

/* ------------------------------------------------------------------ */




/* ------------------------------------------------------------------ */
// 적외선 센서
// 적외선 센서
// 적외선 센서
// 적외선 센서
// 적외선 센서

// 거실에 사람이 있는가?
bool IsDetectPersonLivingRoom() {
  detectValue = digitalRead(dirPin_LivingRoom);

  if(debugMode == 1 && detectValue == HIGH)
    Serial.print("거실 사람 감지됨");
  
  if(detectValue == HIGH)
    return true;
  else
    return false;
}

// 화장실에 사람이 있는가?
bool IsDetectPersonBathroom() {
  detectValue = digitalRead(dirPin_Bathroom);
  
if(debugMode == 2 && detectValue == HIGH)
    Serial.print("화장실 사람 감지됨");
  
  if(detectValue == HIGH)
    return true;
  else
    return false;
}

/* ------------------------------------------------------------------ */
// 초음파 센서
// 초음파 센서
// 초음파 센서
// 초음파 센서
// 초음파 센서

// 거실-화장실 간에 사람이동이 감지 되었는가?
bool IsMovePersonBathroom() {
  long duration, detectValue;

  digitalWrite(sonaPin_Bathroom_trig,HIGH);       // Trig에서 신호 송신 (초음파 쏘기)
  delayMicroseconds(10);                          // 10us 정도 유지
  digitalWrite(sonaPin_Bathroom_trig,LOW);        // Trig 신호 송신 정지

  duration = pulseIn(sonaPin_Bathroom_echo,HIGH); // Echo pin: HIGH->Low 간격을 측정
  detectValue = duration / 29 / 2;                // 측정 단위를 centimeter로 변경

  if(debugMode == 3 && detectValue <= sonaRangeStandard) {
      Serial.print("화장실 이동 사람 감지됨 , 수치 : ");
      Serial.println(detectValue);
  }   
  
  if(detectValue <= sonaRangeStandard) {
    if(!isModeChangedOnce) {
      isModeChangedOnce = true;
      return true;
    }
  }
  else {
    isModeChangedOnce = false;
    return false;
  }
}

// 거실-바깥 간에 사람이동이 감지 되었는가?
bool IsMovePersonOutside() {
  long duration, detectValue;

  digitalWrite(sonaPin_Outside_trig,HIGH);       // Trig에서 신호 송신 (초음파 쏘기)
  delayMicroseconds(10);                         // 10us 정도 유지
  digitalWrite(sonaPin_Outside_trig,LOW);        // Trig 신호 송신 정지

  duration = pulseIn(sonaPin_Outside_echo,HIGH); // Echo pin: HIGH->Low 간격을 측정
  detectValue = duration / 29 / 2;               // 측정 단위를 centimeter로 변경

  if(debugMode == 4 && detectValue <= sonaRangeStandard) {
      Serial.print("현관 이동 사람 감지됨 , 수치 : ");
      Serial.println(detectValue);
  }   
  
  if(detectValue <= sonaRangeStandard) {
    if(!isModeChangedOnce) {
      isModeChangedOnce = true;
      return true;
    }
  }
  else {
    isModeChangedOnce = false;
    return false;
  }
}

/* ------------------------------------------------------------------ */
// 충격 감지 센서
// 충격 감지 센서
// 충격 감지 센서
// 충격 감지 센서
// 충격 감지 센서

// 거실에서 낙상이 감지되었는가?
bool IsFallLivingRoom() {
  detectValue = digitalRead(shockPin_LivingRoom);

  if(debugMode == 5 && detectValue == HIGH)
    Serial.print("거실 충격 감지됨");
  
  if(detectValue == LOW)  // 충격감지는 반대로 해야함
    return true;
  else
    return false;
}

// 화장실에서 낙상이 감지되었는가?
bool IsFallBathroom() {
  detectValue = digitalRead(shockPin_Bathroom);

  if(debugMode == 6 && detectValue == HIGH)
    Serial.print("화장실 충격 감지됨");
  
  if(detectValue == LOW)  // 충격감지는 반대로 해야함
    return true;
  else
    return false;
}

/* ------------------------------------------------------------------ */
// 버튼 센서
// 버튼 센서
// 버튼 센서
// 버튼 센서
// 버튼 센서

// SOS버튼 클릭이 감지되었는가?
bool IsSOS() {
  detectValue = digitalRead(buttonPin);

  if(debugMode == 7 && detectValue == HIGH)
    Serial.print("SOS 버튼 감지됨");
    
  if(detectValue == HIGH)
    return true;
  else
    return false;
}

/* ------------------------------------------------------------------ */




/* ------------------------------------------------------------------ */
// 센서 활용 함수
// 센서 활용 함수
// 센서 활용 함수
// 센서 활용 함수
// 센서 활용 함수

// 도둑이 감지되었는가?
bool IsDetectTheif() {
  if(mode == OUTSIDE_MODE) { // 사람이 방 안에 있고 문을 통한 출입이 없었다면 도둑으로 판단 (문 이외의 수단으로 들어옴)
    if(IsDetectPersonLivingRoom()) {
      return true;
    }
  }
  return false;
}

// 귀가가 감지되었는가?
bool IsHomecoming() {
  if(mode == OUTSIDE_MODE) {   // 사람이 방 안에 없고 문을 통한 출입이 감지가 있었다면 귀가로 판단
    if(IsMovePersonOutside()) {
      return true;
    }
  }
  return false;
}

// 고독사가 감지되었는가?
bool IsDetectLoner() {
  if(IsDetectPersonLivingRoom()) // 사람이 있다고 감지되면 스택 초기화 , 없으면 축적
    lonerStack = 0;
  else if(IsDetectPersonBathroom()) // 사람이 있다고 감지되면 스택 초기화 , 없으면 축적
    lonerStack = 0;
  else
    lonerStack++;

  if(debugMode == 8) {
    Serial.print("고독사 스택 : ");
    Serial.println(lonerStack);
  }
    
  if(mode == INSIDE_MODE && lonerStack >= lonerNormalStandard) { // 축적된 스택이 일정 이상되면 고독사로 판단 (기준은 모드에 따라 다름)
    return true;
  }
  if(mode == SLEEP_MODE && lonerStack >= lonerSleepStandard) {
    return true;
  }
  return false;
}

// 화장실 빈도 높음으로 인해 건강 이상이 감지되었는가?
bool IsBathroomAbnormal() {
   if(IsMovePersonBathroom())
     bathroomAbnormalStack++;

   if(debugMode == 9) {
    Serial.print("화장실 스택 : ");
    Serial.println(bathroomAbnormalStack);
   }
    
  if(bathroomAbnormalStack >= bathroomStackStandard)
     return true;
  else
     return false;
}

/* ------------------------------------------------------------------ */
// 일반 함수
// 일반 함수
// 일반 함수
// 일반 함수
// 일반 함수

// 기상 시간이 되었는가?
bool IsWakeUpTime() {
  // 서버에서 시간을 가져와서 기상 시간이면 true
  // 여기서 화장실 빈도 초기화할것.
  bathroomAbnormalStack = 0;
  return true;
}

// 취침 시간이 되었는가?
bool IsSleepTime() {
  // 서버에서 시간을 가져와서 취침 시간이면 true

  return false;
}

// ------------------------------------------------------------------
// 메인

void setup() {
  mode = INSIDE_MODE;
  stat = NORMAL_STATUS;
  detectValue = 0;
  lonerStack = 0;
  bathroomAbnormalStack = 0;
  isModeChangedOnce = false;

  pinMode(dirPin_LivingRoom, INPUT);
  pinMode(dirPin_Bathroom, INPUT);
  pinMode(sonaPin_Bathroom_echo, INPUT);
  pinMode(sonaPin_Bathroom_trig, OUTPUT);
  pinMode(sonaPin_Outside_echo, INPUT);
  pinMode(sonaPin_Outside_trig, OUTPUT);
  pinMode(shockPin_LivingRoom, INPUT);
  pinMode(shockPin_Bathroom, INPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600); // 테스트용
}

void loop() {
  delay(500); // 1초마다 체크
  
  switch(mode) {
    
    case OUTSIDE_MODE :
      if(IsDetectTheif())         // 현재외출모드 + 도둑감지 = 도둑감지 통보
        stat = THEIF_ABNORMAL_STATUS;
      else {
        if(IsHomecoming())        // 현재외출모드 + 도둑감지X + 귀가감지  = 실내모드로 전환
          mode = INSIDE_MODE;
      }
      break;
      
    case SLEEP_MODE :
      if(IsWakeUpTime())          // 현재취침모드 + 기상시간
        mode = INSIDE_MODE;
      else {
        if(IsDetectLoner())
          stat = LONER_DANGER_STATUS;
        if(IsFallLivingRoom())
          stat = FALL_DANGER_STATUS;
        if(IsFallBathroom())
          stat = FALL_DANGER_STATUS;
        if(IsSOS())
          stat = SOS_DANGER_STATUS;
        if(IsBathroomAbnormal())
          stat = BATHROOM_ABNORMAL_STATUS;
      }
      break;
      
    case INSIDE_MODE :
      if(IsMovePersonOutside())   // 실내모드 + 외출감지
        mode = OUTSIDE_MODE;
      else {
        if(IsSleepTime())         // 실내모드 + 외출감지X + 취침시간
          mode = SLEEP_MODE;          
          
        if(IsDetectLoner())
          stat = LONER_DANGER_STATUS;
        if(IsFallLivingRoom())
          stat = FALL_DANGER_STATUS;
        if(IsFallBathroom())
          stat = FALL_DANGER_STATUS;
        if(IsSOS())
          stat = SOS_DANGER_STATUS;
        if(IsBathroomAbnormal())
          stat = BATHROOM_ABNORMAL_STATUS;
      }
      break;
    }

    if(debugShow) {
      Serial.println("------------------------");
      switch(mode) {
      case 1:
       Serial.println("현재 모드 : 평상(1)");
       break;
      case 2:
       Serial.println("현재 모드 : 외출(2)");
       break;
      case 3:
       Serial.println("현재 모드 : 취침(3)");
       break;
      }

      switch(stat) {
      case 100:
       Serial.println("현재 상태 : 정상(100)");
       break;
      case 200:
       Serial.println("현재 상태 : 고독사(200)");
       break;
      case 201:
       Serial.println("현재 상태 : 낙상(201)");
       break;
      case 202:
       Serial.println("현재 상태 : SOS(202)");
       break;
      case 300:
       Serial.println("현재 상태 : 화장실이상(300)");
       break;
      case 301:
       Serial.println("현재 상태 : 도둑감지(301)");
       break;
      }
   }
}
