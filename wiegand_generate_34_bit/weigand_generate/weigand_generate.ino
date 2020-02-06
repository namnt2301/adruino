

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
#define DOOR_1_W_D0 30
#define DOOR_1_W_D1 31

#define DOOR_2_W_D0 32
#define DOOR_2_W_D1 33

uint8_t d0 = DOOR_1_W_D0;
uint8_t d1 = DOOR_1_W_D1;
uint8_t count ;
uint8_t p_even = 0 ;
uint8_t p_odd = 1 ;

String buffer = "";
String card_number_in_string = "";
uint8_t   door_id;

uint8_t tmp;
uint8_t card_number[4];
char  card_number_in_array[9];
char  card_number_in_array_1[3] = "ff";
char  card_number_in_array_2[3] = "ff";
char  card_number_in_array_3[3] = "ff";
char  card_number_in_array_4[3] = "ff";
void outwiegbit(uint8_t b)
{
  int sel = b == 0 ? d0 : d1;
  digitalWrite(sel, 0);
  delayMicroseconds(67);
  digitalWrite(sel, 1);
  delayMicroseconds(1200);
}
void outwieg(uint8_t u8)
{

  for (int n = 0; n < 8; ++n)
  {
    outwiegbit((u8 >> (7 - n)) & 1);
  }

}

void door_switch(uint8_t door_id)
{
  switch (door_id)
  {
    case 1 :
      d0 = DOOR_1_W_D0;
      d1 = DOOR_1_W_D1;
      break;
    case 2 : 
      d0 = DOOR_2_W_D0;
      d1 = DOOR_2_W_D1;
      break;
    default : break;
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
   pinMode(DOOR_2_W_D0, OUTPUT);
  pinMode(DOOR_2_W_D1, OUTPUT);
  digitalWrite(DOOR_2_W_D0, 1);
  digitalWrite(DOOR_2_W_D1, 1);
}

//the loop function runs over and over again forever
void loop() {

  if (Serial.available() > 0) {
    // read the incoming byte:

    buffer = Serial.readString();

    card_number_in_string = buffer.substring(0, 8);
    door_id     = (buffer.substring(8)).toInt();

    card_number_in_string.toCharArray(card_number_in_array, 9);

    card_number_in_array_1[0] = card_number_in_array[0];
    card_number_in_array_1[1] = card_number_in_array[1];

    card_number_in_array_2[0] = card_number_in_array[2];
    card_number_in_array_2[1] = card_number_in_array[3];

    card_number_in_array_3[0] = card_number_in_array[4];
    card_number_in_array_3[1] = card_number_in_array[5];

    card_number_in_array_4[0] = card_number_in_array[6];
    card_number_in_array_4[1] = card_number_in_array[7];


    card_number[0]  = strtol(card_number_in_array_1, NULL, 16);
    card_number[1]  = strtol(card_number_in_array_2, NULL, 16);
    card_number[2]  = strtol(card_number_in_array_3, NULL, 16);
    card_number[3]  = strtol(card_number_in_array_4, NULL, 16);


    door_switch(door_id);
    //caluclate the even bit
    
    tmp=card_number[1];
    for(count = 0 ; count < 8; count++)
    {
        p_even ^= (tmp & 1);
         tmp >>= 1; 
    }

    tmp=card_number[0];
    for(count = 0 ; count < 8; count++)
    {
        p_even ^= (tmp & 1);
        tmp >>= 1; 
    }

    tmp=card_number[3];
    for(count = 0 ; count < 8; count++)
    {
        p_odd ^= (tmp & 1);
        tmp >>= 1; 
    }

    tmp=card_number[2];
    for(count = 0 ; count < 8; count++)
    {
        p_odd ^= (tmp & 1);
        tmp >>= 1; 
    }
    

    // generate the wiegand 34 bit 
    outwiegbit(p_even);
    for (count = 0 ; count < 4; count++) {
      outwieg(card_number[count]);
    }
    outwiegbit(p_odd);

   p_even = 0 ;
   p_odd = 1 ;

   Serial.print("DONE");
   Serial.print("\r\n");

    
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
}
