#pragma once

#include "SimulationCreator.h"

class GoodSimulationCreator: public SimulationCreator{

	public:

	GoodSimulationCreator(shared_ptr <Simulation> simulation, Vector2f windowSize);
};

