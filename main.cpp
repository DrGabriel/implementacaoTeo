#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include<time.h>
#include <omp.h>
#define TAMANHOMATRIZ 4
#define TOTALFREQUENCIA 11
using namespace std;

int tamanhoMatriz = 4;

void copia(std::array<std::array<int, TOTALFREQUENCIA>, TAMANHOMATRIZ> &data, std::array<std::array<int, TOTALFREQUENCIA>, TAMANHOMATRIZ> &novaCopia){
    for (int i = 0; i < TAMANHOMATRIZ; ++i) {
        for (int j = 0; j < TOTALFREQUENCIA; ++j) {
            novaCopia[i][j] =  data[i][j];
        }

    }
}

void teste(std::array<std::array<int, TOTALFREQUENCIA>, TAMANHOMATRIZ> &data){

    for (int i = 0; i < TAMANHOMATRIZ; ++i) {
        for (int j = 0; j < TOTALFREQUENCIA; ++j) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

int geraFrequenciaAleatoria(){

    int random = rand() % TOTALFREQUENCIA;
    return random;
}
void teste1(std::array<int, TAMANHOMATRIZ> &data){
    for (int i = 0; i < TAMANHOMATRIZ; ++i) {
            cout << data[i] << " ";
    }
    cout << endl;

}

int calculaCusto
(std::array<std::array<int, TAMANHOMATRIZ>, TAMANHOMATRIZ> restricoesDistancia,
 std::array<std::array<int, TOTALFREQUENCIA>, TAMANHOMATRIZ> solucaoAtual,
 int totalFrequencias){
    int custo = 0;
    int i = 0;
    int j = 0;

    for(i=0; i<TAMANHOMATRIZ; i++){
        for(j=0; j<TAMANHOMATRIZ; j++){
            if (i != j){
               for (int frequenciaI = 0; frequenciaI<totalFrequencias; frequenciaI++){
//se sim esta verifica se as restricoes de distancias foram violadas em relacao a j
                if(solucaoAtual[i][frequenciaI] == 1){
            //para cada frequencia verifica se ela está associada a celula j
                    for (int frequenciaJ=0; frequenciaJ<totalFrequencias; frequenciaJ++){
           //se sim esta verifica se as restricoes de distancias foram violadas em relacao a i e  j
                        if(solucaoAtual[j][frequenciaJ] == 1){
                            if(frequenciaI - frequenciaJ >= restricoesDistancia[i][j])
                                custo+=1;
                        }
                    }
                }
               }
            }
        }
    }
    return custo;
}
std::array<std::array<int, TOTALFREQUENCIA>, TAMANHOMATRIZ> geraSolucaoInicial
(std::array<std::array<int, TAMANHOMATRIZ>, TAMANHOMATRIZ> restricoesDistancia,
 std::array<int, TAMANHOMATRIZ> restricoesFrequencia,
 int totalFrequencias  ) {

    std::array<std::array<int, TOTALFREQUENCIA>, TAMANHOMATRIZ> solucaoInicial;
    for(int i = 0; i< TAMANHOMATRIZ; i++){
        solucaoInicial[i].fill(0);
    }
    std::vector<int> canais;
    int totalFrequenciaCelula = 0;
    int contadorQtdFrequenciasCelula = 0;
    int indice = 0;
    int melhorCusto = -1;
    int custoAtual = 0;
    int frequenciaEscolhida = 0;
    int frequencia = 0;
    #pragma omp parallel for
    for(indice = 0; indice < TAMANHOMATRIZ; indice++){
        totalFrequenciaCelula = restricoesFrequencia[indice];
        #pragma omp parallel for
        for(contadorQtdFrequenciasCelula = 0; contadorQtdFrequenciasCelula<totalFrequenciaCelula; contadorQtdFrequenciasCelula++){

            //vejo qual frequencia vou escolher
            bool encontrouFrequencia = false;
            while(!encontrouFrequencia){
                frequenciaEscolhida = geraFrequenciaAleatoria();
                if(solucaoInicial[indice][frequenciaEscolhida]!= 1){
                    solucaoInicial[indice][frequenciaEscolhida] = 1;
                    encontrouFrequencia = true;
                }
            }

        }
    }
    return solucaoInicial;

}

void heuristica(
   std::array<std::array<int, TAMANHOMATRIZ>, TAMANHOMATRIZ> restricoesDistancia,
   std::array<int, TAMANHOMATRIZ> restricoesFrequencia,
   int totalFrequencias ){

    std::array<std::array<int, TOTALFREQUENCIA>, TAMANHOMATRIZ> solucaoInicial =
        geraSolucaoInicial(restricoesDistancia,restricoesFrequencia,totalFrequencias);
    int custoSolucaoInicial = 0;
    cout << "solucao inicial: " << endl;
    teste(solucaoInicial);
    cout<< "custo: ";
    custoSolucaoInicial = calculaCusto(restricoesDistancia,solucaoInicial, totalFrequencias);
    cout << custoSolucaoInicial << endl;

    std::vector<string> listaTabu;

    int qtdIteracoes = 10000;
    int tamanhoListaTabu = 5;

    std::array<std::array<int, TOTALFREQUENCIA>, TAMANHOMATRIZ>xBest;
    std::array<std::array<int, TOTALFREQUENCIA>, TAMANHOMATRIZ>xBestLocal;
    std::array<std::array<int, TOTALFREQUENCIA>, TAMANHOMATRIZ>xAtual;
    copia(solucaoInicial,xBest);
    copia(solucaoInicial,xBestLocal);
    copia(solucaoInicial,xAtual);

    int melhorCusto = custoSolucaoInicial;
    int melhorCustoLocal = 0;
    int indiceCelula = 0;
    int frequencia = 0;
    int frequenciaCelulaSwap = 0;
    int custoIteracaoAtual = 0;
    string stringMovimento = "";

    for(int contador = 0; contador< qtdIteracoes; contador++){
        #pragma omp parallel for
        for(indiceCelula = 0; indiceCelula < TAMANHOMATRIZ; indiceCelula++){
            melhorCustoLocal = calculaCusto(restricoesDistancia,xAtual,totalFrequencias);

            for(frequencia = 0; frequencia < totalFrequencias; frequencia++){
                if(xAtual[indiceCelula][frequencia] == 1){

                    for(frequenciaCelulaSwap = 0; frequenciaCelulaSwap < totalFrequencias; frequenciaCelulaSwap++){
                        if(xAtual[indiceCelula][frequenciaCelulaSwap] == 0){

                            stringMovimento = "("+ std::to_string(indiceCelula)+","+ std::to_string(frequencia)+");("+ std::to_string(indiceCelula)+","+ std::to_string(frequenciaCelulaSwap)+")";
                            if(std::find(listaTabu.begin(), listaTabu.end(), stringMovimento) == listaTabu.end()){
                                if(listaTabu.size() > tamanhoListaTabu){
                                   listaTabu.erase(listaTabu.begin());
                                }
                                listaTabu.push_back(stringMovimento);
                                xAtual[indiceCelula][frequencia] = 0;
                                xAtual[indiceCelula][frequenciaCelulaSwap] = 1;
                                custoIteracaoAtual = calculaCusto(restricoesDistancia,xAtual,totalFrequencias);
                                if(custoIteracaoAtual < melhorCustoLocal){
                                    melhorCustoLocal = custoIteracaoAtual;
                                    copia(xAtual,xBestLocal);
                                }else{
                                   xAtual[indiceCelula][frequencia] = 1;
                                   xAtual[indiceCelula][frequenciaCelulaSwap] = 0;
                                }

                            }
                        }
                    }
                }
            }
            copia(xBestLocal,xAtual);

            if(melhorCustoLocal < melhorCusto){
                melhorCusto = melhorCustoLocal;
                copia(xBestLocal,xBest);
            }
        }
    }
    cout<< "Melhor solucao: " << endl;
    teste(xBest);
    cout<< "custo: " << melhorCusto << endl;
}

int main()
{
    srand (time(NULL));
    std::array<std::array<int, TAMANHOMATRIZ>, TAMANHOMATRIZ> restricoesDistancia;
    std::array<int, TAMANHOMATRIZ> restricoesFrequencia;
    int totalFrequencias = 0;
    std::ifstream file("restricoesDistancia.txt");

    //restricoes
    for (int i = 0; i < TAMANHOMATRIZ; ++i) {
        for (int j = 0; j < TAMANHOMATRIZ; ++j) {
            file >> restricoesDistancia[i][j];
        }
    }
    file.close();
    file.open("restricoesNumeroFrequencia.txt");
    //restricoes frequencia

    for (int i = 0; i < TAMANHOMATRIZ; ++i) {
        file >> restricoesFrequencia[i];
    }
    file.close();

    file.open("qtdFrequenciasDisponiveis.txt");
    file >> totalFrequencias;
    file.close();

    cout << totalFrequencias << endl;


    heuristica(restricoesDistancia, restricoesFrequencia, totalFrequencias);
    return 0;
}



