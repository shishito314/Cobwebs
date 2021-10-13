#include "App.hpp"
#include <iostream>

using std::cout, std::endl;

App::App()
: controller(*this), model(*this), view(*this)
{
    cout << "Constructing App" << endl;
    
    // SDL Inits
    InitSDL();

    // Important note. These setup calls require the resources folder to be copied to the
    // bin folder. This is done via the CMakeList.txt file - see the 'file' call towards
    // the end. This means any changes to the resources after the initial project load
    // require the CMake project to be reloaded - in CLion use File -> Reload CMake Project

    // Run our main game loop
    MainLoop();

    exit(0);
}

App::~App()
{
    // SDL
    SDL_Quit();
}


/**
 * Initialise SDL2 and output some useful display info
 */
void App::InitSDL()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    SDL_Log("[Error] SDL Init : %s \n", SDL_GetError());
  } else {
    SDL_Log("SDL INITIALISED\n");
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    SDL_Log("Display mode is %dx%dpx @ %dhz\n", dm.w, dm.h, dm.refresh_rate);
  }
}

/**
 * The main game loop. Continues to loop until Escape or an SDL_Quit event occurs
 */
void App::MainLoop()
{
  SDL_bool loop = SDL_TRUE;
  SDL_Event event;

  while (loop) {
    loop = controller.Run(event);
    view.Run();
    model.Run();

    SDL_Delay(10);
  }
}