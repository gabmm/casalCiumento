//
// Created by patrick on 01/10/23.
//

#include "AIAlgorithm.h"
#include <stack>
#include <deque>

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

        if (first->getState().isEveryoneSafe()) { // verifica se o no que acabou de ser visitado é a solução
            cout << endl << "PARABÉNS! Estão todos a salvo. Alcançado estado objetivo." << endl;
            break;
        }

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

        //caso não haja mais regras para aplicar e não é a solução então significa que temos de mudar o nosso first
        closed.push(first); // copia o no visitado de aberto para fechado
        open.pop();         // remove o no visitado da fila de abertos
    }

    gtree.printPath(first, depth);
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

        if (top->getState().isEveryoneSafe()) { // verifica se o no que acabou de ser visitado é a solução
            cout << endl << "PARABÉNS! Estão todos a salvo. Alcançado estado objetivo." << endl;
            break;
        }

        // top->printState();                // imprime estado atual
        if (open.empty()) {
            cout << endl << "ERRO! Não foi encontrada a solução." << endl;
            break;
        }


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

        //caso não haja mais regras para aplicar e não é a solução então significa que temos de mudar o nosso first
        closed.push(top);       // copia o no visitado de aberto para fechado
        open.pop();             // remove o no visitado da fila de abertos
    }
    gtree.printPath(top, depth);
}

void AIAlgorithm::manualSearch(GTree& gtree, int &depth){

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

    //GTree gtree; //inicial arvore
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


    gtree.printPath(node, depth);
}


void orderedInsert(deque<GTNode*> &deque, GTNode* node){
    //insert node into deque ordered by cost
    bool inserted = false;
    for (auto it = deque.begin(); it != deque.end(); it++){
        if (node->getWeight() < (*it)->getWeight()) {
            deque.insert(it, node);
            inserted = true;
            break;
        }
    }
    if (!inserted) deque.push_back(node);
}

void greedyInsert(deque<GTNode*> &deque, GTNode* node){
    //insert node into deque ordered by cost
    bool inserted = false;
    for (auto it = deque.begin(); it != deque.end(); it++){
        if (node->getGreedyWeight() < (*it)->getGreedyWeight()) {
            deque.insert(it, node);
            inserted = true;
            break;
        }
    }
    if (!inserted) deque.push_back(node);
}

void AIAlgorithm::orderedSearch(GTree &gtree, bool to_prune, int &depth) {
    GTNode* node = gtree.getRoot(); //ponteiro pro ultimo estado, nesse caso o estado inicial

    cout << "Busca ordenada " << endl;
    gtree.print();

    deque<GTNode*> open; // Fila dos abertos
    //queue<int> empty; // Fila dos abertos
    queue<GTNode*> closed; // Fila dos fechados
    open.push_back(node); // Adicionar a raiz no aberto
    GTNode* first;

    //unsigned int depth = 0;
    while (true)
    {
        first = open.front();               // recebe sempre o primeiro elemento da fila de abertos

        // first->printState();                // imprime estado atual
        cout << endl << "Lista de abertos: ";
        for (auto & i : open){
            cout << i->getWeight() << " ";
        }

        if (first->getState().isEveryoneSafe()) { // verifica se o no que acabou de ser visitado é a solução
            cout << endl << "PARABÉNS! Estão todos a salvo. Alcançado estado objetivo." << endl;
            break;
        }

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
                GTNode* oldNode = nullptr;
                gtree.getNode(state, oldNode);
                if (oldNode != nullptr){
                    if ((first->getWeight() + state.getRuleCost(rule)) < oldNode->getWeight()){
                        node = gtree.Insert(state, first, rule);
                        orderedInsert(open, node);
                        for (int i = 0; i < open.size(); i++){
                            if (oldNode == open[i]) {
                                open.erase(open.begin() + i);
                                gtree.RemoveLeaf(oldNode);
                                cout << endl << "Podou aqui!" << endl;
                            }
                        }
                    }
                    else{
                        cout << endl << "Podou aqui tambem!" << endl;
                    }
                }
                else{
                    node = gtree.Insert(state, first, rule);
                    orderedInsert(open, node);
                }

            }
            else {
                node = gtree.Insert(state, first, rule);    //insere o nó no cenario com o pai first;
                //open.push_back(node);
                orderedInsert(open, node);
            }
            first->popRule();                           //remove a regra usada
        }

        //caso não haja mais regras para aplicar e não é a solução então significa que temos de mudar o nosso first
        closed.push(first); // copia o no visitado de aberto para fechado
        open.pop_front();         // remove o no visitado da fila de abertos
    }

    gtree.printPath(first, depth);
}

void AIAlgorithm::greedySearch(GTree &gtree, bool to_prune, int &depth) {
    GTNode* node = gtree.getRoot(); //ponteiro pro ultimo estado, nesse caso o estado inicial

    cout << "Busca Gulosa " << endl;
    gtree.print();

    deque<GTNode*> open; // Fila dos abertos
    queue<GTNode*> closed; // Fila dos fechados
    open.push_back(node); // Adicionar a raiz no aberto
    GTNode* first;

    while (true)
    {
        first = open.front();               // recebe sempre o primeiro elemento da fila de abertos

        //first->printState();
        cout << endl << "Lista de abertos: ";
        for (auto & i : open){
            cout << i->getGreedyWeight() << " ";
        }

        // first->printState();                // imprime estado atual
        if (open.empty()) {
            cout << endl << "ERRO! Não foi encontrada a solução." << endl;
            break;
        }

        if (first->getState().isEveryoneSafe()) { // verifica se o no que acabou de ser visitado é a solução
            cout << endl << "PARABÉNS! Estão todos a salvo. Alcançado estado objetivo." << endl;
            break;
        }

        while (!first->getQueue().empty())  // Enquanto a lista de regras não for vazia vou aplicar todas as regras possiveis
        {
            Scenario state;                     //cria cenario inicial
            state.setState(first->getState());   // seta ele para que seja igual ao atual
            int rule = first->getQueue().front();       //copia a primeira regra da fila de regras possiveis
            state.applyRule(rule);

            if (to_prune) {
                //implementar poda
                /* Passos:
                 * procurar se existe na árvore, se não, insere e finaliza aqui
                 * se existir já na arvore, comparar os pesos
                 * se o peso do novo for maior que do antigo, não insere e finaliza aqui
                 * se o peso do novo for menor que do antigo, insere na arvore
                 * se o antigo estiver na lista de abertos significa que é folha, portanto remove da arvore e da lista
                 * se o antigo nao estiver na lista de abertos, significa que já foi visitado, logo não faz nada */
                if (!gtree.Search(state))
                {
                    node = gtree.Insert(state, first, rule);
                    greedyInsert(open, node);
                }
                else{
                    cout << endl << "Poda realizada!" << endl;
                }
            }
            else {
                node = gtree.Insert(state, first, rule);
                greedyInsert(open, node);
            }

            first->popRule();                           //remove a regra usada
        }

        //caso não haja mais regras para aplicar e não é a solução então significa que temos de mudar o nosso first
        closed.push(first); // copia o no visitado de aberto para fechado

        /* remove o first da fila de abertos: atentar-se para que, apesar do nome
        o first nao é mais o primeiro da lista, já que novos filhos com heurísticas
        melhores são criados e adicionados */
        for (int i = 0; i < open.size(); i++){
            if (first == open[i]) {
                open.erase(open.begin() + i);
                break;
            }
        }
    }
    gtree.printPath(first, depth);
}
