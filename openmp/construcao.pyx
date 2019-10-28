import numpy as np
import random 
from cython.parallel import parallel, prange
cimport openmp
from libc.stdlib cimport malloc, free, rand
import cython
from cpython cimport array
import array
class Construcao:
    
    def construcaoSolucaoInicial(self,matrizDistancia,vetorRestricaoQtdFrenquencias,numeroCanaisFrequencia):
        #incializo matriz da solucao com 0, portanto nenhuma
        #célula, possui canal(frequência)
        
        canais = list(range(0,numeroCanaisFrequencia))
        cdef int num_threads, numeroCanaisFrequenciaC = numeroCanaisFrequencia
        cdef int indice, totalFrequenciaCelula, canal, contadorQtdFrequenciasCelula
        cdef int tamanhoVetor = len(vetorRestricaoQtdFrenquencias)
        cdef int[:] vetorRestricaoQtdFrenquenciasC = vetorRestricaoQtdFrenquencias
        cdef int[:,:] solucaoInicial = np.zeros([len(matrizDistancia),numeroCanaisFrequencia],dtype = np.int32)

        with nogil, parallel(num_threads=4):
            for indice in prange(0, tamanhoVetor,1):
                totalFrequenciaCelula = vetorRestricaoQtdFrenquenciasC[indice]
                for contadorQtdFrequenciasCelula in prange(0,totalFrequenciaCelula,1):
                    #seleciono canal de frequência aleatório
                    canal = rand() % numeroCanaisFrequenciaC
                    #represento existencia de canal naquela celula
                    solucaoInicial[indice][canal] = 1

        return solucaoInicial.base


        