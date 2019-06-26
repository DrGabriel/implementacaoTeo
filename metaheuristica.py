from queue import Queue
from construcao import Construcao
import numpy as np
import copy
import sys

class BuscaTabu:
    def heuristica(self,restricoesDistancia,solucaoAtual,qtdFrequenciasDisponiveis, restricoesNumeroFrequencia):
        qtdIteracoes = 10000
        #inicializo lista tabu, sem tamanho definido ainda!
        listaTabu = []
        #gero solucao inicial
        x1 = Construcao().construcaoSolucaoInicial(restricoesDistancia, restricoesNumeroFrequencia,qtdFrequenciasDisponiveis)
        print("Solucao inicial:")
        print(x1)
        
        xBest = copy.deepcopy(x1)
        #Melhor  solucao durante a exploração da vizinhança da celula
        xBestLocal = copy.deepcopy(x1)
        xAtual = copy.deepcopy(x1)
        custoInicial = self.calculaCusto(restricoesDistancia,x1,qtdFrequenciasDisponiveis)
        print("Custo inicial:")
        print(custoInicial)
        custoIteracaoAtual = 0
        #coloco um numero muito grande para nas proximas iteracoes ele ser reduzido
        melhorCusto = custoInicial
        contador = 0
        while contador < qtdIteracoes:
            
            

            #para cada célula, tento dar um swap
            for indiceCelula in range(0,len(restricoesDistancia)):
                #Melhor valor de custo durante a exploração da vizinhança da celula
                #Isso é feito para ser possível explorar todo o espaço de busca
                #E não ficar preso em um vale que possui uma solução muito boa
                melhorCustoLocal = self.calculaCusto(restricoesDistancia,xAtual,qtdFrequenciasDisponiveis)
                for frequencia in range (0,qtdFrequenciasDisponiveis):
                    #Se possuo frequencia alocada, tento trocar
                    if(xAtual[indiceCelula][frequencia] == 1):
                            for frequenciaCelulaSwap in range (0,qtdFrequenciasDisponiveis):
                                if(xAtual[indiceCelula][frequenciaCelulaSwap] == 0):
                                    #movimento de swap amarzenado na lista tabu
                                    #tabulist = (indiceCelula,fx);(indiceCelula,fy)
                                    stringMovimento = "("+str(indiceCelula)+","+str(frequencia)+");("+str(indiceCelula)+","+str(frequenciaCelulaSwap)+")"
                                    if stringMovimento not in listaTabu:
                                        #coloco movimento na lista tabu
                                        listaTabu.append(stringMovimento) 
                                        #faco swap
                                        xAtual[indiceCelula][frequencia] = 0
                                        xAtual[indiceCelula][frequenciaCelulaSwap] = 1
                                        custoIteracaoAtual = self.calculaCusto(restricoesDistancia,xAtual,qtdFrequenciasDisponiveis)
                                        if(custoIteracaoAtual < melhorCustoLocal):
                                            melhorCustoLocal = custoIteracaoAtual
                                            xBestLocal = copy.deepcopy(xAtual)
                                        else:
                                            #desfaz swap
                                            xAtual[indiceCelula][frequencia] = 1
                                            xAtual[indiceCelula][frequenciaCelulaSwap] = 0

                #atualizo xAtual com o melhor x local
                xAtual = copy.deepcopy(xBestLocal)

                #atualizo melhor solucao local encontrada em todo o espaco de busca
                if(melhorCustoLocal < melhorCusto):
                    melhorCusto = melhorCustoLocal
                    xBest = copy.deepcopy(xBestLocal)

            #atualizo iteracao
            contador += 1

        print("Melhor solucao:")
        print(xBest)  
        print("Custo melhor solucao:")
        print(melhorCusto)   
                    
                
            
    def calculaCusto(self,matrizRestricaoDistancia,solucaoAtual,qtdFrequencias):
        totalCelulasTelefone = len(matrizRestricaoDistancia)
        custo = 0
        #para cada uma das restricoes entre duas celulas verifica se ela foi violada
        for i in range(0,totalCelulasTelefone):
            for j in range(0,totalCelulasTelefone):
                if (i != j):
        #para cada frequencia verifica se ela está associada a celula i
                    for frequenciaI in range (0,qtdFrequencias):
        #se sim esta verifica se as restricoes de distancias foram violadas em relacao a j
                        if(solucaoAtual[i][frequenciaI] == 1):
        #para cada frequencia verifica se ela está associada a celula j
                            for frequenciaJ in range (0,qtdFrequencias):
        #se sim esta verifica se as restricoes de distancias foram violadas em relacao a i e  j
                                if(solucaoAtual[j][frequenciaJ] == 1):
                                    if(frequenciaI - frequenciaJ >= matrizRestricaoDistancia[i][j]):
        #aumento o custo caso a restrição seja violada
                                        custo+=1
        return custo