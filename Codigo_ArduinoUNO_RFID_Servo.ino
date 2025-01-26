#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// ========== Pines RFID ========== //
#define RST_PIN 9     // RST
#define SS_PIN  10    // SDA(SS)
MFRC522 rfid(SS_PIN, RST_PIN);  

// ========== Servo ========== //
Servo myServo;
const int SERVO_PIN = 3;  // usar pin 3 (PWM)

// ========== Serial ========== //

const unsigned long BAUD_RATE = 9600;

// UID de tarjetas autorizadas 
byte tarjeta1[] = {0xFB, 0xDB, 0x4C, 0xC}; 
byte tarjeta2[] = {0x19, 0x95, 0xc6, 0x2B}; 

void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial) {;}  // Espera si es necesario 

  // Inicializa SPI y RFID
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("RFID inicializado.");

  // Inicializa el servo
  myServo.attach(SERVO_PIN);
  myServo.write(90); // Iniciamos con el servo en 90° (puerta cerrada)
  Serial.println("Servo inicializado en 0°.");

  Serial.println("Setup completo. Esperando datos por Serial y/o lectura de tarjeta...");
}

void loop() {
  // 1) Escuchar comandos desde Serial (NodeMCU)
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();  // Quita espacios o saltos extra
    if (comando.equalsIgnoreCase("OPEN")) {
      abrirPuerta();
      // En este ejemplo, no cierro de inmediato, 
      // lo dejo abierto hasta que se envíe "CLOSE" 
      // o se cumpla otra condición
    } 
    else if (comando.equalsIgnoreCase("CLOSE")) {
      cerrarPuerta();
    }
    else {
      Serial.print("Comando desconocido: ");
      Serial.println(comando);
    }
  }

  // 2) Leer tarjeta RFID
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Obtenemos el UID leído
    byte currentUID[4];
    for (byte i = 0; i < rfid.uid.size; i++) {
      currentUID[i] = rfid.uid.uidByte[i];
    }

    // Imprimimos en Serial para debug
    Serial.print("UID tarjeta leída: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    // Comparamos con tarjetas autorizadas
    if (compareUID(currentUID, tarjeta1, 4) || compareUID(currentUID, tarjeta2, 4)) {
      Serial.println(">> Tarjeta AUTORIZADA <<");
      abrirPuerta();
      delay(3000);   // Mantén la puerta abierta 3 seg
      cerrarPuerta();
      
      // Serial.println("CARD_OK");
    } else {
      Serial.println(">> Tarjeta NO autorizada <<");
      // Serial.println("CARD_FAIL");
    }

    // Detener lectura
    rfid.PICC_HaltA();
  }
}

// ========== Funciones auxiliares ========== //

bool compareUID(byte *uid1, byte *uid2, byte length) {
  for (byte i = 0; i < length; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}

void abrirPuerta() {
  myServo.write(0);  // Gira a 0° 
  Serial.println("Puerta ABRIENDO (servo a 0°)");
}

void cerrarPuerta() {
  myServo.write(90);   // Regresa a 90°
  Serial.println("Puerta CERRANDO (servo a 90°)");
}
