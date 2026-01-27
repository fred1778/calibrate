//
// Created by Fred Clamp-Gray on 26/01/2026.
//
#include "events.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include "SDL3/SDL_time.h"

using json = nlohmann::json;
using namespace std;

void EventManager::loadEvents() {

    string myText;
    ifstream f;
    f.open("/Users/fredcg/Desktop/Dev/calibrate_contain/calibrate/colo.json");
    json data = json::parse(f);

    for (int i=0; i<data.size(); i++) {
        cout<<data[i].at("id")<<endl;

        SDL_DateTime eventDT;
        eventDT.day = data[i].at("day");
        eventDT.month = data[i].at("month");
        eventDT.year = data[i].at("year");
        eventDT.hour = data[i].at("hour");
        eventDT.minute = data[i].at("minute");

        Event newEvent = {
            data[i].at("id"),
            eventDT,
            data[i].at("title"),
            data[i].at("notes"),
            data[i].at("loc"),
        };
        this->events.push_back(newEvent);
    }

    f.close();
}
