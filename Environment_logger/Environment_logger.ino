#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            7         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Initialize the Ethernet server library
// Full internet address information is vital to make a web connection
EthernetClient client;
IPAddress ip(192, 168, 0, 177);
IPAddress dnsip(8,8,8,8);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
char macAddress[] = "0xDE0xAD0xBE0xEF0xFE0xED";
char location[] = "living_room";
char server[] = "12thegreen.uk"; // web address of the sql server
unsigned long seconds = 10000L; //Notice the L. entering a millisecond delay over 32000 fails. 
unsigned long minutes = seconds * 60;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  dht.begin();
  Serial.println("DHT22 Unified Sensor logger");
  Serial.print("Sensor location: ");
  Serial.println(location);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    // initialize digital pin 13 as an output.
    pinMode(13, OUTPUT);
  }
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, dnsip, gateway, subnet);
  Serial.print("Arduino IP address: ");
  Serial.println(Ethernet.localIP());
  Serial.print("Arduino MAC address: ");
  Serial.println(macAddress);
  delay(1000);
}


void loop() {
   if (client.connect(server, 80)) {
    Serial.print("-> Connected to: ");
    Serial.println(server);
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);
    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.println(t);
    Serial.println(h);
    Serial.println(hic);
    Serial.println(location);
    Serial.println(macAddress);
    Serial.println(Ethernet.localIP());

    // Make a HTTP request:
    client.print("GET /write_arduino_log.php?temperature=");
    client.print(t);
    client.print("&humidity=");
    client.print(h);
    client.print("&heat_index=");
    client.print(hic);
    client.print("&location=");
    client.print(location);
    client.print("&MAC_address=");
    client.print(macAddress);
    client.print("&ip_address=");
    client.print(Ethernet.localIP());
    client.print(" HTTP/1.1");
    client.println();
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.println();
    while (client.connected())
    {//Read response
      while (client.available())
      {
        char response = client.read();
        Serial.print(response);
      }
    }
    client.flush();
    Serial.println("drop connection");
    client.stop();
    Serial.println("client disconnected");
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  }
  else {
    // you didn't get a connection to the server:
    Serial.println("--> connection failed");
  }

  delay(minutes);
  
}


