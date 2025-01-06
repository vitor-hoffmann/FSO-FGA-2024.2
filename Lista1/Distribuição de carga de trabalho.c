#include <stdio.h>
#include <pthread.h>

// Variáveis globais
int count = 0; // Contador global
pthread_mutex_t mut; // Mutex para proteger o contador

// Struct para os argumentos da thread
struct thread_arg {
    int vezes; // Número de vezes que a thread deve chamar work
};

// Função executada por cada thread
void *thread_func(void *arg) {
    struct thread_arg *t_arg = (struct thread_arg *)arg;

    for (int i = 0; i < t_arg->vezes; i++) {
        int id;

        // Protege o acesso ao contador com o mutex
        pthread_mutex_lock(&mut);
        id = count; // Obtém o próximo identificador único
        count++; // Incrementa o contador global
        pthread_mutex_unlock(&mut);

        // Chama a função work fora da região crítica
        work(id);
    }

    return NULL;
}

