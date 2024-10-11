#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include "msgs.hpp"
#include "utils.hpp"

using namespace std;

Set<int>* A = new Set<int>();
Set<int>* B = new Set<int>();
Set<int>* C = new Set<int>();

/*
Utilização:
myStr= "A+B";
C->union2(mapeamento[myStr[0]],mapeamento[myStr[2]]);
*/

map<char, Set<int>*> mapeamento=
{
    {'A', A},
    {'B', B},
    {'C', C}
};

void menuImpressao(string choosenSet)
{
    cout << divisor() << endl;
    int opc = 0;
    string opcoesImpressao = 
    R"(Qual dos métodos de impressão você deseja usar ?
    1. inOrder
    2. postOrder
    3. preOrder)";
    cout << opcoesImpressao << endl;
    cin >> opc;

    switch (opc)
    {
        case 1:
            if (choosenSet == "A")
                displayInOrder(A);
            else if (choosenSet == "B")
                displayInOrder(B);
            else
                displayInOrder(C);
            break;
        case 2:
            if (choosenSet == "A")
                displayPostOrder(A);
            else if (choosenSet == "B")
                displayPostOrder(B);
            else
                displayPostOrder(C);
            break;
        case 3:
            if (choosenSet == "A")
                displayPreOrder(A);
            else if (choosenSet == "B")
                displayPreOrder(B);
            else
                displayPreOrder(C);
            break;
        default:
            break;
    }
}

string selectSets()
{
    string answer = "";
    bool invalidAnswer = true, firstIteraction = true;

    while (invalidAnswer)
    {
        if (firstIteraction)
        {
            cout << "Referente à A,B ou C?" << endl;
            cin >> answer;
            //remove espaços em branco
            answer.erase(remove(answer.begin(), answer.end(), ' '),answer.end());
            if (answer > "C" || answer < "A")
            {
                firstIteraction = false;
                continue;
            }
            invalidAnswer = false;
        }
        else
        {
            cout << "Desculpe, mas você precisa inserir uma opção válida. Tente novamente." << endl;
            cin >> answer;
            if (answer >= "A" && answer <= "C")
                invalidAnswer = false;
        }
    }
    return answer;
}

void promptSelectSucessor(char set)
{
    if (mapeamento[set]->empty())
    {    cout << "ERRO: O set está vazio!" << endl;
        return;
    }
    int elem = 0;
    cout << "Qual o elemento que você deseja encontrar o sucessor?" << endl;
    cin >> elem;
    try
    {
        int mySuce = mapeamento[set]->sucessor(elem);
        cout << "O sucessor de " << elem << " é: " << mySuce << endl;
    }
    catch(exception& erro)
    {
        cout << "ERRO: " << erro.what() << endl;
    }
}

void promptSelectPredecessor(char set)
{
    //A única funcionalidade desse if é eu poder verificar a nulidade e retorna
    //para a main caso o set de fato esteja nulo, antes de perguntar ao usuário
    //qual o elemento que ele deseja verificar
    if (mapeamento[set]->empty())
    {    cout << "ERRO: O set está vazio!" << endl;
        return;
    }
    int elem = 0;
    cout << "Qual o elemento que você deseja encontrar o predecessor?" << endl;
    cin >> elem;

    try
    {
        int myPred = mapeamento[set]->predecessor(elem);
        cout << "O predecessor de " << elem << " é: " << myPred << endl;
    }
    catch (exception &erroPred)
    {
        cout << "ERRO: " << erroPred.what() << endl;
    }
}

void promptCheckBelonging(string set)
{
    int elem = 0;
    cout << "Qual o elemento que você deseja verificar a existência?" << endl;
    cin >> elem;
    cout << "O elemento " << elem;
    
    if (set == "A")
    {
        if (!A->contains(elem))
            cout << " não";
        cout <<" está presente em 'A'" << endl;
    }
    else if (set == "B")
    {
        if (!B->contains(elem))
            cout << " não";
        cout <<" está presente em 'B'" << endl;
    }
    else
    {
        if (!C->contains(elem))
            cout << " não";
        cout <<" está presente em 'C'" << endl;
    }
}

void checkNullity(string set)
{
    cout << "O conjunto " << set;
    if (set == "A")
    {
        if (!A->empty())
            cout << " não";
        cout << " está vazio" << endl;
    }
    else if (set == "B")
    {
        if (!B->empty())
            cout << " não";
        cout << " está vazio" << endl;
    }
    else
    {    if (!C->empty())
            cout << " não";
        cout << " está vazio" << endl;
    }
}

void menuSwap()
{
    string swapSets = "";
    cout << "Insira os conjuntos que você deseja realizar o swap. Separe-os por espaços" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, swapSets); 
    swapSets = removeWhiteSpaces(swapSets);

    if ((int) swapSets.size() > 2)
        cout << excessiveParameters() << endl;
    else if ((int) swapSets.size() < 2)
        cout << insufficientParameters() << endl;
    else
    {
        if (((swapSets[0] < 'A' || swapSets[0] > 'C') || (swapSets[1] < 'A' || swapSets[1] > 'C')) && isAlphabetic(swapSets))
            cout << invalidSet() << endl;
        else if ((swapSets[0] < 'A' || swapSets[0] > 'C') || (swapSets[1] < 'A' || swapSets[1] > 'C'))
            cout << illegalCharacters() << endl;
        else
        {
            if ((swapSets[0] == 'A' && swapSets[1] == 'B') || (swapSets[0] == 'B' && swapSets[1] == 'A'))
                A->swap(B);
            else if ((swapSets[0] == 'A' && swapSets[1] == 'C') || (swapSets[0] == 'C' && swapSets[1] == 'A'))
                A->swap(C);
            else if ((swapSets[0] == 'C' && swapSets[1] == 'B') || (swapSets[0] == 'B' && swapSets[1] == 'C'))
                C->swap(B);
            cout << "SUCESSO! O swap entre " << swapSets[0] << " e " << swapSets[1] << " foi realizado" << endl;
        }
    }
}

void promptBinaryOperations()
{
    cout << "Insira a operação binária: ";
    string operacao = "";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, operacao);

    operacao = removeWhiteSpaces(operacao);

    if ((int)operacao.size() < 3)
        cout << insufficientParameters() << endl;
    else if ((int)operacao.size() > 3)
        cout << excessiveParameters() << endl;
    else
    {
        string operands = string(1,operacao[0]) + string(1,operacao[2]);
        char myOperator = operacao[1];
        
        if (!isAlphabetic(operands))
            cout << illegalCharacters() << endl;
        else if ((operands[0] < 'A' || operands[0] > 'C') || (operands[1] < 'A') || (operands[1] > 'C'))
            cout << invalidSet() << endl;
        else if (myOperator != '+' && myOperator != '-' && myOperator != '#')
            cout << invalidOperation() << endl;
        else
        {
            if (operacao[1] == '-')
                C->difference(mapeamento[operacao[0]],mapeamento[operacao[2]]);
            else if (operacao[1] == '+')
                C->union2(mapeamento[operacao[0]], mapeamento[operacao[2]]);
            else if (operacao[1] == '#')
                C->intersection(mapeamento[operacao[0]], mapeamento[operacao[2]]);
            cout << "A operação binária foi realizada com sucesso e foi salva em 'C'!" << endl;
        }
    }
}

void documentacao()
{
    cout << warning() << endl;
    cout << displayInstrucoes() << endl;
}

void displayOptions()
{
    string operacoes = 
    R"(
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    0. Ler documentação (altamente recomendável)
    1. Inserir
    2. Remover
    3. Imprimir
    4. Obter máximo
    5. Obter mínimo
    6. Obter sucessor
    7. Obter predecessor
    8. Obter tamanho
    9. Limpar dados
    10. Checar pertinência
    11. Checar nulidade
    12. Realizar 'swap'
    13. Operação binária
    14. Sair
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    )";
    cout << operacoes << endl;
}

bool selectOptions()
{
    int opc = 0;
    string answer = "";
    cin >> opc;
    /*
    As funções "inserter" e "remover" estão definidas em "utils.hpp"
    e, obviamente, fazem mão dos métodos "insert" e "erase" do set.
    */
   try
   {
        switch(opc)
        {
            case 0:
                documentacao();
                break;
            case 1:
                answer = selectSets();
                if (answer == "A")
                    inserter(A);
                else if (answer == "B")
                    inserter(B);
                else
                    inserter(C);
                break;
            case 2:
                answer = selectSets();
                if (answer == "A")
                    remover(A);
                else if (answer == "B")
                    remover(B);
                else
                    remover(C);
                break;
            case 3:
                answer = selectSets();
                menuImpressao(answer);
                break;
            case 4:
                answer = selectSets();
                if (answer == "A")
                    cout << "O maior elemento do conjunto 'A' é: " << A->maximum() << endl;
                else if (answer == "B")
                    cout << "O maior elemento do conjunto 'B' é: " << B->maximum() << endl;
                else
                    cout << "O maior elemento do conjunto 'C' é: " << C->maximum() << endl;
                break;
            case 5:
                answer = selectSets();
                if (answer == "A")
                    cout << "O menor elemento do conjunto 'A' é: " << A->minimum() << endl;
                else if (answer == "B")
                    cout << "O menor elemento do conjunto 'B' é: " << B->minimum() << endl;
                else
                    cout << "O menor elemento do conjunto 'C' é: " << C->minimum() << endl;
                break;
            case 6:
                answer = selectSets();
                promptSelectSucessor(answer[0]);
                break;
            case 7:
                answer = selectSets();
                promptSelectPredecessor(answer[0]);
                break;
            case 8:
                answer = selectSets();
                if (answer == "A")
                    cout << "O tamanho do set 'A' é: " << A->size() << endl;
                else if (answer == "B")
                    cout << "O tamanho do set 'B' é: " << B->size() << endl;
                else
                    cout << "O tamanho do set 'C' é: " << C->size() << endl;
                break;
            case 9:
                answer = selectSets();
                if (answer == "A")
                    A->clear();
                else if (answer == "B")
                    B->clear();
                else
                    C->clear();
                break;
            case 10:
                answer = selectSets();
                promptCheckBelonging(answer);
                break;
            case 11:
                answer = selectSets();
                checkNullity(answer);
                break;
            case 12:
                menuSwap();
                break;
            case 13:
                promptBinaryOperations();
                break;
            case 14:
                A->~Set();
                B->~Set();
                C->~Set();
                return false;
            case 20:
                displayOptions();
                break;
            default:
                throw invalid_argument("ERRO: Opção inválida!");
                break;
        }
    }
    catch(exception &erro)
    {
        cout << erro.what() << endl;
    }
    return true;
}

void mainMenu()
{
    cout << divisor() << endl;
    displayOptions();
    while (selectOptions())
    {
        cout << divisor() << endl;
        cout << "esperando comando..." << endl;
    }
}

int main()
{
    mainMenu();
    /*
    A->insert(1);
    B->insert(2);
    A->swap(B);

    cout << "O valor antigo de 'A' era 1, agora ele é:" << A->root->info << endl;
    cout << "O valor antigo de 'B' era 2, agora ele é:" << B->root->info << endl;
    */
}