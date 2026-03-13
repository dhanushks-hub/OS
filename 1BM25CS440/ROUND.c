#include <stdio.h>

int main()
{
    int n, tq;
    int at[20], bt[20], rt[20];
    int wt[20], tat[20], ct[20], first[20], resp[20];
    int time = 0, remain;
    int i;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    remain = n;

    for(i = 0; i < n; i++)
    {
        printf("Enter arrival time of P%d: ", i+1);
        scanf("%d", &at[i]);

        printf("Enter burst time of P%d: ", i+1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
        first[i] = -1;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int flag;
    for(time = 0, i = 0; remain != 0;)
    {
        flag = 0;

        if(first[i] == -1)
            first[i] = time;

        if(rt[i] <= tq && rt[i] > 0)
        {
            time += rt[i];
            rt[i] = 0;
            flag = 1;
        }
        else if(rt[i] > 0)
        {
            rt[i] -= tq;
            time += tq;
        }

        if(rt[i] == 0 && flag == 1)
        {
            remain--;

            ct[i] = time;
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
            resp[i] = first[i] - at[i];

            avg_wt += wt[i];
            avg_tat += tat[i];
        }

        if(i == n - 1)
            i = 0;
        else
            i++;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], ct[i], tat[i], wt[i], resp[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt/n);

    return 0;
}
