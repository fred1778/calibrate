#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <iostream>
#include <tuple>
#include <time.h>
#include "config.h"

using namespace std;


class Interface {
    public:
    SDL_Window* window;
    SDL_Surface* screenSurface;
    bool isRunning;
    SDL_Renderer* rend;

    Interface(){
        window = nullptr;
        isRunning = false;

       window = SDL_CreateWindow("Calibrate v0.1", windowWidth, windowHeight, 0);
      rend = SDL_CreateRenderer(window, nullptr); 
       
      if(!SDL_Init(SDL_INIT_VIDEO)){
            SDL_Log("init erro");
            throw std::runtime_error(std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
        }

        SDL_SetRenderLogicalPresentation(rend, windowWidth, windowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        isRunning = true;
    }

    void interfaceLoop(){

        while(isRunning){
        SDL_Event event;
         const bool *keys = SDL_GetKeyboardState(nullptr); 

         // uses SDL Scancodes, map to arrow pad via config.h
         
             while(SDL_PollEvent(&event)){
                if(event.type == SDL_EVENT_QUIT){
                    stop();
                } else if (event.type == SDL_EVENT_KEY_DOWN) {
                    switch (event.key.key) {
                        case LEFT:
                            SDL_Log("Left arrow key pressed");
                            break;
                        case RIGHT:
                            SDL_Log("Right arrow key pressed");
                            break;
                        case UP:
                            SDL_Log("Up arrow key pressed");
                            break;
                        case DOWN:
                            SDL_Log("Down arrow key pressed");
                            break;
                        default:
                            break;
                    }
                }
               }
             }
            }

    void stop(){
        isRunning = false;
        SDL_Quit();
    }
};




int main(int argc, char* argv[]){
    
    Interface interface = Interface();
    interface.interfaceLoop();
    interface.stop();
    return 0;
}
