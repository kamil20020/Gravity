#include "StandardSimulationCreator.h"

StandardSimulationCreator::StandardSimulationCreator(shared_ptr <RenderWindow> window, shared_ptr <Simulation> simulation1, 
    Vector2f windowSize): SimulationCreator(simulation1, windowSize), Menu(window, windowSize), simulation(simulation1) {

    colors[0] = Color::Yellow;
    colors[1] = Color::Green;
    colors[2] = Color::Cyan;

    maxColorIndex = 2;

    maxPositions.x = 1200;
    maxPositions.y = 900;

    putBoxes["WindowSizeX"] = make_shared <PutBox>(window, "Rozmiar okna w OX", Vector2f(100, 50), Vector2f(80, 80), "OpenSans-Regular.ttf",
        1200, true);
    putBoxes["WindowSizeY"] = make_shared <PutBox>(window, "Rozmiar okna w OY", Vector2f(500, 50), Vector2f(80, 80), "OpenSans-Regular.ttf",
        900, true);

    putBoxes["MinMass"] = make_shared <PutBox>(window, "Minimalna masa", Vector2f(100, 200), Vector2f(80, 80), "OpenSans-Regular.ttf",
        1e11, true);
    putBoxes["MaxMass"] = make_shared <PutBox>(window, "Maksymalna masa", Vector2f(500, 200), Vector2f(80, 80), "OpenSans-Regular.ttf",
        1e13, true);

    putBoxes["MinR"] = make_shared <PutBox>(window, "Minimalny promien", Vector2f(100, 350), Vector2f(80, 80), "OpenSans-Regular.ttf",
        5, true);
    putBoxes["MaxR"] = make_shared <PutBox>(window, "Maksymalny promien", Vector2f(500, 350), Vector2f(80, 80), "OpenSans-Regular.ttf",
        15, true);

    putBoxes["MaxVx"] = make_shared <PutBox>(window, "Maksymalna predkosc w OX", Vector2f(100, 500), Vector2f(80, 80), "OpenSans-Regular.ttf",
        5, true);
    putBoxes["MaxVy"] = make_shared <PutBox>(window, "Maksymalna predkosc w OY", Vector2f(500, 500), Vector2f(80, 80), "OpenSans-Regular.ttf",
        5, true);

    putBoxes["HowMuchObjects"] = make_shared <PutBox>(window, "Ile stworzyc obiektow", Vector2f(400, 650), Vector2f(80, 80), "OpenSans-Regular.ttf",
        10, true);

    Vector2f buttonSize(150, 75);

    addButton(Vector2f(window->getSize().x/2 - buttonSize.x / 2, 750), buttonSize, "OpenSans-Regular.ttf", "Start");
}

void StandardSimulationCreator::setStartParametersToSimulation() {

    howMuchObjectsCreate = putBoxes["HowMuchObjects"]->returnValueInFloat();
    radiusRange.x = putBoxes["MinR"]->returnValueInFloat();
    radiusRange.y = putBoxes["MaxR"]->returnValueInFloat();
    massRange.x = putBoxes["MinMass"]->returnValueInFloat();
    massRange.y = putBoxes["MaxMass"]->returnValueInFloat();
    maxSpeed.x = putBoxes["MaxVx"]->returnValueInFloat();
    maxSpeed.y = putBoxes["MaxVy"]->returnValueInFloat();
    windowSize.x = putBoxes["WindowSizeX"]->returnValueInFloat();
    windowSize.y = putBoxes["WindowSizeY"]->returnValueInFloat();
}

float StandardSimulationCreator::radiusValidation() {

    float putR;

    if (radiusRange.x == 0 && radiusRange.y == 0)
        putR = 5;
    else {

        if (radiusRange.x == radiusRange.y)
            putR = radiusRange.x;
        else
            putR = rand() % int(radiusRange.y - radiusRange.x) + radiusRange.x;
    }

    return putR;
}

float StandardSimulationCreator::massValidation() {

    double putM;

    if (massRange.x == 0 && massRange.y == 0)
        putM = 1;
    else {

        if (massRange.x == massRange.y)
            putM = massRange.x;
        else
            putM = rand() % int(massRange.y - massRange.x) + massRange.x;
    }

    return putM;
}

Vector2f StandardSimulationCreator::speedValidation() {

    Vector2f putV;

    if (maxSpeed.x == 0)
        putV.x = 0;
    else
        putV.x = float(rand() % int(maxSpeed.x * 2)) - maxSpeed.x;

    if (maxSpeed.y == 0)
        putV.y = 0;
    else
        putV.y = float(rand() % int(maxSpeed.y * 2)) - maxSpeed.y;

    return putV;
}

Vector2f StandardSimulationCreator::positionValidation() {

    Vector2f putPosition;

    if (maxPositions.x == 0)
        putPosition.x = 0;
    else
        putPosition.x = rand() % int(maxPositions.x);

    if (maxPositions.y == 0)
        putPosition.y = 0;
    else
        putPosition.y = rand() % int(maxPositions.y);

    if (putPosition.x + radiusRange.y * 2 > maxPositions.x)
        putPosition.x = maxPositions.x - radiusRange.y * 2;
    else if (putPosition.x - radiusRange.y * 2 < 0)
        putPosition.x = maxPositions.x + radiusRange.y * 2;

    if (putPosition.y + radiusRange.y * 2 > maxPositions.y)
        putPosition.y = maxPositions.y - radiusRange.y * 2;
    else if (putPosition.y - radiusRange.y * 2 < 0)
        putPosition.y = maxPositions.y + radiusRange.y * 2;

    return putPosition;
}

void StandardSimulationCreator::createSimulation() {

    setStartParametersToSimulation();

    simulation->addCosmoBody(20, 2e13, Vector2f(0, 0), Vector2f(620, 470), Color::Yellow);

    for (int i = 0; i < howMuchObjectsCreate; i++) {

        double putR = radiusValidation();

        double putM = massValidation();

        Vector2f putV = speedValidation();

        Vector2f putPosition = positionValidation();

        simulation->addCosmoBody(putR, putM, putV, putPosition, colors[rand() % maxColorIndex]);

        /*simulation->addCosmoBody(putR, putM, Vector2f(putVx, putVy),
            Vector2f(rand() % int(maxPositions.x), rand() % int(maxPositions.y)), colors[rand() % maxColorIndex]);*/
    }
}
