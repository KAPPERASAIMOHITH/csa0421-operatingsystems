#include <stdio.h>
#include <math.h>

int main() {
    int n, head, i;
    int request[100], total_seek_time = 0;

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk request sequence: ");
    for (i = 0; i < n; i++)
        scanf("%d", &request[i]);

    printf("Request Sequence:\n");
    for (i = 0; i < n; i++)
        printf("%d ", request[i]);
    printf("\n");

    for (i = 0; i < n; i++) {
        total_seek_time += abs(request[i] - head);
        head = request[i];
    }

    printf("Total seek time: %d\n", total_seek_time);

    return 0;
}

