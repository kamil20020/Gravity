#include <sstream>

#include "PutBox.h"

PutBox::PutBox(shared_ptr <RenderWindow> window1, string name, Vector2f position, Vector2f size, string fontSource, float startValue,
	bool useNegatives): window(window1) {

	infoTextFont.loadFromFile(fontSource);
	infoText.setFont(infoTextFont);
	infoText.setString(name);
	infoText.setCharacterSize(22);
	infoText.setPosition(position);
	infoText.setFillColor(Color::White);

	field.setSize(size);
	field.setPosition(position.x + infoText.getGlobalBounds().width + 10, position.y - size.y/2 + infoText.getGlobalBounds().height/2 - 5);

	putedTextFont.loadFromFile(fontSource);
	putedText.setFont(putedTextFont);
	putValue(startValue);
	putedText.setCharacterSize(22);
	putedText.setFillColor(Color::Black);
	updateTextPosition();

	showRenctangle.setSize(Vector2f(2, 22));
	showRenctangle.setFillColor(Color::Black);
	updateShowRectanglePosition();

	actualState = withoutActivity;
}

void PutBox::updateTextPosition() {

	putedText.setPosition(field.getPosition().x + field.getSize().x / 2 - putedText.getGlobalBounds().width / 2 - 1,
		field.getPosition().y + field.getSize().y / 2 - putedText.getGlobalBounds().height / 2 - 5);
}

void PutBox::updateShowRectanglePosition() {

	showRenctangle.setPosition(Vector2f(putedText.getGlobalBounds().left + putedText.getGlobalBounds().width - showRenctangle.getSize().x / 2 + 2,
		putedText.getGlobalBounds().top - 3));
}
	
void PutBox::putValue(float value) {

	ostringstream ss;
	ss << value;
	string putString(ss.str());

	actualValue = putString;

	putedText.setString(putString);
}

void PutBox::addValue(string value) {

	actualValue = actualValue + value;

	putedText.setString(actualValue);
}

float PutBox::returnValueInFloat() {

	return atof(actualValue.c_str());
}

void PutBox::inEvents(Event event) {

	Vector2f worldPos = window->mapPixelToCoords(Mouse::getPosition(*window));

	if (field.getGlobalBounds().contains(worldPos) == true) {

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {

			if (actualState == withoutActivity)
				actualState = buttonPressed;
		}
	}
	else if(event.mouseButton.button == Mouse::Left) {

		if(actualState == buttonPressed)
			actualState = withoutActivity;
	}

	if (event.type == sf::Event::KeyPressed) {

		if (actualState == buttonPressed) {

			if (event.key.code == Keyboard::Num0)
				addValue(to_string(0));
			else if (event.key.code == Keyboard::Num1)
				addValue(to_string(1));
			else if (event.key.code == Keyboard::Num2)
				addValue(to_string(2));
			else if (event.key.code == Keyboard::Num3)
				addValue(to_string(3));
			else if (event.key.code == Keyboard::Num4)
				addValue(to_string(4));
			else if (event.key.code == Keyboard::Num5)
				addValue(to_string(5));
			else if (event.key.code == Keyboard::Num6)
				addValue(to_string(6));
			else if (event.key.code == Keyboard::Num7)
				addValue(to_string(7));
			else if (event.key.code == Keyboard::Num8)
				addValue(to_string(8));
			else if (event.key.code == Keyboard::Num9)
				addValue(to_string(9));
			else if (event.key.code == Keyboard::E) {

				if (actualValue.length() == 0)
					actualValue = 'e';
				else if (actualValue.length() == 1) {

					if (actualValue[0] != 'e')
						actualValue = actualValue + 'e';
				}
				else if (actualValue.length() == 2) {

					if (actualValue[0] == '-' && actualValue[1] != 'e')
						actualValue = actualValue + 'e';
				}
				else if (actualValue.length() == 3) {

					if(actualValue[0] == '-' && actualValue[1] != 'e' && actualValue[2] != 'e')
						actualValue = actualValue + 'e';
				}
			}
			else if (event.key.code == Keyboard::BackSpace) {

				if (actualValue.length() > 0) {

					actualValue.pop_back();
					putedText.setString(actualValue);
				}
			}
		}
	}
}

void PutBox::outEvents() {


}

void PutBox::update() {

	window->draw(infoText);		
	window->draw(field);
	window->draw(putedText);

	if (actualState == buttonPressed) {

		putedText.setString(actualValue);

		updateTextPosition();

		updateShowRectanglePosition();

		window->draw(showRenctangle);
	}
	else {

		
	}
	
}
