#include "GTNode.h"
#include "Scenario.h"
#include <vector>
#include <algorithm>

GTNode::GTNode(Scenario state, GTNode* parent, int stateNumber, int ruleNumber) {
    this->state = state;
    this->parent = parent;
    this->stateNumber = stateNumber;
    this->selectedRule = ruleNumber;
    this->weight = 0;
    this->greedyWeight = 0;

    if(parent != nullptr){
        this->weight = parent->getWeight() + state.getRuleCost(ruleNumber);
    }

    this->greedyWeight = this->getState().getGreedyWeight();
}

GTNode::~GTNode() {

}

Scenario GTNode::getState() {
    return this->state;
}

GTNode* GTNode::getParent() {
    return this->parent;
}

const vector<GTNode*>& GTNode::getChildren() {
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
    queue<int> q = this->getQueue();
    cout << "Possibly rules: {";
    while (!q.empty())
    {
        if (q.size() != 1)
            cout << q.front() << " ";
        else
            cout << q.front();

        q.pop();
    }
    cout << "}" << endl;
    cout << "--------------------------------------" << endl;
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

queue<int> GTNode::getQueue(){
    return this->applicableRules;
}

void GTNode::setQueue(queue<int> q) {
    this->applicableRules = q;
}

void GTNode::popRule() {
    queue<int> q = this->applicableRules;
    q.pop();
    this->setQueue(q);
}

void GTNode::removeChild(GTNode *child) {
    vector<GTNode*>::iterator it;
    it = find(this->children.begin(), this->children.end(), child);
    if (it != this->children.end()){
        this->children.erase(it);
        //cout << "filho removido!" << endl;
    }
    else
    {
        //cout << "filho nao encontrado" << endl;
    }
}

int GTNode::getWeight() const {
    return weight;
}

void GTNode::setWeight(int weight) {
    GTNode::weight = weight;
}

int GTNode::getGreedyWeight() {
    return this->greedyWeight;
};