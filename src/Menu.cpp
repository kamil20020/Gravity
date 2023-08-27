#include "Menu.h"

Menu::Menu(shared_ptr <RenderWindow> window, Vector2f windowSizeForThisState):
	State(window, windowSizeForThisState){

	view.setSize(windowSizeForThisState);
	view.setCenter(windowSizeForThisState.x / 2, windowSizeForThisState.y / 2);

	clickedButtonName = "none";
	clickedButton = nullptr;
}

bool Menu::checkDoClickedButton() {

	if (clickedButtonName != "none")
		return true;

	return false;
}

void Menu::startState() {

	State::startState();

	window->setSize(Vector2u(windowSizeForThisState));

	view.setSize(windowSizeForThisState);
	view.setCenter(windowSizeForThisState.x / 2, windowSizeForThisState.y / 2);
}

void Menu::inEvents(Event event) {

	map <string, shared_ptr <Button> >::iterator itB = buttons.begin();

	for (; itB != buttons.end(); itB++) {

		itB->second->events(event);

		if (itB->second->isButtonPressed()) {

			clickedButton = itB->second;
			clickedButtonName = itB->first;
		}
	}

	map <string, shared_ptr <DropDownMenu> >::iterator itD = dropDownMenus.begin();

	for (; itD != dropDownMenus.end(); itD++) {

		itD->second->events(event);

		shared_ptr <Button> clickedButtonPointer = itD->second->getClickedButton();

		if (clickedButtonPointer != nullptr) {

			clickedButton = clickedButtonPointer;
			clickedButtonName = itD->second->returnClickedButtonName();

			cout << clickedButtonName << endl;
		}
	}

	map <string, shared_ptr <PutBox> >::iterator itPB = putBoxes.begin();

	for (; itPB != putBoxes.end(); itPB++)
		itPB->second->inEvents(event);

	if (event.type == Event::KeyPressed) {

		if (event.key.code == Keyboard::Escape) {

			closeState();
		}
	}
}

void Menu::addButton(Vector2f position, Vector2f size, string fontSource, string message) {

	buttons[message] = make_shared <Button>(window, position, size, fontSource, message);
}

void Menu::addDropDownMenu(Vector2f position, Vector2f size, string title) {

	dropDownMenus[title] = make_shared <DropDownMenu>(window, position, size, title);
}

void Menu::resetClickedButton() {

	clickedButton->resetButton();
	clickedButton = nullptr;
	clickedButtonName = "none";
}

void Menu::outEvents() {


}

void Menu::update() {

	window->setView(view);
	
	map <string, shared_ptr <Button> >::iterator itB = buttons.begin();

	for (; itB != buttons.end(); itB++)
		itB->second->update(window);

	map <string, shared_ptr <DropDownMenu> >::iterator itD = dropDownMenus.begin();

	for (; itD != dropDownMenus.end(); itD++)
		itD->second->update(window);

	map <string, shared_ptr <PutBox> >::iterator itPB = putBoxes.begin();

	for (; itPB != putBoxes.end(); itPB++)
		itPB->second->update();
}
