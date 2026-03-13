#include <stdio.h>

int main() {
    int n, i, j, pos, temp;
    int bt[20], at[20], pr[20], wt[20], tat[20], ct[20], rt[20], p[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i=0;i<n;i++){
        p[i] = i+1;

        printf("Enter priority of P%d: ", i+1);
        scanf("%d",&pr[i]);

        printf("Enter arrival time of P%d: ", i+1);
        scanf("%d",&at[i]);

        printf("Enter burst time of P%d: ", i+1);
        scanf("%d",&bt[i]);
    }

    // Sort by priority (lower number = higher priority)
    for(i=0;i<n;i++){
        pos=i;
        for(j=i+1;j<n;j++){
            if(pr[j] < pr[pos])
                pos=j;
        }

        temp=pr[i]; pr[i]=pr[pos]; pr[pos]=temp;
        temp=bt[i]; bt[i]=bt[pos]; bt[pos]=temp;
        temp=at[i]; at[i]=at[pos]; at[pos]=temp;
        temp=p[i]; p[i]=p[pos]; p[pos]=temp;
    }

    ct[0] = at[0] + bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = tat[0] - bt[0];
    rt[0] = wt[0];

    for(i=1;i<n;i++){
        ct[i] = ct[i-1] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = wt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt += wt[0];
    avg_tat += tat[0];

    printf("\nPriority Scheduling (Non-Preemptive)\n");
    printf("PID\tPrior\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i], pr[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Turnaround Time: %.6f", avg_tat/n);
    printf("\nAverage Waiting Time: %.6f\n", avg_wt/n);

    return 0;
}
