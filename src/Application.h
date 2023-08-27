#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

using namespace sf;
using namespace std;

#include "SimulationCreator.h"
#include "StatesManager.h"

class Application{

	shared_ptr <RenderWindow> window;
	shared_ptr <Event> event;

	shared_ptr <SimulationCreator> simulationCreator;
	shared_ptr <Simulation> simulation;
	shared_ptr <StatesManager> statesManager;

	public:

	Application();

	void inEvents();
	void outEvents();

	void update();

	void loop();
};

