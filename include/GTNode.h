#ifndef CASALCIUMENTO_GTNODE_H
#define CASALCIUMENTO_GTNODE_H

#include "Scenario.h"
#include <vector>
#include <queue>

/* Nó da árvore genérica (GENERAL TREE NODE - GTNODE), contém como key um objeto da classe SCENARIO, classe que
 * mostra uma foto do estado do problema, ou seja, um estado. Contém ponteiro para o pai e um vetor que contém
 * ponteiros para os filhos do nó, que variam entre 0 e número máximo de regras - 1*/

class GTNode{
public:
    GTNode(Scenario state, GTNode* parent, int stateNumber, int ruleNumber); //construtor
    ~GTNode(); //destrutor
    Scenario getState(); //retorna o SCENARIO (key)
    GTNode* getParent(); //retorna o ponteiro para o pai
    vector<GTNode*> getChildren(); //retorna vetor de ponteiros para os filhos
    void makeChild(GTNode* child); //após um no ser criado, essa funcao adiciona um ponteiro para ele no vetor de filhos do no atual
    void printState(); //printa o estado, objeto scenario (key)
    bool isLeaf(); //retorna se é folha (vetor de filhos vazio)
    bool isEqual(Scenario sc); //dada um scenario, confere se é o mesmo do no atual
    queue<int> getQueue(); //retorna a fila de possiveis regras
    void setQueue(queue<int> q); //seta a fila de possiveis regras
    void removeChild(GTNode* child); //se child esta no vetor de filhos, remove-o de lá
    void popRule();//pula uma regra

protected:
    Scenario state; //key
    GTNode *parent; //ponteiro pro pai
    vector<GTNode*> children; //filhos
    int stateNumber; //numero do estado atual (sequencial)
    int selectedRule; //regra escolhida para gerar o estado atual
    queue<int> applicableRules; //fila que representa as possiveis regras. Leva em consideracao tanto as regras do problema quanto a possibilidade de loops
};

#endif //CASALCIUMENTO_GTNODE_H
