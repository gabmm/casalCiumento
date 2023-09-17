#include <iostream>
#include <vector>
#include "include/Person.h"
#include "include/Boat.h"
#include "include/Scenario.h"
#include "include/GTree.h"
#include "include/GTNode.h"
#include <string>
#include <queue>

using namespace std;

int main() {

    /* vetores determinam a escolha da estrategia a partir de uma sequencia de regras conforme a tabela:
    Regra 1: [f1 f2] Regra 2: [f1 f3] Regra 3: [f2 f3]
    Regra 4: [f1 x] Regra 5: [f2 x] Regra 6: [f3 x]
    Regra 7: [m1 m2] Regra 8: [m1 m3] Regra 9: [m2 m3]
    Regra 10: [m1 x] Regra 11: [m2 x] Regra 12: [m3 x]
    Regra 13: [f1 m1] Regra 14: [f2 m2] Regra 15: [f3 m3]*/

    vector<int> crescente{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    vector<int> decrescente{15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    vector<int> casalMulherHomem{13,14,15,1,2,3,4,5,6,7,8,9,10,11,12};
    vector<int> casalHomemMulher{13,14,15,7,8,9,10,11,12,1,2,3,4,5,6};
    vector<int> homemCasalMulher{7,8,9,10,11,12,13,14,15,1,2,3,4,5,6};
    vector<int> chosenVector; // vetor que recebe a regra escolhida

    chosenVector = crescente; //escolhe estrategia de busca

    GTree gtree(chosenVector); //inicializa arvore
    GTNode *node = gtree.getRoot(); //ponteiro pro ultimo estado, nesse caso o estado inicial

    while (!node->getState().isEveryoneSafe()){

        Scenario state; //cria cenário para teste de regras
        state.setState(node->getState()); //seta ele para que seja igual ao atual
        node->printState(); //imprime estado atual

        if (node->getQueue().empty()) //se não houver mais possíveis regras, então backtrack para último estado
        {
            cout << "ESTADO DE IMPASSE! Retornando..." << endl;
            GTNode *p; //cria ponteiro
            p = node; //aponta para o estado atual
            node = p->getParent(); //ponteiro atual aponta para o pai do estado atual; Ou seja, novo estado atual é o pai
            gtree.RemoveLeaf(p); //remove o estado antigo (filho) usando o ponteiro criado
        }
        else //há mais regras, portanto, aplica a próxima regra da fila
        {
            int rule = node->getQueue().front(); //copia a primeira regra da fila de regras possiveis
            node->popRule(); //tira ela da filla
            state.applyRule(rule);//aplica a regra no cenário criado para os testes
            cout << "REGRA " << rule << " aplicada!" << endl;
            GTNode *p;
            p = gtree.Insert(state, node, rule); //cria nó com o novo estado alcançado;
            node = p; //ponteiro atual é o novo nó
        }

        if (node->getState().isEveryoneSafe())
        {
            cout << "PARABÉNS! Estão todos a salvo!" << endl;
            cout << "SOLUÇÃO ENCONTRADO COM PASSAGEM POR " << gtree.getTotalStates() << " estados diferentes." << endl;
        }
    }

    gtree.print();


    return 0;
}