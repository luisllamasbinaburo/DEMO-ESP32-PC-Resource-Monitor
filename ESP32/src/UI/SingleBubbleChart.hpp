#pragma once

#include "UIComponent.hpp"

class SingleBubbleChart :public UIComponent
{
public:
	int X, Y;
	int Radius;

	SingleBubbleChart(int x, int y, int radius) : X(x), Y(y), Radius(radius)
	{
	}

	void Render(TFT_eSprite& screen)
	{
		auto color = circularPalette.GetData(Value * 64);

		screen.fillCircle(X, Y, Radius * Value, color);

		screen.drawCircle(X, Y, Radius, FOREGROUND);
		screen.drawCircle(X, Y, Radius - 2, FOREGROUND_25);

		screen.drawCircle(X, Y, Radius * 0.8, FOREGROUND_50);
		screen.drawCircle(X, Y, Radius * 0.6, FOREGROUND_50);
		screen.drawCircle(X, Y, Radius * 0.4, FOREGROUND_50);
	}

};