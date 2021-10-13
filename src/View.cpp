#include "View.hpp"
#include "App.hpp"
#include <iostream>

using std::cout, std::endl;

View::View(App &app)
: app(app)
{
    cout << "Constructing View" << endl;

    InitWindowAndRenderer();
    InitTTF();
    InitAudio();
    
    // Setup a sample app icon
    SetupWindowIcon();

    // Setup a sample text header that we can draw later
    SetupHeaderText();

    // Setup a sample image
    SetupTexture();

    // Play an audio file
    PlayAudio();
}


/**
 * Initialise an SDL Window and Renderer
 *
 * This uses SDL_CreateWindowAndRenderer. They can alternatively be created separately. See SDL2 Docs
 */
void View::InitWindowAndRenderer()
{
  if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window, &renderer) != 0) {
    SDL_Log("[Error] Creating Window and Renderer: %s\n", SDL_GetError());
    exit(0);
  } else {
    SDL_Log("Created Window and Renderer %dx%d\n", width, height);
    SDL_SetWindowTitle(window, title);
  }
}

/**
 * Initialise TTF
 */
void View::InitTTF()
{
  TTF_Init();
}

/**
 * Initialise mixer
 */
void View::InitAudio()
{
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
    SDL_Log("[Error] Error Initialising Audio : %s\n", SDL_GetError());
  } else {
    SDL_Log("Audio Initialised\n");
  }
}

/**
 * Setup a sample header text
 */
void View::SetupHeaderText()
{
  // See CMakeLists.txt to see how the resources folder is copied from the root to the bin folder
  font = TTF_OpenFont("resources/OpenSans-Regular.ttf", 18);

  SDL_Surface *textSurface = TTF_RenderText_Blended(font, "Mouse Click and Drag Rect. Press [Escape] to Exit",
                                                    white);
  headerText = SDL_CreateTextureFromSurface(renderer, textSurface);

  headerTextRect.x = width / 2 - textSurface->w / 2;
  headerTextRect.y = 0;
  headerTextRect.w = textSurface->w;
  headerTextRect.h = textSurface->h;

  SDL_FreeSurface(textSurface);

  // The value will probably be misreported as never used in CLion, however I think it should always be set
  textSurface = NULL;
}

/**
 * Setup a sample texture
 */
void View::SetupTexture()
{
  image = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load("resources/floor.png");
  if (loadedSurface == NULL) {
    printf("[Error] Unable to load image : %s\n", SDL_GetError());
    exit(0);
  } else {
    image = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (image == NULL) {
      printf("[Error] Unable to create texture : %s\n", SDL_GetError());
    }

    SDL_FreeSurface(loadedSurface);
  }
}

/**
 * Setup a window app icon
 */
void View::SetupWindowIcon()
{
  SDL_Surface *iconSurface;
  iconSurface = IMG_Load("resources/appicon.jpg");

  // The icon requires the window pointer NOT the renderer
  SDL_SetWindowIcon(window, iconSurface);

  // ...and can now free the appicon surface
  SDL_FreeSurface(iconSurface);
}

/**
 * Play a sample audio file
 */
void View::PlayAudio()
{
  music = Mix_LoadMUS("resources/sound.ogg");
  if (Mix_PlayMusic(music, -1) != 0) {
    printf("[Error] Could not play music : %s", Mix_GetError());
  }
}

void View::Run()
{
    // Blank out the renderer with all black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Note that all rendercopys are order specific.

    // Render the sample texture. We could use a source and/or destination rect to render to
    // but for now we'll just use it as a background
    SDL_RenderCopy(renderer, image, NULL, NULL);

    // Render the sample rectangle
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
    SDL_RenderFillRect(renderer, &sampleRect);

    // Render sample text
    SDL_RenderCopy(renderer, headerText, NULL, &headerTextRect);

    // Present to renderer
    SDL_RenderPresent(renderer);
}

View::~View()
{
    // When we exit the loop clean up and exit SDL
    // Audio
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    // Images
    SDL_DestroyTexture(headerText);
    SDL_DestroyTexture(image);
    // TTF
    TTF_CloseFont(font);
    TTF_Quit();
    // Window
    SDL_DestroyWindow(window);
}