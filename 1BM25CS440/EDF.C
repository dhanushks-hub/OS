#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int burst[n], deadline[n], period[n];
    int remaining[n], next_deadline[n];

    for(int i=0;i<n;i++)
    {
        printf("Task %d Burst Time: ", i+1);
        scanf("%d",&burst[i]);

        printf("Task %d Deadline: ", i+1);
        scanf("%d",&deadline[i]);

        printf("Task %d Period: ", i+1);
        scanf("%d",&period[i]);

        remaining[i]=0;
        next_deadline[i]=deadline[i];
    }

    int hyper=20;
    printf("\nPID\tBurst\tDeadline\tPeriod\n");
    for(int i=0;i<n;i++)
        printf("%d\t%d\t%d\t\t%d\n",i+1,burst[i],deadline[i],period[i]);

    printf("Scheduling occurs for %d ms\n\n",hyper);

    for(int t=0;t<hyper;t++)
    {
        for(int i=0;i<n;i++)
        {
            if(t%period[i]==0)
            {
                remaining[i]=burst[i];
                next_deadline[i]=t+deadline[i];
            }
        }

        int selected=-1;
        int min_deadline=9999;

        for(int i=0;i<n;i++)
        {
            if(remaining[i]>0 && next_deadline[i]<min_deadline)
            {
                min_deadline=next_deadline[i];
                selected=i;
            }
        }

        if(selected==-1)
            printf("%dms : CPU is idle.\n",t);
        else
        {
            printf("%dms : Task %d is running.\n",t,selected+1);
            remaining[selected]--;
        }
    }

    return 0;
}

