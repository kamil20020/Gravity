#include "CosmosBody.h"

CosmosBody::CosmosBody(float r, long double m1, Vector2f startVelocities, Vector2f positions, Color color): m(m1){

	shape.setRadius(r);
	shape.setPosition(positions);
	shape.setFillColor(color);

	vx = startVelocities.x;
	vy = startVelocities.y;
}

FloatRect CosmosBody::returnBounds() {

	return shape.getGlobalBounds();
}

CircleShape &CosmosBody::returnShape() {

	return shape;
}

void CosmosBody::moving(long double vx1, long double vy1) {

	Vector2f toPut(vx, vy);

	if (vx1 != 0)
		toPut.x = vx1;

	if (vy1 != 0)
		toPut.y = vy1;

	shape.move(toPut);
}

void CosmosBody::update(RenderWindow& window) {

	window.draw(shape);
}
