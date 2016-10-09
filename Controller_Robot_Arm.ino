//นี่คือโค้ด ฝั่ง nodeMCU

// Add Libraey
#include <ESP8266WiFi.h>  // Connected WiFi
#include <Servo.h>        // Use Servo

#define SERVO_PIN D2  // นี่คือกำหนดขาให้ Servo

const char* ssid     = "Happy Phone 3G 4.0\"";     // Set SSID shareEWTC
const char* password = "900791d51808"; // Set password 12345abcde
const char* host = "dweet.io";          // Set host 

int intStart[4] = {129,50,100,120}; 
int intEnd[4] = {154,120,120,130};
//Happy Phone 3G 4.0" ==> 900791d51808  
//AndroidAP-DUOS ==> nzdn0541
Servo myservo,myservo1,myservo2,myservo3;  // ประกาศ object ของการใช้ Servo
int analogValue;

// ##############################################################################
// setup
// ##############################################################################

void setup() 
{
  //myservo.attach(SERVO_PIN);
  myservo.attach(4);
  myservo.attach(0);
  myservo.attach(2);
  myservo.attach(14);
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

// ##############################################################################
// loop
// ##############################################################################


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

  // ##############################################################################
  //https://dweet.io/get/latest/dweet/for/SuperMaster
  // ##############################################################################
  
  client.print(String("GET /get/latest/dweet/for/SuperWorawut HTTP/1.1\r\n") +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n" +
               "Cache-Control: max-age=0\r\n\r\n");
  delay(3000);
  
  while (client.available()) 
  {
    String strJSON = client.readStringUntil('\r');
    Serial.println(strJSON);  // Display All JSON

    String strAnalog = strJSON.substring(140, 143);
    Serial.println(strAnalog);  // Display only Value from Dweet

    String strServo = strJSON.substring(137,138);
    Serial.println();
    Serial.println("Servo==> ");
    Serial.println(strServo);

    analogValue = strAnalog.toInt(); // Change String to int
    int index =strServo.toInt();

    //การกำหนด องศา ของ Servo (ตัวแปร, ค่าเริ่มต้น, 0, 179)
    analogValue = map(analogValue, 0, 100, intStart[0], intEnd[0]);

    Serial.println();
    Serial.println();
    Serial.print("andlogValue ==> ");
    Serial.println(analogValue);
    
    myservo.write(analogValue);
  
  } // while
  Serial.println();
  Serial.println();
  Serial.print("andlogValue ==> ");
  Serial.println(analogValue);
  
} // loop
