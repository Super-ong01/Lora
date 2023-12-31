#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 15
#define dio0 2
unsigned long lasttime ;
unsigned long lasttime2 ;

int counter = 0;

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");
  pinMode(34, INPUT);
  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);

  //replace the LoRa.begin(---E-) argument with your location's frequency
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {

  Sending();
}

void Sending() {
  //  if (millis() - lasttime >= 8000) {
  //    lasttime = millis();
  //
  //    Serial.print("Sending packet: ");
  //    Serial.println(counter);
  int ong = digitalRead(34);
  //Send LoRa packet to receiver
  if (ong == 1) {
    Serial.println("ok");
    LoRa.beginPacket();
    LoRa.print("ok");

    //LoRa.print(counter);
    LoRa.endPacket();

    //    counter++;
  }
}
void Receiving() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }

}
