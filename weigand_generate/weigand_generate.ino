

/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
#define W_D0 28
#define W_D1 29

const byte interruptPin = 2;
int size = 0; // for incoming serial data
int count = 0 ;
uint8_t buffer[6];

void outwiegbit(unsigned int b)
{
  int sel = b == 0 ? W_D0 : W_D1;
  digitalWrite(sel, 0);
  delayMicroseconds(70);
  digitalWrite(sel, 1); 
  delayMicroseconds(1230);
}
void outwieg36(uint32_t u32)
{

  for (int n = 0; n < 32; ++n)
  {
    outwiegbit((u32 >> (31 - n)) & 1);
  }

}
void setup() {
    //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Serial.setTimeout(100);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(W_D0, OUTPUT);
  pinMode(W_D1, OUTPUT);
    digitalWrite(W_D0, 1);
        digitalWrite(W_D1, 1);
      pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt_fuction, FALLING );
}
// the loop function runs over and over again forever
void interrupt_fuction() {
  if(count==0)
  {
    outwieg36(0xb5aa709c);   // wait for a second
    count++;
  }
}
// the loop function runs over and over again forever
void loop() { 
    if (Serial.available() > 0) {
    // read the incoming byte:
   
    size = Serial.readBytes(buffer, 6);

    // say what you got:
    Serial.print("I received: ");
    for (int i = 0 ; i < size ; i++) {
      Serial.println(char(buffer[i]));
    }
    if(size==6)
    {
      outwieg36(0xb5aa709c); 
    }
   
  }
}
