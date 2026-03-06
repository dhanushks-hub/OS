#include <stdio.h>

int main() {
    int n, i, j, time = 0, min, idx;
    int at[20], bt[20], ct[20], tat[20], wt[20], done[20] = {0};
    float avgwt = 0, avgtat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    int completed = 0;

    while(completed < n) {
        min = 9999;
        idx = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && done[i] == 0) {
                if(bt[i] < min) {
                    min = bt[i];
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            avgwt += wt[idx];
            avgtat += tat[idx];
            done[idx] = 1;
            completed++;
        } else {
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avgwt / n);
    printf("Average Turnaround Time: %.2f\n", avgtat / n);

    return 0;
}
