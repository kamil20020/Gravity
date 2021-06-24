#include "GoodSimulationCreator.h"

GoodSimulationCreator::GoodSimulationCreator(shared_ptr <Simulation> simulation1, Vector2f windowSize): 
	SimulationCreator(simulation1, windowSize) {

	if (simulation1->returnObjects().size() > 0) {

		//for (int i = 0; i < simulation1->returnObjects().size(); i++)
			//simulation1->returnObjects().erase(simulation1->returnObjects().begin());
	}

	simulation1->addCosmoBody(20, 2e13, Vector2f(0, 0), Vector2f(620, 470), Color::Yellow);

	simulation1->addCosmoBody(10, 100, Vector2f(0, -2), Vector2f(820, 670), Color::Green);
	simulation1->addCosmoBody(10, 100, Vector2f(0, 3), Vector2f(520, 370), Color::Cyan);
}
