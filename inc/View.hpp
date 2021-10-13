#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class App;

class View
{
public:
    View(App &app);
    ~View();
    
    void Run();
    
    SDL_Rect &GetSampleRect() { return sampleRect; }
private:
    App &app;

    // SDL Window
    SDL_Window *window;

    // SDL Renderer to draw to
    SDL_Renderer *renderer;

    // Our default font
    TTF_Font *font;

    // Easy access to a useful color
    SDL_Color white = {255, 255, 255, 255};

    // Window size
    int width = 640;
    int height = 480;

    const char *title = "Default window title";

    // Our sample header texture and where we're drawing our header to
    SDL_Rect headerTextRect;
    SDL_Texture *headerText;

    // Our sample texture
    SDL_Texture *image;

    // Our sample rectangle that we can drag around the viewport
    SDL_Rect sampleRect = {.x = 10, .y = 10, .w = 100, .h = 100};
    
    // Our sample 'music'
    Mix_Music *music = NULL;
    
    void InitWindowAndRenderer();
    void InitTTF();
    void InitAudio();

    // Setup a sample app icon
    void SetupWindowIcon();

    // Setup a sample text header that we can draw later
    void SetupHeaderText();

    // Setup a sample image
    void SetupTexture();

    // Play an audio file
    void PlayAudio();

};