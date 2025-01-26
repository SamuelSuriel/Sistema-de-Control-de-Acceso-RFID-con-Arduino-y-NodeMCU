#include <ESP8266WiFi.h>

// Credenciales WiFi
const char* ssid = "MY_NETWORK";
const char* password = "PASSWWORD";

// Creamos un server en el puerto 80
WiFiServer server(80);

// Variables auxiliares
String header;                  
unsigned long lastTime = 0;     
const unsigned long timeout = 2000; 

void setup() {
  // Inicia Serial para comunicar con Arduino
  Serial.begin(9600); 
  delay(100);

  // Iniciar WiFi
  Serial.println();
  Serial.printf("Conectando a %s", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Iniciamos servidor web
  server.begin();
  Serial.println("Servidor web iniciado.");
}

void loop() {
  // 1) Revisar si hay cliente web
  WiFiClient client = server.available();  
  if (client) {
    lastTime = millis();
    Serial.println("Nuevo cliente conectado.");
    String currentLine = "";
    header = "";

    while (client.connected() && (millis() - lastTime <= timeout)) {
      if (client.available()) {
        char c = client.read();
        header += c;

        // Si detectamos fin de línea
        if (c == '\n') {
          // Línea vacía => fin del encabezado HTTP
          if (currentLine.length() == 0) {
            // Responder al cliente con cabeceras
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Verificar rutas
            if (header.indexOf("GET /open") >= 0) {
              Serial.println("Comando desde Web: OPEN");
              // Enviamos a Arduino UNO por Serial
              Serial.println("OPEN");
            }
            else if (header.indexOf("GET /close") >= 0) {
              Serial.println("Comando desde Web: CLOSE");
              // Enviamos a Arduino UNO por Serial
              Serial.println("CLOSE");
            }

            // Página HTML sencilla
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
            client.println("<body><h1>Control de Acceso</h1>");
            client.println("<p><a href=\"/open\"><button>Abrir</button></a></p>");
            client.println("<p><a href=\"/close\"><button>Cerrar</button></a></p>");
            client.println("</body></html>");

            // Cerrar la respuesta
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    // Fin: cerrar conexión
    client.stop();
    Serial.println("Cliente desconectado.\n");
  }

  // 2) (Opcional) Escuchar respuestas del Arduino UNO
  if (Serial.available() > 0) {
    String resp = Serial.readStringUntil('\n');
    resp.trim();
    if (resp.length() > 0) {
      Serial.print("Arduino dice: ");
      Serial.println(resp);
      // Para procesar la respuesta y guardarla en una variable,
      // o mandar otra petición, etc.
    }
  }
}
