//Código Proyecto Fundamentos de Arquitectura
//Estudiante: Meibel Ceciliano Picado

//............................
// CONFIGURACION DE LA LCD
//............................

#include <Wire.h>  // Incluir la librería para la comunicación I2C
#include <LiquidCrystal_I2C.h>  // Incluir la librería para la pantalla LCD I2C

// Definir la dirección I2C de la pantalla LCD (puede variar según el modelo)
#define LCD_ADDRESS 0x27

// Definir el número de columnas y filas de la pantalla LCD
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Crear un objeto de la clase LiquidCrystal_I2C
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

//..................
// PINES DEL SENSOR
//..................

int TRIG = 6; // Pin del sensor ultrasónico - TRIG
int ECHO = 5; // Pin del sensor ultrasónico - ECHO

int duracion;
int distancia;

//....................................
// PINES DEL ARDUINO PARA MANDAR GRAY
//....................................

int pinBitA = 2; // Pin del Arduino para el bit A
int pinBitB = 3; // Pin del Arduino para el bit B
int pinBitC = 4;  // Pin del Arduino para el bit C


//.........................................
// PINES DEL ARDUINO PARA RECIBIR EXCESO 3
//.........................................

int pinBitX = 7; // Pin del Arduino para el bit X
int pinBitY = 8; // Pin del Arduino para el bit Y
int pinBitZ = 9;  // Pin del Arduino para el bit Z


void setup() {
  
  //....................
  // SENSOR ULTRASONICO
  //....................
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(pinBitA, OUTPUT);
  pinMode(pinBitB, OUTPUT);
  pinMode(pinBitC, OUTPUT);
  
  Serial.begin(9600);    // Inicializa la comunicación serial
  
  
  //..................
  //      ARDUINO
  //..................
  
  // PINES QUE RECIBEN EL BINARIO EN EXCESO 3
  pinMode(pinBitX, INPUT);
  pinMode(pinBitY, INPUT);
  pinMode(pinBitZ, INPUT);
  
  //..................
  //      LCD
  //..................
  
  // Inicializar la comunicación I2C y la pantalla LCD
  Wire.begin();
  lcd.init();
  lcd.backlight();  //Se prende la luz de la lcd

  // Limpiar la pantalla LCD y establecer el cursor en la posición (0, 0)
  lcd.clear();
  lcd.setCursor(0, 0);

  // Mostrar un mensaje inicial en la pantalla LCD
  lcd.print(":D Valor Decimal: ");
  
 
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
      Serial.print("Rango: 0-42, Codigo Gray: ");
      Serial.println("000"); 
      digitalWrite(pinBitA, LOW);
      digitalWrite(pinBitB, LOW);
      digitalWrite(pinBitC, LOW);
      break;
    case 1:
      Serial.print("Rango: 43-85, Codigo Gray: ");
      Serial.println("001"); 
      digitalWrite(pinBitA, LOW);
      digitalWrite(pinBitB, LOW);
      digitalWrite(pinBitC, HIGH);
      break;
    case 2:
      Serial.print("Rango: 86-128, Codigo Gray: ");
      Serial.println("011"); 
      digitalWrite(pinBitA, LOW);
      digitalWrite(pinBitB, HIGH);
      digitalWrite(pinBitC, HIGH);
      break;
    case 3:
      Serial.print("Rango: 439-584, Codigo Gray: ");
      Serial.println("010"); 
      digitalWrite(pinBitA, LOW);
      digitalWrite(pinBitB, HIGH);
      digitalWrite(pinBitC, LOW);
      break;
    case 4:
      Serial.print("Rango: 585-730, Codigo Gray: ");
      Serial.println("110"); 
      digitalWrite(pinBitA, HIGH);
      digitalWrite(pinBitB, HIGH);
      digitalWrite(pinBitC, LOW);
      break;
    case 5:
      Serial.print("Rango: 731-876, Codigo Gray: ");
      Serial.println("111"); 
      digitalWrite(pinBitA, HIGH);
      digitalWrite(pinBitB, HIGH);
      digitalWrite(pinBitC, HIGH);
      break;
    case 6:
      Serial.print("Rango: 877-1023, Codigo Gray: ");
      Serial.println("101"); 
      digitalWrite(pinBitA, HIGH);
      digitalWrite(pinBitB, LOW);
      digitalWrite(pinBitC, HIGH);
      break;
    case 7:
      Serial.print("Rango: 877-1023, Codigo Gray: ");
      Serial.println("100"); 
      digitalWrite(pinBitA, HIGH);
      digitalWrite(pinBitB, LOW);
      digitalWrite(pinBitC, LOW);
      break;
    default:
      Serial.println("Error"); 
      break; // Manejo de error, por si acaso
  }
  
   delay(1000);
  
 
  
  //...............................................................
  //  CODIGO PARA ENTRADA EXCESO 3 Y PASAR A DECIMAL PARA LA LCD
  //...............................................................
  
 
  // Leer los valores de los pines de entrada
  int valX = digitalRead(pinBitX);
  int valY = digitalRead(pinBitY);
  int valZ = digitalRead(pinBitZ);

  // Calcular el valor decimal usando expresiones booleanas
  int decimalValue = (!valX && !valY && !valZ) * 0 +
                     (!valX && !valY &&  valZ) * 1 +
                     (!valX &&  valY && !valZ) * 2 +
                     (!valX &&  valY &&  valZ) * 3 +
                     ( valX && !valY && !valZ) * 4 +
                     ( valX && !valY &&  valZ) * 5 +
                     ( valX &&  valY && !valZ) * 6 +
                     ( valX &&  valY &&  valZ) * 7;

  // Imprimir el valor decimal en la pantalla LCD
  lcd.setCursor(0, 1);  // Establecer el cursor en la segunda línea nuevamente
  lcd.print(decimalValue);  // Mostrar el valor decimal en la pantalla LCD

  delay(1000);
}

