#ifndef CASALCIUMENTO_PERSON_H
#define CASALCIUMENTO_PERSON_H

#include <iostream>
#include <string>

using namespace std;

class Person {
public:
    Person(char sex);
    ~Person();
    bool isMale();
    bool isSafe();
    bool isMarriedTo(Person *p);
    char getSex();
    string getPlace();
    Person* getMarriedTo();
    void setMarriedTo(Person *p);
    void setSex(char sex);
    void setPlace(string place);
    void changeMargin();
    string getName();
    void setName(string name);

private:
    string name;
    char sex;
    string place;
    Person *marriedTo;
};


#endif //CASALCIUMENTO_PERSON_H
