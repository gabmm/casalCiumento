#ifndef METRICS_H_INCLUDED
#define METRICS_H_INCLUDED

#include <iostream>
#include <chrono>

using namespace std;

/*
    Biblioteca de metodos criada com o intuito de classificar diferentes
    metodos de ordenacao
*/
typedef chrono::high_resolution_clock Clock;

typedef struct
{

  double time; // Tempo de CPU gasto no processo
} Metrics;

inline void Setup_metrics(Metrics* m)
{
  m->time = 0.0;
}

inline void Set_CPUtime(Metrics* m, double new_time)
{
  m->time = new_time;
}

inline void Print_metrics(Metrics* m)
{

  cout << "Tempo de CPU: " << m->time << " segundos" << endl;
}

#endif // METRICS_H_INCLUDED