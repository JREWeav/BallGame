#pragma once
#include "ofMain.h"

class Button
{
public:
	void create(int x, int y, int width, int height, int value, string text);
	void draw();
	void update();
	int getValue();
	bool isActive();

private:
	ofTrueTypeFont font;
	bool active;
	int xPos;
	int yPos;
	int bWidth;
	int bHeight;
	int bValue;
	string bText;
	ofColor outlineColor;
	ofRectangle boundBox;
};

