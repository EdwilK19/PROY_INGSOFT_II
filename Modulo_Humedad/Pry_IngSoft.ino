
int sensor_pin = A0;
int humedad;
int val_aire = 0;
int intervalo = (val_aire, val_agua)/3;
int x;
int y;
int pin_bomba = D2;

void setup() {
  Serial.begin(115200);
  Serial.print("Reading from the sensor...");
  delay(2000);

  pinMode(pin_bomba, OUTPUT);
//for(x=0; x<5; x++){
    //humedad = analogRead(sensor_pin);
    //humedad = map(humedad,535,847,100,0);
    //Serial.print("Humedad : ");
    //Serial.print(humedad);
    //Serial.println(" %");
    //delay(1000);
    
  //}
}

void loop(){
    humedad = analogRead(sensor_pin);
    humedad = map(humedad,535,847,100,0);
    Serial.print("Humedad : ");
    Serial.print(humedad);
    Serial.println(" %");
    delay(1000);

    if(humedad <= 30){
      digitalWrite(pin_bomba, HIGH);
    }
    else
    {
      digitalWrite(pin_bomba, LOW);
    }
}
