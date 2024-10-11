#ifndef ERRO_MSGS_HPP
#define ERRO_MSGS_HPP

#include <string>
using namespace std;

string displayInstrucoes()
{
    string msgConjuntosDisponiveis =
    R"(
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
                                   DOS CONJUNTOS DIPONÍVEIS
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    Para testar as funções do TAD set, você tem a sua disposição 3 conjuntos:
    1. A
    2. B
    3. C
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
                                  DA UTILIZAÇÃO DAS OPERAÇÕES BINÁRIAS
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    Todas as operações binárias que você fizer (união, intersecção e diferença) vão ser
    guardadas no set 'C', portanto é recomendável que você adicione informações
    nos sets 'A' e 'B', mas fique à vontade para usar o 'C' se quiser, mas saiba que,
    assim que você fizer uma operação binária, todas as informações de 'C' serão dele-
    tadas, ao menos, é claro, que "C" faça parte de um dos operandos. Neste caso, as infor-
    mações de "C" não seram deletadas, pois elas são necessárias para a operação.

    Para realizar uma operação binária, selecione a 13° opção e siga a seguinte sintaxe:
    1. set1-set2 para a diferença
    2. set1+set2 para a uniao
    3. set1#set2 para intersecção
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                                  Da inserção e remoção
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    Para inserir ou deletar elementos, você só precisa dizer a quantidade de elementos
    e quais são eles. É necessário especifícá-los VERTICALMENTE, não horizontalmente.
    Por exemplo, suponha que você queira inserir três elementos o certo seria:
    
    x
    y
    x
    
    e não "x y z"
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                                     DO MENU
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    O Menu só aparecerá uma vez, porque é muito chato ter o menu dando pop-up toda a vez
    que uma operação é feita, mas, caso você precise ver o menu insira '20'.)";
    return msgConjuntosDisponiveis;
}

string warning()
{
    string msgWarning = R"(
                                           WARNING
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    Este menu faz uso somente de sets do tipo inteiro, mas na main, fique à
    vontade para testar sets de floats, strings, etc :)
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=)";
    return msgWarning;
}

string divisor()
{
    return "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
}

string insufficientParameters()
{
    return "ERRO: quantidade de argumentos insuficiente!";
}

string excessiveParameters()
{
    return "ERRO: quantidade excessiva de argumentos!";
}

string illegalCharacters()
{
    return "ERRO: Algum caractere ilegal foi inserido!";
}

string invalidSet()
{
    return "ERRO: Ao menos um cojunto inserido é inválido!";
}

string invalidOperation()
{
    return "ERRO: Está operação é inválida!";
}

string instructionValidInput()
{
    return "ERRO: Separe os elementos por quebras de linha!";
}

string warningOnlyIntegersAllowed()
{
    return "ERRO: Os conjuntos desta aplicação só aceitam valores inteiros!";
}

string negativeSuperiorLimit()
{
    return "ERRO: Você precisa inserir uma quantidade positiva de elementos!";
}
#endif