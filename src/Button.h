#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

using namespace sf;
using namespace std;

class Button {

    protected:

    enum buttonState { withoutActivity = 0, buttonPressed, buttonHovered };

    shared_ptr <RenderWindow> window;

    RectangleShape rect;

    Font font;

    Text text;

    int actualState;

public:

    Button(shared_ptr <RenderWindow> window, Vector2f position, Vector2f size, string fontSource, string message);

    template <class T>
    void drawShape(shared_ptr <RenderWindow> window, T graphic);

    void pushFont(string fontSource, string message);

    bool isButtonPressed();

    bool isButtonHovered();

    void resetButton();

    FloatRect getGlobalBounds();

    string getText();

    void changePosition(Vector2f position);

    void update(shared_ptr <RenderWindow> window1);

    void events(Event event);
};
