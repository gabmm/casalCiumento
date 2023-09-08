#include "GTree.h"
#include "GTNode.h"
#include "Scenario.h"
#include <vector>

GTree::GTree() {
    Scenario scenario;
    GTNode* node = new GTNode(scenario, nullptr, this->stateCounter, 0);
    this->stateCounter++;
    this->root = node;
}

GTree::~GTree() {
    clear(this->root);
}

GTNode* GTree::Insert(Scenario scenario, GTNode *parent, int selectedRule) {
    GTNode* node = new GTNode(scenario, parent, this->stateCounter, selectedRule);
    this->stateCounter++;
    parent->makeChild(node);

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

void GTree::auxSearch(Scenario sc, GTNode *node, int &flag) {
    if (node->isEqual(sc))
        flag = 1;
    else
        if (!node->isLeaf())
            for(int i = 0; i < node->getChildren().size(); i++)
                this->auxSearch(sc, node->getChildren().at(i), flag);
}

GTNode* GTree::getRoot() {
    return this->root;
}

void GTree::print() {
    cout << "Imprimindo sequencia de estados e regras: ";
    auxPrint(this->root);
}

void GTree::auxPrint(GTNode *node) {
    node->printState();
    if (!node->isLeaf())
        for(int i = 0; i < node->getChildren().size(); i++)
            auxPrint(node->getChildren().at(i));
}

void GTree::clear(GTNode *node) {
    if (!node->isLeaf())
        for(int i = 0; i < node->getChildren().size(); i++)
            clear(node->getChildren().at(i));
    delete node;
}


