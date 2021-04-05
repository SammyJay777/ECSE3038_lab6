#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial esp(10, 11); // TX | RX
#define DEBUG true
long randNumber;
int getWaterLevel();

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}
void setup() {

  Serial.begin(115200);
  esp.begin(115200);
  randomSeed(analogRead(0));
  
  Serial.write("AT+RST");
  //Serial.println("Enter AT commands: ");
  sendData("AT+RST\r\n", 10000, DEBUG);
  //sendData("AT+CWLAP\r\n", 10000, DEBUG);
  sendData("AT+CWJAP=\"MonaConnect-iTest\",\"\"\r\n", 5000, DEBUG);
  //sendData("AT+CIFSR\r\n", 3000, DEBUG);  
}
void loop() {
  //Serial.println(getWaterLevel());
   // getWaterLevel();
 if (Serial.available()) {      // If anything comes in Serial (USB),
 esp.write(Serial.read());   // read it and send it out Serial1 (pins 0 & 1)
 }

 if (esp.available()) {     // If anything comes in Serial1 (pins 0 & 1)
   Serial.write(esp.read());   // read it and send it out Serial (USB)
  } 
    // sendData("AT+CIPSTART=\"TCP\",\"10.22.4.44\",5000\r\n", 1000, DEBUG);
    // String post = "POST /data HTTP/1.1\r\nHost: 10.22.4.6595:5000\r\nContent-Type: Application/json\r\n{\"apples\": 1, \"oranges\": 3}\r\n\r\n";
    // sendData("AT+CIPSEND=123\r\n", 1000, DEBUG);
    // sendData(post, 5000, DEBUG);
}
 int getWaterLevel()
 {
   randNumber = random(10, 201);
   return randNumber;
 }