#pragma once
#include <SDL.h>

class App;

class Controller
{
public:
    Controller(App &app);

    SDL_bool Run(SDL_Event event);
private:
    App &app;
    
    SDL_bool inSampleRect = SDL_FALSE;

    void HandleMouseDrag(SDL_Event e);
};