#ifndef CASALCIUMENTO_BOAT_H
#define CASALCIUMENTO_BOAT_H

#include <iostream>
#include <string>
#include "Person.h"

using namespace std;

class Boat {
public:
    Boat();
    ~Boat();
    bool isSafe();
    string getPlace();
    void setPlace(string place);
    void changeMargin();

private:
    string place;
};


#endif //CASALCIUMENTO_BOAT_H
