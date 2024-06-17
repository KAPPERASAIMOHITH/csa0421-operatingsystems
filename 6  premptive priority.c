#include <stdio.h>

typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int priority;
    int arrival_time;
    int wait_time;
    int turn_around_time;
} Process;

void calculateTimes(Process processes[], int n) {
    int complete = 0, time = 0, min_priority = 10000, shortest = 0;
    int check = 0;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((processes[j].arrival_time <= time) && 
                (processes[j].priority < min_priority) && 
                (processes[j].remaining_time > 0)) {
                min_priority = processes[j].priority;
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            time++;
            continue;
        }

        processes[shortest].remaining_time--;
        min_priority = processes[shortest].priority;

        if (processes[shortest].remaining_time == 0) {
            min_priority = 10000;
            complete++;
            check = 0;
            int finish_time = time + 1;
            processes[shortest].wait_time = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;
            processes[shortest].turn_around_time = finish_time - processes[shortest].arrival_time;

            if (processes[shortest].wait_time < 0)
                processes[shortest].wait_time = 0;
        }
        time++;
    }
}

void printAverageTimes(Process processes[], int n) {
    calculateTimes(processes, n);

    int total_wait_time = 0, total_turn_around_time = 0;
    printf("Processes\tPriority\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n");
    
    for (int i = 0; i < n; i++) {
        total_wait_time += processes[i].wait_time;
        total_turn_around_time += processes[i].turn_around_time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].priority, processes[i].burst_time, processes[i].arrival_time, processes[i].wait_time, processes[i].turn_around_time);
    }

    printf("Average waiting time = %.2f\n", (float)total_wait_time / n);
    printf("Average turn around time = %.2f\n", (float)total_turn_around_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time, arrival time and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].burst_time, &processes[i].arrival_time, &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printAverageTimes(processes, n);
    return 0;
}

