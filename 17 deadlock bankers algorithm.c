#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int number_of_processes, number_of_resources;
int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void calculate_need() {
    for (int i = 0; i < number_of_processes; i++) {
        for (int j = 0; j < number_of_resources; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

bool is_safe() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES];
    
    for (int i = 0; i < number_of_resources; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < number_of_processes; i++) {
        finish[i] = false;
    }

    while (true) {
        bool found = false;

        for (int i = 0; i < number_of_processes; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                
                for (int j = 0; j < number_of_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int j = 0; j < number_of_resources; j++) {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            for (int i = 0; i < number_of_processes; i++) {
                if (!finish[i]) {
                    return false;
                }
            }
            return true;
        }
    }
}

bool request_resources(int process_id, int request[]) {
    for (int i = 0; i < number_of_resources; i++) {
        if (request[i] > need[process_id][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }

        if (request[i] > available[i]) {
            printf("Error: Resources are not available.\n");
            return false;
        }
    }

    for (int i = 0; i < number_of_resources; i++) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    if (is_safe()) {
        printf("Request can be granted.\n");
        return true;
    } else {
        for (int i = 0; i < number_of_resources; i++) {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
        printf("Request cannot be granted as it leads to an unsafe state.\n");
        return false;
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &number_of_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &number_of_resources);

    printf("Enter the available resources: ");
    for (int i = 0; i < number_of_resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resource matrix: \n");
    for (int i = 0; i < number_of_processes; i++) {
        for (int j = 0; j < number_of_resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the allocation resource matrix: \n");
    for (int i = 0; i < number_of_processes; i++) {
        for (int j = 0; j < number_of_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    calculate_need();

    int process_id;
    int request[MAX_RESOURCES];

    printf("Enter the process number making the request: ");
    scanf("%d", &process_id);

    printf("Enter the request for resources: ");
    for (int i = 0; i < number_of_resources; i++) {
        scanf("%d", &request[i]);
    }

    if (request_resources(process_id, request)) {
        printf("The system is in a safe state after allocation.\n");
    } else {
        printf("The system is not in a safe state after allocation.\n");
    }

    return 0;
}

