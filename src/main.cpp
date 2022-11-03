#include <iostream>
#include <SDL2/SDL.h>
#include "Screen.hpp"
#include "Swarm.hpp"

using namespace std;

int main()
{

    PixelAccessScreen screen;

    if (screen.init() == false)
    {
        cout << "SDL Init Failed" << endl;
    }

    Swarm swarm;
    int ticks;
    // Main Loop
    while (1)
    {
        ticks = SDL_GetTicks();
        swarm.update(ticks);
        // screen.clear();
        screen.fade();
        Particle *pparticles = swarm.getParticles();

        int r = ((sin(ticks * 0.0001) + 1) / 2) * 255;
        int g = ((sin((3457 + ticks) * 0.0001) + 1) / 2) * 255;
        int b = ((sin((18000 + ticks) * 0.0001) + 1) / 2) * 255;

        // int r = 255;
        // int g = 255;
        // int b = 255;

        for (int i = 0; i < Swarm::NPARTICLES; i++)
        {
            Particle particle = pparticles[i];
            int x = (particle.x + 1) * PixelAccessScreen::WINDOW_WIDTH / 2;
            int y = (particle.y + 1) * PixelAccessScreen::WINDOW_HEIGHT / 2;

            screen.setPixel(x, y, r, g, b);
        }
        // screen.boxBlur();
        screen.update();
        if (screen.processEvents())
        {
            break;
        }
    }

    screen.close();

    return 0;
}