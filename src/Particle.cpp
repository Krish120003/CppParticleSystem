#include "Particle.hpp"
#include <stdlib.h>
#include <math.h>

Particle::Particle()
{
    x = 0;
    y = 0;

    direction = 2 * M_PI * rand() / (double)RAND_MAX;
    speed = (0.05 * rand() / (double)RAND_MAX);
    speed *= speed;
    speed += 0.00001;
}

Particle::~Particle()
{
}

void Particle::update(int interval)
{
    double x_speed = speed * cos(direction) * rand() / RAND_MAX;
    double y_speed = speed * sin(direction) * rand() / RAND_MAX;

    x += x_speed * interval;
    y += y_speed * interval;

    direction += interval * 0.0005;
}
