int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;

int redPin= 7;
int greenPin = 6;
int bluePin = 5;

float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {

  Tc = setTemp();

  if(Tc >= 25){
    setColor(255, 0, 0); // Red
    Tc = setTemp();
    delay(400);
  }

  else if(Tc >= 20){
    setColor(255, 100, 0); //Orange 
    Tc = setTemp();
    delay(400);
  }

  else {
    setColor(0, 0, 255); //Blue
    delay(400);
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

int setTemp(){
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;

  Serial.print("Temperature: "); 
  Serial.print(Tc);
  Serial.println(" C");   
  return Tc;
}
