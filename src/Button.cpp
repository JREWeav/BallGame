#include "Button.h"

void Button::create(int x, int y, int width, int height, int value, string text)
{
	// Loads all global variables based on the input into create
	xPos = x;
	yPos = y;
	bWidth = width;
	bHeight = height;
	bText = text;
	bValue = value;
	font.load("Pridi.ttf", 32);
	boundBox = font.getStringBoundingBox(text, 0, 0);
	active = false;
}

void Button::update()
{
	// tests mouse position to set outline color
	if (ofGetMouseX() > xPos && ofGetMouseX() < xPos + bWidth && ofGetMouseY() > yPos && ofGetMouseY() < yPos + bHeight)
	{
		outlineColor.set(128, 0, 0);
		active = true;
	}
	else
	{
		outlineColor.set(205, 133, 63);
		active = false;
	}
}

int Button::getValue()
{
	// Outputs value set at load
	return bValue;
}

bool Button::isActive()
{
	// Returns if mouse is active
	return active;
}

void Button::draw()
{
	// Draws Button
	ofSetColor(outlineColor);
	ofRectRounded(xPos, yPos, bWidth, bHeight, 10);
	ofSetColor(255);
	ofRectRounded(xPos + 10, yPos + 10, bWidth - 20, bHeight - 20, 10);
	ofSetColor(outlineColor);
	font.drawString(bText, xPos + ((bWidth - boundBox.width) / 2), yPos + (bHeight / 2) + (boundBox.height / 2));
}