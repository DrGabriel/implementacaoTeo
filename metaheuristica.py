import numpy as np

class BuscaTabu:
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
        print(custo)