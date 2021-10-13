#include "Controller.hpp"
#include "App.hpp"
#include <iostream>

using std::cout, std::endl;

Controller::Controller(App &app)
: app(app)
{
    cout << "Constructing Controller" << endl;
}

SDL_bool Controller::Run(SDL_Event event)
{   
    SDL_bool rtrn = SDL_TRUE;
    // Allow quiting with escape key by polling for pending events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        rtrn = SDL_FALSE;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            rtrn = SDL_FALSE;
            break;
          default:
            rtrn = SDL_TRUE;
        }
      }
      HandleMouseDrag(event);
    }
    return rtrn;
}

/**
 * Handles dragging the sample rectangle around. Demonstrates mouse motion events.
 * @param e
 */
void Controller::HandleMouseDrag(SDL_Event e)
{
  SDL_Rect &sampleRect = app.GetView().GetSampleRect();
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    // Point where mouse button down occurs
    SDL_Point p = {.x = e.motion.x, .y = e.motion.y};

    if (SDL_PointInRect(&p, &sampleRect)) {
      inSampleRect = SDL_TRUE;
    }
  }

  if (e.type == SDL_MOUSEBUTTONUP && inSampleRect == SDL_TRUE) {
    inSampleRect = SDL_FALSE;
  }

  if (e.type == SDL_MOUSEMOTION && inSampleRect == SDL_TRUE) {
    sampleRect.x += e.motion.xrel;
    sampleRect.y += e.motion.yrel;
  }
}