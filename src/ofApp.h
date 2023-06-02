#pragma once

#include "ofMain.h"
#include "Shooter.h"
#include "ColoredBall.h"
#include "MainMenu.h"
#include "PauseMenu.h"

class ofApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	// What ???? (02/06/2023)
	void testNear(ColoredBall *&b, vector<ColoredBall *> &bV);
	void cleanupMarked(vector<ColoredBall *> &bV, bool &isRemoving, int &points, ofSoundPlayer sound, int timer);
	void moveBack(ColoredBall *&b, vector<ColoredBall *> &bV, int timer, int lineGap);
	void newLine(vector<ColoredBall *> &bV, int lineGap, int colAmount);
	void startGame(vector<ColoredBall *> &bV, Shooter &sh, int rowGap, int colGap, int &gameScore, int &ballsShot, bool &isRemoving, bool &gameState, unsigned char colAmount);

private:
	Shooter bubbleShooter;
	vector<ColoredBall *> bubbles;

	int score;
	int count;

	int rowDist;
	int colDist;

	bool isRunning;
	bool deleting;

	int ballCount;
	int shootMax;

	ofSoundPlayer pop;
	int colorAmount;
	unsigned char mode;

	ofTrueTypeFont text;

	MainMenu mainMenu;
	PauseMenu pauseMenu;

	bool gameOver;
	bool isPaused;
};
#pragma once
