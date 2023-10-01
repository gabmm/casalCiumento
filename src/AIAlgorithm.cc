//
// Created by patrick on 01/10/23.
//

#include "AIAlgorithm.h"
#include <stack>

void AIAlgorithm::backtrackingSearch(GTree &gtree){

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

        /*  if (node->getState().isEveryoneSafe())
          {
              cout << "PARABÉNS! Estão todos a salvo!" << endl;
              cout << "SOLUÇÃO ENCONTRADO COM PASSAGEM POR " << gtree.getTotalStates() << " estados diferentes." << endl;
          }*/
    }


}

void AIAlgorithm::irrevocableSearch(GTree& gtree){
    GTNode *node = gtree.getRoot(); //ponteiro pro ultimo estado, nesse caso o estado inicial
    int rule = 0; //inicia contador de regras com zero

    while(true){

        Scenario state; //cria cenario inicial
        state.setState(node->getState()); //copia ultimo cenario
        node->printState(); //imprime ultimo cenario
        cout << "Aplicando regra R" << gtree.getRules().at(rule) << "..." << endl;

        if(state.applyRule(gtree.getRules().at(rule))){ //se puder atravessar
            if (!gtree.FindOnPath(state, node)) { //se o estado que a travessia gerou nao se repetir
                cout << "CONCLUÍDO: Regra R" << gtree.getRules().at(rule) << " aplicada!";
                GTNode *n1 = gtree.Insert(state, node, gtree.getRules().at(rule)); //insere novo estado na arvore, salva em n1
                node = n1; //salva ultimo estado
                rule = 0; //reseta contador de regras
            }
            else
            {
                rule++; //incrementa contador de regras (caso estado repetido)
                cout << "PROIBÍDO: Estado já visitado.";
            }
        }
        else{
            rule++; //incrementa contador de regras (caso travessia impossibilitada)
        }

        if (rule >= 15) //nenhuma regra aplicavel
        {
            cout << endl << "ERRO: Nenhuma regra aplicável. Alcançado estado de impasse." << endl;
            break;
        }

        if (node->getState().isEveryoneSafe()) //alcancou estado objetivo
        {
            cout << endl << "PARABÉNS! Estão todos a salvo. Alcançado estado objetivo." << endl;
            break;
        }
    }
}

void AIAlgorithm::breadthFirstSearch(GTree& gtree, bool to_prune, int &depth){
    GTNode* node = gtree.getRoot(); //ponteiro pro ultimo estado, nesse caso o estado inicial

    cout << "Busca em largura " << endl;
    gtree.print();

    queue<GTNode*> open; // Fila dos abertos
    queue<int> empty; // Fila dos abertos
    queue<GTNode*> closed; // Fila dos fechados
    open.push(node); // Adicionar a raiz no aberto
    GTNode* first;

    //unsigned int depth = 0;

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
}

void AIAlgorithm::depthFirstSearch(GTree& gtree, bool to_prune, int &depth){
    GTNode* node = gtree.getRoot(); //ponteiro pro ultimo estado, nesse caso o estado inicial

    cout << "Busca em profundidade " << endl;

    gtree.print();

    stack <GTNode*> open; // Pilha dos abertos
    queue<GTNode*> closed; // Fila dos fechados
    open.push(node); // Adicionar a raiz no aberto
    GTNode* top;

    //unsigned int depth = 0;
    while (true)
    {
        top = open.top();                   // recebe sempre o primeiro elemento da pilha de abertos

        // top->printState();                // imprime estado atual
        if (open.empty()) {
            cout << endl << "ERRO! Não foi encontrada a solução." << endl;
            break;
        }



        //caso não haja mais regras para aplicar e não é a solução então significa que temos de mudar o nosso first

        closed.push(top);       // copia o no visitado de aberto para fechado
        open.pop();             // remove o no visitado da fila de abertos
        while (!top->getQueue().empty())  // Enquanto a lista de regras não for vazia vou aplicar todas as regras possiveis
        {
            Scenario state;                     //cria cenario inicial
            state.setState(top->getState());   // seta ele para que seja igual ao atual
            int rule = top->getQueue().front();       //copia a primeira regra da fila de regras possiveis
            state.applyRule(rule);

            if (to_prune) {
                if (!gtree.Search(state)) {
                    node = gtree.Insert(state, top, rule);    //insere o nó no cenario com o pai first;
                    open.push(node);
                }
            }
            else {
                if (!gtree.FindOnPath(state, node)) { //se o estado que a travessia gerou nao se repetiu                   //aplica a regra no cenário criado
                    node = gtree.Insert(state, top, rule);    //insere o nó no cenario com o pai first;
                    open.push(node);
                }
            }
            top->popRule();
        }

        if (top->getState().isEveryoneSafe()) { // verifica se o no que acabou de ser visitado é a solução
            cout << endl << "PARABÉNS! Estão todos a salvo. Alcançado estado objetivo." << endl;
            break;
        }

    }

    GTNode* parent = open.top();
    while (parent != nullptr)
    {
        parent->getState().print();
        parent = parent->getParent();
        depth++;
    }
}
