#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"

using namespace std;

int main (int argc, char** argv) {

    Game Game;

    Game.generateTerrain();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Mice Wars", 100, 100, Game.win_width, Game.win_height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
    }

    if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG) {
        cout << "IMG_Init Error: " << IMG_GetError() << endl;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    //SDL_Delay(2000);

    SDL_Surface* img = IMG_Load("img/mouse.jpg");
    if (img == nullptr) {
        cout << "IMG_LoadError: " << IMG_GetError() << endl;
        return -1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}