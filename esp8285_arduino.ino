// test esp8285 with arduino nano for serial
//program for arduino ... when receipt a string change led 
//www.costycnc.it low cost foam cutter cnc

void setup() {
  // initialize serial:
  Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {


    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
  }
}
