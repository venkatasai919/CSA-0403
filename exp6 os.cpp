#include <stdio.h>

int main() {
    int n, i, j, time = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n], pr[n], rem_bt[n], wt[n], tat[n], p[n];
    int min_pr, shortest;
    int isFound;

    for (i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
        printf("Enter Priority for Process %d: ", i + 1);
        scanf("%d", &pr[i]);
        p[i] = i + 1;
    }

    int finish_time[n];
    for (i = 0; i < n; i++)
        finish_time[i] = 0;

    while (completed != n) {
        min_pr = 9999;
        isFound = 0;
        for (i = 0; i < n; i++) {
            if (rem_bt[i] > 0 && pr[i] < min_pr) {
                min_pr = pr[i];
                shortest = i;
                isFound = 1;
            }
        }

        if (isFound == 0) {
            time++;
            continue;
        }

        rem_bt[shortest]--;
        time++;

        if (rem_bt[shortest] == 0) {
            completed++;
            finish_time[shortest] = time;
            tat[shortest] = finish_time[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
        }
    }

    float avg_wt = 0, avg_tat = 0;
    printf("\nProcess\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i], pr[i], bt[i], wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}

