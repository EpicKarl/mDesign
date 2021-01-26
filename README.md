# mDesign

# Aufspielen der Fernwartungsoftware auf den Node MCU ESP 8266:

1. Installiere VS Code
2. Installiere die Extension PlatformIO
3. Installiere den USB UART Treiber für den ESP 8266 aus dem Ordner "ESPDriver" oder lade ihn [hier](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) herunter.
4. Workaround für die Treiberinstallation: Arduino IDE installieren

5. Clone Repository
6. VS Code starten Platform IO öffnen "Open Project" auswählen und den Ordner Fernwartung im Repo auswählen.
7. ESP mit PC verbinden
8. Bei COM Port Problemen auf der platformIO [hier](https://docs.platformio.org/en/latest/projectconf/section_env_upload.html) nachschauen.
9. Vorher checken ob SOFTAP definiert und DEBUGMODE NICHT definiert sind.
10. Upload Button in Platform IO Project drücken. (blaue Leiste, Pfeil nach rechts)

# Debugging der Fernwartung

Für das Debuggen gibt es im Code verschiedene Präprozessoranweisungen. Dies ist nötig, da der ESP standardmäßig nur einen Hardware Serial Port besitzt. Beachte Hinweise im Code! Während ein PC an dem ESP angeschlossen ist, können dem Controllino KEINE Befehle gesendet werden.
