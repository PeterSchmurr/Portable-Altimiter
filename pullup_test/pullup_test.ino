

const int zeroButton = 32;//7th pin down on leftside of MCU

void setup() {
  Serial.begin(115200);
  pinMode(zeroButton, INPUT_PULLDOWN);
}
void loop() {
  Serial.println("zeroButton value");
  Serial.println(digitalRead (zeroButton));
  delay(500);                         
}


 
