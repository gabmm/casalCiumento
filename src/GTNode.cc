#include "GTNode.h"
#include "Scenario.h"
#include <vector>

GTNode::GTNode(Scenario state, GTNode* parent, int stateNumber, int ruleNumber) {
    this->state = state;
    this->parent = parent;
    this->stateNumber = stateNumber;
    this->selectedRule = ruleNumber;
}

GTNode::~GTNode() {

}

Scenario GTNode::getState() {
    return this->state;
}

GTNode* GTNode::getParent() {
    return this->parent;
}

vector<GTNode*> GTNode::getChildren() {
    return this->children;
}

void GTNode::makeChild(GTNode *child) {
    this->children.push_back(child);
}

void GTNode::printState() {
    cout << endl;
    cout << "--------------------------------------";
    cout << endl;
    cout << "State: " << this->stateNumber << endl;
    cout << "Last Rule: R" << this->selectedRule << endl;
    this->state.print();
}

bool GTNode::isLeaf() {
    if(children.empty())
        return true;
    else
        return false;
}

bool GTNode::isEqual(Scenario sc) {
    if (this->state == sc)
        return true;
    else
        return false;
}