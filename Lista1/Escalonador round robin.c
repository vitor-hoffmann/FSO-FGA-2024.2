#include <stdio.h>

int main() {
    int cnt, j, n, t, remain, flag = 0, tq;
    int wt = 0, tat = 0, at[201], bt[201], rt[201], pid[201];

    // Lê o número de processos
    scanf("%d", &n);

    remain = n;
    // Lê o quantum de tempo
    scanf("%d", &tq);

    // Lê os tempos de burst (ignora os tempos de chegada)
    for (cnt = 0; cnt < n; cnt++) {
        int id, burst_time;
        scanf("%d %d", &id, &burst_time);
        at[cnt] = 0;      // Define os tempos de chegada como 0
        bt[cnt] = burst_time * 1000;
        rt[cnt] = burst_time * 1000;
        pid[cnt] = id;
    }

    // Escalonador Round-Robin
    for (t = 0, cnt = 0; remain != 0;) {
        if (rt[cnt] <= tq && rt[cnt] > 0) {
            t += rt[cnt];
            rt[cnt] = 0;
            flag = 1;
        } else if (rt[cnt] > 0) {
            rt[cnt] -= tq;
            t += tq;
        }
        if (rt[cnt] == 0 && flag == 1) {
            remain--;
            printf("%d (%d)\n", pid[cnt], t); // Saída no formato esperado
            wt += t - at[cnt] - bt[cnt];
            tat += t - at[cnt];
            flag = 0;
        }
        if (cnt == n - 1) {
            cnt = 0;
        } else if (at[cnt + 1] <= t) {
            cnt++;
        } else {
            cnt = 0;
        }
    }

    return 0;
}