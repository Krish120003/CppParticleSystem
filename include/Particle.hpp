#pragma once

struct Particle
{
    double x;
    double y;

    double direction;
    double speed;

public:
    Particle();
    virtual ~Particle();
    void update(int interval);
};