#pragma once

#include <functional>

#include "./ResourceMonitorPacket.hpp";

#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);


class MqttService
{
public:
	std::function<void(ResourceMonitorPacket)> OnDataReceived;

	void Init()
	{
		mqttClient.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
		SuscribeMqtt();

		mqttClient.setCallback([this](char* topic, uint8_t* payload, unsigned int length) -> void
		{
			this->OnMqttReceived(topic, payload, length);
		});
	}


	void ConnectMqtt()
	{
		while (!mqttClient.connected())
		{
			Serial.print("Starting MQTT connection...");
			if (mqttClient.connect(MQTT_CLIENT_NAME))
			{
				SuscribeMqtt();
			}
			else
			{
				Serial.print("Failed MQTT connection, rc=");
				Serial.print(mqttClient.state());
				Serial.println(" try again in 5 seconds");

				delay(5000);
			}
		}
	}

	void HandleMqtt()
	{
		if (!mqttClient.connected())
		{
			ConnectMqtt();
		}
		mqttClient.loop();
	}

	void Debug(float value)
	{

		Serial.println(value);
	}

	void SuscribeMqtt()
	{
		mqttClient.subscribe("ResourceMonitor/Device1/Received");
	}

	String payload;
	void PublisMqtt(unsigned long data)
	{

	}

	String content = "";
	void OnMqttReceived(char* topic, uint8_t* payload, unsigned int length)
	{
		content = "";
		for (size_t i = 0; i < length; i++)
		{
			content.concat((char)payload[i]);
		}

		StaticJsonDocument<200> doc;
		DeserializationError error = deserializeJson(doc, content);
		if (error) return;


		ResourceMonitorPacket packet;

		packet.Cpu = doc["cpu"];
		packet.Gpu = doc["gpu"];
		packet.Ram = doc["ram"];
		packet.Ssd = doc["ssd"];
		packet.Network = doc["net"];
		packet.Temperature = doc["temp"];

		if(OnDataReceived != nullptr) OnDataReceived(packet);
	}
};