#include "PauseMenu.h"

void PauseMenu::load()
{
	// Jesus Christ, I'm sorry. (02/06/2023)

	// Setup Pause Menu

	pop.load("pop.flac");

	resumeButton.create((ofGetWidth() / 2) - 200, 100, 400, 100, 1, "Resume");
	menuButton.create((ofGetWidth() / 2) - 200, 250, 400, 100, 2, "Main Menu");
	buttons.clear();
	buttons.push_back(menuButton);
	buttons.push_back(resumeButton);
}