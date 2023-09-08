#ifndef CASALCIUMENTO_GTNODE_H
#define CASALCIUMENTO_GTNODE_H

#include "Scenario.h"
#include <vector>

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

protected:
    Scenario state; //key
    GTNode *parent; //ponteiro pro pai
    vector<GTNode*> children; //filhos
    int stateNumber; //numero do estado atual (sequencial)
    int selectedRule; //regra escolhida para gerar o estado atual
};

#endif //CASALCIUMENTO_GTNODE_H
