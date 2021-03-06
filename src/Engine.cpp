#include <sstream>
#include <SDL_ttf.h>
#include "Engine.h"
#include "Timer.h"

Engine* Engine::m_pInstance = nullptr;

Engine* Engine::Instance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new Engine;
    } // Only allow one instance at time
    return m_pInstance;
}

int Engine::createWindow(int win_width, int win_height) {
    window = SDL_CreateWindow("Mice Wars", 100, 100, win_width, win_height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    return 0;
}

int Engine::createRenderer() {
    //renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        return 1;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    return 0;
}

int Engine::createBackground() {
    background = SDL_CreateRGBSurface(0, win_width, win_height, 32, 0, 0, 0, 0);
    return 0;
}


void Engine::colorPixel(SDL_Surface* surface, int x, int y, Uint32 colour) {
    auto pixel = static_cast<Uint8*>(surface->pixels);
    pixel += (y * surface->pitch) + (x * sizeof(Uint32));
    *((Uint32*) pixel) = colour;
}

int Engine::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return 1;
    }
    return 0;
}

int Engine::initializeImageSystem() {
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        cout << "IMG_Init Error: " << IMG_GetError() << endl;
        return 1;
    }
    return 0;
}

int Engine::initializeAudioSystem() {
    return 0;
}

int Engine::initializeFontTTF() {
    if (TTF_Init() != 0) {
        cout << "TTF_Init Error: " << TTF_GetError() << endl;
        return 1;
    }
    return 0;
}

int Engine::getReady() {
    if ((init()) or
        (createWindow(win_width, win_height)) or
        (createRenderer()) or
        (createBackground()) or
        (initializeImageSystem()) or
        (initializeAudioSystem()) or
        (initializeFontTTF())) {
        cout << "Something went wrong! I'm afraid we're going to crash, soldier!" << endl;
        return 1;
    }
    return 0;
}

SDL_Texture* Engine::makeTexture(const char* img_path) const {
    SDL_Texture* texture = IMG_LoadTexture(renderer, img_path);
    return texture;
}

void Engine::destroy() {
    SDL_DestroyRenderer(Engine::Instance()->renderer);
    SDL_DestroyWindow(Engine::Instance()->window);
}

void Engine::clearRenderer() const {
    SDL_RenderClear(renderer);
}

void Engine::readCursorPosition() {
    SDL_GetMouseState(&cursor_pos.first, &cursor_pos.second);
}

void Engine::setWindowTitle() const {
    std::stringstream window_title;
    window_title << "Frametime: " << Timer::Instance()->getTimeFromLastDelta() << " Cursor " << cursor_pos.first <<
    " " << cursor_pos.second;
    window_title.str().c_str();
    SDL_SetWindowTitle(window, window_title.str().c_str());
}

int Engine::setWindowWidth(int width) {
    if (renderer == nullptr) {
        win_width = width;
        return 0;
    }
    cerr << "[ERROR] Can't modify resolution settings while gameplay. Change it in the config.ini file" << endl;
    return -1;
}

int Engine::setWindowHeight(int height) {
    if (renderer == nullptr) {
        win_height = height;
        return 0;
    }
    cerr << "[ERROR] Can't modify resolution settings while gameplay. Change it in the config.ini file" << endl;
    return -1;
}
