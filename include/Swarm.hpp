#pragma once

#include "Particle.hpp"

class Swarm
{
public:
    const static int NPARTICLES = 10000;

private:
    Particle *particles;
    int last_time;

public:
    Swarm();
    ~Swarm();
    Particle *getParticles() { return particles; };
    void update(int elapsed);
};