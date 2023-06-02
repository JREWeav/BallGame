#include "Menu.h"

void Menu::load()
{
	// oh my god (02/06/2023)
	drawn = true;
}

void Menu::makeDrawn()
{
	drawn = true;
}

void Menu::remove()
{
	drawn = false;
}

void Menu::update()
{
	// Test all buttons in menu
	if (drawn)
	{
		for (size_t i = 0; i < buttons.size(); i++)
		{
			buttons[i].update();
		}
	}
}

bool Menu::isDrawn()
{
	// Test if menu is drawn
	return drawn;
}

void Menu::draw()
{
	// Draw all buttons
	if (drawn)
	{
		for (size_t i = 0; i < buttons.size(); i++)
		{
			buttons[i].draw();
		}
	}
}

int Menu::click()
{
	// If any button is active return the value of button
	if (drawn)
	{
		for (size_t i = 0; i < buttons.size(); i++)
		{
			if (buttons[i].isActive())
			{
				pop.play();
				return buttons[i].getValue();
			}
		}
	}
}