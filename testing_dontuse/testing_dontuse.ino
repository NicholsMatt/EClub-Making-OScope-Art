  byte a0 = 0;
  byte a1 = 0;
  byte a2 = 0;
  byte SpinNoSpin = 0;

//void readInputs(int &A0, int &A1, int &A2, int &SpinNoSpin);

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

//  byte input[4] = {bitRead(digitalRead(A0), 0), bitRead(digitalRead(A1), 0), bitRead(digitalRead(A2), 0), bitRead(digitalRead(A3), 0)};
//
//  
//  Serial.print(input[0]);
//  Serial.print(input[1]);
//  Serial.print(input[2]);
//  Serial.println(input[3]);
//  if(input == 0001){
//    Serial.println("True");
//  }else{
//    Serial.println("False");
//  }


  readInputs(a0, a1, a2, SpinNoSpin);
  Serial.print("DIP Switch: ");
  Serial.print(a0);
  Serial.print(a1);
  Serial.println(a2);
//  Serial.print(a1);
//  Serial.println(a2);
  Serial.print("Spin?: ");
  Serial.println(SpinNoSpin);
  
  
  delay(100);
}

void readInputs(byte &a0, byte &a1, byte &a2, byte &SpinNoSpin){
  a0 = digitalRead(A0);
  a1 = digitalRead(A1);
  a2 = digitalRead(A2);
  SpinNoSpin = digitalRead(A3);
}
