#ifndef MICEWARS_ENGINE_H
#define MICEWARS_ENGINE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "global_vars.h"

using std::cout;
using std::cerr;
using std::endl;

// Singleton design pattern
class Engine {
private:
    static Engine* m_pInstance;
    int win_width = DEFAULT_WIN_WIDTH;
    int win_height = DEFAULT_WIN_HEIGHT;
    std::pair<int, int> cursor_pos;

    int init();

    int createWindow(int win_width, int win_height);

    int createRenderer();

    int initializeImageSystem();

    int initializeAudioSystem();

    int initializeFontTTF();

    Engine() { cout << "Engine created!" << endl; };

public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* background = nullptr;
    SDL_Texture* background_texture = nullptr;

    int getReady();

    void readCursorPosition();

    int createBackground();

    void colorPixel(SDL_Surface* surface, int x, int y, Uint32 colour);

    SDL_Texture* makeTexture(const char* img_path);

    void clearRenderer();

    void destroy();

    static Engine* Instance();

    std::pair<int, int> getCursorPosition() { return cursor_pos; };

    void setWindowTitle();

    int getWindowWidth() { return win_width; }

    int getWindowHeight() { return win_height; }

    int setWindowWidth(int width);

    int setWindowHeight(int height);
};


#endif //MICEWARS_ENGINE_H