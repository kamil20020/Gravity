
#include "Application.h"

int main() {

	srand(time(0));

	Application application;
	//application.createStandardSimulation();

	application.loop();

	return 0;
}