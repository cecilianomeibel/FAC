//Código Proyecto Fundamentos de Arquitectura
//Estudiante: Meibel Ceciliano Picado

// PINES DEL SENSOR
//..................

int TRIG = 6; // Pin del sensor ultrasónico - TRIG
int ECHO = 5; // Pin del sensor ultrasónico - ECHO

int duracion;
int distancia;

//....................................
// PINES DEL ARDUINO PARA MANDAR GRAY
//....................................

int pinBit1 = 2; // Pin del Arduino para el bit 1
int pinBit2 = 3; // Pin del Arduino para el bit 2
int pinBit3 = 4;  // Pin del Arduino para el bit 3

void setup() {
  
  //....................
  // SENSOR ULTRASONICO
  //....................
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(pinBit1, OUTPUT);
  pinMode(pinBit2, OUTPUT);
  pinMode(pinBit3, OUTPUT);
  
  Serial.begin(9600);    // Inicializa la comunicación serial
  
}


void loop() {
  
  //.......................................
  // LOGICA DEL SENSOR PARA CODIGO DE GRAY
  //.......................................
  
  //Tiempo de envio y recepcion
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10); // Cambiado a 10 microsegundos para asegurar una señal limpia
  digitalWrite(TRIG, LOW);
  
  //Recepcion del eco de respuesta
  duracion = pulseIn(ECHO, HIGH);
  
  // Calcular la distancia en centímetros
  distancia = duracion / 58.2;
  int gray = distancia / 42; // Divide el rango (335/8 = 42)
  
  switch (gray) {
    case 0:
      Serial.print("Rango: 0-41, Codigo Gray: ");
      Serial.println("000"); 
      digitalWrite(pinBit1, LOW);
      digitalWrite(pinBit2, LOW);
      digitalWrite(pinBit3, LOW);
      break;
    case 1:
      Serial.print("Rango: 42-83, Codigo Gray: ");
      Serial.println("001"); 
      digitalWrite(pinBit1, LOW);
      digitalWrite(pinBit2, LOW);
      digitalWrite(pinBit3, HIGH);
      break;
    case 2:
      Serial.print("Rango: 84-125, Codigo Gray: ");
      Serial.println("011"); 
      digitalWrite(pinBit1, LOW);
      digitalWrite(pinBit2, HIGH);
      digitalWrite(pinBit3, HIGH);
      break;
    case 3:
      Serial.print("Rango: 126-167, Codigo Gray: ");
      Serial.println("010"); 
      digitalWrite(pinBit1, LOW);
      digitalWrite(pinBit2, HIGH);
      digitalWrite(pinBit3, LOW);
      break;
    case 4:
      Serial.print("Rango: 168-209, Codigo Gray: ");
      Serial.println("110"); 
      digitalWrite(pinBit1, HIGH);
      digitalWrite(pinBit2, HIGH);
      digitalWrite(pinBit3, LOW);
      break;
    case 5:
      Serial.print("Rango: 210-251, Codigo Gray: ");
      Serial.println("111"); 
      digitalWrite(pinBit1, HIGH);
      digitalWrite(pinBit2, HIGH);
      digitalWrite(pinBit3, HIGH);
      break;
    case 6:
      Serial.print("Rango: 252-293, Codigo Gray: ");
      Serial.println("101"); 
      digitalWrite(pinBit1, HIGH);
      digitalWrite(pinBit2, LOW);
      digitalWrite(pinBit3, HIGH);
      break;
    case 7:
      Serial.print("Rango: 294-335, Codigo Gray: ");
      Serial.println("100"); 
      digitalWrite(pinBit1, HIGH);
      digitalWrite(pinBit2, LOW);
      digitalWrite(pinBit3, LOW);
      break;
    default:
      Serial.println("Error"); 
      break; // Manejo de error, por si acaso
  }
  
   delay(1000);
}
