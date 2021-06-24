#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <map>

#include "State.h"

#include "DropDownMenu.h"
#include "PutBox.h"

using namespace sf;
using namespace std;

class Menu: public State{

	public:

	map <string, shared_ptr <Button> > buttons;
	map <string, shared_ptr <DropDownMenu> > dropDownMenus;
	map <string, shared_ptr <PutBox> > putBoxes;
	shared_ptr <Button> clickedButton;
	string clickedButtonName;

	Menu(shared_ptr <RenderWindow> window, Vector2f windowSizeForThisState);

	void inEvents(Event event);
	void outEvents();

	void startState();

	void addButton(Vector2f position, Vector2f size, string fontSource, string message);
	void addDropDownMenu(Vector2f position, Vector2f size, string title);

	bool checkDoClickedButton();
	shared_ptr <Button>& returnClickedButton() { return clickedButton; }
	string returnClickedButtonName() { return clickedButtonName; }
	void resetClickedButton();

	map <string, shared_ptr <DropDownMenu> >& returnDropDownMenus() { return dropDownMenus; }

	void update();
};

