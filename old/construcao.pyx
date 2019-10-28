import numpy as np
import random 
class Construcao:
    
    def construcaoSolucaoInicial(self,matrizDistancia,vetorRestricaoQtdFrenquencias,numeroCanaisFrequencia):
        #incializo matriz da solucao com 0, portanto nenhuma
        #célula, possui canal(frequência)
        solucaoInicial = np.zeros([len(matrizDistancia),numeroCanaisFrequencia],dtype = int)
        canais = list(range(0,numeroCanaisFrequencia))

        for indice in range(0,len(vetorRestricaoQtdFrenquencias)):
            totalFrequenciaCelula = vetorRestricaoQtdFrenquencias[indice]
            for contadorQtdFrequenciasCelula in range(0,totalFrequenciaCelula):
                #seleciono canal de frequência aleatório
                canal = random.choice(canais)
                #represento existencia de canal naquela celula
                solucaoInicial[indice][canal] = 1

        return solucaoInicial


        