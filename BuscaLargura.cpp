#include <iostream>
#include <vector>
#include "include/Person.h"
#include "include/Boat.h"
#include "include/Scenario.h"
#include "include/GTree.h"
#include "include/GTNode.h"
#include "include/Metrics.h"
#include <string>
#include <queue>

using namespace std;


int main(int argc, char const* argv[]) {
    // argv[1] -> Se ira realizar poda (1) ou não (0)
    // argv[2] -> Regras a ser escolhida (1) crescente, (2) decrescente,
    //              (3) casalMulherHomem, (4)casalHomemMulher e (5) homemCasalMulher [default = crescente]
    Metrics p;
    Setup_metrics(&p);
    auto t0 = std::chrono::high_resolution_clock::now();

    bool to_prune = false;
    string strRegras;
    if (argv[1] && *argv[1] != '0') {
        to_prune = true;
    }

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
    if (argv[2])
        switch (*argv[2]) {
        case '1':
            chosenVector = crescente; //escolhe estrategia de busca
            break;
        case '2':
            chosenVector = decrescente; //escolhe estrategia de busca
            break;
        case '3':
            chosenVector = casalMulherHomem; //escolhe estrategia de busca
            break;
        case '4':
            chosenVector = casalHomemMulher; //escolhe estrategia de busca
            break;
        case '5':
            chosenVector = homemCasalMulher; //escolhe estrategia de busca
            break;
        default:
            chosenVector = crescente; //escolhe estrategia de busca
        }
    else
        chosenVector = crescente;

    GTree gtree(chosenVector); //inicializa arvore
    GTNode* node = gtree.getRoot(); //ponteiro pro ultimo estado, nesse caso o estado inicial

    cout << "Busca em largura " << endl;
    gtree.print();

    queue<GTNode*> open; // Fila dos abertos
    queue<int> empty; // Fila dos abertos
    queue<GTNode*> closed; // Fila dos fechados
    open.push(node); // Adicionar a raiz no aberto
    GTNode* first;

    unsigned int depth = 0;

    while (true)
    {
        first = open.front();               // recebe sempre o primeiro elemento da fila de abertos

        // first->printState();                // imprime estado atual
        if (open.empty()) {
            cout << endl << "ERRO! Não foi encontrada a solução." << endl;
            break;
        }
        while (!first->getQueue().empty())  // Enquanto a lista de regras não for vazia vou aplicar todas as regras possiveis
        {
            Scenario state;                     //cria cenario inicial
            state.setState(first->getState());   // seta ele para que seja igual ao atual
            int rule = first->getQueue().front();       //copia a primeira regra da fila de regras possiveis
            state.applyRule(rule);

            if (to_prune) {
                if (!gtree.Search(state)) {
                    node = gtree.Insert(state, first, rule);    //insere o nó no cenario com o pai first;
                    open.push(node);
                }
            }
            else {
                if (!gtree.FindOnPath(state, node)) { //se o estado que a travessia gerou nao se repetiu                   //aplica a regra no cenário criado
                    node = gtree.Insert(state, first, rule);    //insere o nó no cenario com o pai first;
                    open.push(node);
                }
            }
            first->popRule();                           //remove a regra usada
        }
        if (first->getState().isEveryoneSafe()) { // verifica se o no que acabou de ser visitado é a solução
            cout << endl << "PARABÉNS! Estão todos a salvo. Alcançado estado objetivo." << endl;
            break;
        }

        //caso não haja mais regras para aplicar e não é a solução então significa que temos de mudar o nosso first
        closed.push(first); // copia o no visitado de aberto para fechado
        open.pop();         // remove o no visitado da fila de abertos
    }




    GTNode* parent = first;
    while (parent != nullptr)
    {
        parent->getState().print();
        parent = parent->getParent();
        depth++;
    }

    if (to_prune)
        cout << "Largura com poda: " << depth << endl;
    else
        cout << "Largura sem poda: " << depth << endl;
    cout << "SOLUÇÃO ENCONTRADO COM PASSAGEM POR " << gtree.getTotalStates() << " estados diferentes." << endl;


    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta = t1 - t0;
    Set_CPUtime(&p, delta.count());
    Print_metrics(&p);
    cout << endl;

    gtree.print();

    return 0;
}