/*
   PROGRAMA DE TESTE
*/
#include <SPI.h>
#include <Wire.h>
#include "BluetoothA2DPSink.h"

BluetoothA2DPSink a2dp_sink;

#include <dWin.h>

#define RXD1 16
#define TXD1 17

#define PAGE0 0x00
#define PAGE1 0x01

String artist = "";
String track = "";
uint8_t _page = 0x00;

void avrc_metadata_callback(uint8_t id, const uint8_t *text) {
  switch (id) {
    case 1:
      track = String((char*)text);
      LCD.Set_HMI_Text_Message(0x0B00, track, 30);
      break;
    case 2:
      artist = String((char*)text);
      LCD.Set_HMI_Text_Message(0x0A00, artist, 30);
      break;
  }
}
void setup() {
  a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
  a2dp_sink.start("DwinMusicPlayer");
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);
  LCD.Set_HMI_Page(PAGE0);
  delay(3000);
  Serial.println("Started");
  //LCD.Set_HMI_Page(PAGE1);
}
int state = 0;
void loop() {

  uint8_t bufferIn[16];
  uint16_t i = 0;

  while (HMI_Serial.available() > 0) {
    bufferIn[i++] = HMI_Serial.read();
  }
  //  Serial.print(">> I");
  //  Serial.println(i);
  if (i == 11) {
    Serial.println(bufferIn[5], HEX);
    switch (bufferIn[5]) {
      case 0x1:
        a2dp_sink.previous(); Serial.print("prev");
        break;
      case 0x2:
        a2dp_sink.next(); Serial.print("next");
        break;
      case 0x3:
        a2dp_sink.stop(); Serial.print("stop");
        break;
      case 0x4:
        a2dp_sink.play(); Serial.print("play");
        break;
      case 0x5:
        a2dp_sink.pause(); Serial.print("pause");
        break;
    }
  }
  
  if (a2dp_sink.is_connected()) {
    if (_page != PAGE1) {
      LCD.Set_HMI_Page(PAGE1);
      _page = PAGE1;
    }
  } else {
    if (_page != PAGE0) {
      LCD.Set_HMI_Page(PAGE0);
      _page = PAGE0;
      LCD.Set_HMI_Text_Message(0x0A00, "", 30);
      LCD.Set_HMI_Text_Message(0x0B00, "", 30);
    }
  }
}
