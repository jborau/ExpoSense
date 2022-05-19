int trig = 9;
int eco = 10;
int led = 3;

int duracion;
int distancia;

void setup () {
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600); // Para ver la distancia, 9600 tasa de comunicacion, cantidad de bits/second
}

void loop() {
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  duracion = pulseIn(eco, HIGH);
  distancia = duracion / 58.2; // cte transformacion duracion to distancia

  Serial.println(distancia);
  delay(200);
  
}
