#ifndef CABECALHO
#define CABECALHO

#include <stdbool.h>

// Definições das macros para tempos e limites
#define TEMPSIM_AM_INICIO 390    // 6:30 AM em minutos desde meia-noite
#define TEMPSIM_AM_FIM 540       // 9:00 AM em minutos desde meia-noite
#define TEMPSIM_PM_INICIO 660    // 11:00 AM em minutos
#define TEMPSIM_PM_FIM 870       // 14:30 PM em minutos
#define TEMPSIM_NT_INICIO 1020   // 17:00 PM em minutos
#define TEMPSIM_NT_FIM 1170      // 19:30 PM em minutos

#define TEMPUSUMIN 3             // Tempo mínimo de atendimento (em segundos)
#define TEMPUSUMAX 6             // Tempo máximo de atendimento (em segundos)

#define NFILAS 3                 // Número de filas
#define QTDBANMIN 1              // Mínimo de bancadas
#define QTDBANMAX 5              // Máximo de bancadas
#define BANSERMIN 3              // Mínimo de serventes por bancada
#define BANSERMAX 6              // Máximo de serventes por bancada
#define TEMPSERMAX 60            // Tempo máximo de trabalho contínuo (em minutos)
#define TEMPSERINT 0.15          // Intervalo de descanso dos serventes (0.15 do tempo de trabalho)
#define QTDSERMIN 3              // Mínimo de serventes
#define QTSERMAX 30              // Máximo de serventes

#define NING 7                   // Número de tipos de ingredientes
#define TEMPUSUBVASILHA 10       // Tempo de substituicao de ingredientes na vasilha
#define CAPAVASILHA 5000          // Capacidade da vasilha (em gramas)

// Estrutura para representar um nó de uma fila
typedef struct no {
    int valor;                 
    struct no *proximo;       
} No;

// Estrutura para representar um servente
typedef struct {
    int id;                    // ID do servente
    bool descanso;             // Já tirou o descanso? 
    int tempoDescanso;         // Tempo de descanso restante
    int tempoTotalAtendimento; // Tempo total de atendimento acumulado
    bool isGerente;            // Se o servente é um gerente
} Servente;

// Estrutura para representar uma bancada
typedef struct {
    int id;                    // ID da bancada
    Servente* serventes;       // Lista de serventes na bancada
    int numAtendimentos;       // Número total de atendimentos realizados na bancada
    int numServentes;          // Número de serventes na bancada
    int ativa;                 // Se a bancada está ativa (1) ou desativada (0)
    bool isVegetariano;        // Se a bancada é para vegetarianos (1) ou não (0)
} Bancada;

// Estrutura para representar os ingredientes utilizados
typedef struct {
    int id;                    // ID do ingrediente
    int quantidade;            // Quantidade do ingrediente escolhido
} Ingrediente;

// Estrutura para representar um usuário
typedef struct {
    int id;                    // ID do usuário
    bool vegetariano;           // Se o usuário é vegetariano (1) ou não (0)
    int tempoEspera;           // Tempo de espera do usuário
    int filaEscolhida;         // Fila escolhida pelo usuário (1 para vegetariano, 0 para não-vegetariano)
    Ingrediente ingredientes[NING]; // Ingredientes escolhidos pelo usuário
} Usuario;

// Estrutura para representar uma vasilha de ingredientes
typedef struct {
    int id;
    int capacidade;            // Capacidade máxima da vasilha
    int tempoSubstituicao[TEMPUSUBVASILHA];    // Tempo para substituir a vasilha (em minutos)
} Vasilha;

// Funções auxiliares para manipulação de filas e simulação
Ingrediente gerarIngredientes[NING];            // Array de ingredientes
Bancada bancadas[QTDBANMAX];                    // Array de bancadas
Servente serventes[QTSERMAX];                   // Array de serventes

// Funções declaradas no arquivo cabecalho.c
void inserir_na_fila(No **fila, int num);                    // Insere um número na fila
void inicializarFilas(No* filas[], int numFilas);            // Inicializa as filas
void simularDia();                                            // Função principal de simulação do dia
Usuario gerarUsuarioAleatorio(int id);                        // Gera um usuário aleatório
int calcularTempoAtendimento();                               // Calcula o tempo de atendimento
void calculaHora(int horaAtual);                               // Calcula a hora do dia
void ativarBancada(Bancada *bancada);                         // Ativa uma bancada
void desativarBancada(Bancada *bancada);                       // Desativa uma bancada
void relatorioFinal(int numUsuariosAtendidos, Ingrediente totalIngredientesConsumidos[], 
                    Servente serventes[], int numServentes, 
                    Bancada bancadas[], int numBancadas);      // Gera o relatório final
void realizarDescanso(Servente *servente);                    // Realiza o descanso de um servente
void iniciarVasilha(Vasilha *vasilha);                        // Inicia a vasilha
#endif 