#include <Arduino.h>
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <ArduinoJson.h>
// #include <SoftwareSerial.h>
// #include <DHT.h>

// DHT dht;

// SoftwareSerial SerialB(16, 17); // RX, TX
HardwareSerial SerialB(2); // A9: TX, A10: RX
// #define SerialB_Txd_pin 17
// #define SeriaB_Rxd_pin 16

// D4 RX - PA9
// D5 TX - PA10
// (Send and Receive)
int led1 = 2;
int led2 = 4;
int button1 = 22;
int button2 = 23;
int ledStart1=0;
int ledStart2=0;
void setup(){
  // dht.begin(); // data pin 2

  Serial.begin(9600);
  SerialB.begin(9600);
  // SerialB.begin(9600, SerialB_Txd_pin, SeriaB_Rxd_pin); // Define and start Receiver serial port
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void loop(){    

  // float humidity2 = dht.getHumidity();
  // float temperature2 = dht.getTemperature();
  // Serial.println(humidity2);
  // Serial.println(temperature2);
  // delay(1000);
  ///////////////
  int ledState1 = digitalRead(led1);
  int ledState2 = digitalRead(led2);
  int buttonState1 = digitalRead(button1);
  int buttonState2 = digitalRead(button2);
  ///

  DynamicJsonDocument jsonDocCS(128);
//hgjgjhgjgfdsđgfdhghgf
  ///
  if( buttonState1 == 0 && ledState1 == ledStart1 ){
    digitalWrite(led1, !ledStart1);
    delay(500);
    ledStart1 = !ledStart1;
    
    //
    //
  }
  if( buttonState2 == 0 && ledState2 == ledStart2 ){
    digitalWrite(led2, !ledStart2);
    delay(500);
    ledStart2 = !ledStart2;
    //
    //
  }
  ///////////////
    jsonDocCS["led1"] = (int)ledStart1;
    // Serial.println(ledStart1);
    jsonDocCS["led2"] = (int)ledStart2;
    // Serial.println(ledStart2);
  String jsonStringCS;
  if(ledState1 != ledStart1 || ledState2 != ledStart2){
  serializeJson(jsonDocCS, jsonStringCS);
  SerialB.println(jsonStringCS);
  Serial.println(jsonStringCS);
  delay(1000);
  }
  if(ledState1 != ledStart1 && ledState2 != ledStart2){
  serializeJson(jsonDocCS, jsonStringCS);
  SerialB.println(jsonStringCS);
  Serial.println(jsonStringCS);
  delay(1000);
  }
  // Serial.println(jsonStringS);


  ///////////////
  ///
  // if (Serial.available())
  // {
  //   // Read from serial monitor and send
  //   // String input = Serial.readString();
  //   // SerialB.println(input);
  //   SerialB.println(jsonStringCS);
  // }
  ///

  if (SerialB.available() > 0 )
  {
    // Read from  STM module and send to serial monitor
    String input = SerialB.readString();

    /*
    Phân tích chuỗi JSON và lưu trữ kết quả vào một DynamicJsonDocument.
    Sau đó, chúng ta sử dụng các trường tương ứng của DynamicJsonDocument
    để lấy ra giá trị của trường "temperature" và "humidity".
    */
    DynamicJsonDocument jsonDocCG(128); // Kích thước buffer là 128 byte

    // Phân tích chuỗi JSON
    deserializeJson(jsonDocCG, input);

    // Lấy giá trị nhiệt độ và độ ẩm
    float temperature = jsonDocCG["temperature"];
    float humidity = jsonDocCG["humidity"];
    float lightValue = jsonDocCG["lightValue"];
    // float soundValue = jsonDocCG["soundValue"];
    bool leda = jsonDocCG["led1"];
    bool ledb = jsonDocCG["led2"];

    Serial.println(input);
    Serial.print("Temperature: ");
    Serial.println(1.00*temperature);
    Serial.print("Humidity: ");
    Serial.println(1.00*humidity);
    Serial.print("LightValue: ");
    Serial.println(1.00*lightValue);
    // Serial.print("soundValue: ");
    // Serial.println(1.00*soundValue);
    Serial.print("led1: ");
    Serial.println(leda);
    Serial.print("led2: ");
    Serial.println(ledb);
  }
  delay(20);
}
