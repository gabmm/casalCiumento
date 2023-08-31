#include "../include/Person.h"

using namespace std;

Person::Person(char sex) {
    if (sex == 'f')
        this->sex = sex;
    else
        this->sex = 'm';

    this->place = "hotel";
    this->marriedTo = nullptr;
}

Person::~Person() {

}

bool Person::isMale() {
    if (this->sex == 'f')
        return false;
    else
        return true;
}

bool Person::isMarriedTo(Person *p) {
    if (this->marriedTo == p)
        return true;
    else
        return false;
}

bool Person::isSafe() {
    if (this->place == "hotel")
        return false;
    else
        return true;
}

Person *Person::getMarriedTo() {
    return this->marriedTo;
}

void Person::setName(std::string name) {
    this->name = name;
}

string Person::getName() {
    return this->name;
}

char Person::getSex() {
    return this->sex;
}

string Person::getPlace() {
    return this->place;
}

void Person::setMarriedTo(Person *p) {
    this->marriedTo = p;
}

void Person::setSex(char sex) {
    this->sex = sex;
}

void Person::setPlace(string place) {
    this->place = place;
}

void Person::changeMargin() {
    if (this->place == "hotel")
        this->place = "safe";
    else
        this->place = "hotel";
}




