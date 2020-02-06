

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
#define DOOR_1_W_D0 8
#define DOOR_1_W_D1 9

// uint64_t valid_card =   0x1FFFFFFFE;
// uint64_t invalid_card = 0x1FFFFFFFE;

uint64_t valid_card =   0xFBEB4CF4;
uint64_t invalid_card = 0xFBEB4CF4;

uint8_t d0 = DOOR_1_W_D0;
uint8_t d1 = DOOR_1_W_D1;

void outwiegbit(unsigned int b)
{
  int sel = b == 0 ? d0 : d1;
  digitalWrite(sel, 0);
  delayMicroseconds(39);
  digitalWrite(sel, 1);
  delayMicroseconds(1000);
}
void outwieg(uint64_t u32)
{
  outwiegbit(1);
  for (int n = 0; n < 32; ++n)
  {
    outwiegbit((u32 >> (31 - n)) & 1);
  }
  outwiegbit(1);

}


void setup() {
  pinMode(DOOR_1_W_D0, OUTPUT);
  pinMode(DOOR_1_W_D1, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(DOOR_1_W_D0, 1);
  digitalWrite(DOOR_1_W_D1, 1);
  digitalWrite(LED_BUILTIN, LOW);
}

//the loop function runs over and over again forever
void loop() {

   delay(3000);
   outwieg(valid_card);
   
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   digitalWrite(LED_BUILTIN, LOW);

   
   delay(10000);   

   
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   digitalWrite(LED_BUILTIN, LOW);
   
   outwieg(invalid_card);
    
   delay(3000);
   /*
    Serial.print("I received: \n");
    Serial.print(card_number[0]);
    Serial.print(" \n");
    Serial.print( card_number[1]);
    Serial.print(" \n");
    Serial.print( card_number[2]);
    Serial.print("\n");
    Serial.print( card_number[3]);
    Serial.print("\n===");
    */


  
}
