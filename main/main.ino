// Definimos puertos del arduino

// Puertos del ultra sonidos
int trig = 9;
int eco = 10;
int productUp = 5;
int productDown = 7;
int pinMotorUp = 4;   // rojo
int pinMotorDown = 3; // amarillo

// Definimos variables a usar
int pulseDuration;
int distance;
int showCount = 0;
int hideCount = 0;
int range = 25;
bool hided = true;

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  pinMode(productDown, OUTPUT);
  pinMode(productUp, OUTPUT);
  pinMode(pinMotorDown, OUTPUT);
  pinMode(pinMotorUp, OUTPUT);
  Serial.begin(9600); // Para ver la distancia, 9600 tasa de comunicacion, cantidad de bits/second
  digitalWrite(productDown, HIGH);
}

void loop()
{
  handClose();
}

void handClose()
{
  // Miramos si hay una mano cerca
  distance = showDistance();
  Serial.println(distance);
  delay(200);
  if (distance < range)
  {
    showCount++;
  }
  else
  {
    showCount = 0;
  }

  if (showCount > 4)
  {
    changeState();
    showCount = 0;
  }
}

int showDistance()
{
  int distancia;
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  pulseDuration = pulseIn(eco, HIGH);
  distancia = pulseDuration / 58.2; // cte transformacion duracion to distancia
  if (distancia < 0)
  {
    distancia = 300;
  }

  return distancia;
}

void changeState()
{
  if (hided)
  {
    showProduct();
  }
  else
  {
    hideProduct();
  }
}

void showProduct()
{
  // Subir motor, encender leds del producto
  digitalWrite(productDown, LOW);
  motorUp();
  digitalWrite(productUp, HIGH);
  hided = false;
  // faltan las luces pero me la suda luego las pongo
}

void hideProduct()
{
  // Bajar motor, apagar leds del producto
  digitalWrite(productUp, LOW);
  motorDown();
  digitalWrite(productDown, HIGH);
  hided = true;
}

void motorUp()
{
  // funcion para mover el motor a arriba
  digitalWrite(pinMotorUp, HIGH);
  delay(2000);
  digitalWrite(pinMotorUp, LOW);
}

void motorDown()
{
  // funcion para mover el motor a abajo
  digitalWrite(pinMotorDown, HIGH);
  delay(2000);
  digitalWrite(pinMotorDown, LOW);
}
