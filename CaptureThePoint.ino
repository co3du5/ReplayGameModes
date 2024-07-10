/*
 * A simple example to interface with rdm6300 rfid reader.
 *
 * Connect the rdm6300 to VCC=5V, GND=GND, TX=any GPIO (this case GPIO-04)
 * Note that the rdm6300's TX line is 3.3V level,
 * so it's safe to use with both AVR* and ESP* microcontrollers.
 * Note that on SAMD the RX_PIN is ignored, the default is Serial1 (pin0),
 * but if specify rdm6300.begin(RDM6300_RX_PIN, 2); then Serial2 (pin30) is used.
 *
 * This example uses SoftwareSerial, please read its limitations here:
 * https://www.arduino.cc/en/Reference/softwareSerial
 *
 * Arad Eizen (https://github.com/arduino12).
 */

#include <Arduino.h>
#include <rdm6300.h>

#define RDM6300_RX_PIN 4 // read the SoftwareSerial doc above! may need to change this pin to 10...


Rdm6300 rdm6300;

void setup()
{
	Serial.begin(115200);
	rdm6300.begin(RDM6300_RX_PIN);

	Serial.println("\nPlace RFID tag near the rdm6300...");
}

void loop()
{
	/* get_new_tag_id returns the tag_id of a "new" near tag,
	following calls will return 0 as long as the same tag is kept near. */
  uint32_t tag_id;

	if (rdm6300.get_new_tag_id())
		//Serial.println(rdm6300.get_tag_id(), HEX);
    tag_id = rdm6300.get_tag_id();
    if(tag_id == 0xB7A546D)
      Serial.println("Orange Team has Captured the point");

    if(tag_id == 0xB7B037F)
      Serial.println("Yellow Team has captured the point");

	delay(10);
}
