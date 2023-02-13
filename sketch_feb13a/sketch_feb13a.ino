void setup() {
  // put your setup code here, to run once:
pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);
pinMode(A3, INPUT);

Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
//  int a0 = digitalRead(A0);
//  int a1 = digitalRead(A1);
//  int a2 = digitalRead(A2);
//  int a3 = digitalRead(A3);

  byte input[4] = {bitRead(digitalRead(A0), 0), bitRead(digitalRead(A1), 0), bitRead(digitalRead(A2), 0), bitRead(digitalRead(A3), 0)};

  
  Serial.print(input[0]);
  Serial.print(input[1]);
  Serial.print(input[2]);
  Serial.println(input[3]);
  if(input == 0001){
    Serial.println("True");
  }else{
    Serial.println("False");
  }


  
  delay(100);
}
