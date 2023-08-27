#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class CosmosBody {

    CircleShape shape;

    public:

    long double F = 0, Fx = 0, Fy = 0;
    long double calculateFx = 0, calculateFy = 0;

    long double v = 0, vx = 0, vy = 0;

    long double m;

    CosmosBody(float r, long double m1, Vector2f startVelocities, Vector2f positions, Color color);

    void moving(long double vx1 = 0, long double vy1 = 0);

    FloatRect returnBounds();

    CircleShape &returnShape();

    void update(RenderWindow &window);
};

