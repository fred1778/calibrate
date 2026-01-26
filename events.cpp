//
// Created by Fred Clamp-Gray on 26/01/2026.
//
#include "events.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


using namespace std;


void EventManager::loadEvents() {

    string myText;
    ifstream f("odl.txt");
    f.open("odl.txt");
    while (getline (f, myText)) {
        // Output the text from the file
        cout << myText;
    }
    json data = json::parse(f);


    f.close();
}
