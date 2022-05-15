int trig = 10;
int eco = 9;
int led = 3;

int duracion;
int distancia;

void setup () {
  pinMode(trig, OUTPUT);
  pinMode(ECO, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600); // Para ver la distancia, 9600 tasa de comunicacion, cantidad de bits/second
}

void loop() {
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, HIGH);
  duracion = pulseIn(eco, HIGH);
  distancia = duracion / 58.2; // cte transformacion duracion to distancia

  Serial.println(distancia);
  delay(200);
  
}
