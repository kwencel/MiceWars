#ifndef MICEWARS_ENGINE_H
#define MICEWARS_ENGINE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using std::cout;
using std::endl;

// Singleton design pattern
class Engine {
private:
    static Engine* m_pInstance;
    int win_width;
    int win_height;
    std::pair<int,int> cursor_pos;

    int init();
    int createWindow(int win_width, int win_height);
    int createRenderer();
    int initializeImageSystem();
    int initializeAudioSystem();
    Engine() { };

public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* background = nullptr;
    SDL_Texture* background_texture = nullptr;

    int getReady(int win_width, int win_height);
    void readCursorPosition();
    void setCursorPosition(int x, int y);
    int createBackground();
    void colorPixel(SDL_Surface *surface, int x, int y, Uint32 color);
    SDL_Texture* makeTexture(const char *img_path);
    void clearRenderer();
    void destroy();
    static Engine* Instance();
    std::pair<int,int> getCursorPosition() { return cursor_pos; };

    void setWindowTitle();
};


#endif //MICEWARS_ENGINE_H
