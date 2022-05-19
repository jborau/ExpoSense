// Definimos puertos del arduino

//Puertos del ultra sonidos
int trig = 9;
int eco = 10;
int motorWorking = 4;
int modelUp = 5;
int modelDown = 7;
int modelLights = 3;
int inRange = 6;


// Definimos variables a usar
int pulseDuration;
int distance;
int contadorSubir = 0;
int contadorBajar = 0;
int range = 25;
bool abajo = true;
bool arriba = false;

void setup () {
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  pinMode(motorWorking, OUTPUT);
  pinMode(modelUp, OUTPUT);
  pinMode(modelDown, OUTPUT);
  pinMode(modelLights, OUTPUT);
  pinMode(inRange, OUTPUT);
  Serial.begin(9600); // Para ver la distancia, 9600 tasa de comunicacion, cantidad de bits/second
}

void loop() {
  distance = showDistance();
  // position = position(distance);
  if (distance < range ) {
    contadorSubir++;
  } else if (distance > range && abajo) {
    contadorSubir = 0;
  } else if (distance <= range && abajo == false) {
    contadorBajar = 0;
  } else if (distance >= range && abajo == false) {
    contadorBajar++;
  }
  
  if (distance < range){
    digitalWrite(inRange, HIGH);
    delay(10);

    digitalWrite(inRange, LOW);
  }

  if (contadorSubir > 4 && abajo){
    digitalWrite(modelDown, LOW);
    subirMotor();
    abajo = false;
    contadorSubir = 0;
    delay(5000);
    pararMotor();
    digitalWrite(modelUp, HIGH);
    digitalWrite(modelLights, HIGH);

  } else if (contadorBajar > 4 && abajo == false) {
    digitalWrite(modelUp, LOW);
    digitalWrite(modelLights, LOW);
    subirMotor();
    abajo = true;
    contadorBajar = 0;
    delay(5000);
    pararMotor();
    digitalWrite(modelDown, HIGH);
  }

  if (abajo){
    digitalWrite(modelDown, HIGH);
    digitalWrite(modelUp, LOW);
    digitalWrite(modelLights, LOW);
  } else {
    digitalWrite(modelDown, LOW);
    digitalWrite(modelUp, HIGH);
    digitalWrite(modelLights, HIGH);

  }
  
  Serial.println(distance);    // envio de valor de distancia por monitor serial
  delay(200);
}

int showDistance() {
  int distancia;
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  pulseDuration = pulseIn(eco, HIGH);
  distancia = pulseDuration / 58.2; // cte transformacion duracion to distancia
  return distancia;
}

void subirMotor () {
  digitalWrite(motorWorking, HIGH);
}

void pararMotor () {
  digitalWrite(motorWorking, LOW);
}


//int position (distance) {
//  if (distance < range && abajo) {
//    contadorSubir++;
//  } else if (distance > range && abajo) {
//    contadorSubir = 0;
//  } else if (distance >= range && abajo == false) {
//    contadorBajar = 0;
//  } else if (distance >= range && abajo == false) {
//    contadorBajar++;
//  }
//  if (distance < range){
//    digitalWrite(inRange, HIGH);
//  } else {
//    digitalWrite(inRange, HIGH);
//  }
//}
