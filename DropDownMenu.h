#include <vector>
#include <memory>
#include <map>
#include <iostream>

#include "Button.h"

using namespace sf;
using namespace std;

class DropDownMenu {

    enum DropDownMenuStates { nonActive = 0, firstButtonActived, secondButtonActived };

    shared_ptr <RenderWindow> window;

    shared_ptr <Button> activeButton;

    map <string, shared_ptr <Button>> buttons;

    int actualState;

    float topDiffrence;

    shared_ptr <Button> clickedButton;
    string clickedButtonName;

    shared_ptr <Button> hoveredButton;

    public:

    DropDownMenu(shared_ptr <RenderWindow> window,  Vector2f positions, Vector2f sizes, string title);

    void addButton(string title, string display = "same");

    map <string, shared_ptr <Button>> &returnButtons();

    shared_ptr <Button>& getClickedButton();
    string returnClickedButtonName();
    shared_ptr <Button>& returnHoveredButton();

    bool doDropDownMenuOpened();
    void close();

    void resetClickedButton();

    void changePosition(Vector2f position);

    void update(shared_ptr <RenderWindow> window1);

    void events(Event event);
};


