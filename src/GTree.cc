#include "GTree.h"
#include "GTNode.h"
#include "Scenario.h"
#include <vector>

GTree::GTree(vector<int> rules) {
    this->rules = rules;
    cout << "ARVORE CRIADA. SEQUENCIA DE REGRAS: ";
    for (int i = 0; i < this->rules.size(); i++)
        cout << rules.at(i) << " ";
    cout << endl;
    Scenario scenario;
    GTNode* node;
    node = this->Insert(scenario, nullptr, 0);
    this->root = node;
}

GTree::~GTree() {
    this->clear(this->root);
}

GTNode* GTree::Insert(Scenario scenario, GTNode* parent, int selectedRule) {
    this->stateCounter++;
    GTNode* node = new GTNode(scenario, parent, this->stateCounter, selectedRule);
    if (parent != nullptr)
        parent->makeChild(node);
    this->updateQueue(node);
    return node;
}

bool GTree::Search(Scenario scenario) {
    int flag = 0;
    this->auxSearch(scenario, this->root, flag);
    if (flag == 0)
        return false;
    else
        return true;
}

void GTree::auxSearch(Scenario sc, GTNode* node, int& flag) {
    if (node->isEqual(sc))
        flag = 1;
    else
        if (!node->isLeaf())
            for (int i = 0; i < node->getChildren().size(); i++)
                this->auxSearch(sc, node->getChildren().at(i), flag);
}

void GTree::getNode(Scenario scenario, GTNode* &p) {
    this->auxGetNode(this->root, scenario, p);
}

void GTree::auxGetNode(GTNode* node, Scenario sc, GTNode* &p) {
    if (node->isEqual(sc)) {
        p = node;
    }
    else {
        if (!node->isLeaf())
            for (int i = 0; i < node->getChildren().size(); i++)
                this->auxGetNode(node->getChildren().at(i), sc, p);
    }
}

GTNode* GTree::getRoot() {
    return this->root;
}

void GTree::print() {
    cout << "Imprimindo sequencia de estados e regras: ";
    int num_node = 1;
    auxPrint(this->root, num_node);
    cout << "Numero de nos: " << num_node << endl;
}

void GTree::auxPrint(GTNode* node, int& num_node) {
    node->printState();
    if (!node->isLeaf())
        for (int i = 0; i < node->getChildren().size(); i++) {
            auxPrint(node->getChildren().at(i), num_node);
            num_node++;
        }
}

void GTree::clear(GTNode* node) {
    if (!node->isLeaf())
        for (int i = 0; i < node->getChildren().size(); i++)
            clear(node->getChildren().at(i));
    delete node;
}

bool GTree::FindOnPath(Scenario scenario, GTNode* node) {
    while (node != nullptr) //unico nó que tem como pai null é a raiz
    {
        if (node->isEqual(scenario))
            return true;

        node = node->getParent();
    }
    return false;
}

GTNode* GTree::RemoveLeaf(GTNode* node) {
    if (!node->isLeaf()) {
        //cout << "Nó não é folha. Impossível remover." << endl;
        return node;
    }
    GTNode* p = node->getParent();
    p->removeChild(node);
    this->clear(node);
    this->stateCounter--;
    return p;
}

void GTree::updateQueue(GTNode* node) {
    queue<int> q;

    for (int i = 0; i < this->rules.size(); i++) {
        Scenario sc;
        sc.setState(node->getState());
        if (sc.applyRule(this->rules.at(i))) {
            //cout << "ENTRA NO APLICA RULE" << endl;
            if (!this->FindOnPath(sc, node)) {
                //cout << "ENTRA NO FIND PATH" << endl;
                //cout << "VOU INSERIR: " << this->rules.at(i);
                q.push(this->rules.at(i));
                //cout << "INSERIDA REGRA " << q.back() << endl;
            }
        }
    }

    node->setQueue(q);
}

GTree::GTree() {
    Scenario scenario;
    GTNode* node = new GTNode(scenario, nullptr, this->stateCounter, 0);
    this->stateCounter++;
    this->root = node;
}

int GTree::getTotalStates() {
    return this->stateCounter;
}

vector<int> GTree::getRules() {
    return this->rules;
}

void GTree::printPath(GTNode* node, int &depth) {
    while (node != nullptr)
    {
        node->getState().print();
        node = node->getParent();
        depth++;
    }
}


