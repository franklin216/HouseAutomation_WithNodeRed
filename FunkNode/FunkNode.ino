#include <RCSwitch.h>
#include <SPI.h>
#include "SSID.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
IPAddress server(192, 168, 1, 44);
 
RCSwitch mySwitch = RCSwitch();
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 
	// Transmitter is connected to NodeMCU Pin #15  
	mySwitch.enableTransmit(15);//nodemcu
	Serial.begin(9600);
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

	client.setServer(server, 1883);
	client.setCallback(callback);

	// Allow the hardware to sort itself out
	delay(1500);

}
void loop() {

	if (!client.connected()) {
		reconnect();
	}
	client.loop();
 
}

void reconnect() {
  // Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect(mqttClientName, mqttUserName, mqttPassword)) {
			  Serial.println("connected");
			  // Once connected, publish an announcement...
			  client.publish("outTopic","hello world");
			  // ... and resubscribe
			  client.subscribe("inTopic");
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

	mySwitch.send(i, 24);
  
}