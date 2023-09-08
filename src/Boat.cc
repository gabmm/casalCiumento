#include "../include/Person.h"
#include "../include/Boat.h"
#include <iostream>
#include <string>

using namespace std;

Boat::Boat() {
    this->place = "hotel";
}
Boat::~Boat() {
    delete this;
}

string Boat::getPlace() {
    return this->place;
}

void Boat::setPlace(string place) {
    this->place = place;
}

bool Boat::isSafe() {
    if (this->place == "hotel")
        return false;
    else
        return true;
}

void Boat::changeMargin() {
    if (this->place == "hotel")
        this->place = "safe";
    else
        this->place = "hotel";
}
