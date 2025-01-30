#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int pid;            // Identificador do processo
    int time_left;      // Tempo restante para execução (em milissegundos)
    struct Node *next;  // Próximo nó (para lista circular)
} Node;

// Função para criar um novo nó
Node* create_node(int pid, int time_left) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->pid = pid;
    new_node->time_left = time_left;
    new_node->next = NULL;
    return new_node;
}

// Função para adicionar um nó à lista circular
Node* add_to_list(Node* tail, int pid, int time_left) {
    Node* new_node = create_node(pid, time_left);
    if (tail == NULL) {
        new_node->next = new_node; // Lista circular com um único nó
        return new_node;
    }
    new_node->next = tail->next;
    tail->next = new_node;
    return new_node;
}

// Função para remover um nó da lista circular
Node* remove_from_list(Node* tail, Node* target) {
    if (tail == target && tail->next == target) {
        free(target); // Remove o único nó da lista
        return NULL;
    }

    Node* current = tail;
    while (current->next != target) {
        current = current->next;
    }
    current->next = target->next;
    if (tail == target) {
        tail = current;
    }
    free(target);
    return tail;
}

int main() {
    int n, tq;
    int total_time = 0; // Tempo total de execução

    // Lê o número de processos
    scanf("%d", &n);

    // Lê o quantum de tempo (em milissegundos)
    scanf("%d", &tq);

    // Lista circular de processos
    Node* tail = NULL;

    // Lê os processos
    for (int i = 0; i < n; i++) {
        int pid, burst_time;
        scanf("%d %d", &pid, &burst_time);
        tail = add_to_list(tail, pid, (burst_time * 1000)); // Adiciona à lista circular
    }

    // Escalonador Round-Robin
    Node* current = tail ? tail->next : NULL; // Começa pelo primeiro processo
    while (current) {
        Node* next_process = current->next; // Armazena o próximo processo antes de qualquer alteração

        if (current->time_left <= tq) {
            // Processo é finalizado neste ciclo
            total_time += current->time_left;
            printf("%d (%d)\n", current->pid, total_time); // Imprime o tempo de término do processo
            tail = remove_from_list(tail, current); // Remove o processo concluído
            if (tail == NULL) {
                current = NULL; // Lista vazia, finaliza o escalonador
            } else {
                current = next_process; // Avança para o próximo processo
            }
        } else {
            // Processo é executado parcialmente
            current->time_left -= tq;
            total_time += tq;
            current = next_process; // Avança para o próximo processo
        }
    }

    return 0;
}
