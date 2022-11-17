# PlantMonitor

## My Plant: Chinese Monet Plant

  Light level: 2
  
  Water level: 1
  
  Humidity level: 2
 ![plant](https://github.com/NXiaoya/PlantMonitor/blob/main/img/plant.jpg) 
## Working Process of plant monitor:
The working process of the plant monitor is shown in figure below:

 ![schematic](https://github.com/NXiaoya/PlantMonitor/blob/main/img/schematic.jpg) 
## Hardware Components used in this project:
1. Adafruit Feather HUZZAH ESP8266 module
![ESP8266](https://github.com/NXiaoya/PlantMonitor/blob/main/img/ESP8266.png)
2. DHT 22 Sensor

![ESP8266](https://github.com/NXiaoya/PlantMonitor/blob/main/img/DHT22.jpg)

3. A pair of nails
4. Raspberry Pi
![ESP8266](https://github.com/NXiaoya/PlantMonitor/blob/main/img/Pi.jpg)
5. PCB board
![PCB](https://github.com/NXiaoya/PlantMonitor/blob/main/img/PCB.png)
5. Resistors
6. LEDs
7. Bread Board
8. Jumper Wire
9. Buzzer
![Buzzer](https://github.com/NXiaoya/PlantMonitor/blob/main/img/Buzzer.jpg)
## Sensing the soil data:
### Set up hardware
We use DHT22 sensor to collect the data about the environment around the plant, 
which has a capacitive humidity sensor and a thermal resistor inside allowing us to measure the temperature and humidity. 
The Data pin, connected to D12 digital I/O pin on microcontroller, outputs serial data and it has a voltage tolerance of 1 V. 
Therefore, a voltage divider circuit is added to limit the maximum voltage:
![Circuit](https://github.com/NXiaoya/PlantMonitor/blob/main/img/circuit.png)
https://workshops.cetools.org/codelabs/CASA0014-2-Plant-Monitor/index.html?index=..%2F..casa0014#7

To measure the moisture value, a pair of nails is used. 
The resistance between two nails from a certain distance can reflect the moisture value. 
One of the nails is connected to Analogue A0 pin and another is connected to D13 digital I/O pin (Act as sensor V_CC  ). The reading is an analogue value from 0 to 1024.
### Get the sensor reading
The circuit was first tested on bread board. I used Arduino IDE to configure all the pin set up. DHT library is installed to translate the serial data to temperature and moisture value.
The Arduino IDE is used.
The first step is inlcude the libary need and configure the pin used:

    // Define the pin name
    uint8_t DHTPin = 12;        // on Pin 2 of the Huzzah
    uint8_t soilPin = 0;      // ADC or A0 pin on Huzzah
    // In set up function, define the pin
    void setup() {
      //Pin mde
      pinMode(Pin_Name/Number, OUTPUT/INPUT);    
      //Initial state
      digitalWrite(Pin_Name/Number, HIGH/LOW);  
Sensing the soil data:

    // power the sensor
      digitalWrite(sensorVCC, HIGH);
      digitalWrite(blueLED, LOW);
      delay(100);
      // read the value from the sensor:
      Moisture = analogRead(soilPin);         
      digitalWrite(sensorVCC, LOW);  
      digitalWrite(blueLED, HIGH);
      delay(100);
      Serial.print("Wet ");
      Serial.println(Moisture);   // read the value from the nails
      
      Temperature = dht.readTemperature(); // Gets the values of the temperature
      Humidity = dht.readHumidity(); // Gets the values of the humidity
      
After the the circuit is tested to work, it is then solded on a PCB. It can be plugged on Adafruit Feather HUZZAH ESP8266 module.

### Sending Data to MQTT
In this system, WIFI module connect to the Cloud via MQTT protocol. MQTT is a publish/subscribe based messaging protocol. The publisher and subscriber are not connected directly.The MQTT protocol contains three identities in communication: publisher, agent and subscriber. Both the publisher and subscriber of the message are regarded as clients. The server is the message agent. And the message publisher can also be a subscriber. A publisher can have many subscribers.

![MQTT](https://github.com/NXiaoya/PlantMonitor/blob/main/img/MQTT.jpg)

The code should also be set up in Arduino with WIFI. Firstly, the ESP8266 will be connected to WIFI. After connection to wifi is successful, it will then connected to MQTT client. Therefore, the key for both WIFI and MQTT client is needed:
    #define SECRET_SSID "ssid name"
    #define SECRET_PASS "ssid password"
    #define SECRET_MQTTUSER "user name"
    #define SECRET_MQTTPASS "password";
 
Connect to Wifi:

    WiFi.begin(ssid, password);

Sending data from MQTT(Example temperature):
       //In setup, start MQTT server
      client.setServer(mqtt_server, 1884);
      //In functions read data
      Temperature = dht.readTemperature(); // Gets the values of the temperature
      snprintf (msg, 50, "%.1f", Temperature);
      client.publish("Topic name", msg);
      
Reading data from MQTT:

    //In setup
    client.setCallback(callback);
    //Subcribe the topic to get data
    client.subscribe("student/CASA0014/plant/ucfnnie/inTopic");
    //In call back function
    void callback(char* topic, byte* payload, unsigned int length) {
      Serial.print("Message arrived [");
      Serial.print(topic);
      Serial.print("] ");
      for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
      }
      Serial.println();
    }
    
![MQTT](https://github.com/NXiaoya/PlantMonitor/blob/main/img/MQTTconnected.jpg)

Then the components are soldered on the PCB

![Soldered](https://github.com/NXiaoya/PlantMonitor/blob/main/img/soldered.jpg)
    
## Visualise the Data:
As MQTT client will not store the data, we need a datastore. In this project, Raspberry Pi is used. The setup process is follwing https://workshops.cetools.org/codelabs/CASA0014-2-Plant-Monitor/index.html?index=..%2F..casa0014#9
remote configuration on RPi can be achieved using Putty.
I use InfluxDB, which us a Time Series Data Platform where developers build IoT, analytics, and cloud applications.
To get the data from MQTT client, I also download Telegraf.
The data is pushed in to a bucket called MQTT. The correspongding api tocken and topic subscribed need to be added.
      ###############################################################################
      #                            OUTPUT PLUGINS                                   #
      ###############################################################################


      [[outputs.influxdb_v2]] 
        urls = ["Host IP"]
        ## Token for authentication.
        token = "API tocken"
        ## Organization is the name of the organization you wish to write to; must exist.
        organization = ""
        ## Destination bucket to write into.
        bucket = "Bucket name"
      ###############################################################################
      #                            SERVICE INPUT PLUGINS                            #
      ###############################################################################

      # Read metrics from MQTT topic(s)
      [[inputs.mqtt_consumer]]
        ## MQTT broker URLs to be used. The format should be scheme://host:port,
        servers = ["MQTT client Host"]
        client_id = ""

        ## Username and password to connect MQTT server.
        username = ""
        #password = "enter password for your mqtt account"  
        password = ""  




        ## Topics that will be subscribed to.
        topics = [
          ""
          ]
        topic_tag = "plant-topics"
        data_format = "value"
        data_type = "float"
        
 After Downloading Grafana on RPi, the plant monitor data can be viewed both on data explore of InfluxDB and Grafana:
 
 ![Grafana](https://github.com/NXiaoya/PlantMonitor/blob/main/img/Grafana.jpg)
 ![Grafana](https://github.com/NXiaoya/PlantMonitor/blob/main/img/GrafanaReading.jpg)
    

## Add and alert
As we alrady have the data reading from the plant, the next step is to set an alarm as a feedback.
I use a buzzer and two LEDs as a visual and auditory alarm. In order to make the buzzer to produce different sounds, it is necessary to drive the buzzer through PWM wave. Adjusting the frequency of PWM wave can produce different tones of sound. PWM is short for pulse width modulation. It is widely used in control, can be used for motor speed control, steering gear control, stepper motor control, etc. In this project I use PWM waves to drive the buzzer to produce different tones of sound. Arduino tone() funtion is used
![alarm](https://github.com/NXiaoya/PlantMonitor/blob/main/img/alarm schematic.jpg)
The related code:
      //function to start the alarm buzzer
      void BuzzerM(){
         //Use tone function to generate wave at certain frequency
         digitalWrite(LEDM, HIGH);

         tone(buzzer,495);
         delay(500); 

         tone(buzzer,556);
         delay(500); 

         noTone(buzzer);//Stop the buzzer

      }
       //In the sending data function
       //Check the moisture level, if it is too low then start the alarm
        if(Moisture<20)
        {
          BuzzerM();
        }else {
          BuzzerC(); //Turn off the Buzzer
        }




## The completed plant monitor
![final](https://github.com/NXiaoya/PlantMonitor/blob/main/img/Whole.jpg)

## Future improvements:
 - Redesign a 3d printed case
 - Add a data filter to smooth the reading and aviod error.
 - Add a remote email alarm function
 
### This project is based on the workshop. Many thanks for Duncan to teach us this wonderful project
https://github.com/ucl-casa-ce/casa0014
    
   


     
