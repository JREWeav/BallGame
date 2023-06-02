#include "MainMenu.h"

void MainMenu::load()
{
	// WHY AM I NOT USING A CONSTRUCTOR FUNCTION HERE????? (02/06/2023)
	// WHY IS POP.FLAC LOADED HERE?????? (02/06/2023)
	// WHY IS POP.FLAC NOT A POINTER?????? (02/06/2023)

	// Setup Main Menu
	pop.load("pop.flac");
	easyButton.create((ofGetWidth() / 2) - 200, 100, 400, 100, 1, "Easiest");
	mediumButton.create((ofGetWidth() / 2) - 200, 250, 400, 100, 2, "Medium");
	hardButton.create((ofGetWidth() / 2) - 200, 400, 400, 100, 3, "Hard");

	buttons.push_back(easyButton);
	buttons.push_back(mediumButton);
	buttons.push_back(hardButton);
}
