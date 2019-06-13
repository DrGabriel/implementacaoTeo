
import numpy as np
class ManipulaArquivo:

    def inicializaVariaveis(self):
        restricoesDistancia = np.loadtxt("restricoesDistancia.txt", dtype='i', delimiter=' ')
        print(restricoesDistancia)
        restricoesNumeroFrequencia = np.loadtxt("restricoesNumeroFrequencia.txt", dtype='i', delimiter=' ')
        print(restricoesNumeroFrequencia)   

        qtdFrequenciasDisponiveis = np.loadtxt("qtdFrequenciasDisponiveis.txt", dtype='i', delimiter=' ')
        print(qtdFrequenciasDisponiveis) 
        return restricoesDistancia, restricoesNumeroFrequencia, qtdFrequenciasDisponiveis