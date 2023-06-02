#pragma once
#include "Menu.h"

class PauseMenu : public Menu
{
public:
	void load() override;

private:
	Button menuButton;
	Button resumeButton;
};

