#pragma once

#include "ofMain.h"

class ColoredBall
{
public:
	ColoredBall();
	~ColoredBall();

	void initialise(int x, int y, unsigned char colNum);
	void update();
	void draw();
	void dropBack(int amount);
	void moveForward(int amount);

	int reportX();
	int reportY();
	bool isMoving();
	unsigned char reportColor();

	bool marked;
	bool emptyBehind;
private:
	int xPos;
	int yPos;
	
	int pos1Y;
	int pos2Y;
	float percentToNew;

	bool moving;

	int colorNum;
	ofColor color;
	ofImage bubImg;
};

