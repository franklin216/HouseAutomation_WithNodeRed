# HouseAutomation_WithNodeRed
My Houseautomation with Node-Red


There is the Library WiFiConstants.h in the Code. It is where i store my Constants for WiFi and MQTT. It looks like this:

/*
  WiFiConstants.h - Library for your own Wifi and MQTT Constants.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef wificonstants_h
#define wificonstants_h

#include <PubSubClient.h>


const char* ssid = "yourssid";
const char* password = "yourpassword";
//must be in the sketch, because must be unique
//const char* mqttClientName = "yourArduinoClient"; 
const char* mqttUserName = "yourmqttuser";
const char* mqttPassword = "yourmqttPassword";
const IPAddress mqttServer(192, 168, 1, 44);
const int mqttPort = 1883;

#endif

