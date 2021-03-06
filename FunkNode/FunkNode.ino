#include <RCSwitch.h>
#include <SPI.h>
#include <WiFiConstants.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

RCSwitch mySwitch = RCSwitch();
WiFiClient espClient;
PubSubClient client(espClient);
 
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 10000;           // interval at which to blink (milliseconds)
const char* mqttClientName = "yourArduinoClient";

void setup() {
 
	// Transmitter is connected to Arduino Pin #10  
	// mySwitch.enableTransmit(10);
	// Transmitter is connected to NodeMCU Pin #15  
	mySwitch.enableTransmit(15);//nodemcu
	Serial.begin(115200);
	Serial.println("Starte Serial");

	delay(10);
	// We start by connecting to a WiFi network
	Serial.println();Serial.print("Connecting to ");Serial.println(ssid);

	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");	Serial.println("WiFi connected");Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	client.setServer(mqttServer, mqttPort);
	client.setCallback(callback);

	// Allow the hardware to sort itself out
	delay(1500);
}

void loop() {

	if (!client.connected()) {
		reconnect();
	}
	client.loop();
	
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= interval) {
		// save the last time you blinked the LED
		previousMillis = currentMillis;

		client.publish("transmitter/livingRoom/heartbeat","hello world");
	}
 
}

void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect(mqttClientName, mqttUserName, mqttPassword)) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			client.publish("transmitter/livingRoom/heartbeat","hello world");
			// ... and resubscribe
			client.subscribe("livingRoom/transmitter");
		} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i=0;i<length;i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();

	payload[length] = '\0';
	String s = String((char*)payload);
	int i= s.toInt();

	//  char string[] = "1234";
	//int sum = atoi( string );
	//
	mySwitch.send(i, 24);

	client.publish("transmitter/livingRoom/sent",(char*)payload);

}