#include <Keypad.h>

// Pin tanımlamaları
#define PIR_PIN 2
#define BUZZER_PIN 3
#define RED_LED_PIN 4
#define GREEN_LED_PIN 5

// Keypad ayarları
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// SENİN BAĞLANTINA GÖRE DÜZENLENMİŞ:
byte rowPins[ROWS] = {9, 8, 7, 6};       // R1, R2, R3, R4
byte colPins[COLS] = {13, 12, 11, 10};   // C1, C2, C3, C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Sistem değişkenleri
String password = "5252";  // Şifreyi buradan değiştirebilirsiniz
String inputPassword = "";
bool motionDetected = false;
bool systemArmed = false;   // Başlangıçta sistem kapalı
bool alarmActive = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);  // Başlangıçta sistem kapalı, yeşil led yanar
  digitalWrite(BUZZER_PIN, LOW);
  
  Serial.println("Güvenlik Sistemi Başlatıldı");
  Serial.println("PIR sensör kalibre ediliyor...");
  delay(2000);
  
  Serial.println("Sistem hazır!");
  Serial.println("Sistem şu anda kapalı (Yeşil LED)");
  Serial.println("'A' tuşuna basarak sistemi aktifleştirin");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    handleKeypadInput(key);
  }

  if (systemArmed) {
    checkMotionSensor();
  }
  
  if (alarmActive) {
    startAlarmSound();
  }
}

void handleKeypadInput(char key) {
  Serial.print("Basılan tuş: ");
  Serial.println(key);

  if (key == 'A') {
    if (!systemArmed) {
      activateSystem();
    }
  }
  else if (key == '#') {
    Serial.print("# tuşuna basıldı. Girilen şifre: ");
    Serial.println(inputPassword);
    
    if (alarmActive || systemArmed) {
      checkPassword();
    } else {
      Serial.println("Sistem aktif değil!");
    }
    inputPassword = "";
  }
  else if (key == 'D') {
    inputPassword = "";
    Serial.println("Şifre girişi iptal edildi");
  }
  else {
    if (inputPassword.length() < 10) {
      inputPassword += key;
      Serial.print("Şifre: ");
      for (int i = 0; i < inputPassword.length(); i++) {
        Serial.print("*");
      }
      Serial.print(" (Uzunluk: ");
      Serial.print(inputPassword.length());
      Serial.println(")");
    }
  }
}

void checkMotionSensor() {
  int pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH && !alarmActive && !motionDetected) {
    motionDetected = true;
    triggerAlarm();
    Serial.println("🚨 YENİ HAREKET ALGILANDI!");
  }
}

void triggerAlarm() {
  alarmActive = true;
  
  Serial.println("HAREKET ALGILANDI! ALARM AKTİF!");
  Serial.println("Şifreyi girin ve '#' tuşuna basın");

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, HIGH);
  
  Serial.println("ALARM");
  // Telegram Python tarafına mesaj gönderiliyor
  Serial.println("ALARM_ON");
  
  startAlarmSound();
}

void startAlarmSound() {
  static unsigned long lastBeep = 0;
  static bool beepState = false;

  if (millis() - lastBeep > 500) {
    beepState = !beepState;
    digitalWrite(BUZZER_PIN, beepState);
    lastBeep = millis();
  }
}

void checkPassword() {
  Serial.print("Kontrol edilen şifre: '");
  Serial.print(inputPassword);
  Serial.print("' - Doğru şifre: '");
  Serial.print(password);
  Serial.println("'");

  if (inputPassword == password) {
    Serial.println("✅ Şifre doğru! Sistem deaktif edildi.");
    deactivateSystem();
  } else {
    Serial.println("❌ Yanlış şifre! Tekrar deneyin.");
    // Kısa uyarı sesi
    tone(BUZZER_PIN, 1000, 200);
  }
  inputPassword = "";
}

void activateSystem() {
  systemArmed = true;
  alarmActive = false;
  motionDetected = false;

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Sistem aktifleştirildi!");
  Serial.println("Hareket algılama başladı...");
  Serial.println("SYSTEM_ON");
  // Kısa bip sesi
  for (int i = 0; i < 2; i++) {
    tone(BUZZER_PIN, 1000, 100);
    delay(150);
  }
}

void deactivateSystem() {
  systemArmed = false;
  alarmActive = false;
  motionDetected = false;

  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);

  Serial.println("✅ Sistem tamamen deaktif edildi!");
  Serial.println("Yeşil LED: Sistem güvenli");
  Serial.println("'*' tuşuna basarak tekrar aktifleştirin");
  Serial.println("SYSTEM_OFF");
}
