#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <iostream>
#include <tuple>
#include "DayModel.hh"
#include <vector>

using namespace std;


class Interface {
    public:
    SDL_Window* window;
    vector<vector<Day>> calFramework;
    tuple<int, int> selectedDay = make_tuple(0,0);
    int dayCount = 100;

    bool isRunning;
    SDL_Renderer* rend;
    vector<Day> days;

    Interface(){

        window = nullptr;
        isRunning = false;

       window = SDL_CreateWindow("Calibrate v0.1", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
      rend = SDL_CreateRenderer(window, nullptr);
        SDL_Time today;
        SDL_DateTime today_dt;
        SDL_DateTime end_dt;


         SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);

        SDL_GetCurrentTime(&today);
        SDL_TimeToDateTime(today, &today_dt, false);
        SDL_Time end = SDL_SECONDS_TO_NS((SDL_NS_TO_SECONDS(today) + (100 * DAYSECONDS)));
        SDL_TimeToDateTime(end, &end_dt, false);
        days = generateFromDate(today_dt, 100);

        for (auto day : days) {
            SDL_Log("-> %d", day.date.day);
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
            int tally = 0;

            for (int row = 0; row < y_count; row++) {
                for (int col = 0; col < x_count; col++) {
                    if (tally < dayCount) {
                        SDL_FRect rect;
                        rect.x = (col * sqSize) + 50;
                        rect.y = (row * sqSize) + 50;
                        rect.w = sqSize;
                        rect.h = sqSize;

                        int red = 255;
                        int green = 255;
                        int blue = 255;

                        Day d = days[tally];
                        SDL_SetRenderDrawColor(rend, red, green,  blue, SDL_ALPHA_OPAQUE);



                        if (selectedDay == make_tuple(row, col)) {

                            SDL_RenderFillRect(rend, &rect);
                            string dayStr = d.display;
                            SDL_SetRenderDrawColor(rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
                            SDL_RenderDebugText(rend, 300, 10, dayStr.c_str());

                        } else if (d.dtype == WEEKEND) {
                            SDL_SetRenderDrawColor(rend, 0, 0,  255, 70);

                            SDL_RenderFillRect(rend, &rect);
                        } else if (d.dtype == SIGNIFICANT){
                            SDL_SetRenderDrawColor(rend, 255, 153,  0, 70);

                            SDL_RenderFillRect(rend, &rect);

                            } else {
                                SDL_SetRenderDrawColor(rend, red, green,  blue, SDL_ALPHA_OPAQUE);


                                SDL_RenderRect(rend, &rect);
                        }

                        // day specific render text



                        tally++;
                    }
                }
            }


        // text
        int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
        SDL_SetRenderDrawColor(rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDebugText(rend, 10, 10, "CALIBRATE 2026");

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

                    int current_x = get<0>(selectedDay);
                    int current_y = get<1>(selectedDay);



                    switch (event.key.key) {
                        case LEFT:
                            SDL_Log("X: %d  Y: %d", current_x, current_y);

                            if (!(current_x == 0 && current_y == 0)) {
                                if (current_y == 0) {
                                    // wrap back
                                    SDL_Log("Left arrow wrap");
                                    selectedDay = make_tuple(current_x-1, y_count-1);
                                } else {
                                    selectedDay = make_tuple(current_x,current_y - 1);
                                }
                            }
                            break;
                        case RIGHT:
                            // need to standardise 'x' and 'y' uses
                            if (!(current_x == x_count-1 && current_y == y_count-1)) {
                                if (current_y == y_count-1) {

                                } else {
                                    selectedDay = make_tuple(current_x,current_y + 1);
                                }
                            }

                            break;
                        case UP:
                            if (current_x > 0) {
                                selectedDay = make_tuple(current_x -1,current_y);
                            }
                            break;
                        case DOWN:
                            if (current_x < x_count-1) {
                                selectedDay = make_tuple(current_x + 1,current_y);
                            }

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
    interface.interfaceLoop();
    interface.stop();
    return 0;
}
