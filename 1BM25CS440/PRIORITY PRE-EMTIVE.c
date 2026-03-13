#include <stdio.h>

int main() {
    int n, i, time = 0, smallest;
    int bt[20], at[20], pr[20], rt[20];
    int wt[20], tat[20], ct[20], response[20];
    int completed = 0;
    int min = 9999;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("Enter arrival time P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Enter burst time P%d: ",i+1);
        scanf("%d",&bt[i]);

        printf("Enter priority P%d: ",i+1);
        scanf("%d",&pr[i]);

        rt[i] = bt[i];
        response[i] = -1;
    }

    while(completed != n){

        smallest = -1;
        min = 9999;

        for(i=0;i<n;i++){
            if(at[i] <= time && rt[i] > 0 && pr[i] < min){
                min = pr[i];
                smallest = i;
            }
        }

        if(smallest == -1){
            time++;
            continue;
        }

        if(response[smallest] == -1)
            response[smallest] = time - at[smallest];

        rt[smallest]--;
        time++;

        if(rt[smallest] == 0){
            completed++;

            ct[smallest] = time;
            tat[smallest] = ct[smallest] - at[smallest];
            wt[smallest] = tat[smallest] - bt[smallest];

            avg_wt += wt[smallest];
            avg_tat += tat[smallest];
        }
    }

    printf("\nPriority Scheduling (Preemptive)\n");
    printf("PID\tPrior\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,pr[i],at[i],bt[i],ct[i],tat[i],wt[i],response[i]);
    }

    printf("\nAverage turnaround time: %.6f", avg_tat/n);
    printf("\nAverage waiting time: %.6f\n", avg_wt/n);

    return 0;
}
