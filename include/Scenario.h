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
    bool isEveryoneSafe(); // testa se todos estão na margem SAFE
    Boat* getBoat();
    void setBoat();
    void setPerson(string person, Person* p);
    bool traverse(string p1, string p2); // atravessa uma ou duas pessoas
    bool isThereOtherMale(Person *wife, bool margin, Person *guest); // confere se existem outros homens na margem
    bool isAllowed(Person *p, Person *guest); // confere se a pessoa pode atravessar
    bool isThereWifeNoHusband(Person *husband, bool margin, Person *guest); // confere se existem esposas sem maridos na margem
    void printCheck();

private:
    Person *f1, *f2, *f3, *m1, *m2, *m3;
    Boat *boat;
    int iterCounter;
};

#endif //CASALCIUMENTO_SCENARIO_H
