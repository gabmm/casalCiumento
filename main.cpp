#include <iostream>
#include <vector>
#include "include/Person.h"
#include "include/Boat.h"
#include "include/Scenario.h"
#include <string>

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

    Scenario scenario;

    scenario.print();

    string pessoa1;
    string pessoa2;

    while (!scenario.isEveryoneSafe())
    {
        cout << "Selecione uma pessoa para remar (m/f + 1/2/3): ";
        cin >> pessoa1;
        cout << "Selecine uma pessoa para acompanhar ('m/f + 1/2/3' ou 'x' para sem acompanhante): ";
        cin >> pessoa2;
        cout << endl;

        if (scenario.traverse(pessoa1, pessoa2)){
            scenario.print();
            if (scenario.isEveryoneSafe()){
                cout << "Parabéns! Estão todos a salvo!";
            }
        }
    }

    return 0;
}
