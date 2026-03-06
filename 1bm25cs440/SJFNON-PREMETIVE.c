#include <stdio.h>

struct Process {
    int pid, arrival, burst;
    int completion, turnaround, waiting;
};

void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void SJF_NonPreemptive(struct Process p[], int n) {
    sortByArrival(p, n);
    int completed = 0, current_time = 0;
    int done[n]; for (int i=0;i<n;i++) done[i]=0;
    while (completed < n) {
        int idx = -1, minBurst = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= current_time && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                idx = i;
            }
        }
        if (idx == -1) { current_time++; continue; }
        current_time += p[idx].burst;
        p[idx].completion = current_time;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        done[idx] = 1;
        completed++;
    }
}

void printTable(struct Process p[], int n) {
    float totalTAT=0, totalWT=0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
        totalTAT += p[i].turnaround;
        totalWT += p[i].waiting;
    }
    printf("\nAverage turnaround time: %fms", totalTAT/n);
    printf("\nAverage waiting time: %fms\n", totalWT/n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        scanf("%d", &p[i].arrival);
    }
    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].burst);
    }
    printf("SJF scheduling:\n");
    SJF_NonPreemptive(p, n);
    printTable(p, n);
    return 0;
}
