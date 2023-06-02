#pragma once
#include "ofMain.h"
#include "Button.h"

class Menu
{
public:
	// Load all functions for Menu
	virtual void load();
	void makeDrawn();
	void remove();
	void draw();
	void update();
	int click();
	bool isDrawn();

protected:
	// Dont even ask (02/06/2023)
	ofSoundPlayer pop;
	ofTrueTypeFont text;
	bool drawn;
	vector<Button> buttons;
};
