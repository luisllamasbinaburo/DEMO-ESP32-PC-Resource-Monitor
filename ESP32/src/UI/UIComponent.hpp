#pragma once

class UIComponent
{
public:
	virtual void Render(TFT_eSprite& screen) = 0;

	void SetValue(float value)
	{
		Value = value;
	}

	float Value;
};
