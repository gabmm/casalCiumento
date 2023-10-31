# Problema Casal Ciumento
**Disciplina Inteligência Artificial**

**Semestre 2023/3**

**UFJF - Faculdade de Ciência da Computação**


## Problema: 

Três casais ficaram ilhados em um hotel quando passavam férias.
Há um barco que pode levar duas pessoas por viagem para uma margem segura.
Entretanto, os maridos são ciumentos e não permitem que suas esposas fiquem sozinhas na presença de outros homens sem que eles próprios estejam presentes.
Deve-se encontrar uma forma de atravessar as seis pessoas em segurança sem que os maridos fiquem zangados.


### Estrutura de classes:

*PERSON*
-   Classe que representa as pessoas no problema


*SCENARIO*
- Classe controladora que representa os estados no problema

*GTREE*
- Classe que representa a estrutura de dados reponsável por armazenar os estados (objetos tipo SCENARIO) em seus nós e descrever os caminhos tomados pelas diferentes buscas implementadas.

*AIAlgorithm*
- Classe com métodos estáticos que implementam as buscas.

### ROTINA DE TESTES:

1. Seleciona uma entre quinze regras. As buscas dirão determinarão a escolha da regra.
2. Ao menos uma pessoa deve existir em cada travessia.
3. Caso a pessoa 1 seja a mesma pessoa que a pessoa 2, trata-se como se a pessoa 1 atravessasse sozinha.
4. Barco deve estar na mesma margem que a(s) pessoa(s) escolhida(s) para a travessia.
5. Para cada uma das pessoas escolhidas, se:
   1. Mulher, **não** poderá atravessar caso:
      1. Há outros homens na outra margem e,
      2. seu marido não está no barco e,
      3. seu marido não está na outra margem.
   2. Homem, **não** poderá atravessar caso:
      1. Há mulheres sem seus respectivos maridos na outra margem e,
      2. há homens na margem em que está sua esposa e,
      3. sua esposa não está no barco e,
      4. sua esposa não está na outra margem.
6. Após a travessia, compara-se o objeto SCENARIO gerado com os demais já guardados em nós da árvore. Se:
   1. Encontrar algum objeto SCENARIO igual ao SCENARIO atual, retorna ao estado anterior, descarta o atual e solicita nova regra.
   2. Não encontrar algum objeto SCENARIO igual ao SCENARIO atual, gera novo nó na árvore com o SCENARIO gerado.
7. **Encerra rotina** se o SCENARIO atual for igual ao estado objetivo ou se as regras se esgoarem. Caso nenhuma das duas proposições for verdadeira, retorna em 1.

---

## Funcionamento do código

### Como compilar

- gerado utilizando-se
```
$ make casalCiumento
```

### Como executar
```
$ ./casalCiumento <algoritmo>  [outras_opcoes]
```
A opção "algoritmo" deve ser uma das seguintes:

| Flag | Algoritmo                          | 
  |------|------------------------------------|
| `-m` | Execução manual através do teclado |
| `-i` | Busca irrevogável                  |
| `-b` | Busca Backtracking                 | 
| `-l` | Busca em largura                   | 
| `-d` | Busca em profundidade              |
| `-o` | Busca ordenada                     |
| `-g` | Busca gulosa                       |
| `-a` | Busca A*                           |


A opção "outras_opcoes" pode ser uma das seguintes:

| Opção               | Função                                                                                                                                                                             |
|---------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `-t <caminho>`      | Executa o algorimo indicado um núemro de vezes e cria arquivo no caminho indicado com os resultados. Caso `-t` seja passado sem o caminho, o arquivo será escrito em `output.csv`. |
| `-p`                | Ativa a poda (quando aplicável). Desativado por padrão.                                                                                                                            |
| `-r <ordem_regras>` | Define a ordem em que as regras serão aplicadas de acordo com a tabela a seguir. Por padrão é igual a 0.                                                                           |

O parâmetro "ordem_regras" após a flag `-r` deve ser um dos seguintes:

| Valor | Ordem das regras                   | 
  |-------|------------------------------------|
| `0`   | Ordem crescente                    |
| `1`   | Ordem decrescente                  |
| `2`   | Ordem casalMulherHomem             |
| `3`   | Ordem casalHomemMulher             |
| `4`   | Ordem homemCasalMulher             |


### Exemplos de execução:

- Executa a busca backtracking com a ordem de regras decrescente:
   ```
   $ ./casalCiumento -b -r 1
   ```

- Executa o mesmo algoritmo em modo de teste com saída em output.csv:
   ```
   $ ./casalCiumento -b -r 1 -t output.csv
   ```

- Executa a busca em largura com a ordem de regras crescente e com a poda ativada:
   ```
   $ ./casalCiumento -l -r 0 -p
   ```



