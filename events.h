//
// Created by Fred Clamp-Gray on 26/01/2026.
//
#ifndef CALIBRATE_EVENTS_H
#define CALIBRATE_EVENTS_H
#include <nlohmann/json.hpp>
#include <vector>

#include "SDL3/SDL_time.h"
using json = nlohmann::json;

using namespace std;


struct Event {

    string id;
    SDL_DateTime eventDateTime;
    string title;
    string notes;
    string location;

    string lineDisplay;
};


class EventManager {
    public:
    void loadEvents();
    vector<Event> events;

    EventManager(){}


};



#endif //CALIBRATE_EVENTS_H