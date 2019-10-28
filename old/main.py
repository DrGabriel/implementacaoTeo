from metaheuristica import BuscaTabu
from leituraArquivo import ManipulaArquivo
from construcao import Construcao
import time


restricoesDistancia, restricoesNumeroFrequencia,qtdFrequenciasDisponiveis = ManipulaArquivo().inicializaVariaveis()
start_time = time.time()
solucaoInicial = Construcao().construcaoSolucaoInicial(restricoesDistancia, restricoesNumeroFrequencia,qtdFrequenciasDisponiveis)
print("---tempo construindo solução inicial: %s segundos ---" % (time.time() - start_time))
start_time = time.time()
BuscaTabu().heuristica(restricoesDistancia,solucaoInicial,qtdFrequenciasDisponiveis, restricoesNumeroFrequencia)
print("---tempo executando busca tabu: %s segundos ---" % (time.time() - start_time))