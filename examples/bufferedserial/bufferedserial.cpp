#include <Arduino.h>
#include "StrRingBuffer.h"

StrRingBuffer buf(32);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    char tmp[32];

    if(Serial.available())
        buf.push(Serial.read());

    if(buf.endswith((char *) ".")) {
        buf.getstr(tmp);
        Serial.println("Got:");
        Serial.println(tmp);
        Serial.println("---");
        buf.reset();
    }
}
