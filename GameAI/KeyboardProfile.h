#pragma once

class KeyboardProfile
{
public:
	KeyboardProfile();
	~KeyboardProfile();

	void SetKeys(int leftKey, int rightKey, int upKey, int downKey, int mouseButton);

	int leftKey;
	int rightKey;
	int upKey;
	int downKey;
	int mouseButton;
};

