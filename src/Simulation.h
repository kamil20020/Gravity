#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "State.h"

#include "CosmosBody.h"
#include "Physics.h"

using namespace sf;
using namespace std;

class Simulation :public State{

	shared_ptr <Physics> physics;

	vector <shared_ptr <CosmosBody> > objects;

	public:

	Simulation(shared_ptr <RenderWindow> window, Vector2f windowSizeForThisState);

	void addCosmoBody(float r, float m1, Vector2f startVelocities, Vector2f positions, Color color);

	vector <shared_ptr <CosmosBody> >& returnObjects() { return objects; }

	void outEvents();
	void inEvents(Event event);

	void resetSimulation();

	void update();
};

