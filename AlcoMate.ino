/*
 *  Simple HTTP get webclient test
 */

#include <ESP8266WiFi.h>

const char* ssid     = "privateNetwork";
const char* password = "dontUseMyWifi";

const char* host = "104.237.146.42";

const double analogInPin = A0;  // Analog input pin that the potentiometer is attached to
// const int analogOutPin = 0; // Analog output pin 

double sensorValue = 0; 
double sensorValueArr[10];

void setup() {

  pinMode(4, OUTPUT);
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  double max = 0;

//  for (int c = 0; c <5; c++){
//    digitalWrite(4, HIGH);
//    delay(500);
//    digitalWrite(4, LOW);
//    delay(500);
//  }

//delay(5000);

  for (int m = 0; m<3; m++){
    digitalWrite(4, HIGH);
    delay(2000);
    digitalWrite(4, LOW);
    delay(2000);
  }

  delay(3000);
  
  // delay(5000);
  ++value;
  
  // analogWrite(analogOutPin, 1);
  // read the analog in value:
  sensorValue = analogRead(analogInPin);


for (int i=0; i<10; i++){
   sensorValueArr[i] = analogRead(A0);
   delay(100);
}

for (int j=0; j<10; j++){
  //Serial.print(sensorValueArr[j]);
  if (sensorValueArr[j] > max) {
    max = sensorValueArr[j];
  }
}



double BAC=max*(.25/1000);
 
  // print the results to the serial monitor:
  Serial.print("BAC = " );
  Serial.println(BAC);
  //Serial.print("max = " );
  //Serial.println(max);
  Serial.print("connecting to ");
  Serial.println(host);
  String HTTPget = "";
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/alco-mate.com/public_html/PA2/request.php?usr=adamdom&pass=asdf&BAC="+String(BAC);
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  //client.print(String("GET") + url + " HTTP/1.1\r\n" +
   //            "Host: " + host + "\r\n" + 
    //           "Connection: close\r\n\r\n");

   client.println(String("GET ") + "/alco-mate.com/public_html/PA2/request.php?usr=adamdom&pass=asdf&BAC=" +String(BAC)+ " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");   
   

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
      
  delay(5000);
  
//  else {Serial.println(F("Email failed"));digitalWrite(LED_PIN, LOW);} 
//  ESP.deepSleep(0, WAKE_RF_DEFAULT); 
//  delay(10000); //Security, the sleep mode need some time to activate    


  Serial.println();
  Serial.println("closing connection");
}
