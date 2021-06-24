#include <iostream>

#include "Button.h"

Button::Button(shared_ptr <RenderWindow> window1, Vector2f position, Vector2f size, string fontSource, string message):
    window(window1){

    rect.setSize(size);
    rect.setPosition(position);
    rect.setFillColor(Color::White);

    pushFont(fontSource, message);

    actualState = withoutActivity;
}

template <class T>
void Button::drawShape(shared_ptr <RenderWindow> window, T graphic) {

    window->draw(graphic);
}

void Button::pushFont(string fontSource, string message) {

    font.loadFromFile(fontSource);

    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(22);
    text.setFillColor(Color::Black);
    text.setPosition(rect.getPosition().x + rect.getSize().x / 2 - text.getGlobalBounds().width / 2 - 1, 
        rect.getPosition().y + rect.getSize().y / 2 - text.getGlobalBounds().height / 2 - 5);
}

void Button::changePosition(Vector2f position) {

    rect.setPosition(position);
    text.setPosition(rect.getPosition().x + rect.getSize().x / 2 - text.getGlobalBounds().width / 2 - 1,
        rect.getPosition().y + rect.getSize().y / 2 - text.getGlobalBounds().height / 2 - 5);
}

string Button::getText() {

    return text.getString();
}

void Button::update(shared_ptr <RenderWindow> window) {

    drawShape(window, rect);
    drawShape(window, text);
}

void Button::events(Event event) {

    Vector2f worldPos = window->mapPixelToCoords(Mouse::getPosition(*window));

    if (rect.getGlobalBounds().contains(worldPos) == true) {

        actualState = buttonHovered;

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {

            actualState = buttonPressed;

            //cout << getText() << endl;
        }
    }
    else {

        actualState = withoutActivity;
    }
}

FloatRect Button::getGlobalBounds() {

    return rect.getGlobalBounds();
}

void Button::resetButton() {

    actualState = withoutActivity;
}

bool Button::isButtonPressed() {

    if (actualState == buttonPressed) {

        return true;
    }

    return false;
}

bool Button::isButtonHovered() {

    if (actualState == buttonHovered) {

        return true;
    }

    return false;
}
