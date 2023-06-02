#include "Shooter.h"

Shooter::Shooter()
{
}

Shooter::~Shooter()
{
}

void Shooter::setPosition(int x, int y, int cols)
{
	// Initialize all variables
	shootHomeX = x;
	shootHomeY = y;
	xPos = x;
	yPos = y;
	pos1X = x;
	pos2X = x;
	pos1Y = y;
	pos2Y = y;
	hasShot = false;
	colours = cols;
	newColor();
}

void Shooter::update()
{
	// Update mouse position and move ball if we have shot
	lineX = ofGetMouseX();
	lineY = min(max(ofGetMouseY(), shootHomeY - 250), shootHomeY - 100);

	if (hasShot)
	{
		percent += 0.03f;
		xPos = (1 - percent) * pos1X + (percent)*pos2X;
		yPos = (1 - percent) * pos1Y + (percent)*pos2Y;
	}

	// Update the ColoredBall
	shotBall.initialise(xPos, yPos, shotColor);
}

int Shooter::reportX()
{
	// Report X Position
	return xPos;
}

int Shooter::reportY()
{
	// Report Y Position
	return yPos;
}

unsigned char Shooter::reportColour()
{
	// Report color
	return shotColor;
}

bool Shooter::isShooting()
{
	// See if ball is moving
	return hasShot;
}

void Shooter::newColor()
{
	// Set new color of ball
	shotColor = ofRandom(colours);
}

void Shooter::draw()
{
	// Draw dotted line
	for (int i = 1; i < 10; i++)
	{
		int totalDistX = lineX - shootHomeX;
		int totalDistY = lineY - shootHomeY;
		int incrementX = totalDistX / 10;
		int incrementY = totalDistY / 10;

		ofCircle((shootHomeX + incrementX * i), (shootHomeY + incrementY * i), 5);
	}

	// Draw Ball
	shotBall.draw();
}

void Shooter::shoot()
{
	// Move ball to end of line and beyond
	percent = 0;
	pos1X = shootHomeX;
	pos1Y = shootHomeY;
	pos2X = lineX;
	pos2Y = lineY;
	hasShot = true;
}

void Shooter::collide()
{
	// Reset to start
	hasShot = false;
	xPos = shootHomeX;
	yPos = shootHomeY;
	newColor();
}

void Shooter::swapDir()
{
	// Reverse direction
	pos1X = xPos;
	pos2X = shootHomeX;
	pos1Y = yPos;
	pos2Y = yPos - (shootHomeY - yPos);
	percent = 0;
}