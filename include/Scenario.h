#ifndef CASALCIUMENTO_SCENARIO_H
#define CASALCIUMENTO_SCENARIO_H

#include <iostream>
#include <string>
#include <queue>
#include "Person.h"
#include "Boat.h"

/* Classe que representa o problema em si. A classe possui as seis pessoas e o barco. Testas os impedimentos do problema
 * e troca pessoas e o barco de margem. Também testa se o estado objetivo foi atingido. */

class Scenario {
public:
    Scenario(); //construtor
    ~Scenario(); //destrutor
    Person* getPerson(string person); //retorna pessoa pelo nome EX.: "f1" para Mulher 1
    void print(); //imprime estado
    bool isEveryoneSafe(); // testa se todos estão na margem SAFE, ou seja, estado objetivo
    Boat* getBoat(); //retorna o barco
    void setBoat(); //seta o barco
    void setPerson(string person, Person* p); //seta uma pessoa
    bool traverse(string p1, string p2); // atravessa uma ou duas pessoas
    bool isThereOtherMale(Person *wife, bool margin, Person *guest); // confere se existem outros homens na margem
    bool isAllowed(Person *p, Person *guest); // confere se a pessoa pode atravessar
    bool isThereWifeNoHusband(Person *husband, bool margin, Person *guest); // confere se existem esposas sem maridos na margem
    void printCheck(); //impressão pra testes (nao mais usado)
    bool operator == (Scenario &sc); //se a margem de todas as pessoas for a mesma, entao temos estados iguais
    void setState(Scenario state); //copia o state para o estado que o chama
    bool applyRule(int rule); //aplica a regra
    bool canApply(int rule); //retorna true se a regra pode ser aplicada
    bool canTraverse(string p1, string p2); // retorna true se P1 e P2 puderem atravessar


private:
    Person *f1, *f2, *f3, *m1, *m2, *m3;
    Boat *boat;
    int iterCounter; //acho que isso nao tem mais uso, mas tenho medo de tirar
};

#endif //CASALCIUMENTO_SCENARIO_H
