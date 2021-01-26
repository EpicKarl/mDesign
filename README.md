# mDesign

# Aufspielen der Fernwartungsoftware auf den Node MCU ESP 8266:

1. Installiere VS Code
2. Installiere die Extension PlatformIO
3. Installiere den USB UART Treiber für den ESP 8266 (Ordner: ESPDriver oder https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers).
3.1 Workaround für die Treiberinstallation: Arduino IDE installieren

4. Clone Repository
5. VS Code starten Platform IO öffnen "Open Project" auswählen und den Ordner Fernwartung im Repo auswählen.
6. ESP mit PC verbinden
6.1 Bei COM Port Problemen siehe: https://docs.platformio.org/en/latest/projectconf/section_env_upload.html
7. Vorher checken ob SOFTAP definiert und DEBUGMODE NICHT definiert sind.
8. Upload Button in Platform IO Project drücken. (blaue Leiste, Pfeil nach rechts)

# Debugging der Fernwartung

Für das Debuggen gibt es im Code verschiedene Präprozessoranweisungen. Dies ist nötig, da der ESP standardmäßig nur einen Hardware Serial Port besitzt. Beachte Hinweise im Code! Während ein PC an dem ESP angeschlossen ist, können dem Controllino KEINE Befehle gesendet werden.
