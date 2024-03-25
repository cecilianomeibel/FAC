
//CODIGO ACTUADOR
//TALLER 2 FUNDAMENTOS DE ARQUITECTURA
//ESTUDIANTE: MEIBEL CECILIANO PICADO

long valor;

const int pinBit1 = 2;  // Pin digital para el bit 1
const int pinBit2 = 3;  // Pin digital para el bit 2
const int pinBit3 = 4;  // Pin digital para el bit 3

void setup() {
  pinMode(A0, INPUT);  // Porque es la terminan que está conectada al potenciómetro
  pinMode(pinBit1, OUTPUT);
  pinMode(pinBit2, OUTPUT);
  pinMode(pinBit3, OUTPUT);

  Serial.begin(9600);  // Inicializa la comunicación serial
}

void loop() {
  valor = analogRead(A0);      // lee el valor del potenciómetro
  int division = valor / 146;  // Divide el rango (1023/7 = 146.14)

  // Imprime el rango y el código de Gray correspondiente
  switch (division) {
    case 0:
      Serial.print("Rango: 0-146, Codigo Gray: ");
      Serial.println("000");
      digitalWrite(pinBit1, LOW);
      digitalWrite(pinBit2, LOW);
      digitalWrite(pinBit3, LOW);
      break;
    case 1:
      Serial.print("Rango: 147-292, Codigo Gray: ");
      Serial.println("001");
      digitalWrite(pinBit1, LOW);
      digitalWrite(pinBit2, LOW);
      digitalWrite(pinBit3, HIGH);
      break;
    case 2:
      Serial.print("Rango: 293-438, Codigo Gray: ");
      Serial.println("011");
      digitalWrite(pinBit1, LOW);
      digitalWrite(pinBit2, HIGH);
      digitalWrite(pinBit3, HIGH);
      break;
    case 3:
      Serial.print("Rango: 439-584, Codigo Gray: ");
      Serial.println("010");
      digitalWrite(pinBit1, LOW);
      digitalWrite(pinBit2, HIGH);
      digitalWrite(pinBit3, LOW);
      break;
    case 4:
      Serial.print("Rango: 585-730, Codigo Gray: ");
      Serial.println("110");
      digitalWrite(pinBit1, HIGH);
      digitalWrite(pinBit2, HIGH);
      digitalWrite(pinBit3, LOW);
      break;
    case 5:
      Serial.print("Rango: 731-876, Codigo Gray: ");
      Serial.println("111");
      digitalWrite(pinBit1, HIGH);
      digitalWrite(pinBit2, HIGH);
      digitalWrite(pinBit3, HIGH);
      break;
    case 6:
      Serial.print("Rango: 877-1023, Codigo Gray: ");
      Serial.println("101");
      digitalWrite(pinBit1, HIGH);
      digitalWrite(pinBit2, LOW);
      digitalWrite(pinBit3, HIGH);
      break;
    default:
      Serial.println("Error");
      break;  // Manejo de error, por si acaso
  }
  delay(1000);  // Espera un breve período antes de volver a leer
}