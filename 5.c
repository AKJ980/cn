#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep function

#define BUCKET_SIZE 10 // Maximum capacity of the bucket
#define OUTPUT_RATE 4  // Rate at which the bucket can send out packets

void leakyBucket(int packets[], int n) {
    int bucketContent = 0;

    printf("Time\tPacket\tBucket Content\tSent\tDropped\n");
    for (int i = 0; i < n; i++) {
        int incomingPacket = packets[i];
        int sentPackets = 0;
        int droppedPackets = 0;

        // Add incoming packets to the bucket
        if (bucketContent + incomingPacket <= BUCKET_SIZE) {
            bucketContent += incomingPacket;
        } else {
            droppedPackets = bucketContent + incomingPacket - BUCKET_SIZE;
            bucketContent = BUCKET_SIZE;
        }

        // Send packets from the bucket
        if (bucketContent > OUTPUT_RATE) {
            sentPackets = OUTPUT_RATE;
            bucketContent -= OUTPUT_RATE;
        } else {
            sentPackets = bucketContent;
            bucketContent = 0;
        }

        // Print the status at this time step
        printf("%d\t%d\t%d\t\t%d\t%d\n", i + 1, incomingPacket, bucketContent, sentPackets, droppedPackets);

        sleep(1); // Simulate time delay for each second
    }
}

int main() {
    int n;
    printf("Enter the number of time steps: ");
    scanf("%d", &n);

    int packets[n];
    printf("Enter the number of packets arriving at each time step:\n");
    for (int i = 0; i < n; i++) {
        printf("Time step %d: ", i + 1);
        scanf("%d", &packets[i]);
    }

    leakyBucket(packets, n);

    return 0;
}

