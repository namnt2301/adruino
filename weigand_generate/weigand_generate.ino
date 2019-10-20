

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
#define DOOR_1_W_D0 28
#define DOOR_1_W_D1 29


uint8_t d0;
uint8_t d1;

String buffer = "";
String card_number_in_string="";
uint8_t   door_id;
uint32_t card_number;
char  card_number_in_array[9];
void outwiegbit(unsigned int b)
{
  int sel = b == 0 ? d0 : d1;
  digitalWrite(sel, 0);
  delayMicroseconds(65);
  digitalWrite(sel, 1); 
  delayMicroseconds(1200);
}
void outwieg32(uint32_t u32 , unsigned int door_id)
{
  switch(door_id)
  {
    case 1 : 
         d0 = DOOR_1_W_D0;
         d1 = DOOR_1_W_D1;
         break; 
    default : break;
  }

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
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(DOOR_1_W_D0, OUTPUT);
  pinMode(DOOR_1_W_D1, OUTPUT);
  digitalWrite(DOOR_1_W_D0, 1);
  digitalWrite(DOOR_1_W_D1, 1);
}

//the loop function runs over and over again forever
void loop() { 
    if (Serial.available() > 0) {
    // read the incoming byte:
   
    buffer = Serial.readString();

    card_number_in_string = buffer.substring(0,8);
    door_id     = (buffer.substring(8)).toInt();

    card_number_in_string.toCharArray(card_number_in_array,9);
    card_number  = strtoul(card_number_in_array,NULL,16);

    outwieg32(card_number , door_id);  
    
    /*
    // say what you got:
    Serial.print("I received: \n");
    Serial.print(card_number_in_array);    
    Serial.print(" \n");
    Serial.print(card_number);  
    Serial.print(" \n"); 
    Serial.print(door_id);
    Serial.print("\n==="); 
    */
      
  }
}
