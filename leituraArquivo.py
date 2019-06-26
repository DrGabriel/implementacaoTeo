
import numpy as np
class ManipulaArquivo:

    def inicializaVariaveis(self):
        restricoesDistancia = np.loadtxt("restricoesDistancia.txt", dtype='i', delimiter=' ')

        restricoesNumeroFrequencia = np.loadtxt("restricoesNumeroFrequencia.txt", dtype='i', delimiter=' ')

        qtdFrequenciasDisponiveis = np.loadtxt("qtdFrequenciasDisponiveis.txt", dtype='i', delimiter=' ')

        return restricoesDistancia, restricoesNumeroFrequencia, qtdFrequenciasDisponiveis