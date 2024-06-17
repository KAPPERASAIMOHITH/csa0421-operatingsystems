#include <stdio.h>

void sjn_schedule(int burst_times[], int n) {
    int wt = 0, tat = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        int shortest_job = 0;
        for (int j = 1; j < n; j++)
            if (burst_times[j] < burst_times[shortest_job])
                shortest_job = j;

        printf("%d\t%d\t\t%d\t\t%d\n", shortest_job + 1, burst_times[shortest_job], wt, wt + burst_times[shortest_job]);

        tat += wt + burst_times[shortest_job];
        wt += burst_times[shortest_job];
        burst_times[shortest_job] = 9999;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)tat / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_times[n];
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for Process %d: ", i + 1);
        scanf("%d", &burst_times[i]);
    }

    sjn_schedule(burst_times, n);

    return 0;
}

