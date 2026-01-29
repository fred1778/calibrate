//
// Created by Fred Clamp-Gray on 28/01/2026.
//

#ifndef CALIBRATE_EVENTMAKER_H
#define CALIBRATE_EVENTMAKER_H
#include <iostream>
#include <ostream>
#include <string>

#include "events.h"
using namespace std;


class EventMaker {

    Event event;
    void parseEvent(string input);

    public:
    EventMaker(string input) {

        cout<<input<<endl;
        parseEvent(input);

    };

};


#endif //CALIBRATE_EVENTMAKER_H