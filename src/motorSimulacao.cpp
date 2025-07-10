#include "motorSimulacao.hpp"
#include <sstream>
#include <climits>


// Implementação do VetorEstatico

VetorEstatico ::VetorEstatico()
{
    tamanho = 0;
}

Pacote *VetorEstatico::GetItem(int pos)
{
    if ((pos >= tamanho) || (pos < 0))
        throw "ERRO: Posicao Invalida!";
    return pacotes[pos];
}

int VetorEstatico :: GetTamanho(){
    return tamanho;
}

void VetorEstatico::InsereFinal(Pacote* item)
{
    if (tamanho == MAXTAM)
        throw "ERRO: Lista cheia!";
    pacotes[tamanho] = item;
    tamanho++;
};

Pacote* VetorEstatico::RemoveFinal()
{
    Pacote* aux;
    if (tamanho == 0)
        throw "ERRO: Lista vazia!";
    tamanho--;
    aux = pacotes[tamanho];
    return aux;
}

void VetorEstatico::Limpa()
{
    tamanho = 0;
};

/*----------------------------------------------------------------------------------------------------------------------------------*/

Simulacao::Simulacao(DadosSimulacao *dados)
{
    this->dados = dados;
    this->escalonador = new Escalonador(100000);
    this->relogioAtual = 0;
}

Simulacao ::Simulacao()
{
    this->dados = nullptr;
    this->escalonador = nullptr;
    this->transporte = nullptr;
    this->relogioAtual = 0;
}

Simulacao::~Simulacao()
{
    delete escalonador;
    delete transporte;
}

long long Simulacao::criarChavePacote(int tempo, int idPacote)
{
    return (long long)tempo * 1000000000LL + idPacote * 100LL + 1LL;
}

long long Simulacao::criarChaveTransporte(int tempo, int origem, int destino)
{
    return (long long)tempo * 1000000000LL + origem * 10000LL + destino * 100LL + 2LL;
}


void Simulacao::inicializarEventosTransporte()
{
    int tempoEvento = dados->intervaloTransportes + dados->custoRemocao + tempoPrimeiroPacote;
    // Para cada ligação entre dois armazéns
    for (int i = 0; i < dados->numArmazens; i++)
    {
        for (int j = 0; j < dados->numArmazens; j++)
        {
            if (i != j && dados->grafo->ExisteAresta(i, j))
            {
                // Cria evento de transporte inicial no tempo 0 + intervalo
                DadosTransporte *dt = new DadosTransporte{i, j};
                long long chave = criarChaveTransporte(tempoEvento, i, j);
                
                escalonador->InsereEvento(chave, tempoEvento,dt, 2);
                
            }
            
        }
    }
}

void Simulacao::inicializarEventosPacotes()
{
    // Para cada pacote a ser transportado
    for (int i = 0; i < dados->numPacotes; i++)
    {
        Pacote *p = dados->pacotes[i];

        // Calcula e armazena a rota do pacote
        ListaEncadeada *rota = dados->grafo->CalculaMenorCaminho(
            p->getArmazemOrigem(),
            p->getArmazemDestino());

        if (rota == nullptr)
        {
            std::cout << "ERRO: Rota é NULL!" << std::endl;
            continue;
        }

        if (rota->getTamanho() == 0)
        {
            std::cerr << "  ERRO: Rota calculada está vazia!" << std::endl;
            continue;
        }

        p->definirRota(rota);

        // Escalona a chegada de pacotes nos armazéns de postagem
        long long chave = criarChavePacote(p->getTempoChegada(), p->getId());
        
        escalonador->InsereEvento(chave, p->getTempoChegada(),p, 1);
    }
}

void Simulacao::processarEventoPacote(HeapItem *evento)
{
    Pacote *pacote = (Pacote *)evento->dados;

    if (pacote->chegouNoDestino())
    {
        pacote->atualizarEstado(ENTREGUE);

        char buffer[100];
        sprintf(buffer, "%07d pacote %03d entregue em %03d",
                relogioAtual, pacote->getId(), pacote->getArmazemAtual());
        std::cout << buffer << std::endl;
    }
    else
    {
        // Armazena o pacote na respectiva seção
        int proximoDestino = pacote->proximoDestino();
        int armazemAtual = pacote->getArmazemAtual();

        // DEBUG
        if (proximoDestino == -1)
        {
            std::cerr << "ERRO: Pacote " << pacote->getId()
                      << " não tem próximo destino válido no armazém "
                      << armazemAtual << std::endl;
            return;
        }

        // Encontrar qual seção corresponde ao próximo destino
        int secao = dados->armazens[armazemAtual]->encontrarSecao(proximoDestino);

        dados->armazens[armazemAtual]->armazenarPacote(pacote, proximoDestino);
        pacote->atualizarEstado(ARMAZENADO);

        // DEBUG
        if (secao == -1)
        {
            std::cerr << "ERRO: Não foi possível encontrar seção para destino "
                      << proximoDestino << " no armazém " << armazemAtual
                      << "\nVerifique se existe conexão entre os armazéns." << std::endl;
            return;
        }

        char buffer[100];
        sprintf(buffer, "%07d pacote %03d armazenado em %03d na secao %03d",
                relogioAtual, pacote->getId(), armazemAtual, secao);
        std::cout << buffer << std::endl;
    }
}

void Simulacao::processarEventoTransporte(HeapItem *evento)
{
    DadosTransporte *dt = (DadosTransporte *)evento->dados;
    int origem = dt->origem;
    int destino = dt->destino;

    int secao = dados->armazens[origem]->encontrarSecao(destino);

    if (secao != -1 && !dados->armazens[origem]->secaoVazia(secao))
    {
        int capacidade = transporte->getCapacidade();

        // 1. Remover TODOS os pacotes da seção
        VetorEstatico todosOsPacotes;
        while (!dados->armazens[origem]->secaoVazia(secao))
        {
            Pacote *p = dados->armazens[origem]->removerPacote(secao);
            todosOsPacotes.InsereFinal(p);
        }

        // 2. Separar pacotes para transporte e rearmazenamento
        VetorEstatico pacotesParaTransporte;
        VetorEstatico pacotesParaRearmazenar;

        int pacotesTransportados = 0;
        // Processar de trás para frente (mais antigos primeiro)
        for (int i = todosOsPacotes.GetTamanho() - 1; i >= 0; i--)
        {
            Pacote *p = todosOsPacotes.GetItem(i);
            if (p->proximoDestino() == destino && pacotesTransportados < capacidade)
            {
                pacotesParaTransporte.InsereFinal(p);
                pacotesTransportados++;
            }
            else
            {
                pacotesParaRearmazenar.InsereFinal(p);
            }
        }

        // 3. Imprimir todas as remoções em ordem cronológica
        int tempoAtual = relogioAtual;

        // Imprimir do mais antigo (fundo da pilha) para o mais recente (topo)
        for (int i = 0; i < todosOsPacotes.GetTamanho(); i++)
        {
            Pacote *p = todosOsPacotes.GetItem(i);
            
            printf("%07d pacote %03d removido de %03d na secao %03d\n",
                tempoAtual, p->getId(), origem, secao);
                tempoAtual += dados->custoRemocao;
            }

        // Tempo final após todas as remoções
        int tempoFinalRemocao = relogioAtual + (dados->custoRemocao * todosOsPacotes.GetTamanho());

        // 4. Imprimir transportes
        for (int i=0; i<pacotesParaTransporte.GetTamanho();i++)
        {
            
            Pacote* p = pacotesParaTransporte.GetItem(i);
            printf("%07d pacote %03d em transito de %03d para %03d\n",
                   tempoFinalRemocao - dados->custoRemocao, p->getId(), origem, destino);

            p->avancarNaRota();
            int tempoChegada = tempoFinalRemocao + transporte->getLatencia() - dados->custoRemocao;
            long long chave = criarChavePacote(tempoChegada, p->getId());
            /* std::cout<<"Chave Pacote Após Inicialização: "<<chave <<std::endl; */
            escalonador->InsereEvento(chave, tempoChegada,p, 1);
        }

        // 5. Imprimir rearmazenamentos
        for (int i = 0; i < pacotesParaRearmazenar.GetTamanho(); i++)
        {
            Pacote* p = pacotesParaRearmazenar.GetItem(i);
            dados->armazens[origem]->armazenarPacote(p, p->proximoDestino());

            printf("%07d pacote %03d rearmazenado em %03d na secao %03d\n",
                   tempoFinalRemocao-dados->custoRemocao, p->getId(), origem, secao);
        }
    }

    // Agendar próximo transporte
    int proximoTempo = relogioAtual + transporte->getIntervalo();
    long long chave = criarChaveTransporte(proximoTempo, origem, destino);
    
    DadosTransporte *novoDt = new DadosTransporte{origem, destino};
    escalonador->InsereEvento(chave, proximoTempo,novoDt, 2);

    delete dt;
}

bool Simulacao::todasSecoesVazias()
{
    for (int i = 0; i < dados->numArmazens; i++)
    {
        for (int j = 0; j < dados->armazens[i]->getNumConexoes(); j++)
        {
            if (!dados->armazens[i]->secaoVazia(j))
            {
                return false;
            }
        }
    }
    return true;
}

void Simulacao::executar()
{
    // Encontra o tempo de chegada do primeiro pacote antes de inicializar eventos
    tempoPrimeiroPacote = INT_MAX;
    for (int i = 0; i < dados->numPacotes; i++)
    {
        if (dados->pacotes[i]->getTempoChegada() < tempoPrimeiroPacote)
        {
            tempoPrimeiroPacote = dados->pacotes[i]->getTempoChegada();
        }
    }
    this->transporte = new Transporte(
        dados->capacidadeTransporte,
        dados->latenciaTransporte ,
        dados->intervaloTransportes);
    
    // Inicializa eventos
    inicializarEventosPacotes();
    inicializarEventosTransporte();

    // Loop principal
    while (!escalonador->Vazio() || !todasSecoesVazias())
    {
        if (escalonador->Vazio())
            break;

        // Remove o próximo evento
        HeapItem *evento = escalonador->RetiraProximoEvento();
        if (evento == nullptr)
            break;

        // Avança o relógio
        relogioAtual = evento->tempo;

        // Condição de parada: Tempo máximo atingido
        if (relogioAtual > TEMPO_MAXIMO_SIMULACAO)
        {
            delete evento;
            break;
        }

        // Processa evento baseado no tipo
        if (evento->tipo == 1)
        {
            processarEventoPacote(evento);
        }
        else if (evento->tipo == 2)
        {
            processarEventoTransporte(evento);
        }

        delete evento;
    }
}

DadosSimulacao *Simulacao::lerArquivoEntrada(const char *nomeArquivo)
{
    DadosSimulacao *dados = new DadosSimulacao();
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir arquivo!" << std::endl;
        return nullptr;
    }

    // Lê parâmetros
    arquivo >> dados->capacidadeTransporte;
    arquivo >> dados->latenciaTransporte;
    arquivo >> dados->intervaloTransportes;
    arquivo >> dados->custoRemocao;

    // Lê número de armazéns
    arquivo >> dados->numArmazens;

    // Cria grafo e armazéns
    dados->grafo = new GrafoListaAdjacencia();
    dados->armazens = new Armazem *[dados->numArmazens];

    // Insere vértices
    for (int i = 0; i < dados->numArmazens; i++)
    {
        dados->grafo->InsereVertice();
    }

    // Lê matriz de adjacência e converte para lista de adjacência
    for (int i = 0; i < dados->numArmazens; i++)
    {
        for (int j = 0; j < dados->numArmazens; j++)
        {
            int valor;
            arquivo >> valor;
            if (valor == 1 && i < j)
            {
                dados->grafo->InsereAresta(i, j);
            }
        }
    }

    // Cria armazéns

    for (int i = 0; i < dados->numArmazens; i++)
    {
        dados->armazens[i] = new Armazem(i, dados->numArmazens);

        //Configura Conexões baseado na matriz de adjacência.
        for (int j = 0; j < dados->numArmazens; j++)
        {
            if (i != j && dados->grafo->ExisteAresta(i, j))
            {
                dados->armazens[i]->configurarConexaoArmazens(j, j);
            }
        }
    }

    // Lê pacotes
    arquivo >> dados->numPacotes;
    dados->pacotes = new Pacote *[dados->numPacotes];

    std::string linha;
    std::getline(arquivo, linha);

    for (int i = 0; i < dados->numPacotes; i++)
    {
        std::getline(arquivo, linha);
        std::istringstream iss(linha);

        int tempo, id, origem, destino;
        std::string pac, org, dst;

        iss >> tempo >> pac >> id >> org >> origem >> dst >> destino;

        dados->pacotes[i] = new Pacote(i, tempo, origem, destino);
    }

    arquivo.close();
    return dados;
}