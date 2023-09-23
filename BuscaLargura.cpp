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

    vector<int> crescente{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
    vector<int> decrescente{ 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };
    vector<int> casalMulherHomem{ 13,14,15,1,2,3,4,5,6,7,8,9,10,11,12 };
    vector<int> casalHomemMulher{ 13,14,15,7,8,9,10,11,12,1,2,3,4,5,6 };
    vector<int> homemCasalMulher{ 7,8,9,10,11,12,13,14,15,1,2,3,4,5,6 };
    vector<int> chosenVector; // vetor que recebe a regra escolhida

    chosenVector = crescente; //escolhe estrategia de busca
    GTree gtree(chosenVector); //inicializa arvore
    GTNode* node = gtree.getRoot(); //ponteiro pro ultimo estado, nesse caso o estado inicial


    gtree.print();

    queue<GTNode*> open;
    queue<GTNode*> closed;
    open.push(node);

    unsigned int rule = 0; //inicia contador de regras com zero
    unsigned int depth = 0;
    while (true) // Verifico se o último estado é a solução
    {
        Scenario state; //cria cenario inicial
        state.setState(node->getState()); //copia ultimo cenario
        node->printState(); //imprime ultimo cenario
        cout << "Aplicando regra R" << chosenVector.at(rule) << "..." << endl;

        while (rule < 15) // Para cada estado vamos verificar todas as regras
        {
            if (state.applyRule(chosenVector.at(rule))) {  // Verifica se pode aplicar a regra
                if (!gtree.FindOnPath(state, node)) { //se o estado que a travessia gerou nao se repetir
                    cout << "CONCLUÍDO: Regra R" << chosenVector.at(rule) << " aplicada!" << endl;
                    node = gtree.Insert(state, open.front(), chosenVector.at(rule)); // insere novo estado na arvore, salva em node (o pai vai ter todas as possibilidades de estado)
                    open.push(node); // adiciona o novo estado na fila de abertos 
                }
            }
            rule++;
        }
        closed.push(open.front()); // copia o no visitado de aberto para fechado
        open.pop(); // remove o no visitado da fila de abertos
        if (closed.back()->getState().isEveryoneSafe()) { // verifica se o no que acabou de ser visitado é a solução
            cout << endl << "PARABÉNS! Estão todos a salvo. Alcançado estado objetivo." << endl;
            break;
        }
        rule = 0; // reseta contador de regras 
    }

    GTNode* parent = closed.back();
    while (parent != nullptr)
    {
        parent->getState().print();
        parent = parent->getParent();
        depth++;
    }
    cout << "Profundidade " << depth << endl;
    cout << "SOLUÇÃO ENCONTRADO COM PASSAGEM POR " << gtree.getTotalStates() << " estados diferentes." << endl;

    return 0;
}