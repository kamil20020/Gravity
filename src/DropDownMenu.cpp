#include "DropDownMenu.h"

DropDownMenu::DropDownMenu(shared_ptr <RenderWindow> window1, Vector2f positions, Vector2f sizes, string title):
    window(window1){

    activeButton = make_shared <Button>(window, positions, sizes, "OpenSans-Regular.ttf", title);

    topDiffrence = positions.y;

    actualState = nonActive;

    clickedButton = nullptr;
    hoveredButton = nullptr;
}

void DropDownMenu::addButton(string title, string display) {

    FloatRect activeButtonGlobalBounds = activeButton->getGlobalBounds();
    
    string displayPut = title;

    if(display != "same")
        displayPut = display;

    buttons[title] = make_shared <Button>(window, Vector2f(activeButtonGlobalBounds.left,
        topDiffrence + activeButtonGlobalBounds.height), Vector2f(activeButtonGlobalBounds.width, 
            activeButtonGlobalBounds.height), "OpenSans-Regular.ttf", displayPut);

    topDiffrence = topDiffrence + activeButtonGlobalBounds.height;
}

void DropDownMenu::changePosition(Vector2f position) {

    FloatRect startPosition = activeButton->getGlobalBounds();

    Vector2f put(position);

    activeButton->changePosition(put);

    map <string, shared_ptr <Button>>::iterator it;

    for (it = buttons.begin(); it != buttons.end(); it++) {

        put.y = put.y + startPosition.height;

        it->second->changePosition(put);
    }
}

map <string, shared_ptr <Button>> & DropDownMenu::returnButtons(){

    return buttons;
}

shared_ptr <Button>& DropDownMenu::returnHoveredButton() {

    return hoveredButton;
}

bool DropDownMenu::doDropDownMenuOpened() {

    if (actualState == firstButtonActived) {

        return true;
    }

    return false;
}

string DropDownMenu::returnClickedButtonName() {

    return clickedButtonName;
}

void DropDownMenu::events(Event event){

    if (activeButton->isButtonHovered()) {

        hoveredButton = activeButton;
    }
    else {

        hoveredButton = nullptr;
    }

    if (activeButton->isButtonPressed()) {

        actualState = firstButtonActived;

        activeButton->resetButton();
    }
    else {

        activeButton->events(event);
    }

    if (actualState == firstButtonActived) {

        if (!activeButton->isButtonPressed()) {

            map <string, shared_ptr <Button>>::iterator it;

            bool checkDoHovered = false;
            bool checkDoClicked = false;

            for (it = buttons.begin(); it != buttons.end(); it++) {

                it->second->events(event);

                if (it->second->isButtonPressed()) {

                    clickedButton = it->second;

                    clickedButtonName = it->first;

                    checkDoClicked = true;

                    break;
                }
                
                if (it->second->isButtonHovered()) {

                    hoveredButton = it->second;

                    checkDoHovered = true;
                }
            }

            if (!checkDoClicked) {

                clickedButton = nullptr;

                clickedButtonName = "none";
            }

            if (!checkDoHovered)
                hoveredButton = nullptr;
        }
        else {

            actualState = nonActive;

            activeButton->resetButton();
        }
    }
}

void DropDownMenu::resetClickedButton() {

    clickedButton->resetButton();

    clickedButton = nullptr;

    clickedButtonName = "none";
}

shared_ptr <Button>& DropDownMenu::getClickedButton() {

    return clickedButton;
}

void DropDownMenu::close() {

    clickedButton = nullptr;

    actualState = nonActive;
}

void DropDownMenu::update(shared_ptr <RenderWindow> window){

    activeButton->update(window);

    if (actualState == firstButtonActived) {

        map <string, shared_ptr <Button>>::iterator it;

        for (it = buttons.begin(); it != buttons.end(); it++) {

            it->second->update(window);
        }
    }
}


