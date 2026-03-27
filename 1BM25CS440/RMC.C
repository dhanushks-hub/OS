#include <stdio.h>
#include <math.h>

int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}

int main()
{
    int n;
    printf("Enter the number of processes:");
    scanf("%d", &n);

    int burst[n], period[n];

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &burst[i]);

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &period[i]);

    int hyper = period[0];
    for (int i = 1; i < n; i++)
        hyper = lcm(hyper, period[i]);

    printf("LCM=%d\n\n", hyper);

    printf("Rate Monotone Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\n", i + 1, burst[i], period[i]);

    float U = 0;
    for (int i = 0; i < n; i++)
        U += (float)burst[i] / period[i];

    float bound = n * (pow(2, 1.0 / n) - 1);

    printf("\n%.6f <= %.6f => %s\n", U, bound, (U <= bound) ? "true" : "false");
    printf("Scheduling occurs for %d ms\n\n", hyper);

    int remaining[n];
    for (int i = 0; i < n; i++)
        remaining[i] = 0;

    int last = -2;

    for (int t = 0; t < hyper; t++)
    {
        for (int i = 0; i < n; i++)
        {
            if (t % period[i] == 0)
                remaining[i] = burst[i];
        }

        int selected = -1;
        int min_period = 9999;

        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0 && period[i] < min_period)
            {
                min_period = period[i];
                selected = i;
            }
        }

        if (selected != last)
        {
            if (selected == -1)
                printf("%dms onwards: CPU is idle\n", t);
            else
                printf("%dms onwards: Process %d running\n", t, selected + 1);
            last = selected;
        }

        if (selected != -1)
            remaining[selected]--;
    }

    return 0;
}


