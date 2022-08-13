/***************************************************
Copyright (c) 2022 Luis Llamas
(www.luisllamas.es)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses
****************************************************/

#include <M5StickCPlus.h> 

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <ESP_Color.h>

#include "./utils/config.h"  // fill with your network data
#include "./themes/modern.h"

#include "./utils/ESP32_Utils.hpp"

#include "./src/ResourceMonitorPacket.hpp";
#include "./src/ResourceMonitor.hpp";
#include "./src/MqttService.hpp";

static TFT_eSprite tftSprite(&M5.Lcd);

ResourceMonitor resourceMonitor(tftSprite);

MqttService mqttService;

void setup()
{
	Serial.begin(105200);
	M5.begin();
	M5.IMU.Init();

	M5.Lcd.setRotation(3);

	tftSprite.createSprite(240, 135);

	ConnectWiFi_STA(true);

	mqttService.Init();
	mqttService.OnDataReceived = [](ResourceMonitorPacket packet) -> void
	{
		resourceMonitor.Update(packet);
		resourceMonitor.Render();
		tftSprite.pushSprite(0, 0);
	};

	resourceMonitor.Render();
	tftSprite.pushSprite(0, 0);
}

void loop()
{
	M5.update();

	mqttService.HandleMqtt();
}