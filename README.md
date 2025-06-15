MASAÜSTÜ AKILLI GÜVENLİK ASİSTANI


Arduino ile geliştirilmiş, hareket algılayıcı (PIR), tuş takımı üzerinden şifre girilerek kontrol edilen, Telegram ile uzaktan alarm bildirimi gönderen, kamera ile görüntü alabilen güvenlik sistemi projesi.

🛡️ Proje Tanımı


Bu proje, PIR hareket sensörü ve 4x4 tuş takımını kullanarak şifre ile kontrol edilen bir güvenlik alarm sistemidir. Sistemin temel işlevleri şunlardır:
-'A' tuşu ile sistemi aktif hale getirme (kollama)
-Hareket algılandığında alarm çalma ve kırmızı LED yakma
-Doğru şifre (varsayılan: 5252) girilip '#' tuşuna basıldığında alarmı durdurma
-Yanlış şifre girişlerinde kısa uyarı sesi
-Python üzerinden seri port ile bağlantı kurularak Telegram üzerinden alarm durumlarının bildirilmesi
-Hareket algılanınca kamera ile görüntü alma ve anlık kayıt


🧩 Kullanılan Bileşenler


-Arduino UNO veya ESP32
-PIR Hareket Sensörü (HC-SR501)
-4x4 Tuş Takımı
-Buzzer
-Kırmızı ve Yeşil LED
-Dirençler
-Jumper Kablolar
-Python (Telegram Bot entegrasyonu için)

🔧 Tuş Görevleri

Tuş	İşlev
-A	Sistemi aktif hale getir (kol)
-#	Girilen şifreyi onayla (alarmı durdurmak için)
-D	Girilen şifreyi iptal et
-0-9, B, C	Şifre girişinde kullanılır

📚 Kullanılan Kütüphaneler

Arduino (ESP32/UNO) Tarafında:
Kütüphane	Açıklama
-Keypad.h :	4x4 tuş takımı girişini okumak için
-(Standart)	Arduino temel fonksiyonları otomatik
-PIR sensörü için ayrı bir kütüphane gerekmez, doğrudan dijital giriş olarak kullanılır.

Python Tarafında:
Kütüphane	Açıklama
-pyserial (serial):	Arduino ile bilgisayar arasında seri iletişim
-asyncio:	Asenkron Telegram mesaj gönderimi için
-python-telegram-bot:	Telegram API’si ile mesaj göndermek için

Python kütüphanelerini yüklemek için:
pip install pyserial python-telegram-bot


🛠️ Kurulum ve Kullanım

1.Arduino kodunu cihazınıza yükleyin.
2.PIR sensör, LED’ler, buzzer ve tuş takımını uygun pinlere bağlayın (kodda belirtilen pinler).
3.Python Telegram bot scriptini çalıştırın (bot token ve chat ID ayarlarını yapmayı unutmayın).
4.Sistemi A tuşuyla aktifleştirin.
5.Hareket algılandığında alarm devreye girer, Telegram’dan bildirim gelir.
6.Alarmı durdurmak için doğru şifreyi girip # tuşuna basın.

📅 Hazırlayan
Ceylan Ulusoy
Tarih: 17/06/2025
