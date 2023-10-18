#include <iostream>
#include <vector>
#include "include/GTree.h"
#include "include/AIAlgorithm.h"
#include "Metrics.h"
#include <string>
#include <chrono>
#include <getopt.h>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

ofstream createOutputFile(string outputPath){
    ofstream f_out;
    f_out.open(outputPath, ios::app); // ir alterando o nome do arquivo para não se confundir

    if (!f_out.good())
        throw "Erro ao abrir arquivo";
    else cout << "Arquivo criado!";

    return f_out;
}

string runAlgorithm(int algorithm, bool to_prune, vector<int> rules){
    Metrics p;
    Setup_metrics(&p);
    auto t0 = std::chrono::high_resolution_clock::now();
    int depth = 0;
    GTree gtree(rules); //inicializa arvore
    int totalStates = gtree.getTotalStates();
    stringstream str;

    if(algorithm==-1)
        AIAlgorithm::manualSearch(gtree, depth);
    if(algorithm==0)
        AIAlgorithm::irrevocableSearch(gtree);
    else if(algorithm==1)
        AIAlgorithm::backtrackingSearch(gtree);
    else if(algorithm==2)
        AIAlgorithm::breadthFirstSearch(gtree, to_prune, depth);
    else if(algorithm==3)
        AIAlgorithm::depthFirstSearch(gtree, to_prune, depth);
    else if(algorithm==4)
        AIAlgorithm::orderedSearch(gtree, to_prune, depth);

    cout << "Profundidade (poda = " << boolalpha <<to_prune<<"): " << depth << endl;
    cout << "SOLUÇÃO ENCONTRADO COM PASSAGEM POR " << gtree.getTotalStates() << " estados diferentes." << endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta = t1 - t0;
    Set_CPUtime(&p, delta.count());
    Print_metrics(&p);
    cout << endl;

    str << "Profundidade (poda = " << boolalpha << to_prune
        << ");" << depth << ";" << totalStates << ";"
        << to_string(p.time) << "\n";

    return str.str();

}

int runPerformanceTest(int algorithm, bool to_prune, vector<int> rules, string outputPath) {
    ofstream f_out = createOutputFile(outputPath);
    stringstream str;
    int i_aux = 0;

    f_out << "Tipo;Profundidade;Estados;Tempo\n";

    while (i_aux < 20) {
        string result = runAlgorithm(algorithm, to_prune, rules);
        f_out << result;
        i_aux++;
    }
}

int main(int argc, char* argv[]) {
    // argv[1] -> Se ira realizar poda (1) ou não (0)
    // argv[2] -> Regras a ser escolhida (1) crescente, (2) decrescente,
    //              (3) casalMulherHomem, (4)casalHomemMulher e (5) homemCasalMulher [default = crescente]

    bool to_prune = false;
    vector<int> crescente{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
    vector<int> decrescente{ 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };
    vector<int> casalMulherHomem{ 13,14,15,1,2,3,4,5,6,7,8,9,10,11,12 };
    vector<int> casalHomemMulher{ 13,14,15,7,8,9,10,11,12,1,2,3,4,5,6 };
    vector<int> homemCasalMulher{ 7,8,9,10,11,12,13,14,15,1,2,3,4,5,6 };
    vector<vector<int>> ruleSets{ crescente, decrescente, casalMulherHomem,
                                  casalHomemMulher, homemCasalMulher };

    int opt;
    int algorithm = 0;
    bool performanceTest = false;
    int chosenRuleSet = 0;
    string outputPath = "output.csv";

    while((opt = getopt(argc, argv, "mt:ibldpor:")) != -1)
    {
        if(opt == 't') {
            performanceTest = true;
            outputPath = string(optarg);
        }
        else if(opt == 'p') {
            to_prune = true;
        }
        else if(opt == 'r') {
            chosenRuleSet = atoi(optarg);
            if(chosenRuleSet < 0 || chosenRuleSet > ruleSets.size()){
                cout << "Regra escolhida inválida. Definindo valor padrão (0)." << endl;
                chosenRuleSet = 0;
            }
        }
        else if(opt == 'm') {
            algorithm = -1;
        }
        else if(opt == 'i') {
            algorithm = 0;
        }
        else if(opt == 'b') {
            algorithm = 1;
        }
        else if(opt == 'l') {
            algorithm = 2;
        }
        else if(opt == 'd') {
            algorithm = 3;
        }
        else if(opt == 'o') {
            algorithm = 4;
        }
    }

    cout << "Regra escolhida: " << chosenRuleSet << endl;
    cout << "Poda: " << boolalpha << to_prune << endl;
    cout << "Algoritmo: " << algorithm << endl;

    if (performanceTest) {
        runPerformanceTest(algorithm, to_prune, ruleSets[chosenRuleSet], outputPath);
    } else {
        runAlgorithm(algorithm, to_prune, ruleSets[chosenRuleSet]);
    }

    return 0;
}