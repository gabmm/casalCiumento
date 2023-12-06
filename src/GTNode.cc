#include "GTNode.h"
#include "Scenario.h"
#include <vector>
#include <algorithm>

int GTNode::NEXT_ID = 0;

GTNode::GTNode(Scenario state, GTNode *parent, int ruleNumber) {
    this->state = state;
    this->parent = parent;
    this->stateNumber = NEXT_ID;
    this->selectedRule = ruleNumber;
    this->weight = 0;
    this->greedyWeight = 0;
    this->greedyWeight = this->getState().getGreedyWeight();
    this->aStarWeight = greedyWeight;

    if(parent != nullptr){
        this->weight = parent->getWeight() + state.getRuleCost(ruleNumber);
        this->aStarWeight += weight;
    }
    NEXT_ID++;
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
}

// AStarWeight = greedyWeight + parent.getWeight + custoDaRegra
int GTNode::getAStarWeight() {
    return this->aStarWeight;
}


string GTNode::dotString(bool ruleWeight, bool greedyWeight) {
    string str = std::to_string(this->stateNumber);
    string edgeLabel = "";
    string xLabel = "";

    if(ruleWeight){
        edgeLabel = to_string(this->state.getRuleCost(this->selectedRule));
    }
    else{
        edgeLabel = "R"+ to_string(this->selectedRule);
    }

    if(greedyWeight){
        xLabel ="xlabel=<<font color=\"green\">"+ to_string(this->greedyWeight)+"</font>>";
    }else{
        xLabel = "";
    }

    str+= "[label=\"" + this->state.toString()+"\" "+xLabel+ "];\n";

    if(this->getParent() != nullptr){
        str += std::to_string(this->getParent()->stateNumber) + " -> " + std::to_string(this->stateNumber);
        str += "[label=\"" + edgeLabel + "\"];\n";
    }

    return str;
}

string GTNode::dotStringTopDown(int current, int limit, bool ruleWeight, bool greedyWeight) {
    string str = this->dotString(ruleWeight, greedyWeight);

    if(current < limit){
        for(int i = 0; i < this->children.size(); i++){
            str += this->children[i]->dotStringTopDown(current +1, limit, ruleWeight, greedyWeight);
        }
    }

    return str;
}

string GTNode::dotStringBottomUp(bool ruleWeight, bool greedyWeight) {
    string str = this->dotString(ruleWeight, greedyWeight);

    if(this->getParent() != nullptr){
        //str += std::to_string(this->getParent()->stateNumber) + " -> " + std::to_string(this->stateNumber);
        //str += "[label=\"" + std::to_string(this->selectedRule) + "\"];\n";
        str += this->getParent()->dotStringBottomUp(ruleWeight, greedyWeight);
    }

    return str;
}