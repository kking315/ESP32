#include <IRremote.h>
#define RECV_PIN 0
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
    Serial.begin(115200);
    irrecv.enableIRIn();
    delay(50);
}
void loop()
{
    if (irrecv.decode(&results))
    {
      Serial.println(results.value, HEX);
      Serial.println("");
      irrecv.resume();
    }
    delay(300);
}