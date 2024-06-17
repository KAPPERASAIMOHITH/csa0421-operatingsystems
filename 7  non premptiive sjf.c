#include <stdio.h>
typedef struct {
    int pid;         
    int burst_time;  
    int wait_time;   
    int turn_around_time;
} Process;

void calculateTimes(Process processes[], int n) {
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    processes[0].wait_time = 0;
    int total_wait_time = 0, total_turn_around_time = 0;

    
    for (int i = 1; i < n; i++) {
        processes[i].wait_time = processes[i - 1].wait_time + processes[i - 1].burst_time;
        processes[i].turn_around_time = processes[i].wait_time + processes[i].burst_time;
    }

    printf("Processes\tBurst Time\tWaiting Time\tTurn-Around Time\n");
    for (int i = 0; i < n; i++) {
        processes[i].turn_around_time = processes[i].burst_time + processes[i].wait_time;
        total_wait_time += processes[i].wait_time;
        total_turn_around_time += processes[i].turn_around_time;
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].wait_time, processes[i].turn_around_time);
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
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i + 1;
    }

    calculateTimes(processes, n);
    return 0;
}

