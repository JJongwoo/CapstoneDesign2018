    /*
    한성대 캡스톤 디자인
    망고스틴 조 - Hello, Grandma
*/
// ------------------------------------------------------------------
// 전처리

// #include <time.h> 테스트 필요

#define INSIDE_MODE               1    // 모드 - 실내
#define OUTSIDE_MODE              2    // 모드 - 외출
#define SLEEP_MODE                3    // 모드 - 취침
#define NORMAL_STATUS             100  // 상태 - 정상
#define LONER_DANGER_STATUS       200  // 상태 - 위험(고독사 감지)
#define FALL_DANGER_STATUS        201  // 상태 - 위험(낙상 감지)
#define SOS_DANGER_STATUS         202  // 상태 - 위험(SOS 감지)
#define BATHROOM_ABNORMAL_STATUS  300  // 상태 - 이상(화장실 빈도 높음)
#define THEIF_ABNORMAL_STATUS     301  // 상태 - 이상(도둑 감지)

// #define LIGHT_ALALOG_PIN       A0   // 아날로그핀인데 현재 조도 센서 안씀.

// ------------------------------------------------------------------
// 변수

int mode;           // 모드 값 ( 1 / 2 / 3 )
int stat;           // 상태 값 ( 100 / 200 / 201 / 202 / 300 / 301 )

int detectValue;    // 측정 값
int lonerStack;     // 고독사 스택 (일정 스택 이상 쌓이면 고독사 판정)
int bathroomStack;  // 화장실 스택 (일정 스택 이상 쌓이면 건강 이상 판정)

const int lonerNormalStandard = 10; // 고독사 검사 기준 (실내)
const int lonerDownStandard =   10; // 고독사 검사 기준 (취침)
const int sonaStandard =        50; // 출입 검사 기준
const int bathroomStandard =    20; // 출입 검사 기준

const int dirPin_Innerroom =          1;  // 적외선 센서 (안방)
const int dirPin_Bathroom =           2;  // 적외선 센서 (화장실)
const int sonaPin_InnerroomBathroom_echo = 3;  // 초음파 센서 (안방-화장실) 에코(input)
const int sonaPin_InnerroomBathroom_trig = 4;  // 초음파 센서 (안방-화장실) 트리거(output)
const int sonaPin_InnerroomOutside_echo =  5;  // 초음파 센서 (현관-안방) 에코(input)
const int sonaPin_InnerroomOutside_trig =  6;  // 초음파 센서 (현관-안방) 트리거(output)
const int shockPin =                  7;  // 충격감지 센서 (안방)
const int buttonPin =                 8;  // SOS 버튼 (안방)

// ------------------------------------------------------------------
// 센서 함수

// 안방에 사람이 있는가? (적외선 센서)
bool IsDetectPersonInnerroom() {
  detectValue = digitalRead(dirPin_Innerroom);
  if(detectValue == HIGH)
    return true;
  else
    return false;
}

// 화장실에 사람이 있는가? (적외선 센서)
bool IsDetectPersonBathRoom() {
  detectValue = digitalRead(dirPin_Bathroom);
  if(detectValue == HIGH)
    return true;
  else
    return false;
}

// 안방-화장실 간에 사람이동이 감지 되었는가? (초음파 센서)
bool IsDetectPersonInnerroomBathroom() {
  long duration, detectValue;

  digitalWrite(sonaPin_InnerroomBathroom_trig,HIGH);       // Trig에서 신호 송신 (초음파 쏘기)
  delayMicroseconds(10);      // 10us 정도 유지
  digitalWrite(sonaPin_InnerroomBathroom_trig,LOW);        // Trig 신호 송신 정지

  duration = pulseIn(sonaPin_InnerroomBathroom_echo,HIGH); // Echo pin: HIGH->Low 간격을 측정
  detectValue = duration / 29 / 2;     // 측정 단위를 centimeter로 변경
  
  if(detectValue <= sonaStandard)
    return true;
  else
    return false;
}

// 안방-바깥 간에 사람이동이 감지 되었는가? (초음파 센서)
bool IsDetectPersonInnerroomOutside() {
  long duration, detectValue;

  digitalWrite(sonaPin_InnerroomOutside_trig,HIGH);       // Trig에서 신호 송신 (초음파 쏘기)
  delayMicroseconds(10);      // 10us 정도 유지
  digitalWrite(sonaPin_InnerroomOutside_trig,LOW);        // Trig 신호 송신 정지

  duration = pulseIn(sonaPin_InnerroomOutside_echo,HIGH); // Echo pin: HIGH->Low 간격을 측정
  detectValue = duration / 29 / 2;     // 측정 단위를 centimeter로 변경
  
  if(detectValue <= sonaStandard)
    return true;
  else
    return false;
}

// 낙상이 감지되었는가? (충격감지 센서)
bool IsDetectFall() {
  detectValue = digitalRead(shockPin);
  //Serial.print("충격센서값:");   // 테스트
  //Serial.println(detectValue);   // 테스트
  if(detectValue == LOW)  // 충격감지는 반대로 해야함
    return true;
  else
    return false;
}

// SOS버튼 클릭이 감지되었는가? (버튼 센서)
bool IsDetectSOS() {
  detectValue = digitalRead(buttonPin);
  if(detectValue == HIGH)
    return true;
  else
    return false;
}

// ------------------------------------------------------------------
// 센서 함수를 이용한 함수

// 도둑이 감지되었는가?
bool IsDetectTheif() {
  if(IsDetectPersonInnerroom()) {   // 사람이 방 안에 있고 문을 통한 출입이 없었다면 도둑으로 판단 (문 이외의 수단으로 들어옴)
    if(!IsDetectPersonInnerroomOutside())
      return true;
  }
  return false;
}

// 귀가가 감지되었는가?
bool IsDetectHomecoming() {
  if(!IsDetectPersonInnerroom()) {   // 사람이 방 안에 없고 문을 통한 출입이 감지가 있었다면 귀가로 판단
    if(IsDetectPersonInnerroomOutside())
      return true;
  }
  return false;
}

// 고독사가 감지되었는가?
bool IsDetectLoner() {
  if(IsDetectPersonInnerroom()) // 사람이 있다고 감지되면 스택 초기화 , 없으면 축적
    lonerStack = 0;
  else
    lonerStack++;
    
  if(mode == INSIDE_MODE && lonerStack >= lonerNormalStandard) { // 축적된 스택이 일정 이상되면 고독사로 판단 (기준은 모드에 따라 다름)
    return true;
  }
  if(mode == SLEEP_MODE && lonerStack >= lonerDownStandard) {
    return true;
  }
  return false;
}

// 화장실 빈도 높음으로 인해 건강 이상이 감지되었는가?
bool IsDetectBathroomAbnormal() {
   if(IsDetectPersonInnerroomBathroom())
     bathroomStack++;
    
  if(bathroomStack >= bathroomStandard)
     return true;
  else
     return false;
}

// ------------------------------------------------------------------
// 일반 함수

// 기상 시간이 되었는가?
bool IsDetectWakeUpTime() {
  // 서버에서 시간을 가져와서 기상 시간이면 true
  // 여기서 화장실 빈도 초기화할것.
  bathroomStack = 0;
  return true;
}

// 취침 시간이 되었는가?
bool IsDetectSleepTime() {
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
  bathroomStack = 0;

  pinMode(dirPin_Innerroom, INPUT);
  pinMode(dirPin_Bathroom, INPUT);
  pinMode(sonaPin_InnerroomBathroom_echo, INPUT);
  pinMode(sonaPin_InnerroomBathroom_trig, OUTPUT);
  pinMode(sonaPin_InnerroomOutside_echo, INPUT);
  pinMode(sonaPin_InnerroomOutside_trig, OUTPUT);
  pinMode(shockPin, INPUT);
  pinMode(buttonPin, INPUT);

  //Serial.begin(9600); // 테스트용
}

void loop() {
  delay(200); // 0.2초마다 체크

  //Serial.println(mode); // 테스트용
  //Serial.println(stat); // 테스트용
  
  switch(mode) {
    
    case OUTSIDE_MODE :
      if(IsDetectTheif())         // 현재외출모드 + 도둑감지 = 도둑감지 통보
        stat = THEIF_ABNORMAL_STATUS;
      else {
        if(IsDetectHomecoming())  // 현재외출모드 + 도둑감지X + 귀가감지  = 실내모드로 전환
          mode = INSIDE_MODE;
      }
      break;
      
    case SLEEP_MODE :
      if(IsDetectWakeUpTime())    // 현재취침모드 + 기상시간
        mode = INSIDE_MODE;
      else {
        if(IsDetectLoner())
          stat = LONER_DANGER_STATUS;
        if(IsDetectFall())
          stat = FALL_DANGER_STATUS;
        if(IsDetectSOS())
          stat = SOS_DANGER_STATUS;
        if(IsDetectBathroomAbnormal())
          stat = BATHROOM_ABNORMAL_STATUS;
      }
      break;
      
    case INSIDE_MODE :
      if(IsDetectPersonInnerroomOutside())   // 실내모드 + 외출감지
        mode = OUTSIDE_MODE;
      else {
        if(IsDetectSleepTime()) // 실내모드 + 외출감지X + 취침시간
          mode = SLEEP_MODE;          
          
        if(IsDetectLoner())
          stat = LONER_DANGER_STATUS;
        if(IsDetectFall())
          stat = FALL_DANGER_STATUS;
        if(IsDetectSOS())
          stat = SOS_DANGER_STATUS;
        if(IsDetectBathroomAbnormal())
          stat = BATHROOM_ABNORMAL_STATUS;
      }
      break;
      
    default:
      // SEND_ERROR(30001); // 모드 이상값 발생?
      break;
    }
}
