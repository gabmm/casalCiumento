#include <iostream>
#include <vector>
#include "include/Person.h"
#include "include/Boat.h"
#include "include/Scenario.h"
#include "include/GTree.h"
#include "include/GTNode.h"
#include <string>


/* RESOLUCAO MANUAL
USUARIO ESCOLHE REGRA APÓS REGRA */

using namespace std;

int main() {

    cout << endl;
    cout << "Problema: TRAVESSIA DOS MARIDOS CIUMENTOS\n"
            "Após uma enchente, três casais ficaram cercados de água\n"
            "e viram-se obrigados a fugir do hotel onde passavam\n"
            "férias num barco que comportava no máximo duas pessoas\n" << endl;
    cout << "REGRAS: \n"
            "1. Um marido não permite que a sua mulher permaneça\n"
            "em qualquer lugar, com qualquer outro homem, a não ser\n"
            "que ele próprio estivesse presente.\n"
            "2. Qualquer um pode remar o barco \n"
            "3. Não é permitdo atravessar de qualquer outra forma." << endl;

    GTree gtree; //inicial arvore
    GTNode *node = gtree.getRoot(); //cria ponteiro pro ultimo estado (no caso, estado inicial)

    int rule; //cria variavel que armazena a regra escolhida pelo usuario

    while(!node->getState().isEveryoneSafe()){ //testa se chegou ao estado objetivo

        Scenario state; //reseta o estado pro inicial
        state.setState(node->getState()); //copia o estado pro ultimo estado
        node->printState(); //printa ultimo estado

        cout << "Regra 1: [f1 f2]  -  Regra 2: [f1 f3]  -  Regra 3: [f2 f3]" << endl;
        cout << "Regra 4: [f1 x]  -  Regra 5: [f2 x]  -  Regra 6: [f3 x]" << endl;
        cout << "Regra 7: [m1 m2]  -  Regra 8: [m1 m3]  -  Regra 9: [m2 m3]" << endl;
        cout << "Regra 10: [m1 x]  -  Regra 11: [m2 x]  -  Regra 12: [m3 x]" << endl;
        cout << "Regra 13: [f1 m1]  -  Regra 14: [f2 m2]  -  Regra 15: [f3 m3]" << endl;
        cout << "Escolha uma regra: ";
        cin >> rule; //le regra fornecida pelo usuario

        if (rule == 30) //caso o usuario queira terminar o processo e ver o estado da arvore
        {
            cout << "QUEBRA PELO USUARIO.";
            break;
        }

        if(state.applyRule(rule)){ //se a regra é aplicavel
            if (!gtree.Search(state)) { //se o estado que a regra causa nao for repetido
                GTNode *n1 = gtree.Insert(state, node, rule);
                node = n1;
            }
            else //caso seja repetido
            {
                cout << "PROIBÍDO: Estado já visitado.";
            }
        } //caso seja estado ilegal
    }

    cout << endl << "Parabéns, estão todos a salvo!" << endl;
    gtree.print(); //printa sequencia de estados ate o estado objetivo ou a quebra manual pelo usuario
    return 0;
}
