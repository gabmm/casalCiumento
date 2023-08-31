#ifndef CASALCIUMENTO_SCENARIO_H
#define CASALCIUMENTO_SCENARIO_H

#include <iostream>
#include <string>
#include "Person.h"
#include "Boat.h"

class Scenario {
public:
    Scenario();
    ~Scenario();
    Person* getPerson(string person);
    void print();
    bool isEveryoneSafe();
    Boat* getBoat();
    void setBoat();
    void setPerson(string person, Person* p);
    bool traverse(string p1, string p2);
    bool isThereOtherMale(Person *wife, bool margin, Person *guest);
    bool isAllowed(Person *p, Person *guest);
    bool isThereWifeNoHusband(Person *husband, bool margin, Person *guest);
    void printCheck();

private:
    Person *f1, *f2, *f3, *m1, *m2, *m3;
    Boat *boat;
    int iterCounter;
};

#endif //CASALCIUMENTO_SCENARIO_H
