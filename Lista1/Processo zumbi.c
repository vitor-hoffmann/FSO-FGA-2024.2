#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t signal_count = 0; // Contador de sinais recebidos
pid_t zombie_pid = -1; // PID do processo zumbi (inicialmente inválido)

// Tratador de sinais SIGUSR1 e SIGUSR2
void signal_handler(int signum) {
    signal_count++;

    if (signal_count == 1) {
        // Cria um processo zumbi
        zombie_pid = fork();
        if (zombie_pid == 0) {
            // Processo filho sai imediatamente, tornando-se zumbi
            exit(0);
        }
    } else if (signal_count == 2 && zombie_pid > 0) {
        // Elimina o processo zumbi (recolhe o status do filho)
        waitpid(zombie_pid, NULL, 0);
        zombie_pid = -1; // Reseta o PID do zumbi
    } else if (signal_count == 3) {
        // Encerra o programa com sucesso
        exit(0);
    }
}

int main() {
    // Instala os tratadores de sinal
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    // Aguarda sinais continuamente
    while (1) {
        pause(); // Espera por sinais
    }

    return 0;
}
