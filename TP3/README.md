TP3 — Computação Paralela e Estruturas de Árvores com OpenMP

Aluno: Eduardo de Sá Abrahão
Disciplina: Programação Paralela
Ambiente: Docker + Linux + OpenMP + VI

📌 Objetivo do Trabalho

Este projeto tem como objetivo aplicar conceitos de:

Estruturas de dados em árvore
Algoritmos eficientes
Computação paralela com OpenMP
Processamento de grandes volumes de dados
Simulação de problemas reais (roteamento, busca espacial)

Todos os programas foram desenvolvidos em C, utilizando OpenMP e executados dentro de um container Docker Linux, conforme solicitado.

🐳 Ambiente de Execução
Dockerfile

O container contém:

Ubuntu 22.04
GCC
OpenMP
Make
Editor VI

Build do ambiente:

docker build -t tp3_openmp .
docker run -it -v ${PWD}:/workspace tp3_openmp

Compilação padrão:

gcc -fopenmp arquivo.c -o programa
🌳 PARTE 1 — Dicionário com Árvore AVL
Objetivo

Implementar um dicionário eficiente usando uma árvore binária balanceada (AVL).

Funcionalidades
Operação	Complexidade
Inserção	O(log n)
Busca	O(log n)
Remoção	O(log n)
Listagem	O(n)
Motivação

Uma árvore binária comum pode degenerar para lista (O(n)).
A AVL mantém o balanceamento garantindo altura logarítmica.

Teste executado

Palavras inseridas:

CPU → Processador
RAM → Memória
GPU → Placa gráfica

Saída observada:

Listagem ordenada
Busca correta
Cálculo da altura
Contagem de nós
⚡ PARTE 2 — K-Way Merge Paralelo
Problema

Ordenação externa usa k-way merge para juntar grandes arquivos ordenados.

Problema sequencial

Merge de k listas = custo alto e pouco escalável.

Solução Paralela — Merge Tree

Estratégia:

Passo	Threads	Listas
1	8	16 → 8
2	4	8 → 4
3	2	4 → 2
4	1	2 → 1

Uso de:

#pragma omp parallel for
Ganhos esperados

Complexidade total permanece O(n log k), porém com speedup proporcional ao número de threads.

🌌 PARTE 3 — Quadtree Paralela (100k partículas)
Problema

Encontrar vizinhos em simulações físicas.

Busca ingênua:

100k² = 10 bilhões de comparações ❌
Solução: QUADTREE

Divide o espaço 2D recursivamente.

Cada nó contém:

Limites espaciais
Lista de pontos
4 filhos (NW, NE, SW, SE)
Paralelização
Construção

Uso de OpenMP para inserção paralela:

#pragma omp parallel for
Desafio: concorrência

Inserção altera a árvore → uso de regiões críticas.

Otimização conceitual usada
Divisão espacial reduz drasticamente comparações
Complexidade média ≈ O(n log n)
Aplicações reais
Jogos (detecção de colisão)
Simulação de fluidos
Google Maps
Renderização 3D
🌐 PARTE 4 — Roteador de Alta Performance (Trie)
Problema

Roteadores realizam milhões de buscas de IP por segundo.

Algoritmo necessário:
Longest Prefix Match (LPM)

Exemplo:

Prefixo	Rota
192.168.0.0/16	A
192.168.1.0/24	B

IP: 192.168.1.5 → rota B (prefixo mais específico)

Estrutura usada: Trie Binária

Cada bit do IP = um nível da árvore.

Complexidade:

Operação	Complexidade
Inserção	O(32)
Busca	O(32)

Tempo constante 🚀

Resultado do teste

Busca do IP 192.168.1.5 retornou corretamente a rota mais específica.

📊 Análise de Paralelismo
Parte	Tipo de paralelismo
K-way merge	Task parallelism
Quadtree	Data + task parallelism
Trie	Estrutura otimizada (baixa latência)
Problemas tratados
Load balancing
False sharing (minimizado via divisão de listas)
Overhead de threads (uso conceitual de cutoff)
🎯 Conclusão

O trabalho demonstrou:

✔ Uso de OpenMP
✔ Estruturas de árvore avançadas
✔ Paralelização de algoritmos clássicos
✔ Aplicação em cenários reais

O uso de paralelismo mostrou-se essencial para escalabilidade e desempenho.