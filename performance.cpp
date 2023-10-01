#include <fstream>
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
#include <stack>
using namespace std;


int main(int argc, char const* argv[]) {
  // argv[1] -> Se ira realizar poda (1) ou não (0)


  ofstream f_out;
  f_out.open("../output/planilhaIrrev.csv", ios::app); // ir alterando o nome do arquivo para não se confundir

  if (!f_out.good())
    return -1;
  else cout << "Arquivo criado!";

  string str;

  //hedears para a planilha
  str = "\nTipo;Profundidade;Estados;Tempo\n";
  f_out << str;
  int i_aux = 0;

  while (i_aux < 20)
  {


    Metrics p;
    Setup_metrics(&p);
    auto t0 = std::chrono::high_resolution_clock::now();

    bool to_prune = false;

    if (argv[1] && argv[1] != "0") {
      to_prune = true;
    }


    // TODO: copiar aqui o algoritmo que deseja executar 

    int depth = 0; // saber a profundidade do caminho solução
    /* Usado para contar quantos estados esta no caminho solução*/
    //  GTNode* parent = first;
    // while (parent != nullptr)
    // {
    //   parent->getState().print();
    //   parent = parent->getParent();
    //   depth++;
    // }
    int totalStates;
    // int totalStates = gtree.getTotalStates();

    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta = t1 - t0;
    Set_CPUtime(&p, delta.count());
    Print_metrics(&p);
    cout << endl;
    if (to_prune)
      str = "Profundidade com poda;" + to_string(depth) + ";" + to_string(totalStates) + ";" + to_string(p.time) + "\n";
    else
      str = "Profundidade sem poda;" + to_string(depth) + ";" + to_string(totalStates) + ";" + to_string(p.time) + "\n";

    // TODO: fechar aqui o algoritmo que deseja executar 
    f_out << str;
    i_aux++;

  }


  return 0;
}