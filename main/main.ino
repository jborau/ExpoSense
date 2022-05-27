// Definimos puertos del arduino

// Puertos del ultra sonidos
int trig = 12;     // Pin trig del sensor ultrasonido
int eco = 13;      // Pin eco del sensor ultrasonido
int luces = 11;    // luces expositor, led cuando el producto esta arriba
int dirPin = 2;    // pin direccion del driver del motor
int stepPin = 3;   // pin pulso del driver del motor
int enablePin = 4; // pin enable del driver del motor, lo dejamos desconectado ya que no lo usamos
// Definimos variables a usar
int duracionPulso; // duracion del pulso del ultrasonidos para medir distancia
int distancia;
int contador = 0;      // contador para que suba o baje cuando detecte la mano
int rango = 25;        // distancia a la que hay que poner la mano
bool escondido = true; // nos dice si el prod esta arriba o abajo (escondido)
int altura = 6500;     // altura que queremos que suba
int espera = 500;      // espera entre cada paso, mas espera mas lento sube

void setup()
{
  // output = salida, input = entrada
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
  handClose(); // llamamos a la funcion que detecta si la mano esta cerca y actua sobre el motor
}

void handClose()
{
  // Miramos si hay una mano cerca
  distancia = calcDistancia();
  delay(200);
  if (distancia < rango) // contador para que la mano tenga que estar un poco encima del sensor
  {
    contador++;
  }
  else
  {
    contador = 0;
  }

  if (contador > 4)
  {
    cambiarEstado(); // funcion que si esta abajo sube y si esta arriba baja
    contador = 0;
  }
}

int calcDistancia() // funcion que nos dice la distancia que mide el ultrasonidos
{
  int distanciaSensor;
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  duracionPulso = pulseIn(eco, HIGH);
  distanciaSensor = duracionPulso / 58.2; // cte transformacion duracion to distancia
  if (distanciaSensor < 0)                // a veces no detecta nada y da distancia negativa
  {
    distanciaSensor = 300; // si es negativa ==> Distancia = 300 (muy lejos)
  }

  return distanciaSensor;
}

void cambiarEstado()
{
  if (escondido) // si esta abajo sube y si esta arriba baja
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
  digitalWrite(dirPin, LOW); // le decimos que gire en sentido que suba el prod
  motor();                   // funcion que activa el motor
  digitalWrite(luces, HIGH); // encendemos leds del producto
  escondido = false;         // decimos que ya no esta escondido
  // Igual poner las luces antes, para  que se enciendan abajo y ya esten encendidas mientras sube
}

void bajarProducto()
{
  // Bajar motor, apagar leds del producto
  digitalWrite(dirPin, HIGH); // le decimos que gire en sentido que baje el prod
  digitalWrite(luces, LOW);   // apagamos las luces del producto
  motor();                    // funcion que activa el motor
  escondido = true;           // ahora el producto esta abajo (escondido)
}

void motor()
{
  for (int i = 0; i < altura; i++) // ejecuta tantos paso = altura (no se corresponde con la altura en cm)
  {
    // un paso del motor
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(espera);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(espera);
  }
}
