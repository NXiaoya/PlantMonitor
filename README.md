# PlantMonitor

## My Plant: Chinese Monet Plant

  Light level: 2
  Water level: 1
  Humidity level: 2
  
## Working Process of plant monitor:
The working process of the plant monitor is shown in figure below:


## Hardware Components used in this project:
1. Adafruit Feather HUZZAH ESP8266 module

2. DHT 22 Sensor

3. A pair of nails

4. PCB board

5. Resistors

6. LEDs

7. Bread Board

8. Jumper Wire

9. Buzzer

## Sensing the soil data:
We use DHT22 sensor to collect the data about the environment around the plant, 
which has a capacitive humidity sensor and a thermal resistor inside allowing us to measure the temperature and humidity. 
The Data pin, connected to D12 digital I/O pin on microcontroller, outputs serial data and it has a voltage tolerance of 1 V. 
Therefore, a voltage divider circuit is added to limit the maximum voltage:

To measure the moisture value, a pair of nails is used. 
The resistance between two nails from a certain distance can reflect the moisture value. 
One of the nails is connected to Analogue A0 pin and another is connected to D13 digital I/O pin (Act as sensor V_CC  ). The reading is an analogue value from 0 to 1024.
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
     
