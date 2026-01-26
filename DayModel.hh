
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <iostream>
#include <tuple>
#include <time.h>
#include <vector>



#ifndef DAYMODEL_H
#define DAYMODEL_H




#define LEFT 1073741904
#define UP 1073741906
#define RIGHT 1073741903
#define DOWN 1073741905

#define DAYERROR -1
#define DAYSECONDS 86400
#define NODATE 0
#define NOSTR ""


constexpr int windowWidth{ 800 };
constexpr int windowHeight{ 600 };
constexpr int sqSize{50};
constexpr int x_count{10};
constexpr int y_count{10};



using namespace std;

// this stuff should really come from OS-level locale info
const string daynames[7] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};
const string months[12] = {
    "January",
    "February",
    "March",
        "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

const vector<tuple<int, int, int, string>> sig_dates = {
    make_tuple(17,3,2026, "birthday")
};
enum DayType{
    WORKDAY,
    WEEKEND,
    BANKHOL,
    SIGNIFICANT
};



class Day {



    tuple<int, int, int, string> getSigDate() {
        for (auto sd: sig_dates) {
            if (dateCompare(sd)) {
                return sd;
            }
        }
        return make_tuple(NODATE, NODATE, NODATE, NOSTR);
    }


    bool dateCompare(tuple<int, int, int, string> s_date) {
        return date.day == get<0>(s_date) && date.month == get<1>(s_date) && date.year == get<2>(s_date);
    }



    public:
     SDL_DateTime date;
     DayType dtype;
    string display;

     Day(SDL_DateTime sdlday){

         date = sdlday;

         display = daynames[date.day_of_week] + "    " + to_string(date.day) + " " + months[date.month - 1] + " " + to_string(date.year);


        int DoW = SDL_GetDayOfWeek(sdlday.year, sdlday.month, sdlday.day);
         SDL_Log("DoW: %d", DoW);
        if(DoW != DAYERROR){

            if (get<0>(getSigDate()) != NODATE) {
                dtype = SIGNIFICANT;
            } else {
                dtype = (DoW > 0 && DoW < 6) ? DayType::WORKDAY : DayType::WEEKEND;
            }
            SDL_Log("day type %d", dtype);
            // specific date  BH allocation here - not sure if this can be wrangled from OS 
        }
     }

    

};



static vector<Day> generateFromDate(SDL_DateTime start, int span){

        // using ctime would make this easier....
        vector<Day> days;
        Sint64 end_t, start_t;
        SDL_Log("gen start");
        SDL_DateTimeToTime(&start, &start_t);
        // work in time_t not SDL as seconds better than nanoseconds for calcs
        time_t root = SDL_NS_TO_SECONDS(start_t);


        for(int i = 1; i <= span; i++){
            SDL_Log("gen %d", i);
            SDL_Time newTime = SDL_SECONDS_TO_NS(root + (i * DAYSECONDS));
            SDL_DateTime newDay;
             SDL_TimeToDateTime(newTime, &newDay, false);
            Day nextDay = Day(newDay);
            days.push_back(nextDay);
        }
    return days;
    }
#endif