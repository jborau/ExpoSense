// Definimos puertos del arduino

// Puertos del ultra sonidos
int trig = 12;
int eco = 13;
int luces = 11;    // luces expositor
int dirPin = 2;    // pin digital 8 de Arduino a IN1 de modulo controlador
int stepPin = 3;   // pin digital 9 de Arduino a IN2 de modulo controlador
int enablePin = 4; // pin digital 10 de Arduino a IN3 de modulo controlador
int altura = 5000; // pin digital 11 de Arduino a IN4 de modulo controlador

// Definimos variables a usar
int duracionPulso;
int distancia;
int contador = 0;
int rango = 25;
bool escondido = true;
// altura de lo que queremos que suba
bool subir;

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  pinMode(luces, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(stepPin, OUTPUT);


  Serial.begin(9600); // Para ver la distancia, 9600 tasa de comunicacion, cantidad de bits/second
}

void loop()
{
  handClose();
  // lucesBase();
}

void handClose()
{
  // Miramos si hay una mano cerca
  distancia = calcDistancia();
  // Serial.println(distancia);
  delay(200);
  if (distancia < rango)
  {
    contador++;
  }
  else
  {
    contador = 0;
  }

  if (contador > 4)
  {
    cambiarEstado();
    contador = 0;
  }
}

int calcDistancia()
{
  int distanciaSensor;
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  duracionPulso = pulseIn(eco, HIGH);
  distanciaSensor = duracionPulso / 58.2; // cte transformacion duracion to distancia
  if (distanciaSensor < 0)
  {
    distanciaSensor = 300;
  }

  return distanciaSensor;
}

void cambiarEstado()
{
  if (escondido)
  {
    subirProducto();
  }
  else
  {
    bajarProducto();
  }
}

void subirProducto()
{
  // Subir motor, encender leds del producto
  digitalWrite(dirPin, HIGH);
  motor();
  digitalWrite(luces, HIGH);
  Serial.println("Estamos arriba");
  escondido = false;
  // Igual poner las luces antes, para  que se enciendan abajo y ya esten encendidas mientras sube
}

void bajarProducto()
{
  // Bajar motor, apagar leds del producto
  digitalWrite(dirPin, LOW);
  digitalWrite(luces, LOW);
  motor();
  Serial.println("Estamos abajo");
  escondido = true;
}

void motor()
{
  for (int i = 0; i < altura; i++)
  {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}

/* void lucesBase()
{
  if (digitalRead(interruptor) == HIGH)
  {
    digitalWrite(rele, HIGH);
  }
  else
  {
    digitalWrite(rele, LOW);
  }
}
 */
