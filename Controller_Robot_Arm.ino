// Add Liabrary
#include <ESP8266WiFi.h> //Connected WiFi
#include <Servo.h>  //Use Servo

#define SERVO_PIN D2  // นี่คือกำหนดขาให้ Servo ไฟมากน้อยขึ้นกะองศาservoด้วย

const char* ssid     = "shareEWTC";     // Set SSID 
const char* password = "12345abcde"; // Set password 
const char* host = "dweet.io";          // Set host  


Servo myservo;  // ประกาศ object ของการใช้ Servo
int analogValue;

void setup() 
{
  myservo.attach(SERVO_PIN);
  Serial.begin(115200);                 // Print setting message
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");                  // Print WiFi status
  }
  Serial.println("");
  Serial.println("WiFi connected");     // Print connect status
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());       // Print IP address
} // setup

void loop() 
{
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;              // Set HTTP Port
  if (!client.connect(host, httpPort))  // Test connection
  {
    Serial.println("connection failed");  // Print connection fail messag
    return;
  }

  
  //https://dweet.io/get/latest/dweet/for/SuperWorawut
  client.print(String("GET /get/latest/dweet/for/SuperWorawut HTTP/1.1\r\n") +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n" +
               "Cache-Control: max-age=0\r\n\r\n");
  delay(1000);
  while (client.available()) 
  {
    String line = client.readStringUntil('\r');
    Serial.println(line);

    String test = line.substring(140, 143);
    Serial.println(test);

    analogValue = test.toInt(); // Change String to int
    //analogValue = map(analogValue, 0, 1023, 0, 140);

    Serial.println();
    Serial.println();
    Serial.print("andlogValue ==> ");
    Serial.println(analogValue);
    
    myservo.write(analogValue);

    
  } // while
} // loop

