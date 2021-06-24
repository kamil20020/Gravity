#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <map>

using namespace sf;
using namespace std;

class PutBox{

	enum putBoxState { withoutActivity = 0, buttonPressed};

	RectangleShape field;
	RectangleShape showRenctangle;

	string actualValue;
	bool doUseNegatives;

	Text putedText;
	Font putedTextFont;

	Text infoText;
	Font infoTextFont;

	shared_ptr <RenderWindow> window;

	int actualState;

	public:

	PutBox(shared_ptr <RenderWindow> window, string name, Vector2f position, Vector2f size, string fontSource, float startValue,
		bool useNegatives);

	float returnValueInFloat();

	void putValue(float value);
	void addValue(string value);

	void updateTextPosition();
	void updateShowRectanglePosition();

	void inEvents(Event event);
	void outEvents();

	void update();
};

