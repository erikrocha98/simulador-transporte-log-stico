# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -g -std=c++11

# Diretórios
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCDIR = include

# Nome do executável
TARGET = $(BINDIR)/tp2.out

# Lista de arquivos fonte
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Lista de arquivos objeto
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Regra principal
all: directories $(TARGET)

# Criar diretórios se não existirem
directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

# Linkar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Limpar arquivos compilados
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)

# Limpar tudo (incluindo diretórios)
cleanall:
	rm -rf $(OBJDIR) $(BINDIR)

# Executar o programa com arquivo de teste
run: all
	./$(TARGET) entrada.txt

# Recompilar tudo
rebuild: clean all

# Indica que estas regras não são arquivos
.PHONY: all clean cleanall run rebuild directories

# Dependências específicas (se necessário)
$(OBJDIR)/main.o: $(INCDIR)/motorSimulacao.hpp
$(OBJDIR)/motorSimulacao.o: $(INCDIR)/motorSimulacao.hpp $(INCDIR)/escalonador.hpp $(INCDIR)/armazem.hpp $(INCDIR)/pacote.hpp $(INCDIR)/transporte.hpp $(INCDIR)/grafoListaAdjacencia.hpp
$(OBJDIR)/escalonador.o: $(INCDIR)/escalonador.hpp $(INCDIR)/minHeap.hpp
$(OBJDIR)/armazem.o: $(INCDIR)/armazem.hpp $(INCDIR)/pilha.hpp $(INCDIR)/pacote.hpp
$(OBJDIR)/pacote.o: $(INCDIR)/pacote.hpp $(INCDIR)/listaEncadeada.hpp
$(OBJDIR)/transporte.o: $(INCDIR)/transporte.hpp
$(OBJDIR)/grafoListaAdjacencia.o: $(INCDIR)/grafoListaAdjacencia.hpp $(INCDIR)/listaEncadeada.hpp
$(OBJDIR)/listaEncadeada.o: $(INCDIR)/listaEncadeada.hpp
$(OBJDIR)/pilha.o: $(INCDIR)/pilha.hpp $(INCDIR)/pacote.hpp
$(OBJDIR)/minHeap.o: $(INCDIR)/minHeap.hpp