#include "Application.h"

#include "StandardSimulationCreator.h"
#include "GoodSimulationCreator.h"

Application::Application() {

    window = make_shared <RenderWindow>();
    window->create(VideoMode(1200, 1000), "CosmosSimulation");
    window->setFramerateLimit(60);

    event = make_shared <Event>();

    statesManager = make_shared <StatesManager>(window);
}

void Application::inEvents() {

    if (event->type == Event::Closed) {

        window->close();
    }

    statesManager->inEvents(*event);
}

void Application::outEvents() {

    statesManager->outEvents();
}

void Application::update() {

    statesManager->update(window);
}

void Application::loop() {

    while (window->isOpen()) {

        while (window->pollEvent(*event)) {

            inEvents();
        }

        window->clear();

        outEvents();

        update();

        if (statesManager->checkDoAllStatesEnded())
            break;

        window->display();

    }
}
