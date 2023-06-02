#include "ofApp.h"

// I'm convined that openFrameworks is a HORRIBLE way to learn C++ (02/06/2023)

//--------------------------------------------------------------
void ofApp::setup()
{

	cout << "Setup Started" << endl;

	// Set Background
	ofBackground(160, 82, 45);

	// Initialize Variables
	rowDist = 55;
	colDist = 55;
	mode = 0;
	colorAmount = 0;

	isRunning = false;
	gameOver = false;
	isPaused = false;

	// SO I LOAD THEM HERE AND THEN DON'T PASS THEM TO EVERYTHING ELSE????? (02/06/2023)
	// Load Files
	pop.load("pop.flac");
	text.load("Pridi.ttf", 16);

	// Draw Main Menu and Load Menus
	mainMenu.load();
	mainMenu.makeDrawn();
	pauseMenu.load();

	cout << "Setup Complete" << endl;
}

void ofApp::startGame(vector<ColoredBall *> &bV, Shooter &sh, int rowGap, int colGap, int &gameScore, int &ballsShot, bool &isRemoving, bool &gameState, unsigned char colAmount)
{

	// Reset all variables
	gameState = false;
	isRemoving = false;
	gameScore = 0;
	ballsShot = 0;

	// Clear the Balls vector
	bV.clear();

	// Reset shooter position and give it a new color
	sh.setPosition(ofGetWidth() / 2, ofGetHeight() - ofGetHeight() / 8, colAmount);
	sh.newColor();

	// Draw a 20*4 grid of the bubbles
	for (int column = 0; column < 20; column++)
	{
		for (int row = 0; row < 4; row++)
		{
			ColoredBall *b = new ColoredBall;
			b->initialise((column * colGap) + ((ofGetWidth() - 1095) / 2) + 25, (row * rowGap) + 75, ofRandom(colAmount));
			bV.push_back(b);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	// BLEH (02/06/2023)
	// Test if a choice has been made on the Menu
	//  Mode 1 = Easy, Mode 2 = Medium, Mode 3 = Hard
	if (mainMenu.isDrawn())
	{
		if (mode == 1)
		{
			colorAmount = 4;
			shootMax = 4;
			mainMenu.remove();
			startGame(bubbles, bubbleShooter, rowDist, colDist, score, ballCount, deleting, gameOver, colorAmount);
		}
		if (mode == 2)
		{
			colorAmount = 6;
			shootMax = 7;
			mainMenu.remove();
			startGame(bubbles, bubbleShooter, rowDist, colDist, score, ballCount, deleting, gameOver, colorAmount);
		}
		if (mode == 3)
		{
			colorAmount = 8;
			shootMax = 10;
			mainMenu.remove();
			startGame(bubbles, bubbleShooter, rowDist, colDist, score, ballCount, deleting, gameOver, colorAmount);
		}
		else
		{
			mainMenu.update();
		}
	}
	// Update Pause Menu if the game is paused
	else if (isPaused)
	{
		pauseMenu.update();
	}
	// Finally run the game if nothing is stopping
	else if (!mainMenu.isDrawn() && !gameOver && !isPaused)
	{

		// Counter for animation timing
		count += 1;

		// Update the shooter
		bubbleShooter.update();

		// If we have shot run these (Improving performance by not always running these checks)
		if (isRunning)
		{
			// Cleanup bubbles that have been marked by the shot bubble
			cleanupMarked(bubbles, deleting, score, pop, count);
			// See if any of the bubbles have space behind
			for (size_t i = 0; i < bubbles.size(); i++)
			{
				moveBack(bubbles[i], bubbles, count, rowDist);
			}
			// Game over condition
			for (size_t i = 0; i < bubbles.size(); i++)
			{
				if (bubbles[i]->reportY() > rowDist * 9 + 75)
				{
					gameOver = true;
					cout << "Game Over!" << endl;
				}
			}
		}
		else
		{
			// Test to see if we have reached the point where we add a line
			if (ballCount > shootMax)
			{
				newLine(bubbles, rowDist, colorAmount);
				ballCount = 0;
			}
		}

		// Conditions to see if the game is running
		for (size_t i = 0; i < bubbles.size(); i++)
		{

			if (bubbles[i]->isMoving() || bubbleShooter.isShooting() || bubbles[i]->marked)
			{
				isRunning = true;
				break;
			}
			else
			{
				isRunning = false;
			}
		}

		// Update individual bubbles
		for (size_t i = 0; i < bubbles.size(); i++)
		{
			bubbles[i]->update();
		}

		// Collision on sides
		if (bubbleShooter.reportX() < ((ofGetWidth() - 1095) / 2) + 25 || bubbleShooter.reportX() > (ofGetWidth() - (((ofGetWidth() - 1095) / 2) + 25)))
		{
			bubbleShooter.swapDir();
		}

		for (size_t b = 0; b < bubbles.size(); b++)
		{
			// Collision detection
			if (abs(bubbleShooter.reportX() - bubbles[b]->reportX()) < 49 && abs(bubbleShooter.reportY() - bubbles[b]->reportY()) < 49 || bubbleShooter.reportY() < 100)
			{

				int newBallX;
				int newBallY;
				// Find closest spot next to collided area and set X and Y of new bubble
				for (int i = 0; i < 20; i++)
				{
					if (abs(bubbleShooter.reportX() - ((i * 55) + ((ofGetWidth() - 1095) / 2) + 25)) < 27.5f)
					{
						for (int j = 0; j < 12; j++)
						{
							if (abs(bubbleShooter.reportY() - ((j * rowDist) + 75)) < 27.5f)
							{
								newBallX = (i * 55) + ((ofGetWidth() - 1095) / 2) + 25;
								newBallY = (j * rowDist) + 75;
								break;
							}
						}
						break;
					}
				}

				// Push new bubble to vector
				unsigned char newCol = bubbleShooter.reportColour();
				bubbleShooter.collide();
				ColoredBall *b = new ColoredBall;
				b->initialise(newBallX, newBallY, newCol);
				bubbles.push_back(b);
				cout << "New bubble created" << endl;

				// Test if there are matching colours near the newest bubble
				testNear(bubbles[bubbles.size() - 1], bubbles);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::testNear(ColoredBall *&b, vector<ColoredBall *> &bV)
{
	// Mark bubble
	b->marked = true;
	for (size_t i = 0; i < bV.size() - 1; i++)
	{
		if (b->reportColor() == bV[i]->reportColor() && abs(b->reportX() - bV[i]->reportX()) < 60 && abs(b->reportY() - bV[i]->reportY()) < 60 && !bV[i]->marked)
		{
			// Recursion to test newly marked bubble for nearby same colours
			testNear(bV[i], bV);
		}
	}
}

//--------------------------------------------------------------
void ofApp::cleanupMarked(vector<ColoredBall *> &bV, bool &isRemoving, int &points, ofSoundPlayer sound, int timer)
{
	vector<ColoredBall *> tempVec = {};

	int amountMarked = 0;

	// Gather total amount of marked bubbles
	for (size_t i = 0; i < bubbles.size(); i++)
	{
		if (bubbles[i]->marked)
		{
			amountMarked++;
		}
	}

	// Set removing to true if we have a line of 4
	if (amountMarked > 3)
	{
		isRemoving = true;
	}

	// Remove until there are no marked bubbles left and increase score. Using timer to remove one at a time and not all at once for cool pop effect.
	if (isRemoving)
	{
		if (timer % 2 == 0)
		{
			cout << "removing: " + to_string(amountMarked) << endl;
			for (size_t i = 0; i < bV.size(); i++)
			{
				if (bV[i]->marked)
				{
					bV.erase(bV.begin() + i);
					sound.play();
					if (amountMarked > 3)
					{
						points += 100 * (amountMarked - 3);
					}
					amountMarked--;
					if (amountMarked == 0)
					{
						isRemoving = false;
					}
					break;
				}
			}
		}
	}
	// If we dont have more than 3 marked and we arent currently removing we unmark everything
	else
	{
		for (size_t i = 0; i < bV.size(); i++)
		{
			bV[i]->marked = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::moveBack(ColoredBall *&b, vector<ColoredBall *> &bV, int timer, int lineGap)
{

	bool isEmpty = false;
	// Test every bubble to see if it is empty behind
	for (size_t i = 0; i < bV.size(); i++)
	{
		if ((b->reportY() - lineGap) == bV[i]->reportY() && b->reportX() == bV[i]->reportX())
		{
			isEmpty = false;
			break;
		}
		isEmpty = true;
	}
	b->emptyBehind = isEmpty;

	// Move back if it is empty behind and it isn't at the back of the board
	if (b->emptyBehind && b->reportY() > 80 && !b->isMoving())
	{
		b->dropBack(lineGap);
	}
}

//--------------------------------------------------------------
void ofApp::newLine(vector<ColoredBall *> &bV, int lineGap, int colAmount)
{
	// Move all current bubbles one forward
	for (size_t i = 0; i < bV.size(); i++)
	{
		bV[i]->moveForward(lineGap);
	}
	// Make new row at the back
	for (int column = 0; column < 20; column++)
	{
		ColoredBall *b = new ColoredBall;
		b->initialise((column * 55) + ((ofGetWidth() - 1095) / 2) + 25, 75, ofRandom(colAmount));
		bV.push_back(b);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// draw little board
	ofSetColor(139, 69, 19);
	ofDrawRectRounded(((ofGetWidth() - 1095) / 2) - 10, 40, rowDist * 20 + 15, colDist * 10 + 10, 20);

	// Draw either main menu or game
	ofSetColor(255);
	if (mainMenu.isDrawn())
	{
		mainMenu.draw();
	}
	else
	{

		// Draw Game
		text.drawString("Press P to Pause", ((ofGetWidth() - 1095) / 2) + 25, 650);
		text.drawString("Shots Until New Line: " + to_string(shootMax - ballCount + 1), ((ofGetWidth() - 1095) / 2) + 25, 680);
		text.drawString("Score: " + to_string(score), ((ofGetWidth() - 1095) / 2) + 25, 710);
		bubbleShooter.draw();
		for (size_t i = 0; i < bubbles.size(); i++)
		{
			bubbles[i]->draw();
		}

		// Draw Game Over Message
		if (gameOver)
		{
			ofRectangle boundBox1 = text.getStringBoundingBox("Game Over!", 0, 0);
			ofRectangle boundBox2 = text.getStringBoundingBox("Your Score Was: " + to_string(score), 0, 0);
			ofRectangle boundBox3 = text.getStringBoundingBox("Press R to Restart or M to go to menu.", 0, 0);
			ofSetColor(181, 101, 14);
			ofDrawRectRounded((ofGetWidth() / 2) - 225, 370, 450, 150, 20);
			ofSetColor(255);
			text.drawString("Game Over!", (ofGetWidth() - boundBox1.width) / 2, ofGetHeight() / 2);
			text.drawString("Your Score Was: " + to_string(score), (ofGetWidth() - boundBox2.width) / 2, ofGetHeight() / 2 + 50);
			text.drawString("Press R to Restart or M to go to menu.", (ofGetWidth() - boundBox3.width) / 2, ofGetHeight() / 2 + 100);
		}
		// Draw Pausemenu
		else if (isPaused)
		{
			pauseMenu.draw();
		}
	}
	// Draw Framerate
	ofSetColor(255);
	ofDrawBitmapString(("(" + to_string(ofGetFrameRate()) + ")"), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	// Test for different keys to open menus
	if (!mainMenu.isDrawn() && !isPaused)
	{
		// If game is over allow for restart or main menu return
		if (gameOver)
		{
			if (key == 'r')
			{
				startGame(bubbles, bubbleShooter, rowDist, colDist, score, ballCount, deleting, gameOver, colorAmount);
			}
			if (key == 'm')
			{
				mode = 0;
				mainMenu.makeDrawn();
			}
		}
		// Otherwise we can pause the game
		if (!gameOver)
		{
			if (key == 'p')
			{
				isPaused = !isPaused;
				if (isPaused)
				{
					pauseMenu.makeDrawn();
				}
				else
				{
					pauseMenu.remove();
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	// If Main Menu is drawn set Mode to button we click on
	if (mainMenu.isDrawn())
	{
		mode = mainMenu.click();
	}
	// If we are paused perform action based on button pressed
	else if (isPaused)
	{
		if (pauseMenu.click() == 1)
		{
			isPaused = false;
			pauseMenu.remove();
		}
		else if (pauseMenu.click() == 2)
		{
			isPaused = false;
			mode = 0;
			pauseMenu.remove();
			mainMenu.makeDrawn();
		}
	}
	// Otherwise we shoot the ball like normal
	else
	{
		if (!isRunning && !gameOver && !isPaused)
		{
			bubbleShooter.shoot();
			ballCount++;
		}
	}
}
