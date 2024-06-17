#include <stdio.h>
typedef struct {
    int pid;       
    int burst_time;
    int remaining_time;
} Process;

void roundRobinScheduling(Process processes[], int n, int quantum) {
    int time = 0; 
    int remaining_processes = n;    
    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > quantum) {
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                    printf("Process %d executed for %d units.\n", processes[i].pid, quantum);
                } else {
                    time += processes[i].remaining_time;
                    printf("Process %d executed for %d units.\n", processes[i].pid, processes[i].remaining_time);
                    processes[i].remaining_time = 0;
                    remaining_processes--;
                    printf("Process %d finished at time %d.\n", processes[i].pid, time);
                }
            }
        }
    }
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];    
    for (int i = 0; i < n; i++) {
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);    
    roundRobinScheduling(processes, n, quantum);
    return 0;
}

