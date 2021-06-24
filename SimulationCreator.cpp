#include "SimulationCreator.h"

SimulationCreator::SimulationCreator(shared_ptr <Simulation> simulation1, Vector2f windowSize) {

	if (simulation1->returnObjects().size() > 0)
		simulation1->returnObjects().clear();
}
