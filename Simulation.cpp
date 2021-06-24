#include "Simulation.h"

Simulation::Simulation(shared_ptr <RenderWindow> window, Vector2f windowSizeForThisState): 
    State(window, windowSizeForThisState) {

    physics = make_shared <Physics>();
}

void Simulation::addCosmoBody(float r, float m1, Vector2f startVelocities, Vector2f positions, Color color) {

    objects.push_back(make_shared <CosmosBody>(r, m1, startVelocities, positions, color));
}

void Simulation::resetSimulation() {

    objects.clear();
}

void Simulation::inEvents(Event event) {

    if (event.type == Event::KeyPressed) {

        if (event.key.code == Keyboard::Escape) {

            closeState();
        }
    }
}

void Simulation::outEvents() {

}

void Simulation::update() {

    physics->mainLogic(objects);

    for (unsigned int i = 0; i < objects.size(); i++) {

        window->draw(objects[i]->returnShape());
    }
}
