#include <stdio.h>
#include <limits.h> // For INT_MAX

#define MAX_REQUESTS 100

int main() {
    int n, head, total_seek_time = 0;
    int requests[MAX_REQUESTS];

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
    }

    // C-SCAN Simulation
    printf("\nC-SCAN Disk Scheduling\n");
    printf("Head starts at: %d\n", head);

    // Move head right until the end of the disk
    int max_track = INT_MIN; // Find the maximum track among requests
    for (int i = 0; i < n; i++) {
        max_track = requests[i] > max_track ? requests[i] : max_track; // Update max track
    }

    for (int i = 0; i < n; i++) {
        if (requests[i] != head) {
            int seek_time = abs(requests[i] - head);
            total_seek_time += seek_time;
            printf("Seek from %d to %d (seek time: %d)\n", head, requests[i], seek_time);
        }
        head = requests[i];
    }

    // Move head back to the beginning (treating disk as circular)
    int seek_time = abs(max_track - head);  // Seek to the highest track
    total_seek_time += seek_time;
    printf("Seek from %d to %d (seek time: %d)\n", head, max_track, seek_time);

    head = 0; // Simulate head returning to the beginning
    seek_time = abs(head - requests[0]);  // Seek to the first request
    total_seek_time += seek_time;
    printf("Seek from %d to %d (seek time: %d)\n", max_track, head, seek_time);

    for (int i = 1; i < n; i++) { // Service remaining requests on the left side
        if (requests[i] != head) {
            seek_time = abs(requests[i] - head);
            total_seek_time += seek_time;
            printf("Seek from %d to %d (seek time: %d)\n", head, requests[i], seek_time);
        }
        head = requests[i];
    }

    printf("Total Seek Time: %d\n", total_seek_time);

    return 0;
}

