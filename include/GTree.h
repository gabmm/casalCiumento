#ifndef CASALCIUMENTO_GTREE_H
#define CASALCIUMENTO_GTREE_H

#include "Scenario.h"
#include <vector>
#include "GTNode.h"

/*Árvore Geral (General Tree - GTREE) - Tipo de arvore que tem nos com 0 até infinitos filhos
 * https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/GenTreeIntro.html*/

class GTree {
public:
    GTree();
    GTree(vector<int> rules); //construtor. Solicita vetor de sequencia de regras
    ~GTree(); //destrutor
    bool Search(Scenario scenario); //dado um SCENARIO, retorna true se existe no nesta arvore que o contem, usada para evitar loops
    bool FindOnPath(Scenario scenario, GTNode* node); //dado um SCENARIO, retorna true se existe tal SCENARIO no caminho do no parâmetro até no raiz
    GTNode* Insert(Scenario scenario, GTNode* parent, int selectedRule); //insere novo no na arvore
    GTNode* getRoot(); //retorna ponteiro para o nó raiz
    void print(); //imprime arvore
    void clear(GTNode* node); //deleta a arvore
    GTNode* RemoveLeaf(GTNode* node); //remove nó folha e retorna ponteiro para o pai
    void updateQueue(GTNode* node); //atualiza a fila de regras aplicáveis ao node
    vector<int> getRules(); //retorna o vetor de sequencia de regra escolhido
    int getTotalStates(); // retorna o total de estados visitados até agora (nao confundir com passos)

private:
    GTNode* root; //ponteiro para a raíz
    int stateCounter = 0; //contador de estados
    void auxPrint(GTNode* node); //funcao auxiliar a Print
    void auxSearch(Scenario sc, GTNode* node, int &flag); //funcao auxiliar a Search
    vector<int> rules; //vetor de sequencia de regras
};

#endif //CASALCIUMENTO_GTREE_H
