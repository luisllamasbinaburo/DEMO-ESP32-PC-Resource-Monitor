#pragma once

#include "UI/UI.hpp"

class ResourceMonitor
{
public:
	ResourceMonitor(TFT_eSprite& screen) : _screen(screen)
	{
		CpuBar = new StripedBarChart(10 + 30 * 0, 15, 20, 105);
		GpuBar = new StripedBarChart(10 + 30 * 1, 15, 20, 105);
		RamBar = new StripedBarChart(10 + 30 * 2, 15, 20, 105);
		SsdBar = new StripedBarChart(10 + 30 * 3, 15, 20, 105);
		TemperatureChart = new SingleBubbleChart(165, 45, 26);
		NetworkChart = new CircularSectorChart(180, 120, 26);

		uiComponents.push_back(CpuBar);
		uiComponents.push_back(GpuBar);
		uiComponents.push_back(RamBar);
		uiComponents.push_back(SsdBar);
		uiComponents.push_back(TemperatureChart);
		uiComponents.push_back(NetworkChart);
	}


	void Update(ResourceMonitorPacket packet)
	{
		config.Cpu = packet.Cpu;
		config.Gpu = packet.Gpu;
		config.Ram = packet.Ram;
		config.Ssd = packet.Ssd;
		config.Network = packet.Network;
		config.Temperature = packet.Temperature;
	}

	void DrawLabels()
	{
		_screen.setTextColor(TFT_WHITE);
		_screen.setTextSize(1);

		_screen.setCursor(12 + 30 * 0, 5);
		_screen.printf("CPU");
		_screen.setCursor(12 + 30 * 0, 125);
		_screen.printf("%.0f%%", config.Cpu);

		_screen.setCursor(12 + 30 * 1, 5);
		_screen.printf("GPU");
		_screen.setCursor(12 + 30 * 1, 125);
		_screen.printf("%.0f%%", config.Gpu);

		_screen.setCursor(12 + 30 * 2, 5);
		_screen.printf("RAM");
		_screen.setCursor(12 + 30 * 2, 125);
		_screen.printf("%.0f%%", config.Ram);

		_screen.setCursor(12 + 30 * 3, 5);
		_screen.printf("SSD");
		_screen.setCursor(12 + 30 * 3, 125);
		_screen.printf("%.0f%%", config.Ssd);

		_screen.setCursor(180 - 35, 6);
		_screen.printf("TEMP:");
		_screen.setCursor(200, 45);
		_screen.printf("%.1f C", config.Temperature);

		_screen.setCursor(180 - 35, 120 - 38);
		_screen.printf("NETWORK");
		_screen.setCursor(180 - 12, 120 - 6);
		_screen.printf("%.1f%%", config.Network);
	}

	void Render()
	{
		_screen.fillRect(0, 0, 240, 135, APP_BACKGROUND);
		_screen.fillRect(3, 3, 234, 129, WIDGET_BACKGROUND);

		CpuBar->SetValue(config.Cpu / 100);
		GpuBar->SetValue(config.Gpu / 100);
		SsdBar->SetValue(config.Ram / 100);
		RamBar->SetValue(config.Ssd / 100);
		TemperatureChart->SetValue(config.Temperature / TEMPERATURE_MAX);
		NetworkChart->SetValue(config.Network / NETWORK_SPEED_MAX);

		for (auto uiComponent : uiComponents)
			uiComponent->Render(_screen);

		DrawLabels();
	}


private:
	TFT_eSprite& _screen;

	ResourceMonitorPacket config;

	const double TEMPERATURE_MAX = 95;
	const double NETWORK_SPEED_MAX = 50;

	StripedBarChart* CpuBar;
	StripedBarChart* GpuBar;
	StripedBarChart* SsdBar;
	StripedBarChart* RamBar;
	SingleBubbleChart* TemperatureChart;
	CircularSectorChart* NetworkChart;

	std::vector<UIComponent*> uiComponents;
};