#pragma once

#include "UIComponent.hpp"

class CircularSectorChart : public UIComponent
{
public:
	int X, Y;
	int Radius;

	static void fillCircularSector(TFT_eSprite& screen, int x, int y, int start_angle, int sub_angle, int r, unsigned int colour)
	{

		const float DEG2RAD = 0.0174532925;

		// Calculate first pair of coordinates for segment start
		float sx = cos((start_angle - 90) * DEG2RAD);
		float sy = sin((start_angle - 90) * DEG2RAD);
		uint16_t x1 = sx * r + x;
		uint16_t y1 = sy * r + y;

		// Draw colour blocks every inc degrees
		for (int i = start_angle; i < start_angle + sub_angle; i++)
		{

			// Calculate pair of coordinates for segment end
			int x2 = cos((i + 1 - 90) * DEG2RAD) * r + x;
			int y2 = sin((i + 1 - 90) * DEG2RAD) * r + y;

			screen.fillTriangle(x1, y1, x2, y2, x, y, colour);

			// Copy segment end to sgement start for next segment
			x1 = x2;
			y1 = y2;
		}
	}

	CircularSectorChart(int x, int y, int radius) : X(x), Y(y), Radius(radius)
	{
	}

	void Render(TFT_eSprite& screen)
	{
		auto angle = 180 * Value;
		fillCircularSector(screen, X, Y, -90, 180, Radius, FOREGROUND_50);
		fillCircularSector(screen, X, Y, -90, angle, Radius, FOREGROUND);
		fillCircularSector(screen, X, Y, -90, 180, Radius - 4, WIDGET_BACKGROUND);
	}

};