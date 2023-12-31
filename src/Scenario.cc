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

Scenario::Scenario(int couple1Weight, int couple2Weight, int couple3Weight) {
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

    this->f1->setWeight(couple1Weight);
    this->m1->setWeight(couple1Weight);
    this->f2->setWeight(couple2Weight);
    this->m2->setWeight(couple2Weight);
    this->f3->setWeight(couple3Weight);
    this->m3->setWeight(couple3Weight);

    this->boat = new Boat();

    this->iterCounter = 0;
}

Scenario::~Scenario() {
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
    //cout << "Estado " << iterCounter << ": " << endl;
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
    cout << endl;

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
    // Testa se todas as pessoas estão na margem SAFE

    if (this->f1->isSafe() && this->f2->isSafe() && this->f3->isSafe() &&
            this->m1->isSafe() && this->m2->isSafe() && this->m3->isSafe())
        return true;
    else
        return false;
}

bool Scenario::isThereOtherMale(Person *wife, bool margin, Person *guest) {
    // Testa se existem homens que não são maridos da [wife] na [margin]

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
    // Testa se existem mulheres que não são esposas do [husband] na [margin] e que estão sem seus maridos

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
    // Se [a pessoa é mulher] e [há outros homens na outra margem] e [seu marido não está no barco] e
    //[seu marido não está na outra margem], então nao pode atravessar
    if (!p->isMale()) {
        if (this->isThereOtherMale(p, desiredMargin, guest) &&
            !p->isMarriedTo(guest) && p->getMarriedTo()->isSafe() != desiredMargin) {
            //cout << "PROIBÍDO: Uma mulher não pode atravessar pois ficará na presença de homens sem que esteja com seu marido.";
            return false;
        }
    }
    // Se [pessoa 1 é homem] e [sua esposa não está na outra margem] e [há homens na margem em que está sua esposa]
    // e [há esposas sem seus maridos na outra margem] e [sua esposa não está indo no barco], então não pode atravessar
    else {
        if (p->getMarriedTo()->isSafe() != desiredMargin &&
            isThereOtherMale(p->getMarriedTo(), p->getMarriedTo()->isSafe(), guest) && !p->isMarriedTo(guest)){
            //cout << "PROIBÍDO: Um homem não pode atravessar pois deixará sua esposa na presença de outros homens.";
            return false;
        }
        if (this->isThereWifeNoHusband(p, desiredMargin, guest)){
            //cout << "PROIBÍDO: Um homem não pode atravessar pois ficará na presença da esposa de outro homem sem que ele esteja presente";
            return false;
        }
    }

    return true;
}

bool Scenario::canTraverse(std::string person1, std::string person2) {
    Person *p1 = getPerson(person1);
    Person *p2 = getPerson(person2);

    // TESTE 1: Existe pelo menos uma pessoa no barco?
    if (p1 == nullptr && p2 == nullptr){
        //cout << "PROIBÍDO: Barco nao pode fazer a travessia sozinho.";
        return false;
    }

    //Caso o usuário selecione duas vezes a mesma pessoa, considera apenas a primeira seleção
    if (p1 == p2){
        p2 = nullptr;
    }

    // TESTE 2: O barco está na mesma margem dos ocupantes?
    if ((p1 != nullptr && this->getBoat()->isSafe() != p1->isSafe()) ||
        (p2 != nullptr && this->getBoat()->isSafe() != p2->isSafe())){
        //cout << "PROIBÍDO: Uma das pessoas não está na mesma margem do barco.";
        return false;
    }

    // TESTE 3: as pessoas selecionadas podem atravessar?
    if (p1 != nullptr && !this->isAllowed(p1, p2))
        return false;

    if (p2 != nullptr && !this->isAllowed(p2, p1))
        return false;

    //OK, TUDO CERTO
    return true;
}

bool Scenario::traverse(std::string person1, std::string person2) {

    Person *p1 = getPerson(person1);
    Person *p2 = getPerson(person2);

    if (this->canTraverse(person1, person2))
    {
        if(p1 != nullptr)
            p1->changeMargin();

        if(p2 != nullptr)
            p2->changeMargin();

        this->boat->changeMargin();

        iterCounter++;

        return true;
    }

    return false;
}

bool Scenario::operator == (Scenario &sc) {
    if(this->f1->isSafe() == sc.f1->isSafe() &&
            this->f2->isSafe() == sc.f2->isSafe() &&
            this->f3->isSafe() == sc.f3->isSafe() &&
            this->m1->isSafe() == sc.m1->isSafe() &&
            this->m2->isSafe() == sc.m2->isSafe() &&
            this->m3->isSafe() == sc.m3->isSafe() &&
            this->boat->isSafe() == sc.boat->isSafe())
        return true;
    else
        return false;
}

void Scenario::setState(Scenario state) {
    this->f1->setPlace(state.f1->getPlace());
    this->f2->setPlace(state.f2->getPlace());
    this->f3->setPlace(state.f3->getPlace());
    this->m1->setPlace(state.m1->getPlace());
    this->m2->setPlace(state.m2->getPlace());
    this->m3->setPlace(state.m3->getPlace());
    this->boat->setPlace(state.boat->getPlace());
}

bool Scenario::applyRule(int rule) {
    switch(rule) {
        case 1:
            return this->traverse("f1", "f2");
            break;
        case 2:
            return this->traverse("f1", "f3");
            break;
        case 3:
            return this->traverse("f2", "f3");
            break;
        case 4:
            return this->traverse("f1", "x");
            break;
        case 5:
            return this->traverse("f2", "x");
            break;
        case 6:
            return this->traverse("f3", "x");
            break;
        case 7:
            return this->traverse("m1", "m2");
            break;
        case 8:
            return this->traverse("m1", "m3");
            break;
        case 9:
            return this->traverse("m2", "m3");
            break;
        case 10:
            return this->traverse("m1", "x");
            break;
        case 11:
            return this->traverse("m2", "x");
            break;
        case 12:
            return this->traverse("m3", "x");
            break;
        case 13:
            return this->traverse("f1", "m1");
            break;
        case 14:
            return this->traverse("f2", "m2");
            break;
        case 15:
            return this->traverse("f3", "m3");
            break;
        default:
            break;
    }
}

int Scenario::getRuleCost(int rule) {
    switch(rule) {
        case 1:
            return 3;
            break;
        case 2:
            return 4;
            break;
        case 3:
            return 5;
            break;
        case 4:
            return 1;
            break;
        case 5:
            return 2;
            break;
        case 6:
            return 3;
            break;
        case 7:
            return 3;
            break;
        case 8:
            return 4;
            break;
        case 9:
            return 5;
            break;
        case 10:
            return 1;
            break;
        case 11:
            return 2;
            break;
        case 12:
            return 3;
            break;
        case 13:
            return 2;
            break;
        case 14:
            return 4;
            break;
        case 15:
            return 6;
            break;
        default:
            break;
    }
}

bool Scenario::canApply(int rule) {
    switch(rule) {
        case 1:
            return this->canTraverse("f1", "f2");
            break;
        case 2:
            return this->canTraverse("f1", "f3");
            break;
        case 3:
            return this->canTraverse("f2", "f3");
            break;
        case 4:
            return this->canTraverse("f1", "x");
            break;
        case 5:
            return this->canTraverse("f2", "x");
            break;
        case 6:
            return this->canTraverse("f3", "x");
            break;
        case 7:
            return this->canTraverse("m1", "m2");
            break;
        case 8:
            return this->canTraverse("m1", "m3");
            break;
        case 9:
            return this->canTraverse("m2", "m3");
            break;
        case 10:
            return this->canTraverse("m1", "x");
            break;
        case 11:
            return this->canTraverse("m2", "x");
            break;
        case 12:
            return this->canTraverse("m3", "x");
            break;
        case 13:
            return this->canTraverse("f1", "m1");
            break;
        case 14:
            return this->canTraverse("f2", "m2");
            break;
        case 15:
            return this->canTraverse("f3", "m3");
            break;
        default:
            break;
    }


}

int Scenario::getGreedyWeight() {
    int greedyWeight = 0;

    if (!this->getPerson("f1")->isSafe())
        greedyWeight += 3;

    if (!this->getPerson("f2")->isSafe())
        greedyWeight += 2;

    if (!this->getPerson("f3")->isSafe())
        greedyWeight += 1;

    if (!this->getPerson("m1")->isSafe())
        greedyWeight += 3;

    if (!this->getPerson("m2")->isSafe())
        greedyWeight += 2;

    if (!this->getPerson("m3")->isSafe())
        greedyWeight += 1;

    return greedyWeight;
}

string Scenario::toString() {
    std::string stateStr = "";

    this->m1->isSafe() ? stateStr += " 1 |" : stateStr += " 0 |";
    this->f1->isSafe() ? stateStr += " 1 |" : stateStr += " 0 |";
    this->m2->isSafe() ? stateStr += " 1 |" : stateStr += " 0 |";
    this->f2->isSafe() ? stateStr += " 1 |" : stateStr += " 0 |";
    this->m3->isSafe() ? stateStr += " 1 |" : stateStr += " 0 |";
    this->f3->isSafe() ? stateStr += " 1 |" : stateStr += " 0 |";
    this->boat->isSafe() ? stateStr += " 1 " : stateStr += " 0 ";

    return stateStr;
}
