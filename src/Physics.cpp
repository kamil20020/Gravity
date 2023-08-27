#include <math.h>

#include "Physics.h"

void Physics::gravityForce(shared_ptr <CosmosBody> &first, shared_ptr <CosmosBody>& second) {

	float dx, dy, r;

	long double m1, m2;

	m1 = first->m;
	m2 = second->m;

	dx = second->returnBounds().left + second->returnBounds().width / 2 - first->returnBounds().left - first->returnBounds().width / 2;
	dy = second->returnBounds().top + second->returnBounds().height / 2 - first->returnBounds().top - first->returnBounds().height / 2;

	r = sqrt(pow(dx,2) + pow(dy,2));

	first->F = G * m1 * m2 / (pow(r, 2));

	//Fy = F*sina / sina = dy/r
	//Fx = F*cosa / cosa = dx/r

	first->Fx = first->F * dx / r;
	first->Fy = first->F * dy / r;

	first->calculateFx += first->Fx;
	first->calculateFy += first->Fy;
}

void Physics::velocity(shared_ptr <CosmosBody> &object) {

	object->vx = object->vx + object->Fx / object->m;
	object->vy = object->vy + object->Fy / object->m;
}

void Physics::whatDoWhenTwoObjectsAreIntersected(shared_ptr <CosmosBody>& first, shared_ptr <CosmosBody>& second) {

	first->m = first->m + second->m;

	float firstField = PI * pow(first->returnShape().getRadius(), 2);
	float secondField = PI * pow(second->returnShape().getRadius(), 2);
	float additionedFields = firstField + secondField;
	float radiusToPut = sqrt((firstField + secondField) / PI);
	float diffrenceBetweenAdditionedRadiusToFirstRadius = radiusToPut - first->returnShape().getRadius();

	first->returnShape().setRadius(radiusToPut);
	first->moving(-diffrenceBetweenAdditionedRadiusToFirstRadius,
		-diffrenceBetweenAdditionedRadiusToFirstRadius);
}

int Physics::addition(shared_ptr <CosmosBody>& first, shared_ptr <CosmosBody>& second) {

	if (first->returnBounds().intersects(second->returnBounds())) {

		if (first->m >= second->m) {

			first->m = first->m + second->m;

			whatDoWhenTwoObjectsAreIntersected(first, second);

			return 1;
		}
		else
			return 3;
	}

	return 2;
}

void Physics::mainLogic(vector <shared_ptr <CosmosBody> > &objects) {

	for (unsigned int i = 0; i < objects.size(); i++) {

		objects[i]->calculateFx = 0;
		objects[i]->calculateFy = 0;

		for (unsigned int j = 0; j < objects.size(); j++) {

			if (objects[i] != objects[j]) {

				int additionFunctionCheck = addition(objects[i], objects[j]);

				if (additionFunctionCheck == 1) {

					objects.erase(objects.begin() + j);

					if (j > 0)
						j--;

					if (i > 0)
						i--;
				}
				else{

					gravityForce(objects[i], objects[j]);
				}
			}
		}

		if (objects.size() > 1) {

			objects[i]->Fx = objects[i]->calculateFx;
			objects[i]->Fy = objects[i]->calculateFy;

			velocity(objects[i]);
		}

		//cout << "before: " << objects[i]->vx << "\t" << objects[i]->vy << "\t\t";

		objects[i]->moving();

		//cout << "after: " << objects[i]->vx << "\t" << objects[i]->vy << endl << endl;
	}
}
