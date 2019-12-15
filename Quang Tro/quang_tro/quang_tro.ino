int quangtro = A0; //Thiết đặt chân analog đọc quang trở
int ledPin=4;
void setup() {
  // Khởi tạo cộng Serial 9600
  Serial.begin(9600);
 pinMode(ledPin, OUTPUT); 
  
}

void loop() {
  int giatriQuangtro = analogRead(quangtro);// đọc giá trị quang trở
  
  Serial.println(giatriQuangtro); // Xuất giá trị ra Serial Monitor
  if(giatriQuangtro < 30){
  digitalWrite(ledPin, HIGH);
  }
  else
  {
  digitalWrite(ledPin, LOW);
  }
  delay(1000);
}
