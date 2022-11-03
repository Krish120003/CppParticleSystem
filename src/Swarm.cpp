#include "Swarm.hpp"
#include <algorithm>

Swarm::Swarm()
{
    particles = new Particle[NPARTICLES];
    last_time = 0;
}

Swarm::~Swarm()
{
    delete[] particles;
}

void Swarm::update(int elapsed)
{
    for (int i = 0; i < NPARTICLES; i++)
    {
        particles[i].update(std::max(elapsed - last_time, 0));
    }
    last_time = elapsed;
}