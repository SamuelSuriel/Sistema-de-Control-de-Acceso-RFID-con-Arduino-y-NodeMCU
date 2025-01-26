# **Sistema de Control de Acceso RFID con Arduino y NodeMCU**
![rfid](https://github.com/user-attachments/assets/c6a00bb8-28d7-4263-8f3b-6700a6e54610)

Este proyecto implementa un sistema de control de acceso mediante tarjetas RFID utilizando un Arduino UNO y un NodeMCU (ESP8266). Incluye una app móvil para interactuar con el sistema y controlar un servo que simula la apertura y cierre de una puerta.  

## **Características principales**
- Control de acceso basado en tarjetas RFID.
- Apertura y cierre de puerta controlado por un servo.
- Comunicación entre Arduino y NodeMCU para sincronización del sistema.
- Interfaz móvil creada en MIT App Inventor para enviar comandos al sistema.
- Botones para funciones futuras como registrar tarjetas y ver registros.

---

## **Requisitos del Proyecto**

### **Hardware**
- **Arduino UNO**: Controla el lector RFID y el servo.
- **NodeMCU (ESP8266)**: Permite la comunicación con la app móvil vía WiFi.
- **Lector RFID RC522**: Para leer las tarjetas RFID.
- **Servo SG90**: Simula la apertura/cierre de una puerta.
- Fuente de alimentación externa (opcional para el servo).
- Cables, protoboard y resistencias para conexiones.

![Componentes](https://github.com/user-attachments/assets/4a0ddcb5-aa3c-4661-b7e9-0d60cb73ee84)

### **Software**
- [**Arduino IDE**](https://www.arduino.cc/en/software): Para programar el Arduino UNO y el NodeMCU.
- [**MIT App Inventor**](https://appinventor.mit.edu/): Para crear la app móvil.
- Librerías:
  - **MFRC522**: Para el lector RFID.
  - **ESP8266WiFi**: Para el manejo de WiFi en el NodeMCU.

---

## **Estructura del Proyecto**
```
proyecto-control-acceso-rfid/
│
├── ArduinoUNO/
│   ├── codigo_arduino.ino        # Código para el Arduino UNO + Servo
│   
├── NodeMCU/
│   ├── codigo_nodemcu.ino        # Código para el NodeMCU
│   
├── App/
│   ├── proyecto_mit_app.aia      # Archivo del proyecto de la app móvil
│   ├── capturas_app/             # Capturas de pantalla de la app
│   
├── Documentacion/
│   ├── Reporte.pdf               # Documento con los detalles del proyecto
│   ├── esquema_conexiones.png    # Diagrama de conexiones físicas
│   ├── diagrama_flujo.png        # Diagrama de flujo del sistema
│   
├── LICENSE                       # Licencia del proyecto
└── README.md                     # Este archivo
```

![Diagrama de flujo -mermaid](https://github.com/user-attachments/assets/3de1bb74-93f2-4d51-a711-b390f505505a)

---

## **Diagrama de Conexiones**
Aquí se describe cómo conectar los componentes principales del sistema. 
![Diagrama lógico](https://github.com/user-attachments/assets/9a26e283-a9b8-4f60-84d9-fce566ef8355)


### **Conexiones del RC522 (Lector RFID) al Arduino UNO**
| Lector RFID | Arduino UNO |
|-------------|-------------|
| VCC         | 3.3V        |
| GND         | GND         |
| RST         | Pin 9       |
| SDA         | Pin 10      |
| MOSI        | Pin 11      |
| MISO        | Pin 12      |
| SCK         | Pin 13      |

### **Conexiones del Servo al Arduino UNO**
| Servo | Arduino UNO |
|-------|-------------|
| GND   | GND         |
| VCC   | 5V          |
| Signal| Pin 3       |

### **Conexión entre Arduino UNO y NodeMCU**
| Arduino UNO | NodeMCU    |
|-------------|------------|
| TX (Pin 1)  | RX (D9)    |
| RX (Pin 0)  | TX (D10)   |

---

## **Cómo usar el Proyecto**

1. **Clona el repositorio**:
   ```bash
   git clone https://github.com/TU_USUARIO/proyecto-control-acceso-rfid.git
   cd proyecto-control-acceso-rfid
   ```

2. **Carga los códigos en los microcontroladores**:
   - Abre `codigo_arduino.ino` en el Arduino IDE y súbelo al Arduino UNO.
   - Abre `codigo_nodemcu.ino` en el Arduino IDE, configura las credenciales de tu red WiFi y súbelo al NodeMCU.

3. **Configura la app móvil**:
   - Importa el archivo `proyecto_mit_app.aia` en [MIT App Inventor](https://appinventor.mit.edu/).
   - Compila la app e instálala en tu dispositivo Android.

4. **Conecta el hardware**:
   - Sigue el diagrama de conexiones descrito arriba.
   - Alimenta los microcontroladores y prueba las conexiones.

5. **Prueba el sistema**:
   - Acerca una tarjeta RFID al lector.
   - Observa cómo el servo reacciona abriendo o cerrando la puerta.
   - Controla el servo desde la app móvil.

---

## **Capturas de Pantalla**
### **Sistema en funcionamiento**
![cs](https://github.com/user-attachments/assets/9c11ee3e-436c-4095-b5de-a7ae4fb48d80)

![bloques app](https://github.com/user-attachments/assets/9704c625-c965-4509-876f-65ba54ef8220)

![app](https://github.com/user-attachments/assets/739bb93b-1f2a-43b7-aba1-c464a15168bc)

---

## **Licencia**
Este proyecto está licenciado bajo la [MIT License](LICENSE).

---

## **Contribuciones**
¡Las contribuciones son bienvenidas! Si deseas mejorar el proyecto o agregar funcionalidades, por favor:
1. Haz un fork del repositorio.
2. Crea una rama para tu cambio (`git checkout -b nueva-funcionalidad`).
3. Realiza tus cambios y súbelos (`git push origin nueva-funcionalidad`).
4. Abre un pull request.
