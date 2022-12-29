#include <stdio.h>

void display(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("\n%d",arr[i]);
    }
}

void bubble(int arr[], int n)
{
    int temp;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-1; j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void insert(int arr[], int n)
{
    int j,temp;
    for(int i=1; i<n; i++)
    {
        j=i-1;
        while(j>=0)
        {
            if(arr[j]>arr[j+1])
            {
                temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
            j--;
        }
    }
}

int main()
{
    int pid, no;
    int arr[20];

    printf("Arr no:");
    scanf("%d",&no);

    for(int i=0; i<no; i++)
    {
        scanf("%d",&arr[i]);
    }

    pid = fork();

    if(pid==0)
    {
        printf("IN CHILD INSERT: ");
        insert(arr, no);
        display(arr, no);
    }
    else
    {
        wait();
        printf("IN PARENT BUBBLE: ");
        bubble(arr, no);
        display(arr, no);
    }

}
