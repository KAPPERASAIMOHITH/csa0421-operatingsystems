#include <stdio.h>
#include <stdlib.h>

#define MAX_READERS 3  // Maximum number of concurrent readers
#define MAX_WRITERS 1 // Maximum number of concurrent writers

int read_count = 0; // Number of readers currently reading
int writing = 0;    // Flag indicating if a writer is writing

void reader(int id) {
  while (1) {
    // Busy waiting until no writer is writing and read_count is less than maximum
    while (writing || read_count == MAX_READERS) {
      // Simulate some waiting time for the reader
      printf("Reader %d: Waiting...\n", id);
      usleep(100000); // Sleep for 0.1 seconds (microsecond resolution)
    }

    // Reader section (simulated by printing a message)
    printf("Reader %d: Reading...\n", id);
    read_count++;
    usleep(500000); // Simulate reading time (0.5 seconds)
    read_count--;

    // Exit critical section
    printf("Reader %d: Finished reading.\n", id);
  }
}

void writer(int id) {
  while (1) {
    // Busy waiting until no reader is reading and no writer is writing
    while (read_count > 0 || writing) {
      // Simulate some waiting time for the writer
      printf("Writer %d: Waiting...\n", id);
      usleep(200000); // Sleep for 0.2 seconds
    }

    // Writer section (simulated by printing a message)
    writing = 1;
    printf("Writer %d: Writing...\n", id);
    usleep(1000000); // Simulate writing time (1 second)
    writing = 0;

    // Exit critical section
    printf("Writer %d: Finished writing.\n", id);
  }
}

int main() {
  // Create threads for readers and writers
  #pragma omp parallel sections num_threads(MAX_READERS + MAX_WRITERS)
  {
    #pragma omp section
    {
      for (int i = 0; i < MAX_READERS; i++) {
        reader(i);
      }
    }

    #pragma omp section
    {
      for (int i = 0; i < MAX_WRITERS; i++) {
        writer(i);
      }
    }
  }

  return 0;
}

