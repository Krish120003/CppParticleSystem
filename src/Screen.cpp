#include "Screen.hpp"
#include <iostream>

PixelAccessScreen::PixelAccessScreen() : window(NULL), renderer(NULL), texture(NULL), buffer(NULL){};

bool PixelAccessScreen::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return false;
    }
    window = SDL_CreateWindow("Particle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_Quit();
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    buffer = new Uint32[WINDOW_WIDTH * WINDOW_HEIGHT];
    temp_buffer = new Uint32[WINDOW_WIDTH * WINDOW_HEIGHT];

    memset(buffer, 0, WINDOW_HEIGHT * WINDOW_WIDTH * sizeof(Uint32));
    memset(temp_buffer, 0, WINDOW_HEIGHT * WINDOW_WIDTH * sizeof(Uint32));

    update();

    return true;
};

void PixelAccessScreen::update()
{
    SDL_UpdateTexture(texture, NULL, buffer, WINDOW_WIDTH * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

bool PixelAccessScreen::processEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return true;
        }
    }
    return false;
};

void PixelAccessScreen::close()
{
    delete[] buffer;
    delete[] temp_buffer;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

void PixelAccessScreen::setPixel(int x, int y, int r, int g, int b)
{
    // std::cout << "Settings pixel at X: " << x << " Y: " << y << " to RGB(" << r << "," << g << "," << b << ")" << std::endl;
    if (x < 0 or y < 0 or x > WINDOW_WIDTH or y > WINDOW_HEIGHT)
    {
        return;
    }
    Uint32 color = 0;

    color += r;
    color <<= 8;
    color += g;
    color <<= 8;
    color += b;
    color <<= 8;
    color += 0xff;

    buffer[(y * WINDOW_WIDTH) + x] = color;
}

void PixelAccessScreen::clear()
{
    memset(buffer, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(Uint32));
}

void PixelAccessScreen::fade()
{
    float fade = 0.98;
    for (int i = 0; i < WINDOW_WIDTH; i++)
    {
        for (int j = 0; j < WINDOW_HEIGHT; j++)
        {
            Uint32 temp_color = buffer[(WINDOW_WIDTH * j) + i];
            int red = temp_color >> 24;
            int green = (temp_color >> 16) - (temp_color >> 24 << 8);
            int blue = (temp_color >> 8) - (temp_color >> 16 << 8);
            setPixel(i, j, red * fade, green * fade, blue * fade);
        }
    }
}

void PixelAccessScreen::boxBlur()
{
    Uint32 *temp = buffer;
    buffer = temp_buffer;
    temp_buffer = temp;

    for (int i = 0; i < WINDOW_WIDTH; i++)
    {
        for (int j = 0; j < WINDOW_HEIGHT; j++)
        {
            int red_sum = 0;
            int green_sum = 0;
            int blue_sum = 0;

            double count = 0.2;
            for (int offsetX = -2; offsetX < 2; offsetX++)
            {
                for (int offsetY = -2; offsetY < 2; offsetY++)
                {
                    int currentX = i + offsetX;
                    int currentY = j + offsetY;
                    if (currentX < WINDOW_WIDTH and currentX >= 0 and currentY < WINDOW_HEIGHT and currentY >= 0)
                    {
                        Uint32 temp_color = temp_buffer[(WINDOW_WIDTH * currentY) + currentX];
                        red_sum += temp_color >> 24;
                        green_sum += (temp_color >> 16) - (temp_color >> 24 << 8);
                        blue_sum += (temp_color >> 8) - (temp_color >> 16 << 8);
                        count++;
                    }
                }
            }
            setPixel(i,
                     j,
                     red_sum / count,
                     green_sum / count,
                     blue_sum / count);
        }
    }
}