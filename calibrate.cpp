#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <iostream>
#include <tuple>
#include <time.h>
#include "DayModel.hh"

using namespace std;


class Interface {
    public:
    SDL_Window* window;
    Day* calFramework[y_count][x_count];
    int dayCount = 100;

    bool isRunning;
    SDL_Renderer* rend;

    Interface(){

        window = nullptr;
        isRunning = false;

       window = SDL_CreateWindow("Calibrate v0.1", windowWidth, windowHeight, 0);
      rend = SDL_CreateRenderer(window, nullptr);
        SDL_Time today;
        SDL_DateTime today_dt;
        SDL_DateTime end_dt;

        SDL_Log("----");

        SDL_GetCurrentTime(&today);
        SDL_TimeToDateTime(today, &today_dt, false);
        SDL_Time end = SDL_SECONDS_TO_NS((SDL_NS_TO_SECONDS(today) + (100 * DAYSECONDS)));
        SDL_TimeToDateTime(end, &end_dt, false);

        Day* range[dayCount];
        generateFromDate(today_dt, end_dt, range);
        SDL_Log("gen done");

        int tally = 0;

        for (int row = 0; row < y_count; row++) {
            for (int col = 0; col < x_count; col++) {
                if (tally < dayCount) {
                    calFramework[row][col] = range[tally];
                    SDL_Log("for x %d and y %d, day is %p", col, row, calFramework[row][col] );
                    tally++;
                } else {
                    return;
                }
            }
        }


SDL_Log("screen go");

      if(!SDL_Init(SDL_INIT_VIDEO)){
            SDL_Log("init erro");

            throw std::runtime_error(std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
        }
        SDL_Log("screen on");

        SDL_SetRenderLogicalPresentation(rend, windowWidth, windowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        SDL_Log("screen setrend");
        isRunning = true;
        SDL_Log("Init completed");
    }


    void render(){
        // draw calander grid
        SDL_SetRenderDrawColor(rend, 54, 54, 54, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rend);

            int max_x = 300;
            int max_y = 300;

            // find row and col (x/y pos) - quicker than another nested for
            int tally = 0;
        SDL_SetRenderDrawColor(rend, 54, 0, 0, SDL_ALPHA_OPAQUE);

            for (int row = 0; row < y_count; row++) {
                for (int col = 0; col < x_count; col++) {
                    if (tally < dayCount) {
                        SDL_FRect rect;
                        rect.x = col * sqSize;
                        rect.y = row * sqSize;
                        rect.w = sqSize;
                        rect.h = sqSize;
                        if (!SDL_RenderRect(rend, &rect)) {
                            SDL_Log("SDL_RenderFillRect Error: %s", SDL_GetError());
                        }
                        SDL_Log("sq at %f %f", rect.x, rect.y);
                        tally++;
                    }
                }
            }


    SDL_RenderPresent(rend);

    }


    void interfaceLoop(){
        //SDL_Log("ILOOP FUNC");
        while(isRunning){
          //  SDL_Log("ILOOP RUN");

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
            render();

             }

            }

    void stop(){
        isRunning = false;
        SDL_Quit();
    }
};




int main(int argc, char* argv[]){

    Interface interface = Interface();

    SDL_Log("Intf on");
    interface.interfaceLoop();

    interface.stop();
    return 0;
}
