//
// Created by Fred Clamp-Gray on 26/01/2026.
//
#ifndef CALIBRATE_EVENTS_H
#define CALIBRATE_EVENTS_H
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;

using namespace std;


struct Event {

    string id;
    string date;
    string time;
    string title;
    string notes;
};


class EventManager {
    public:
    void loadEvents();
    vector<Event> events;

    EventManager(){}


};



#endif //CALIBRATE_EVENTS_H