import serial
import asyncio
from telegram import Bot

# Telegram bot token ve chat ID (kendine göre değiştir)
TOKEN = "7710120435:AAHo4RVpLI7-T0Fk-wp5y4EcTHyLr1q4Ilc"
CHAT_ID = 5124667852

# Seri port ayarları
SERIAL_PORT = "COM5"    # Arduino'nun bağlı olduğu COM portu
BAUD_RATE = 9600

bot = Bot(token=TOKEN)

async def send_telegram_message(text):
    try:
        await bot.send_message(chat_id=CHAT_ID, text=text)
        print(f"Telegram mesajı gönderildi: {text}")
    except Exception as e:
        print(f"Telegram mesaj gönderme hatası: {e}")

def send_message(text):
    asyncio.run(send_telegram_message(text))

def main():
    try:
        arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print("Arduino bağlantısı açıldı. Telegram bildirim sistemi başladı...")
    except Exception as e:
        print(f"Arduino seri portu açılamadı: {e}")
        return

    while True:
        try:
            line = arduino.readline().decode('utf-8', errors='ignore').strip()
            if line:
                print(f"Arduino'dan gelen: {line}")

                # Mesajlara göre Telegram mesajı gönder
                if "SYSTEM_ON" in line:
                    send_message("✅ Güvenlik sistemi aktifleştirildi.")
                elif "ALARM" in line:
                    send_message("🚨 Güvenlik alarmı: Hareket algılandı!")
                elif "SYSTEM_OFF" in line:
                    send_message("❌ Güvenlik sistemi devre dışı bırakıldı.")
        except Exception as e:
            print(f"Hata: {e}")

if __name__ == "__main__":
    main()


