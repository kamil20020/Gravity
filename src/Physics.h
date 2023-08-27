#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "CosmosBody.h"

using namespace sf;
using namespace std;

class Physics{

	const double G = 6.67e-11;

	const double PI = 3.141592;

	public:

	void gravityForce(shared_ptr <CosmosBody> &first, shared_ptr <CosmosBody>& second);

	void velocity(shared_ptr <CosmosBody>& first);

	int addition(shared_ptr <CosmosBody>& first, shared_ptr <CosmosBody> &second);
	void whatDoWhenTwoObjectsAreIntersected(shared_ptr <CosmosBody>& first, shared_ptr <CosmosBody>& second);

	void mainLogic(vector <shared_ptr <CosmosBody> >& objects);
};

