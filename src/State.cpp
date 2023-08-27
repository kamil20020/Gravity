#include "State.h"

State::State(shared_ptr <RenderWindow> window1, Vector2f windowSizeForThisState1):
	window(window1), windowSizeForThisState(windowSizeForThisState1) {

	doClosedState = false;
}

void State::startState() {

	if (Vector2f(window->getSize()) != windowSizeForThisState)
		window->setSize(Vector2u(windowSizeForThisState));

	doClosedState = false;
}

void State::closeState() {

	doClosedState = true;
}
