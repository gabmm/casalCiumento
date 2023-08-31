#include "../include/Person.h"
#include "../include/Boat.h"
#include "../include/Scenario.h"
#include <iostream>
#include <string>

Scenario::Scenario() {
    this->f1  = new Person('f');
    this->f2  = new Person('f');
    this->f3  = new Person('f');
    this->m1  = new Person('m');
    this->m2  = new Person('m');
    this->m3  = new Person('m');

    this->f1->setName("f1");
    this->f2->setName("f2");
    this->f3->setName("f3");
    this->m1->setName("m1");
    this->m2->setName("m2");
    this->m3->setName("m3");

    this->f1->setMarriedTo(m1);
    this->m1->setMarriedTo(f1);
    this->m2->setMarriedTo(f2);
    this->f2->setMarriedTo(m2);
    this->m3->setMarriedTo(f3);
    this->f3->setMarriedTo(m3);

    this->boat = new Boat();

    this->iterCounter = 0;
}

Scenario::~Scenario() {
    delete f1;
    delete f2;
    delete f3;
    delete m1;
    delete m2;
    delete m3;
    delete boat;
}

Person *Scenario::getPerson(std::string name) {
    if (this->m1->getName() == name)
        return this->m1;
    else if(this->m2->getName() == name)
        return this->m2;
    else if(this->m3->getName() == name)
        return this->m3;
    else if(this->f1->getName() == name)
        return this->f1;
    else if(this->f2->getName() == name)
        return this->f2;
    else if(this->f3->getName() == name)
        return this->f3;
    else
        return nullptr;
}

Boat *Scenario::getBoat() {
    return this->boat;
}

void Scenario::print() {
    cout << "Estado " << iterCounter << ": " << endl;
    cout << "S A F E│````│H O T E L" << endl;
    cout << "       │````│         " << endl;
    cout << "  ";
    if (this->m1->isSafe())
        cout << "M1";
    else
        cout << "  ";
    if (this->f1->isSafe())
        cout << " F1";
    else
        cout << "   ";
    cout << "│````│";
    if (!this->m1->isSafe())
        cout << "M1";
    else
        cout << "  ";
    if (!this->f1->isSafe())
        cout << " F1";
    else
        cout << "   ";
    cout <<  "    " << endl;
    cout << "  ";
    if (this->m2->isSafe())
        cout << "M2";
    else
        cout << "  ";
    if (this->f2->isSafe())
        cout << " F2";
    else
        cout << "   ";
    if (this->boat->isSafe())
        cout << "│B```│";
    else
        cout << "│```B│";
    if (!this->m2->isSafe())
        cout << "M2";
    else
        cout << "  ";
    if (!this->f2->isSafe())
        cout << " F2";
    else
        cout << "   ";
    cout <<  "    " << endl;
    cout << "  ";
    if (this->m3->isSafe())
        cout << "M3";
    else
        cout << "  ";
    if (this->f3->isSafe())
        cout << " F3";
    else
        cout << "   ";
    cout << "│````│";
    if (!this->m3->isSafe())
        cout << "M3";
    else
        cout << "  ";
    if (!this->f3->isSafe())
        cout << " F3";
    else
        cout << "   ";
    cout <<  "    " << endl;
    cout << "       │````│         " << endl;

    //this->printCheck();
}

void Scenario::printCheck() {
    cout << f1->getName() << " " << f1->getSex() << " " << f1->getPlace() << " eh casado com " << f1->getMarriedTo()->getName() << endl;
    cout << f2->getName() << " " << f2->getSex() << " " << f2->getPlace() << " eh casado com " << f2->getMarriedTo()->getName() << endl;
    cout << f3->getName() << " " << f3->getSex() << " " << f3->getPlace() << " eh casado com " << f3->getMarriedTo()->getName() << endl;
    cout << m1->getName() << " " << m1->getSex() << " " << m1->getPlace() << " eh casado com " << m1->getMarriedTo()->getName() << endl;
    cout << m2->getName() << " " << m2->getSex() << " " << m2->getPlace() << " eh casado com " << m2->getMarriedTo()->getName() << endl;
    cout << m3->getName() << " " << m3->getSex() << " " << m3->getPlace() << " eh casado com " << m3->getMarriedTo()->getName() << endl;
    cout << "boat " << boat->getPlace() << endl;
}

bool Scenario::isEveryoneSafe(){
    if (this->f1->isSafe() && this->f2->isSafe() && this->f3->isSafe() &&
            this->m1->isSafe() && this->m2->isSafe() && this->m3->isSafe())
        return true;
    else
        return false;
}

bool Scenario::isThereOtherMale(Person *wife, bool margin, Person *guest) {
    if (!this->m1->isMarriedTo(wife) && this->m1->isSafe() == margin && this->m1 != guest){
        return true;
    }

    if (!this->m2->isMarriedTo(wife) && this->m2->isSafe() == margin && this->m2 != guest){
        return true;
    }

    if (!this->m3->isMarriedTo(wife) && this->m3->isSafe() == margin && this->m3 != guest){
        return true;
    }

    return false;
}

bool Scenario::isThereWifeNoHusband(Person *husband, bool margin, Person *guest) {
    if (!this->f1->isMarriedTo(husband) && this->f1->isSafe() == margin && this->f1->getMarriedTo()->isSafe() != margin && !this->f1->isMarriedTo(guest)){
        return true;
    }

    if (!this->f2->isMarriedTo(husband) && this->f2->isSafe() == margin && this->f2->getMarriedTo()->isSafe() != margin && !this->f2->isMarriedTo(guest)){
        return true;
    }

    if (!this->f3->isMarriedTo(husband) && this->f3->isSafe() == margin && this->f3->getMarriedTo()->isSafe() != margin && !this->f3->isMarriedTo(guest)){
        return true;
    }

    return false;
}

bool Scenario::isAllowed(Person *p, Person *guest) {

    bool desiredMargin = !p->isSafe();
    // Se [a pessoa é mulher], [seu marido não está na outra margem ou no barco] e [há outros homens na outra margem]
    // então nao pode atravessar
    if (!p->isMale()) {
        if (this->isThereOtherMale(p, desiredMargin, guest) &&
            !p->isMarriedTo(guest) && p->getMarriedTo()->isSafe() != desiredMargin) {
            cout
                    << "PROIBÍDO: Uma mulher não pode atravessar pois ficará na presença de homens sem que esteja com seu marido."
                    << endl;
            return false;
        }
    }
    // Se [pessoa 1 é homem], [a travessia vai separá-lo de sua esposa], [há homens na margem em que ficou sua esposa]
    // e [há esposas sem seus maridos], então não pode atravessar
    else {
        if (p->getMarriedTo()->isSafe() != desiredMargin &&
            isThereOtherMale(p->getMarriedTo(), p->getMarriedTo()->isSafe(), guest) && !p->isMarriedTo(guest)){
            cout << "PROIBÍDO: Um homem não pode atravessar pois deixará sua esposa na presença de outros homens."
                 << endl;
            return false;
        }
        if (this->isThereWifeNoHusband(p, desiredMargin, guest)){
            cout << "PROIBÍDO: Um homem não pode atravessar pois ficará na presença da esposa de outro homem sem que "
                    "ele esteja presente" << endl;
            return false;
        }
    }

    return true;
}

bool Scenario::traverse(std::string person1, std::string person2) {

    Person *p1 = getPerson(person1);
    Person *p2 = getPerson(person2);

    // TESTE 1: Existe pelo menos uma pessoa no barco?
    if (p1 == nullptr && p2 == nullptr){
        cout << "PROIBÍDO: Barco nao pode fazer a travessia sozinho." << endl;
        return false;
    }

    //Caso o usuário selecione duas vezes a mesma pessoa, considera apenas a primeira seleção
    if (p1 == p2){
        p2 = nullptr;
    }

    // TESTE 2: O barco está na mesma margem dos ocupantes?
    if ((p1 != nullptr && this->getBoat()->isSafe() != p1->isSafe()) ||
            (p2 != nullptr && this->getBoat()->isSafe() != p2->isSafe())){
        cout << "PROIBÍDO: Uma das pessoas não está na mesma margem do barco." << endl;
        return false;
    }

    // TESTE 3: as pessoas selecionadas podem atravessar?
    if (p1 != nullptr && !this->isAllowed(p1, p2))
        return false;

    if (p2 != nullptr && !this->isAllowed(p2, p1))
        return false;


    // OK TUDO CERTO!
    if(p1 != nullptr)
        p1->changeMargin();

    if(p2 != nullptr)
        p2->changeMargin();

    this->boat->changeMargin();

    iterCounter++;

    return true;
}