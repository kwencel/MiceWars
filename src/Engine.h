#ifndef MICEWARS_ENGINE_H
#define MICEWARS_ENGINE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

// Singleton design pattern
class Engine {
private:
    int win_width;
    int win_height;
    int init();
    int createWindow(int win_width, int win_height);
    int createRenderer();
    int initializeImageSystem();
    int initializeAudioSystem();
    Engine() { };
    Engine(Engine const&) { };
    Engine& operator=(Engine const&) { };
    static Engine* m_pInstance;

public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* background = nullptr;
    SDL_Texture* background_texture = nullptr;

    int getReady(int win_width, int win_height);
    void clearRenderer();
    void destroy();
    SDL_Texture* makeTexture(const char *img_path);
    static Engine* Instance();

    int createBackground();

    void colorPixel(SDL_Surface *surface, int x, int y, Uint32 color);
};


#endif //MICEWARS_ENGINE_H
