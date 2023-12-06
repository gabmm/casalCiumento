#include <iostream>
#include <vector>
#include "include/GTree.h"
#include "include/AIAlgorithm.h"
#include "include/Metrics.h"
#include <string>
#include <chrono>
#include <getopt.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

ofstream createOutputFile(string outputPath, bool append = false){
    ofstream f_out;

    if(append)
        f_out.open(outputPath, ios::app); // ir alterando o nome do arquivo para não se confundir
    else
        f_out.open(outputPath); // ir alterando o nome do arquivo para não se confundir

    if (!f_out.good())
        throw "Erro ao abrir arquivo";
    else cout << "Arquivo criado!";

    return f_out;
}

void outputDotFile(string outputPath, GTree& gtree, bool ruleWeight, bool greedyWeight, bool onlySolutionPath){
    ofstream f_out = createOutputFile(outputPath, false);
    if(onlySolutionPath){
        f_out <<  gtree.dotStringUpwards(gtree.getGoalNode(), ruleWeight, greedyWeight);
    }else{
        f_out << gtree.dotString(std::numeric_limits<int>::max(), ruleWeight, greedyWeight);
    }

    f_out.close();

}

string runAlgorithm(int algorithm, bool to_prune, vector<int> rules){
    Metrics p;
    Setup_metrics(&p);
    auto t0 = std::chrono::high_resolution_clock::now();
    int depth = 0;
    GTree gtree(rules); //inicializa arvore
    stringstream str;
    string algName;

    if(algorithm==-1) {
        algName = "Busca Manual";
        AIAlgorithm::manualSearch(gtree, depth);
        outputDotFile("manual.dot", gtree, false, false, false);
    }
    if(algorithm==0) {
        algName = "Busca Irrevogável";
        AIAlgorithm::irrevocableSearch(gtree);
        outputDotFile("irrevocable.dot", gtree, false, false, false);

    }
    else if(algorithm==1) {
        algName = "Busca Backtracking";
        AIAlgorithm::backtrackingSearch(gtree, depth);
        outputDotFile("backtracking.dot", gtree, false, false, false);
        outputDotFile("backtracking_sol.dot", gtree, false, false, true);

    }
    else if(algorithm==2) {
        algName = "Busca em Largura";
        AIAlgorithm::breadthFirstSearch(gtree, to_prune, depth);
        outputDotFile("bfs_prune_"+ to_string(to_prune)+".dot", gtree, false, false, false);
        outputDotFile("bfs_prune_"+ to_string(to_prune)+"_sol.dot", gtree, false, false, true);

    }
    else if(algorithm==3) {
        algName = "Busca em Profundidade";
        AIAlgorithm::depthFirstSearch(gtree, to_prune, depth);
        outputDotFile("dfs_prune_"+ to_string(to_prune)+".dot", gtree, false, false, false);
        outputDotFile("dfs_prune_"+ to_string(to_prune)+"_sol.dot", gtree, false, false, true);

    }
    else if(algorithm==4) {
        algName = "Busca Ordenada";
        AIAlgorithm::orderedSearch(gtree, to_prune, depth);
        outputDotFile("ordered_prune_"+ to_string(to_prune)+".dot", gtree, true, false, false);
        outputDotFile("ordered_prune_"+ to_string(to_prune)+"_sol.dot", gtree, true, false, true);

    }
    else if(algorithm==5) {
        algName = "Busca Gulosa";
        AIAlgorithm::greedySearch(gtree, to_prune, depth);
        outputDotFile("greedy_prune_"+ to_string(to_prune)+".dot", gtree, true, false, false);
        outputDotFile("greedy_prune_"+ to_string(to_prune)+"_sol.dot", gtree, true, false, true);
    }
    else if(algorithm==6) {
        algName = "Busca A*";
        AIAlgorithm::aStarSearch(gtree, to_prune, depth);
        outputDotFile("astar_prune_"+ to_string(to_prune)+".dot", gtree, true, true, false);
        outputDotFile("astar_prune_"+ to_string(to_prune)+"_sol.dot", gtree, true, true, true);


    }

    int totalStates = gtree.getTotalStates();
    cout << algName << " (poda = " << boolalpha <<to_prune<<"): " << depth << endl;
    cout << "SOLUÇÃO ENCONTRADO COM PASSAGEM POR " << totalStates << " estados diferentes." << endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta = t1 - t0;
    Set_CPUtime(&p, delta.count());
    Print_metrics(&p);
    cout << endl;

    str << algName << " (poda = " << boolalpha << to_prune
        << ");" << depth << ";" << totalStates << ";"
        << to_string(p.time) << "\n";


    /*ofstream f_out = createOutputFile("output.dot");
    f_out << gtree.dotString(std::numeric_limits<int>::max());
    f_out.close();

    ofstream f_out2 = createOutputFile("solution.dot");
    f_out2 << gtree.dotStringUpwards(gtree.getGoalNode());
    f_out2.close();*/

    return str.str();

}

int runPerformanceTest(int algorithm, bool to_prune, vector<int> rules, string outputPath) {
    ofstream f_out = createOutputFile(outputPath, true);
    stringstream str;
    int i_aux = 0;

    f_out << "Tipo;Profundidade;Estados;Tempo\n";

    while (i_aux < 20) {
        string result = runAlgorithm(algorithm, to_prune, rules);
        f_out << result;
        i_aux++;
    }
    f_out.close();

    return 0;
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

    while((opt = getopt(argc, argv, "mt:ibldpogar:")) != -1)
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
            //reverse(ruleSets[chosenRuleSet].begin(), ruleSets[chosenRuleSet].end());
            algorithm = 3;
        }
        else if(opt == 'o') {
            algorithm = 4;
        }
        else if(opt == 'g') {
            algorithm = 5;
        }
        else if(opt == 'a') {
            algorithm = 6;
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
