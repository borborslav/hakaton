#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883L.h>
#include <SoftwareSerial.h>
#include <FastSerial.h>
#include <mavlink.h>

Adafruit_HMC5883L mag;
SoftwareSerial serial(10, 11);
mavlink_message_t msg;
uint8_t buf[MAVLINK_MAX_PACKET_LEN];

void setup() {
  Serial.begin(57600);
  serial.begin(57600);
  Wire.begin();
  mag.begin();
}

void loop() {
  float heading = mag.readHeading();
  
  mavlink_msg_command_long_pack(1, 200, &msg, 
    1, 0, MAV_CMD_CONDITION_YAW, 0, 0, heading, 0, 0, 0, 0);
    
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  serial.write(buf, len);
  
  delay(1000);
}
