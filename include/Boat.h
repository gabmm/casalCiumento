#ifndef CASALCIUMENTO_BOAT_H
#define CASALCIUMENTO_BOAT_H

#include <iostream>
#include <string>
#include "Person.h"

/* classe que representa o BOAT
 * necessita de ser excluida, ja que o barco pode ser um booleando do SCENARIO*/

using namespace std;

class Boat {
public:
    Boat(); //construtor
    ~Boat(); //destrutor
    bool isSafe(); //true se esta na margem segura, false se esta no hotel
    string getPlace(); //retorna a margem (safe ou hotel)
    void setPlace(string place); //seta a margem
    void changeMargin(); //troca a margem (EX.: se hotel, entao safe)

private:
    string place;
};


#endif //CASALCIUMENTO_BOAT_H
