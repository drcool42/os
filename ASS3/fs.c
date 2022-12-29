#include <stdio.h>

int Total_Wait = 0,  Total_Turn = 0;


void sort(int n);
struct process
{
    char pname[10];
    int at, bt, et, st, tat, wt;

} p[10], temp;

int i, j, n;

void sort(int n)
{
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void waiting(int n)
{
    int i;
    printf("\n Waiting time of %s is %d",p[0].pname, p[0].wt);
    for (i = 1; i < n; i++)
    {
        p[i].st = p[i - 1].st + p[i - 1].bt;
        p[i].wt = p[i].st - p[i].at;
        printf("\n Waiting time of %s is %d",p[i].pname, p[i].wt);
        Total_Wait += p[i].wt;
    }
}

void turnaround(int n)
{
    int i;
    printf("\n Turnaround time of %s is %d",p[0].pname, p[0].tat);
    for (i = 1; i < n; i++)
    {
        p[i].et = p[i - 1].et + p[i].bt;
        p[i].tat = p[i].et - p[i].at;
        printf("\n Turnaround time of %s is %d",p[i].pname, p[i].tat);
        Total_Turn += p[i].tat;
    }
}

int main()
{
    int i, j, tat = 0, twt = 0, n;
    printf("enter the process no. of process:");
    scanf("%d", &n);
    printf("enter the process name:");

    for (i = 0; i < n; i++)
    {
        scanf("%s", &p[i].pname);
    }

    printf("\n Enter the burst time:");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &p[i].bt);
    }

    printf("\n Enter the Arrival time:");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &p[i].at);
    }

    sort(n);
    p[0].st = 0;
    p[0].et = p[0].bt;
    p[0].wt = 0;
    p[0].tat = p[0].et-p[0].at;
    Total_Turn += p[0].tat;
    Total_Wait += p[0].wt;

    waiting(n);
    turnaround(n);


    printf("\nTotal turn around time is %d", Total_Turn);
    printf("\nTotal waiting time is %d", Total_Wait);

    printf("\nAvg Turnaround: %.3f", (float)Total_Turn/n);
    printf("\nAvg Waiting: %.3f", (float)Total_Wait/n);

}
