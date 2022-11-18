#include <ESP8266WiFi.h>

#define pinLed D6
String ssid = "Jose";//aqui va el nombre de la red wifi
String password = "zjos1271";// y esta es la clave del wifi

WiFiServer server(80);//se crea el servidor web
int estado = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\n");

  pinMode(pinLed,OUTPUT);

  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
   Serial.println("");
   Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++++");
   Serial.print("Conectado a la red wifi: ");
   Serial.println(WiFi.SSID());
   Serial.print("IP: ");
   Serial.println(WiFi.localIP());//para acceder al contro remoto de la luz se necesita la ip que no brinda
   Serial.print("macAdress: ");
   Serial.println(WiFi.macAddress());
   Serial.println("++++++++++++++++++++++++++++++++++++++++++++++++++");

   server.begin();
   digitalWrite(pinLed, 0);

}

void loop() {
  // put your main code here, to run repeatedly:

  WiFiClient client = server.available();//se genera el cliente

  if(!client){
      return;
    }

  Serial.println("Nuevo cliente...");
  while(!client.available()){
      delay(1);
    }

String peticion = client.readStringUntil('\r');
Serial.println(peticion);
client.flush();

if(peticion.indexOf('LED=ON') != -1)
  estado=1;
if(peticion.indexOf('LED=OFF') != -1)
  estado=0;

 digitalWrite(pinLed, estado);


 client.println("HTTP/1.1 200 OK");
 client.println("");
 client.println("");
 client.println("");
 client.println("");

 //inicia la pagina

  client.println("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  client.println("<title>Control de LED</title></head>");
  client.println("<body style='font-family: Century gothic ;width: 800;'><center>");
  client.println("<div style='box-shadow: 0 0 20px 8px rgba(0,0,0,0.22); padding: 20px; display:inline-block; margin:30px; '>");
  client.println("<h1>LED 1</h1>");
  
  client.println("<h2>el led esta encendido</h2>");
            
  client.println("<button style='background-color: red ; color: white; border-radius: 10px;'");
  client.println("type='button' onClick=location.href='/LED=OFF'><h2>Apagar</h2>");
  client.println("</button><button style='background-color: blue ; color: white; border-radius: 10px;'");
  client.println("type='button' onClick=location.href='/LED=ON'><h2>Encender</h2>");
  client.println("</button></div></center></body></html>");
  //fin de la pagina
  delay(10);
  Serial.println("peticion Finalizada");
  Serial.println("");

}
