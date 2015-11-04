#include "Engine.h"

Engine* Engine::m_pInstance = nullptr;

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
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        return 1;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    return 0;
}

int Engine::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return 1;
    }
    return 0;
}

int Engine::initializeImageSystem() {
//    if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG) {
//        cout << "IMG_Init Error: " << IMG_GetError() << endl;
//        return 1;
//    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        cout << "IMG_Init Error: " << IMG_GetError() << endl;
        return 1;
    }
    return 0;
}

int Engine::initializeAudioSystem() {
    return 0;
}

int Engine::getReady(int win_width, int win_height) {
    if ((init()) or
        (createWindow(win_width, win_height)) or
        (createRenderer()) or
        (initializeImageSystem()) or
        (initializeAudioSystem())) {
        cout << "Something went wrong! I'm afraid we're going to crash, soldier!" << endl;
        return 1;
    }
    return 0;
}

SDL_Texture* Engine::makeTexture(const char* img_path) {
//    SDL_Surface* img = IMG_Load(img_path);
//    if (img == nullptr) {
//        cout << "IMG_LoadError: " << IMG_GetError() << endl;
//        return nullptr;
//    }
//    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
//    SDL_FreeSurface(img);
//    return texture;
    SDL_Texture* texture = IMG_LoadTexture(renderer, img_path);
    return texture;
}

Engine* Engine::Instance() {
    if (!m_pInstance) {
        m_pInstance = new Engine;
    } // Only allow one instance at time
}

void Engine::destroy() {
    SDL_DestroyRenderer(Engine::Instance()->renderer);
    SDL_DestroyWindow(Engine::Instance()->window);
}

void Engine::clearRenderer() {
    SDL_RenderClear(renderer);
}
