#include <MAVLink.h>

// змінні для зберігання даних компаса
int16_t magX, magY, magZ;

void setup() {
  // ініціалізація Serial
  Serial.begin(115200);
  while (!Serial) {}

  // ініціалізація MAVLink
  mavlink.begin(MAVLINK_COMM_0, 115200);
}

void loop() {
  // отримання повідомлення MAVLink з ArduPilot
  mavlink_message_t msg;
  mavlink_status_t status;
  
  while (Serial.available()) {
    uint8_t c = Serial.read();
    if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
      // якщо отримано повідомлення, обробити його
      switch (msg.msgid) {
        case MAVLINK_MSG_ID_RAW_IMU: {
          // отримання даних компаса з повідомлення
          mavlink_raw_imu_t raw_imu;
          mavlink_msg_raw_imu_decode(&msg, &raw_imu);
          magX = raw_imu.mag_x;
          magY = raw_imu.mag_y;
          magZ = raw_imu.mag_z;
          break;
        }
        default:
          break;
      }
    }
  }

  // далі можна використовувати дані компаса для різних цілей
  // ...
}
