# masa-st-ak-ll-g-venlikasistan-
Arduino ile geliştirilmiş, hareket algılayıcı (PIR), keypad üzerinden şifre girilerek kontrol edilen, Telegram ile uzaktan alarm bildirimi gönderen güvenlik sistemi projesi.
/*
  =============================================================
  🛡️ Arduino Tabanlı Güvenlik Alarm Sistemi
  =============================================================

  📌 Açıklama:
  Bu proje, PIR hareket sensörü ve 4x4 keypad kullanarak şifre ile
  kontrol edilen bir güvenlik alarm sistemidir. Sistemde:
  
  - 'A' tuşu ile sistemi aktif hale getirirsiniz.
  - Hareket algılanırsa alarm çalar (buzzer) ve LED yanar.
  - Doğru şifre ('5252') girilip '#' tuşuna basıldığında sistem durur.
  - Yanlış şifrelerde uyarı sesi verilir.
  - Python üzerinden seri port ile bağlanılarak Telegram'a alarm durumu gönderilir.

  🧩 Kullanılan Bileşenler:
  - PIR Sensör (HC-SR501)
  - 4x4 Keypad
  - Buzzer
  - Kırmızı ve Yeşil LED
  - Arduino UNO/Nano
  - Python (Telegram bot ile seri port üzerinden bildirim)

  🔧 Tuş Görevleri:
  - 'A' → Sistemi aktif hale getir (arm)
  - '#' → Şifreyi onayla (alarmı durdur)
  - 'D' → Girilen şifreyi iptal et
  - 0-9, A-D → Şifre karakterleri olarak kullanılır

  🛡️ Varsayılan Şifre: 5252

  🖥️ Python Scripti:
  Arduino'nun seri port çıktısına göre Telegram üzerinden
  kullanıcıya SYSTEM_ON / ALARM_ON / SYSTEM_OFF bildirimleri gönderilir.

  Hazırlayan: [Adını buraya yazabilirsin]
  Tarih: [Tarih buraya]
*/

