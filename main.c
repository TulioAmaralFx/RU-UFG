#include "cabecalho.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inicializarFilas(No* filas[], int numFilas) {
    for (int i = 0; i < numFilas; i++) {
        filas[i] = NULL;  
    }
}

void inserir_na_fila(No **fila, int num) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    novoNo->valor = num;
    novoNo->proximo = NULL;

    if (*fila == NULL) {
        *fila = novoNo;
    } else {
        No* temp = *fila;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoNo;
    }
}

No* remover_da_fila(No **fila) {
    if (*fila == NULL) {
        return NULL;  
    }
    No* removido = *fila;
    *fila = (*fila)->proximo; 
    return removido;  
}

void criarServente(Servente *s, int id){
    s->id = id;
    s->descanso = false;
    s->tempoDescanso = 0;
    s->tempoTotalAtendimento = 0;
    s->isGerente = rand() % 2;  
}

void alocarServentesNaBancada(Bancada *bancada) {
    int numServentes = rand() % (BANSERMAX - BANSERMIN + 1) + BANSERMIN;
    bancada->serventes = (Servente*) malloc(numServentes * sizeof(Servente));
    bancada->numServentes = numServentes;

    for (int i = 0; i < numServentes; i++) {
        criarServente(&bancada->serventes[i], i + 1); // ID dos serventes começa em 1
    }
    bancada->numAtendimentos = 0; // Inicializa o número de atendimentos
}

void iniciarTrabalho(Bancada *bancada) {
    for (int i = 0; i < bancada->numServentes; i++) {
        Servente *servente = &bancada->serventes[i];

        if (!servente->descanso) {
            // O servente pode trabalhar por até TEMPSERMAX minutos
            servente->tempoTotalAtendimento += TEMPSERMAX;
            // Se o tempo de trabalho atingir TEMPSERMAX, o servente entra em descanso
            if (servente->tempoTotalAtendimento >= TEMPSERMAX) {
                realizarDescanso(servente);
            }

        }
    }
}

void realizarDescanso(Servente *servente) {
    if (!servente->descanso) {
        servente->descanso = true;
        servente->tempoDescanso = TEMPSERINT;
        printf("Servente %d entrou em descanso por %d minutos.\n", servente->id, servente->tempoDescanso);
    }
}


// Função para calcular a hora atual
void calculaHora(int horaAtual) {
    int hora = horaAtual / 60;
    int minuto = horaAtual % 60;
    printf("Hora atual: %02d:%02d\n", hora, minuto);
}


// Função para gerar usuário aleatório
Usuario gerarUsuarioAleatorio(int id) {
    Usuario u;
    u.id = id;
    u.vegetariano = rand() % 3;  // 33,33% de chance de ser vegetariano
    u.tempoEspera = calcularTempoAtendimento();  // Calcula o tempo de atendimento
    u.filaEscolhida = u.vegetariano ? true : false;  // Se vegetariano, escolhe a fila 1, caso contrário a fila 0
    int ingredEscolhidos = NING;  // Escolhe aleatoriamente quantos ingredientes (1 a NING)

    return u;
}



// Função para calcular o tempo de atendimento aleatório
int calcularTempoAtendimento(int tempoAll) {
    
    return TEMPUSUMIN + rand() % (TEMPUSUMAX - TEMPUSUMIN + 1);  // Retorna tempo em segundos
}

// Função para ativar bancadatempoTotalAtendimento
void ativarBancada(Bancada *bancada) {
    bancada->ativa = 1;
    printf("Bancada %d ativada.\n", bancada->id);
}

// Função para desativar bancada
void desativarBancada(Bancada *bancada) {
    bancada->ativa = 0;
    printf("Bancada %d desativada.\n", bancada->id);
}
void iniciarVasilhas(Vasilha vasilha[QTDBANMAX][NING]) {
    int id = 1; // Contador global para IDs únicos de vasilhas
    for (int i = 0; i < QTDBANMAX; i++) {
        for (int j = 0; j < NING; j++) {
            vasilha[i][j].id = id++;
            vasilha[i][j].capacidade = CAPAVASILHA;
        }
    }
}

// Função para gerar o relatório final
void relatorioFinal(int numUsuariosAtendidos, Ingrediente totalIngredientesConsumidos[], Servente serventes[], int numServentes, Bancada bancadas[], int numBancadas) {
    printf("Relatório final:\n");
    printf("Número total de usuários atendidos: %d\n", numUsuariosAtendidos);


    // Relatório das bancadas

    for (int i = 0; i < numBancadas; i++) {
        if(bancadas[i].numAtendimentos==0){
            bancadas[i].ativa = false;
        }
        if(bancadas[i].ativa){
            printf("\nRelatório da Bancada %d:\n", bancadas[i].id);
            printf("Número de serventes: %d\n", bancadas[i].numServentes);
            printf("Bancada vegetariana: %s\n", bancadas[i].isVegetariano ? "Não" : "Sim");
            printf("Bancada ativa: %s\n", bancadas[i].ativa ? "Sim" : "Não");
            printf("Número total de atendimentos realizados: %d\n", bancadas[i].numAtendimentos);
            printf("-------------------------------------\n");
        }else{
            printf("\nRelatório da Bancada %d:\n", bancadas[i].id);
            printf("Bancada desativada\n");
            printf("-------------------------------------\n");
        }
    }

    // Relatório dos serventes
        for(int j = 0 ; j < numBancadas; j++){
        printf("Bancada: %d\n", bancadas[j].id);
        for (int i = 0; i < bancadas[j].numServentes; i++) {
            if(bancadas[j].serventes[i].tempoTotalAtendimento >= TEMPSERMAX){
                bancadas[j].serventes[i].descanso = true;
            }
        if(bancadas[j].ativa){
            printf("\nRelatório do Servente %d:\n", bancadas[j].serventes[i].id);
            printf("Tempo total de trabalho: %0.f minutos\n", bancadas[j].serventes[i].tempoTotalAtendimento * 0.85);
            printf("Já descansou?: %s\n", bancadas[j].serventes[i].descanso ? "Sim" : "Não");
            printf("Tempo de descanso: %0.f minutos\n", bancadas[j].serventes[i].tempoTotalAtendimento * 0.15);
            printf("-------------------------------------\n");
        }else{
            printf("\nRelatório do Servente %d:\n", bancadas[j].serventes[i].id);
            printf("Servente liberado para descanso\n");
            printf("-------------------------------------\n");
        }
    }}

    // Total consumido de cada ingrediente
    for (int i = 0; i < NING; i++) {
        if(i != 5 && i != 6){
            printf("\nIngrediente %d: %d KG consumidos\n", totalIngredientesConsumidos[i].id, totalIngredientesConsumidos[i].quantidade / 1000);
        }else if(i == 5){
            printf("\nIngrediente Carne: %d KG consumidos\n", totalIngredientesConsumidos[i].quantidade / 1000);
        }else{
            printf("\nIngrediente Especial: %d KG consumidos\n", totalIngredientesConsumidos[i].quantidade / 1000);
        }
        
    }
}
void simularDia() {
    No* filas[NFILAS];  // Criando um vetor de filas
    Vasilha vasilha[QTDBANMAX][NING];
    inicializarFilas(filas, NFILAS);  // Inicializando as filas
    iniciarVasilhas(vasilha); // Inicializando as vasilhas com 5000 gramas de cada ingrediente

    Ingrediente listaIngredientesConsumidos[NING];
    Bancada listaBancada[QTDBANMAX];
    Servente listaServente[QTSERMAX];
    Usuario listaUsuarios[500];

    int idGlobal = 1;
    int serventeIndex = 0; // Índice para preencher listaServente

      for (int i = 0; i < QTDBANMAX; i++) {
        bancadas[i].id = i + 1;  // ID das bancadas começa em 1
        bancadas[i].ativa = true;  // Ativa as bancadas inicialmente
        bancadas[i].numServentes = rand() % (BANSERMAX - BANSERMIN + 1) + BANSERMIN;  // Número aleatório de serventes
        bancadas[i].isVegetariano = rand() % 2;  // 50% de chance de ser vegetariano

        // Aloca memória para os serventes da bancada
        bancadas[i].serventes = (Servente*)malloc(sizeof(Servente) * bancadas[i].numServentes);
        for (int j = 0; j < bancadas[i].numServentes; j++) {
            bancadas[i].serventes[j].id = idGlobal++;  // ID dos serventes começa em 1
            bancadas[i].serventes[j].tempoTotalAtendimento = 0;  // Inicializa tempo total de atendimento
            bancadas[i].serventes[j].descanso = false;  // Inicializa estado de descanso
            bancadas[i].serventes[j].tempoDescanso = 0 ;  // Inicializa tempo de descanso
            bancadas[i].serventes[j].isGerente = rand() % 2;  // 50% de chance de ser gerente
            // Preenche o vetor listaServente com todos os serventes das bancadas
            if (serventeIndex < QTSERMAX) {
                listaServente[serventeIndex++] = bancadas[i].serventes[j];
            }

        }


        // Preenche a listaBancada com todas as bancadas
        listaBancada[i] = bancadas[i];

    }

    int horaAtual = TEMPSIM_AM_INICIO;
    while (horaAtual < TEMPSIM_NT_FIM) {
        if (horaAtual == TEMPSIM_AM_FIM) {
            printf("Finalizado o período da manhã.\nIniciando o período da tarde.\n");
            horaAtual = TEMPSIM_PM_INICIO;
        } else if (horaAtual == TEMPSIM_PM_FIM) {
            printf("Finalizado o período da tarde.\nIniciando o período da noite.\n");
            horaAtual = TEMPSIM_NT_INICIO;  // Ajuste para iniciar o jantar
        }
        
        int numUsuarios = rand() % 101 + 1;  // Número aleatório de usuários para a hora
        for (int i = 1; i <= numUsuarios; i++) {

            Usuario user = gerarUsuarioAleatorio(i);
            listaUsuarios[i] = user;
            printf("Usuário %d chegou. Vegetariano: %d, Tempo de Atendimento: %d minutos\n", 
                   user.id, user.vegetariano, user.tempoEspera);

            bancadas[i].numAtendimentos += 1;

            for (int i = 0; i < QTDBANMAX; i++) {
            for (int j = 0; j < bancadas[i].numServentes; j++) {
                if (i < numUsuarios) {
                    listaBancada[i].serventes[j].tempoTotalAtendimento += listaUsuarios[i].tempoEspera;
                }
            }
        }

            // Determina a fila com base no tipo do usuário
            if (user.vegetariano) {
                inserir_na_fila(&filas[0], user.id);  // Fila de vegetarianos
            } else {
                inserir_na_fila(&filas[1], user.id);  // Fila de não-vegetarianos

            }
            horaAtual += user.tempoEspera;  // Atualiza o horário
        }

        // Processar as filas separadas
        printf("Atendendo a fila de vegetarianos:\n");
        while (filas[0] != NULL) {
            No* atendido = remover_da_fila(&filas[0]);
            // Simular atendimento
            printf("\nAtendendo o usuário %d da fila de vegetarianos\n", atendido->valor);
            // Simula a escolha de ingredientes
            for (int i = 1; i <= NING; i++) {
                int chance = rand () % 100;
                int quantidadeIngredientes = rand() % 101 + 100;
                if(chance < 70 && i != 6){
                    if(i == 7)
                        {
                            quantidadeIngredientes = rand() % 71 + 30;
                            printf("Ingrediente Especial: ");
                        }else{
                            printf("Ingrediente escolhido: %d ", i);
                        }
                    printf("Quantidade do ingrediente (em gramas): %d g\n", quantidadeIngredientes);
                    listaIngredientesConsumidos[i-1].id = i;
                    listaIngredientesConsumidos[i-1].quantidade += quantidadeIngredientes;
                    listaBancada[i].numAtendimentos += 1;
                }else{
                    quantidadeIngredientes = 0;
                    listaIngredientesConsumidos[i-1].id = i;
                    listaIngredientesConsumidos[i-1].quantidade += quantidadeIngredientes;
                    listaBancada[i].numAtendimentos += 1;
                }
                
            }


            printf("\n");
            free(atendido);  // Liberar a memória alocada
        }

        printf("\nAtendendo a fila de não-vegetarianos:\n");
        while (filas[1] != NULL) {
            No* atendido = remover_da_fila(&filas[1]);
            // Simular atendimento
            printf("\nAtendendo o usuário %d da fila de não-vegetarianos\n", atendido->valor);
            // Simula a escolha de ingredientes
            for (int i = 1; i <= NING; i++) {
                int chance = rand () % 100;
                int quantidadeIngredientes = rand() % 101 + 100;
                if((chance < 70 && i != 7) || i == 6){
                    if(i == 6)
                    {
                        printf("Ingrediente carne: ");
                        quantidadeIngredientes = rand() % 71 + 30;
                    }else{
                        printf("Ingrediente escolhido: %d ", i);
                    }
                    
                    printf("Quantidade do ingrediente (em gramas): %d g\n", quantidadeIngredientes);
                    listaIngredientesConsumidos[i-1].id = i;
                    listaIngredientesConsumidos[i-1].quantidade += quantidadeIngredientes;
                    listaBancada[i].numAtendimentos += 1;
                }else{
                    quantidadeIngredientes = 0;
                    listaIngredientesConsumidos[i-1].id = i;
                    listaIngredientesConsumidos[i-1].quantidade += quantidadeIngredientes;
                    listaBancada[i].numAtendimentos += 1;
                }

            }

            printf("\n");
            free(atendido);  // Liberar a memória alocada
        }
    }
    int numUsuariosTotal = 0;  // Número total de usuários atendidos
    for(int i = 0; i < QTDBANMAX; i++){
        numUsuariosTotal += listaBancada[i].numAtendimentos;
    }

    // Relatório final
        relatorioFinal(numUsuariosTotal, listaIngredientesConsumidos, listaServente, QTSERMAX, listaBancada, QTDBANMAX);

    for (int i = 0; i < QTDBANMAX; i++) {
    free(bancadas[i].serventes);
    }
    }

// Função principal
int main() {
    // Inicialização do gerador de números aleatórios
    srand(time(NULL));

    printf("Iniciando simulação do restaurante...\n");

    // Simulação de um dia de funcionamento do restaurante
    simularDia();

    return 0;
}