#pragma once

#include "ofMain.h"
#include "ColoredBall.h"

class Shooter
{
public:
	Shooter();
	~Shooter();
	void setPosition(int x, int y, int cols);
	void update();
	void draw();
	void shoot();
	void collide();
	void swapDir();
	void newColor();
	
	int reportX();
	int reportY();
	unsigned char reportColour();
	bool isShooting();

private:
	bool hasShot;

	int pos1X;
	int pos1Y;
	int pos2X;
	int pos2Y;

	int lineX;
	int lineY;
	int colours;

	int xPos;
	int yPos;
	
	int shootHomeX;
	int shootHomeY;
	float percent;

	unsigned char shotColor;

	ColoredBall shotBall;
};

