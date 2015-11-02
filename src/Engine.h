#ifndef MICEWARS_ENGINE_H
#define MICEWARS_ENGINE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

// Singleton design pattern
class Engine {
private:
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

    int getReady(int win_width, int win_height);
    void clearRenderer();
    void destroy();
    SDL_Texture* makeTexture(const char *img_path);
    static Engine* Instance();

};


#endif //MICEWARS_ENGINE_H
