# Simulador de Escalonamento Logístico – Armazéns Hanoi

Este projeto implementa um sistema de simulação para automatizar o processo logístico dos Armazéns Hanoi — uma rede fictícia de armazéns com regras específicas de armazenamento. A solução foi desenvolvida como parte do Trabalho Prático 2 da disciplina de Estruturas de Dados (UFMG, 2025/1).

## 📦 Objetivo

Simular o transporte de pacotes entre armazéns interconectados, respeitando restrições operacionais. O sistema acompanha cada pacote desde a postagem até a entrega final, permitindo identificar gargalos logísticos e avaliar a eficiência do fluxo de transporte.

## ⚙️ Como Funciona

- **Modelagem realista:** Cada armazém possui seções que operam com lógica *LIFO* (Last-In, First-Out), o que impacta diretamente a ordem de retirada dos pacotes.
- **Roteamento automático:** As rotas dos pacotes são calculadas com base na estrutura da rede de armazéns, modelada como um grafo não-direcionado.
- **Simulação baseada em eventos:** O tempo é tratado como uma sequência de eventos discretos, como postagem, armazenamento, transporte e entrega.
- **Fila de prioridade (MinHeap):** Utilizada para garantir o processamento dos eventos na ordem correta.

## 🧱 Estruturas de Dados Utilizadas

- `MinHeap`: para gerenciamento eficiente dos eventos futuros.
- `Pilha`: representa o armazenamento interno de cada seção dos armazéns (LIFO).
- `Fila`: auxilia na busca em largura para encontrar rotas entre armazéns.
- `Lista Encadeada`: armazena a rota de cada pacote.
- `Grafo`: modela as conexões entre os armazéns.

## 📊 Resultados Experimentais

- O desempenho do sistema piora proporcionalmente ao número de armazéns, devido ao aumento no custo de roteamento.
- Aumentar a **capacidade de transporte** reduz gargalos e melhora o tempo de entrega.
- Altas frequências de chegada de pacotes aumentam o tempo de execução devido à sobrecarga no sistema.

## 🛠️ Tecnologias

- **Linguagem:** C++
- **Paradigma:** Programação orientada a objetos
- **Compilação:** Makefile

## ▶️ Execução

Para compilar e executar o simulador:

```bash
make all
./bin/tp3.out
