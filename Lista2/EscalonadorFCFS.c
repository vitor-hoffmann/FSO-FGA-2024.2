#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar um processo
typedef struct Processo {
    int id;
    int *instrucoes;
    int num_instrucoes;
    int instrucao_atual;
    struct Processo *prox;
} Processo;

// Estrutura para a fila de processos
typedef struct {
    Processo *frente, *tras;
} Fila;

// Função para criar um novo processo
Processo *criar_processo(int id, int *instrucoes, int num_instrucoes) {
    Processo *novo = (Processo *)malloc(sizeof(Processo));
    novo->id = id;
    novo->instrucoes = instrucoes;
    novo->num_instrucoes = num_instrucoes;
    novo->instrucao_atual = 0;
    novo->prox = NULL;
    return novo;
}

// Inicializa a fila
void inicializar_fila(Fila *fila) {
    fila->frente = fila->tras = NULL;
}

// Adiciona um processo ao final da fila
void enfileirar(Fila *fila, Processo *p) {
    if (!fila->tras) {
        fila->frente = fila->tras = p;
    } else {
        fila->tras->prox = p;
        fila->tras = p;
    }
    p->prox = NULL;
}

// Remove e retorna o primeiro processo da fila
Processo *desenfileirar(Fila *fila) {
    if (!fila->frente) return NULL;
    Processo *removido = fila->frente;
    fila->frente = fila->frente->prox;
    if (!fila->frente) fila->tras = NULL;
    return removido;
}

int main() {
    int N;
    scanf("%d", &N);

    int *M = (int *)malloc(N * sizeof(int));  // Array para armazenar M1, M2, ..., MN
    Processo **processos = (Processo **)malloc(N * sizeof(Processo *));
    Fila fila;
    inicializar_fila(&fila);

    for (int i = 0; i < N; i++) {
        scanf("%d", &M[i]);
    }

    // Lendo processos
    for (int i = 0; i < N; i++) {
        int *instrucoes = (int *)malloc(M[i] * sizeof(int));
        for (int j = 0; j < M[i]; j++) {
            scanf("%d", &instrucoes[j]);
        }
        processos[i] = criar_processo(i + 1, instrucoes, M[i]);
        enfileirar(&fila, processos[i]);
    }

    int tempo_atual = 0;
    while (fila.frente) {
        Processo *p = desenfileirar(&fila);

        while (p->instrucao_atual < p->num_instrucoes) {
            if (p->instrucoes[p->instrucao_atual] == 1) {
                // Se for blocante, muda para não blocante e move para o fim da fila
                p->instrucoes[p->instrucao_atual] = 0;
                enfileirar(&fila, p);
                break;
            } else {
                // Executa instrução não blocante
                tempo_atual += 10;
                p->instrucao_atual++;
            }
        }

        // Se todas as instruções foram executadas, imprime o tempo final
        if (p->instrucao_atual == p->num_instrucoes) {
            printf("%d (%d)\n", p->id, tempo_atual);
            free(p->instrucoes);
            free(p);
        }
    }

    free(M);
    free(processos);
    return 0;
}
