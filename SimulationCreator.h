#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <map>

using namespace sf;
using namespace std;

#include "Simulation.h"

class SimulationCreator{

	public:

	SimulationCreator(shared_ptr <Simulation> simulation, Vector2f windowSize);
};

