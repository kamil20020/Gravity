#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

using namespace std;
using namespace sf;

class State{

	protected:

	shared_ptr <RenderWindow> window;
	Vector2f windowSizeForThisState;
	View view;

	bool doClosedState;

	public:

	State(shared_ptr <RenderWindow> window, Vector2f windowSizeForThisState);
	
	virtual void startState();
	virtual void closeState();
	virtual bool doStateShouldBeClosed() { return false; }
	bool doIsClosedState() { return doClosedState; }
	
	virtual void inEvents(Event event) {};
	virtual void outEvents() {};

	virtual void update() = 0;
};

