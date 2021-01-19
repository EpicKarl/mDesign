// Version 1.5
/*
Ein Emergency Button aus der Ferne ist gefählich, da wir nicht sicherstellen können, dass die Verbidnung zu jeden Zeitpunkt zuverläsig ist, daher nicht zu empfehlen ---> Überarbeitung
Reset Button unnötog, wenn Emergency Button nicht implementiert
*/


#include <Arduino.h>
#include <ESP8266WebServer.h> 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <stdlib.h>

// Receiving Data by Philipp Otto ------------------------------------------------------------------------------
byte bufferData[11] = {'0'};
char incomingData[10] = {'0'};
byte dataToSend[6] = {'0'};
byte old_dataToSend[6] = {'0'};
char tmp_state[2] = {'0'};

byte incomingSignal;
char state;

void recieveData(){
  //Serial.setTimeout(100);
  if(Serial.available()){
    incomingSignal = Serial.readBytes(bufferData, 11);
    tmp_state[0] = bufferData[0];
    tmp_state[1] = bufferData[1];
    state = atoi(tmp_state)/10;            //verwendet bufferData[0],[1] um aus 6 & 5 -> 0x65 -> 'A' zu machen (Durch 10 um eine nichterklärebare Null loszuwerden!)
    incomingData[0] = state;            //Zuweisungen in char Array für Server
    incomingData[1] = bufferData[2];
    incomingData[2] = bufferData[3];
    incomingData[3] = bufferData[4];
    incomingData[4] = bufferData[5];
    incomingData[5] = bufferData[6];
    incomingData[6] = bufferData[7];
    incomingData[7] = bufferData[8];
    incomingData[8] = bufferData[9];
    incomingData[9] = bufferData[10];
//    for (auto &current : incomingData) {  //Konsolenausgabe zum Debuggen sendDataToSerial() muss in der main() auskommentiert sein
//      Serial.print(current);              
//    }Serial.print("\n");
  }
}

void sendDataToSerial(){
  if(dataToSend[0] != old_dataToSend[0] || //sendet nur wenn sich irgendwas ändert
     dataToSend[1] != old_dataToSend[1] || 
     dataToSend[2] != old_dataToSend[2] ||
     dataToSend[3] != old_dataToSend[3] ||
     dataToSend[4] != old_dataToSend[4] ||
     dataToSend[5] != old_dataToSend[5]){
    for (auto &current : dataToSend) { //Konsolenausgabe zum Debuggen receiveData() muss in der main() auskommentiert sein
      Serial.print(current);
    }
    for (int i = 0; i < 6; i++) {
      old_dataToSend[i] = dataToSend[i];
    }
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Instanz des ESP8266WebServers
ESP8266WebServer server(80);

// Make a wifi name and password as access points
const char *ssid = "AntidustA_Control";
const char *password = "AntidustA";

// ------------------------------------Declare constants to make the page to be visited.----------------------------
/*const String HtmlHtml = "<html><head>"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";*/
const String HtmlHtml = "<html><head>"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />"
"<meta http-equiv=\"REFRESH\" content=\"1\"/>"
"</head>";
const String HtmlTitle = "<h1>Control AntidustA 2.0 mit NodeMCU WiFi Access Point</h1><br/>";
const String HtmlHtmlClose = "</html>";
// -----------------------------------------------------------------------------------------------------------------
void response(){
  String htmlRes = HtmlHtml + HtmlTitle;
  if(dataToSend[0] == '0'){
    //STATE
    switch (state)
    {
      case 'A':
        htmlRes += "<h2>State: NONE</h2><br/>";
        break;
      case 'B':
        htmlRes += "<h2>State: INIT_DRIVE_LEFT</h2><br/>";
        break;
      case 'C':
        htmlRes += "<h2>State: INIT_DRIVE_UP</h2><br/>";
        break;
      case 'D':
        htmlRes += "<h2>State: IDLE</h2><br/>";
        break;
      case 'E':
        htmlRes += "<h2>State: START_CLEANING</h2><br/>";
        break;
      case 'F':
        htmlRes += "<h2>State: DRIVE_TO_UPPER_ENDPOSITION</h2><br/>";
        break;
      case 'G':
        htmlRes += "<h2>State: MOTOR_BREAK</h2><br/>";
        break;
      case 'H':
        htmlRes += "<h2>State: DRIVE_TO_LOWER_ENDPOSITION</h2><br/>";
        break;
      case 'I':
        htmlRes += "<h2>State: DRIVE_TO_THE_LEFT</h2><br/>";
        break;
      case 'J':
        htmlRes += "<h2>State: DRIVE_TO_THE_RIGHT</h2><br/>";
        break;
      case 'K':
        htmlRes += "<h2>State: STOP_EVERYTHING</h2><br/>";
        break;
      case 'L':
        htmlRes += "<h2>State: EMERGENCY_HOLD</h2><br/>";
        break;
      default:
        htmlRes += "<h2><font style=\"color:red\">FSM IST IN KEINEM DEFINIERTEN STATE! KONTROLLE DES SYSTEMS ERFORDERLICH!</font></h2><br/>";
        break;
    }
    //Fernwarung Starten
    htmlRes += "<a href=\"Start_FW\"><button style=\"background-color:red;color:black;width:60%;height:30%;\"><h1>Fernwartung starten</h1></button></a>";
    //Aktor und Sensorwerte
    htmlRes += "<h2>Aktor- und Sensorwerte des AntidustA:</h2><br/>";
    
    htmlRes += "<table>";
    
    if(incomingData[1] == '1'){
      htmlRes += "<tr> <td> <b>MOTOR_UP</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[1] == '0'){
      htmlRes += "<tr> <td> <b>MOTOR_UP</b> </td> <td style=\"background-color:#000000;color:white;\"align=center>OFF</td> </tr>";
    }
    
    if(incomingData[2] == '1'){
      htmlRes += "<tr> <td> <b>MOTOR_DOWN</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[2] == '0'){
      htmlRes += "<tr> <td> <b>MOTOR_DOWN</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }
    
    if(incomingData[3] == '1'){
      htmlRes += "<tr> <td> <b>MOTOR_LEFT</b </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[3] == '0'){
      htmlRes += "<tr> <td> <b>MOTOR_LEFT</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[4] == '1'){
      htmlRes += "<tr> <td> <b>MOTOR_RIGHT</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[4] == '0'){
      htmlRes += "<tr> <td> <b>MOTOR_RIGHT</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[5] == '1'){
      htmlRes += "<tr> <td> <b>MOTOR_CLEANINGUNIT</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[5] == '0'){
      htmlRes += "<tr> <td> <b>MOTOR_CLEANINGUNIT</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[6] == '1'){
      htmlRes += "<tr> <td> <b>SENSOR_RIGHT</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[6] == '0'){
      htmlRes += "<tr> <td> <b>SENSOR_RIGHT</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[7] == '1'){
      htmlRes += "<tr> <td> <b>SENSOR_LEFT</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[7] == '0'){
      htmlRes += "<tr> <td> <b>SENSOR_LEFT</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[8] == '1'){
      htmlRes += "<tr> <td> <b>SENSOR_UP</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[8] == '0'){
      htmlRes += "<tr> <td> <b>SENSOR_UP</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[9] == '1'){
      htmlRes += "<tr> <td> <b>SENSOR_DOWN</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[9] == '0'){
      htmlRes += "<tr> <td> <b>SENSOR_DOWN</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    htmlRes += "</table>";

    htmlRes += HtmlHtmlClose;
    server.send(200, "text/html", htmlRes); 
  }
  else {
    //STATE
    switch (state)
    {
      case 'A':
        htmlRes += "<h2>State: <font color:red>NONE</font></h2><br/>";
        break;
      case 'B':
        htmlRes += "<h2>State: DRIVE_UP</h2><br/>";
        break;
      case 'C':
        htmlRes += "<h2>State: DRIVE_DOWN</h2><br/>";
        break;
      case 'D':
        htmlRes += "<h2>State: DRIVE_LEFT</h2><br/>";
        break;
      case 'E':
        htmlRes += "<h2>State: DRIVE_RIGHT</h2><br/>";
        break;
      case 'F':
        htmlRes += "<h2>State: CLEANINGUNIT</h2><br/>";
        break;
      case 'G':
        htmlRes += "<h2>State: MOTOR_BREAK</h2><br/>";
        break;
      case 'H':
        htmlRes += "<h2>State: EMERGENCY_HOLD</h2><br/>";
        break;
      default:
        htmlRes += "<h2><font style=\"color:red\">FSM IST IN KEINEM DEFINIERTEN STATE! KONTROLLE DES SYSTEMS ERFORDERLICH!</font></h2><br/>"; 
        break;
    }
    //Y Drive Buttons
    if(dataToSend[1] == '1'){
      htmlRes += 
        "<a href=\"Pos_Y\"><button style=\"background-color:green;color:black;width:20%;height:5%;\">Hochfahren </button></a>"
        "<a href=\"Neg_Y\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Runterfahren </button></a>"
        "<a href=\"SY\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Stopp Hoch/Runter-Fahrt </button></a><br/><br/><br/>";
    }
    else if(dataToSend[2] == '1'){
      htmlRes += 
        "<a href=\"Pos_Y\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Hochfahren </button></a>"
        "<a href=\"Neg_Y\"><button style=\"background-color:green;color:black;width:20%;height:5%;\">Runterfahren </button></a>"
        "<a href=\"SY\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Stopp Hoch/Runter-Fahrt </button></a><br/><br/><br/>";
    } else {
      htmlRes += 
        "<a href=\"Pos_Y\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Hochfahren </button></a>"
        "<a href=\"Neg_Y\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Runterfahren </button></a>"
        "<a href=\"SY\"><button style=\"background-color:red;color:black;width:20%;height:5%;\">Stopp Hoch/Runter-Fahrt </button></a><br/><br/><br/>";
    }
    // X Drive Buttons
    if(dataToSend[3] == '1'){
      htmlRes += 
        "<a href=\"Pos_X\"><button style=\"background-color:green;color:black;width:20%;height:5%;\">Rechtsfahren </button></a>"
        "<a href=\"Neg_X\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Linksfahren </button></a>"
        "<a href=\"SX\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Stopp Rechts/Links-Fahrt </button></a><br/><br/><br/>";
    }
    else if(dataToSend[4] == '1'){
      htmlRes += 
        "<a href=\"Pos_X\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Rechtsfahren </button></a>"
        "<a href=\"Neg_X\"><button style=\"background-color:green;color:black;width:20%;height:5%;\">Linksfahren </button></a>"
        "<a href=\"SX\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Stopp Rechts/Links-Fahrt </button></a><br/><br/><br/>";
    } else {
      htmlRes += 
        "<a href=\"Pos_X\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Rechtsfahren </button></a>"
        "<a href=\"Neg_X\"><button style=\"background-color:black;color:white;width:20%;height:5%;\">Linksfahren </button></a>"
        "<a href=\"SX\"><button style=\"background-color:red;color:black;width:20%;height:5%;\">Stopp Rechts/Links-Fahrt </button></a><br/><br/><br/>";
    }

    
    //Cleaning Buttons
    if(dataToSend[5] == '1'){
      htmlRes += 
        "<a href=\"Start_Cleaning\"><button style=\"background-color:green;color:black;width:30%;height:5%;\">Start Reinigung</button></a>"
        "<a href=\"Stop_Cleaning\"><button style=\"background-color:black;color:white;width:30%;height:5%;\">Stopp Reinigung</button></a><br/><br/><br/>";
    } else
    {
      htmlRes += 
        "<a href=\"Start_Cleaning\"><button style=\"background-color:black;color:white;width:30%;height:5%;\">Start Reinigung</button></a>"
        "<a href=\"Stop_Cleaning\"><button style=\"background-color:red;color:black;width:30%;height:5%;\">Stopp Reinigung</button></a><br/><br/><br/>";
    }

    //Fernwartung Stoppen Button
    htmlRes += "<a href=\"Stop_FW\"><button style=\"background-color:black;color:white;width:60%;height:5%;\">Fernwartung stoppen</button></a>";
    
    //Aktor und Sensorwerte
    htmlRes += "<h2>Aktor- und Sensorwerte des AntidustA:</h2>";
    
    htmlRes += "<table>";
    
    if(incomingData[1] == '1'){
      htmlRes += "<tr> <td> <b>MOTOR_UP</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[1] == '0'){
      htmlRes += "<tr> <td> <b>MOTOR_UP</b> </td> <td style=\"background-color:#000000;color:white;\"align=center>OFF</td> </tr>";
    }
    
    if(incomingData[2] == '1'){
      htmlRes += "<tr> <td> <b>MOTOR_DOWN</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[2] == '0'){
      htmlRes += "<tr> <td> <b>MOTOR_DOWN</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }
    
    if(incomingData[3] == '1'){
      htmlRes += "<tr> <td> <b>MOTOR_LEFT</b </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[3] == '0'){
      htmlRes += "<tr> <td> <b>MOTOR_LEFT</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[4] == '1'){
      htmlRes += "<tr> <td> <b>MOTOR_RIGHT</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[4] == '0'){
      htmlRes += "<tr> <td> <b>MOTOR_RIGHT</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[5] == '1'){
      htmlRes += "<tr> <td> <b>MOTOR_CLEANINGUNIT</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[5] == '0'){
      htmlRes += "<tr> <td> <b>MOTOR_CLEANINGUNIT</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[6] == '1'){
      htmlRes += "<tr> <td> <b>SENSOR_RIGHT</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[6] == '0'){
      htmlRes += "<tr> <td> <b>SENSOR_RIGHT</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[7] == '1'){
      htmlRes += "<tr> <td> <b>SENSOR_LEFT</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[7] == '0'){
      htmlRes += "<tr> <td> <b>SENSOR_LEFT</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[8] == '1'){
      htmlRes += "<tr> <td> <b>SENSOR_UP</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[8] == '0'){
      htmlRes += "<tr> <td> <b>SENSOR_UP</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    if(incomingData[9] == '1'){
      htmlRes += "<tr> <td> <b>SENSOR_DOWN</b> </td> <td style=\"background-color:#08FF08;color:#000000\"align=center>ON</td> </tr>";
    }
    if(incomingData[9] == '0'){
      htmlRes += "<tr> <td> <b>SENSOR_DOWN</b> </td> <td style=\"background-color:#000000;color:white\"align=center>OFF</td> </tr>";
    }

    htmlRes += "</table>";

    htmlRes += HtmlHtmlClose;
    server.send(200, "text/html", htmlRes);
  }
}
void positiveYDrive(){
  dataToSend[1] = '1';
  dataToSend[2] = '0';
  response();
}
void negativeYDrive(){
  dataToSend[1] = '0';
  dataToSend[2] = '1';
  response();
}
void stopYDrive(){
  dataToSend[1] = '0';
  dataToSend[2] = '0';
  response();
}
void positiveXDrive(){
  dataToSend[3] = '1';
  dataToSend[4] = '0';
  response();
}
void negativeXDrive(){
  dataToSend[3] = '0';
  dataToSend[4] = '1';
  response();
}
void stopXDrive(){
  dataToSend[3] = '0';
  dataToSend[4] = '0';
  response();
}
void startCleaning(){
  dataToSend[5] = '1';
  response();
}
void stopCleaning(){
  dataToSend[5] = '0';
  response();
}
void startFW(){
  dataToSend[0] = '1';
  response();
}
void stopFW(){
  dataToSend[0] = '0';
  dataToSend[1] = '0';
  dataToSend[2] = '0';
  dataToSend[3] = '0';
  dataToSend[4] = '0';
  dataToSend[5] = '0';
  response();
}

// STANDARD ARDUINO CODE AB HIER --------------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  // Status LED
  pinMode(D0, OUTPUT);
  
  WiFi.softAP(ssid, password);
  
  IPAddress apip = WiFi.softAPIP(); // Get the IP server
  Serial.print("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
  Serial.println(ssid);
  Serial.print("Visit this IP : ");
  Serial.print(apip); // Prints the IP address of the server to be visited
  Serial.println(" in your browser.");
      
  server.on("/", response); 

  // Y Drive
  server.on("/Pos_Y", positiveYDrive);
  server.on("/Neg_Y", negativeYDrive);
  server.on("/SY", stopYDrive);

  // X Drive
  server.on("/Pos_X", positiveXDrive);
  server.on("/Neg_X", negativeXDrive);
  server.on("/SX", stopXDrive);

  // Cleaning
  server.on("/Start_Cleaning", startCleaning);
  server.on("/Stop_Cleaning", stopCleaning);

  //Fernwartung 
  server.on("/Start_FW", startFW);
  server.on("/Stop_FW", stopFW);

  // Start the server
  server.begin();
  Serial.println("HTTP server beginned");
}

void loop() {
  //Status LED, lights up when system ready
  digitalWrite(D0, LOW);
  recieveData();
  server.handleClient();
  sendDataToSerial();
}