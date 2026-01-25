
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <iostream>
#include <tuple>
#include <time.h>



#ifndef DAYMODEL_H
#define DAYMODEL_H




#define LEFT 1073741904
#define UP 1073741906
#define RIGHT 1073741903
#define DOWN 1073741905

#define DAYERROR -1
#define DAYSECONDS 86400

constexpr int windowWidth{ 800 };
constexpr int windowHeight{ 600 };
constexpr int sqSize{50};
constexpr int x_count{10};
constexpr int y_count{10};

enum DayType{
    WORKDAY,
    WEEKEND,
    BANKHOL,
    SIGNIFICANT
};




class Day {

    public:
    
     SDL_DateTime date;
     //DayType dtype;




     Day(SDL_DateTime day){

        
        this->date = day;
      /*  int DoW = SDL_GetDayOfWeek(day.year, day.month, day.day);
        if(DoW != DAYERROR){
            dtype = (DoW > 0 && DoW < 6) ? DayType::WORKDAY : DayType::WEEKEND;

            // specific date  BH allocation here - not sure if this can be wrangled from OS 
        }*/
     }

    

};




static void generateFromDate(SDL_DateTime start, SDL_DateTime end, Day** collection){

        // using ctime would make this easier....

        Sint64 end_t, start_t;
        long span;

        SDL_Log("gen start");

        SDL_DateTimeToTime(&end, &end_t);
        SDL_DateTimeToTime(&start, &start_t);
        span = end_t - start_t;
    SDL_Log("end_t %lld, start_t %lld", end_t, start_t);
        // work in time_t not SDL as seconds better than nanoseconds for calcs
        time_t root = SDL_NS_TO_SECONDS(start_t);
        time_t span_sec = SDL_NS_TO_SECONDS(span);
         SDL_Log("Span: %ld root: %ld, spanSec: %ld", span, root, span_sec);

        long span_count = span_sec / DAYSECONDS;
             SDL_Log("Span sec %ld Span count: %ld", span_count, span_sec);

        Day* days[span_count];

        for(int i = 1; i <= span_count; i++){
            SDL_Log("DAY CALL");
            SDL_Time newTime = SDL_SECONDS_TO_NS(root + (i * DAYSECONDS));
            SDL_DateTime newDay;
            if(!SDL_TimeToDateTime(newTime, &newDay, false)){
                return;
            }
            Day nextDay = Day(newDay);
            SDL_Log("Day: %d", newDay.day);

            collection[i-1] = &nextDay;
            SDL_Log("update collection");
        }
    }
#endif