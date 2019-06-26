from metaheuristica import BuscaTabu
from leituraArquivo import ManipulaArquivo
from construcao import Construcao


restricoesDistancia, restricoesNumeroFrequencia,qtdFrequenciasDisponiveis = ManipulaArquivo().inicializaVariaveis()
solucaoInicial = Construcao().construcaoSolucaoInicial(restricoesDistancia, restricoesNumeroFrequencia,qtdFrequenciasDisponiveis)

BuscaTabu().heuristica(restricoesDistancia,solucaoInicial,qtdFrequenciasDisponiveis, restricoesNumeroFrequencia)