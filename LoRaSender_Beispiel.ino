#include <SPI.h>
#include <LoRa.h>
#include <U8x8lib.h>

#define ss 18
#define rst 14
#define dio0 26

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(15, 4, 16);

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
  
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0, 1, "LoRa Rx Test");
  
  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(ss, rst, dio0);
  
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  String message = "hello ";
  Serial.print("Sending packet: ");
  u8x8.setCursor(0, 4);
  u8x8.print("Sending packet: ");
  u8x8.setCursor(0, 7);
  Serial.println(counter);
  u8x8.print(message);
  u8x8.print(counter);
  
  
  
  // send packet
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.print(counter);
  LoRa.endPacket();

  
  
  counter++;

  delay(5000);
}
