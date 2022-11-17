
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ezTime.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <DHT_U.h>
int pinBuzzer = 15; //管脚D3连接到蜂鸣器模块的信号脚



void setup() {
  pinMode(pinBuzzer, OUTPUT); //设置pinBuzzer脚为输出状态
  Serial.begin(115200);
}
 
void loop() { 
   
   //用tone()函数发出频率为frequency的波形
   tone(pinBuzzer,441);
   delay(500); //等待1000毫秒
   //用tone()函数发出频率为frequency的波形
   tone(pinBuzzer,495);
   delay(500); //等待1000毫秒
   //用tone()函数发出频率为frequency的波形
   tone(pinBuzzer,441);
   delay(500); //等待1000毫秒
   //用tone()函数发出频率为frequency的波形
   tone(pinBuzzer,495);
   delay(500); //等待1000毫秒
   //用tone()函数发出频率为frequency的波形
   tone(pinBuzzer,556);
   delay(500); //等待1000毫秒
   
   noTone(pinBuzzer);//停止发声
   delay(2000); //等待2000毫秒
    // Switch on the LED if an 1 was received as first character
  int i = Serial.read();
  if (i = 1) {
     noTone(pinBuzzer);   //Turn off buzzer
  } 
}