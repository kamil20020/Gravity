#pragma once

#include "SimulationCreator.h"
#include "Menu.h"

class StandardSimulationCreator: public SimulationCreator, public Menu{

	shared_ptr <Simulation> simulation;

	Vector2f windowSize; //
	int maxColorIndex; 
	Vector2f massRange; //
	Vector2f radiusRange; //
	Vector2f maxSpeed; //
	Vector2f maxPositions; //
	map <int, Color> colors;
	int howMuchObjectsCreate; //

	public:

	StandardSimulationCreator(shared_ptr <RenderWindow> window, shared_ptr <Simulation> simulation, Vector2f windowSize);

	void setStartParametersToSimulation();

	float radiusValidation();
	float massValidation();
	Vector2f speedValidation();
	Vector2f positionValidation();

	void createSimulation();
};

