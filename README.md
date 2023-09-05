# Problema Casal Ciumento
Disciplina Inteligência Artificial
Semestre 2023/3
UFJF - Faculdade de Ciência da Computação

Problema: 

Três casais ficaram ilhados em um hotel quando passavam férias.
Há um barco que pode levar duas pessoas por viagem para uma margem segura.
Entretanto, os maridos são ciumentos e não permitem que suas esposas fiquem sozinhas na presença de outros homens sem que eles próprios estejam presentes.
Deve-se encontrar uma forma de atravessar as seis pessoas em segurança sem que os maridos fiquem zangados.

Funcionamento do código: 
Estrutura de classes:

PERSON - Classe que representa as pessoas no problema
string name - nome da pessoa, para o problema pode ser m1, m2, m3, f1, f2 ou f3. Sendo f representando female e m, male. 1, 2 e 3 representando cada casal.
char sex - 'f' ou 'm', como no nome
string place - em que local a pessoa está no momento, variando entre 'hotel' e 'safe'
Person *marriedTo - ponteiro em que aponta para um objeto tipo PERSON a qual a pessoa em questão é casa, ex. f1 é casada com m1


SCENARIO - Classe controladora que representa os estados no problema
Person *f1, *f2, *f3, *m1, *m2, *m3 - pessoas do problema
bool boat - representação do barco


MWTREE - Classe que representa a estrutura de dados 
