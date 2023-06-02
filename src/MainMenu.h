#pragma once
#include "ofMain.h"
#include "Button.h"
#include "Menu.h"

class MainMenu : public Menu
{
public:
	void load() override;

private:
	Button easyButton;
	Button mediumButton;
	Button hardButton;
};

