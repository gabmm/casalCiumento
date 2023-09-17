#ifndef CASALCIUMENTO_PERSON_H
#define CASALCIUMENTO_PERSON_H

#include <iostream>
#include <string>

/* classe que representa as pessoas no problema. Uma pessoa pode ser do sexo feminino ou masculino,
 * pode estar no margem hotel ou na margem safe e é casada com uma pessoa do sexo oposto*/

using namespace std;

class Person {
public:
    Person(char sex); //construtor (sexo a escolha, margem hotel, casado com a pessoa que tem o mesmo numero)
    ~Person(); //destrutor
    bool isMale(); //verdadeiro se homem, falso se mulher
    bool isSafe(); //verdadeiro se esta na margem safe, falso se esta no hotel
    bool isMarriedTo(Person *p); //verdadeiro se "this" é casado com pessoa p)
    char getSex(); //retorna sexo da pessoa
    string getPlace(); //retorna margem (safe ou hotel)
    Person* getMarriedTo(); //retorna um ponteiro para quem "this" é casado
    void setMarriedTo(Person *p); //casa "this" com p
    void setSex(char sex); //seta o sexo
    void setPlace(string place); //seta a margem (default: hotel)
    void changeMargin(); //troca a margem (de hotel para safe e vice-versa)
    string getName(); //retorna o nome (sempre será f ou M + 1, 2 ou 3)
    void setName(string name); //seta o nome

private:
    string name;
    char sex;
    string place;
    Person *marriedTo; //ponteiro para o esposo(a)
};


#endif //CASALCIUMENTO_PERSON_H
