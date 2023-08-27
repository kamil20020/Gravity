#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <stack>

#include "State.h"

using namespace sf;
using namespace std;

class StatesManager{

	shared_ptr <RenderWindow> window;

	bool doAllStatesEnded;

	public:

	map <string, shared_ptr <State> > states;

	stack <string> statesSequence;
	string actualState;

	StatesManager(shared_ptr <RenderWindow> window);

	void inEvents(Event event);
	void outEvents();

	bool logicForButtons();
	void exit();

	void createGoodSimulation();

	void createButtonsForMenu();
	void createDropDownMenusForMenu();

	void createButtonsForSimulationOptions();
	void createDropDownMenusForSimulationOption();

	bool checkDoAllStatesEnded() { return doAllStatesEnded; }

	void update(shared_ptr <RenderWindow> window);
};

