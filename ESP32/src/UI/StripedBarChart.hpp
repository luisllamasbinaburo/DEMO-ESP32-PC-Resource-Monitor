#pragma once

#include "UIComponent.hpp"


class StripedBarChart : public UIComponent
{
public:
	int X, Y;
	int Width, Height;

	StripedBarChart(int x, int y, int width, int height) : X(x), Y(y), Width(width), Height(height)
	{
	}

	void Render(TFT_eSprite& screen)
	{
		screen.fillRect(X, Y, Width, Height, FOREGROUND_25);

		for (size_t y_count = 0; y_count < Height * Value; y_count++)
		{

			if (y_count % 3 == 0)
			{
				screen.drawFastHLine(X, 135- y_count - Y, Width, FOREGROUND_25);
			}
			else
			{
				auto color = barPalette.GetData((float)y_count / Height * 64);
				screen.drawFastHLine(X, 135 - y_count - Y, Width, color);
			}
		}

		screen.drawRect(X, Y, Width, Height, FOREGROUND);
	}

};

