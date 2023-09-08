#ifndef CASALCIUMENTO_GTREE_H
#define CASALCIUMENTO_GTREE_H

#include "Scenario.h"
#include <vector>
#include "GTNode.h"

/*Árvore Geral (General Tree - GTREE) - Tipo de arvore que tem nos com 0 até infinitos filhos
 * https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/GenTreeIntro.html*/

class GTree {
public:
    GTree(); //construtor
    ~GTree(); //destrutor
    bool Search(Scenario scenario); //dado um SCENARIO, retorna true se existe no nesta arvore que o contem, usada para evitar loops
    GTNode* Insert(Scenario scenario, GTNode* parent, int selectedRule); //insere novo no na arvore
    GTNode* getRoot(); //retorna ponteiro para o nó raiz
    void print(); //imprime arvore
    void clear(GTNode* node);

private:
    GTNode* root; //ponteiro para a raíz
    int stateCounter = 0; //contador de estados
    void auxPrint(GTNode* node);
    void auxSearch(Scenario sc, GTNode* node, int &flag);
};

#endif //CASALCIUMENTO_GTREE_H
