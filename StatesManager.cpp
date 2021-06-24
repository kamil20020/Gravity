#include "StatesManager.h"

#include "Menu.h"

#include "StandardSimulationCreator.h"
#include "GoodSimulationCreator.h"
#include "Simulation.h"

StatesManager::StatesManager(shared_ptr <RenderWindow> window1):
	window(window1){

	doAllStatesEnded = false;

	states["Menu"] = make_shared <Menu>(window, Vector2f(1200, 900));
	createButtonsForMenu();
	createDropDownMenusForMenu();

	states["SimulationOptions"] = make_shared <Menu>(window, Vector2f(1200, 900));
	createButtonsForSimulationOptions();
	createDropDownMenusForSimulationOption();

	states["Simulation"] = make_shared <Simulation>(window, Vector2f(1200, 900));

	actualState = "Menu";
	states[actualState]->startState();

	statesSequence.push(actualState);
}

void StatesManager::createButtonsForSimulationOptions() {

	shared_ptr <Menu> menuCast = dynamic_pointer_cast <Menu> (states["SimulationOptions"]);

	menuCast->addButton(Vector2f(600, 100), Vector2f(200, 100), "OpenSans-Regular.ttf", "Start");
}

void StatesManager::createDropDownMenusForSimulationOption() {

	shared_ptr <Menu> menuCast = dynamic_pointer_cast <Menu> (states["SimulationOptions"]);

	menuCast->addDropDownMenu(Vector2f(600, 500), Vector2f(200, 100), "Simulation type");

	menuCast->returnDropDownMenus()["Simulation type"]->addButton("Standard");
	menuCast->returnDropDownMenus()["Simulation type"]->addButton("Good");
}

void StatesManager::createGoodSimulation() {

	dynamic_pointer_cast <Simulation> (states["Simulation"])->resetSimulation();

	shared_ptr <GoodSimulationCreator> simulationCreator = make_shared <GoodSimulationCreator>(
		dynamic_pointer_cast <Simulation> (states["Simulation"]), Vector2f(1200, 900));
}

void StatesManager::createButtonsForMenu() {

	shared_ptr <Menu> menuCast = dynamic_pointer_cast <Menu> (states["Menu"]);

	menuCast->addButton(Vector2f(600, 100), Vector2f(200, 100), "OpenSans-Regular.ttf", "Simulation");
	menuCast->addButton(Vector2f(600, 300), Vector2f(200, 100), "OpenSans-Regular.ttf", "Exit");
}

void StatesManager::createDropDownMenusForMenu() {

	shared_ptr <Menu> menuCast = dynamic_pointer_cast <Menu> (states["Menu"]);
}

void StatesManager::exit() {

	states[actualState]->closeState();
}

bool StatesManager::logicForButtons() {

	if (actualState == "none")
		return false;

	shared_ptr <Menu> actualStateMenu = dynamic_pointer_cast<Menu> (states[actualState]);

	string clickedButton;

	if (actualStateMenu != nullptr) {

		clickedButton = actualStateMenu->returnClickedButtonName();

		if (clickedButton == "none")
			return false;
	}
	else
		return false;

	if (actualState == "Menu") {

		if (clickedButton == "Exit") {

			exit();
		}
		else if (clickedButton == "Simulation") {


			states[actualState]->closeState();

			actualState = "SimulationOptions";

			if(statesSequence.top() != "SimulationOptions")
				statesSequence.push(actualState);

			states[actualState]->startState();
		}

		dynamic_pointer_cast<Menu> (states["Menu"])->resetClickedButton();
	}
	else if (actualState == "SimulationOptions") {

		if (clickedButton == "Standard") {

			states[actualState]->closeState();

			states["StandardSimulationOptions"] = make_shared <StandardSimulationCreator>(window,
				dynamic_pointer_cast <Simulation> (states["Simulation"]), Vector2f(1200, 900));

			statesSequence.push("StandardSimulationOptions");
			actualState = "StandardSimulationOptions";

			states[actualState]->startState();

		}
		else if (clickedButton == "Good") {

			createGoodSimulation();
		}
		else if (clickedButton == "Start") {

			states[actualState]->closeState();

			actualState = "Simulation";

			statesSequence.push(actualState);

			states[actualState]->startState();
		}

		dynamic_pointer_cast<Menu> (states["SimulationOptions"])->resetClickedButton();
	}
	else if (actualState == "StandardSimulationOptions") {

		if (clickedButton == "Start") {

			dynamic_pointer_cast <Simulation> (states["Simulation"])->resetSimulation();

			dynamic_pointer_cast<StandardSimulationCreator> (states["StandardSimulationOptions"])->createSimulation();

			states[actualState]->closeState();

			actualState = "Simulation";	

			statesSequence.push(actualState);

			states[actualState]->startState();
		}

		dynamic_pointer_cast<Menu> (states["StandardSimulationOptions"])->resetClickedButton();
	}

	return true;
}

void StatesManager::inEvents(Event event) {

	if (!states[actualState]->doIsClosedState()) {

		states[actualState]->inEvents(event);

		logicForButtons();
	}
}

void StatesManager::outEvents() {

	if(!states[actualState]->doIsClosedState())
		states[actualState]->outEvents();
}

void StatesManager::update(shared_ptr <RenderWindow> window) {

	if (states[actualState]->doIsClosedState()){

		statesSequence.pop();

		if (!statesSequence.empty()) {

			actualState = statesSequence.top();

			states[actualState]->startState();
		}
		else
			doAllStatesEnded = true;
		
	}
	else
		states[actualState]->update();
}
