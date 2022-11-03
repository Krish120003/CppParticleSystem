#pragma once

#include <SDL2/SDL.h>

class PixelAccessScreen
{
public:
    const static int WINDOW_WIDTH = 800;
    const static int WINDOW_HEIGHT = 800;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Uint32 *buffer;
    Uint32 *temp_buffer;

public:
    PixelAccessScreen();
    bool init();
    bool processEvents();
    void close();
    void update();
    void setPixel(int x, int y, int r, int g, int b);
    void boxBlur();
    void clear();
    void fade();
};
