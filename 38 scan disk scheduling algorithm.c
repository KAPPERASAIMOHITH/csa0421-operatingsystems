#include <stdio.h>
#include <limits.h> // For INT_MAX

#define MAX_REQUESTS 100

int main() {
    int n, head, direction, total_seek_time = 0;
    int requests[MAX_REQUESTS], sorted_requests[MAX_REQUESTS];

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    if (n > MAX_REQUESTS) {
        printf("Error: Maximum number of requests exceeded (%d).\n", MAX_REQUESTS);
        return 1;
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk access requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        sorted_requests[i] = requests[i]; // Copy for sorting
    }

    // Sort requests (ascending order for SCAN)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted_requests[i] > sorted_requests[j]) {
                int temp = sorted_requests[i];
                sorted_requests[i] = sorted_requests[j];
                sorted_requests[j] = temp;
            }
        }
    }

    // Determine initial direction (move towards the larger requests)
    direction = head <= sorted_requests[n - 1] ? 1 : -1; // 1 for right, -1 for left

    // SCAN Simulation
    printf("\nSCAN Disk Scheduling\n");
    printf("Head starts at: %d\n", head);

    // Move head in the chosen direction until the end
    int i = 0;
    while (i < n && sorted_requests[i] <= head) {
        if (sorted_requests[i] != head) { // Skip the initial head position
            int seek_time = abs(sorted_requests[i] - head);
            total_seek_time += seek_time;
            printf("Seek from %d to %d (seek time: %d)\n", head, sorted_requests[i], seek_time);
        }
        head = sorted_requests[i];
        i++;
    }

    // Reverse direction and service remaining requests
    direction = -direction;

    // Check if there are any requests remaining in the opposite direction
    while (i < n) {
        if (sorted_requests[i] != head) { // Skip the head position again
            int seek_time = abs(sorted_requests[i] - head);
            total_seek_time += seek_time;
            printf("Seek from %d to %d (seek time: %d)\n", head, sorted_requests[i], seek_time);
        }
        head = sorted_requests[i];
        i++;
    }

    printf("Total Seek Time: %d\n", total_seek_time);

    return 0;
}

