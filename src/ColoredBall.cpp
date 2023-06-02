#include "ColoredBall.h"

ColoredBall::ColoredBall()
{
	// WHY IS THIS EMPTY
}

ColoredBall::~ColoredBall()
{
}

void ColoredBall::initialise(int x, int y, unsigned char colNum)
{
	// Clearly I had no idea what a constructor function was. I'm sorry. (02/06/2023)
	xPos = x;
	yPos = y;
	colorNum = colNum;

	// Set color based off of number

	if (colorNum == 0)
	{
		color.set(255, 0, 0);
	}
	else if (colorNum == 1)
	{
		color.set(0, 255, 0);
	}
	else if (colorNum == 2)
	{
		color.set(0, 0, 255);
	}
	else if (colorNum == 3)
	{
		color.set(255, 0, 255);
	}
	else if (colorNum == 4)
	{
		color.set(255, 255, 0);
	}
	else if (colorNum == 5)
	{
		color.set(0, 255, 255);
	}
	else if (colorNum == 6)
	{
		color.set(128, 0, 255);
	}
	else if (colorNum == 7)
	{
		color.set(0, 128, 255);
	}
	// Define Variables
	marked = false;
	moving = false;
	emptyBehind = false;
	// NAHHHHH (02/06/2023)
	bubImg.load("bubble.png");

	percentToNew = 100;

	pos1Y = yPos;
	pos2Y = yPos;
}

void ColoredBall::dropBack(int amount)
{
	// Move balls back 1 spot
	pos1Y = yPos;
	pos2Y = yPos - amount;
	percentToNew = 0;
}

void ColoredBall::moveForward(int amount)
{
	// Move ball 1 spot forward
	pos2Y = yPos + amount;
	percentToNew = 100;
}

int ColoredBall::reportX()
{
	// Report X Position
	return xPos;
}

int ColoredBall::reportY()
{
	// Report Y Position
	return yPos;
}

bool ColoredBall::isMoving()
{
	// See if ball is moving
	return moving;
}

unsigned char ColoredBall::reportColor()
{
	// Report number
	return colorNum;
}

void ColoredBall::update()
{
	// Allow ball to move with fluid motion by increasing percent to new by 5 making it move 5 percent closer to the next position each tick
	if (floor(percentToNew) != 100)
	{
		yPos = ((100 - percentToNew) / 100) * pos1Y + ((percentToNew) / 100) * pos2Y;
		percentToNew += 5;
		moving = true;
	}
	else
	{
		moving = false;
		yPos = pos2Y;
	}
}

void ColoredBall::draw()
{
	// Draw Ball
	ofSetColor(color);
	ofFill();
	ofDrawCircle(xPos, yPos, 25);
	ofSetColor(255);
	bubImg.draw(xPos - 26, yPos - 26);
}