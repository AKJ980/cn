#include <stdio.h>
#define MAX_ROUTERS 10
#define INFINITY 9999

int numRouters;
int cost[MAX_ROUTERS][MAX_ROUTERS]; // Cost matrix
int dist[MAX_ROUTERS][MAX_ROUTERS]; // Distance vector
int nextHop[MAX_ROUTERS][MAX_ROUTERS]; // Next hop matrix

void initializeRoutingTable() {
    for (int i = 0; i < numRouters; i++) {
        for (int j = 0; j < numRouters; j++) {
            dist[i][j] = cost[i][j];
            nextHop[i][j] = (cost[i][j] < INFINITY && i != j) ? j : -1;
        }
    }
}

void updateRoutingTable() {
    for (int k = 0; k < numRouters; k++) { // Intermediate router
        for (int i = 0; i < numRouters; i++) { // Source router
            for (int j = 0; j < numRouters; j++) { // Destination router
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nextHop[i][j] = nextHop[i][k];
                }
            }
        }
    }
}

void printRoutingTable(int routerId) {
    printf("Routing Table for Router %d:\n", routerId);
    for (int i = 0; i < numRouters; i++) {
        if (dist[routerId][i] < INFINITY) {
            printf("To: %d, Cost: %d, Next Hop: %d\n", i, dist[routerId][i], nextHop[routerId][i]);
        } else {
            printf("To: %d, Cost: INFINITY\n", i);
        }
    }
}

int main() {
    printf("Enter the number of routers: ");
    scanf("%d", &numRouters);

    printf("Enter the cost matrix (use %d for INFINITY):\n", INFINITY);
    for (int i = 0; i < numRouters; i++) {
        for (int j = 0; j < numRouters; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    initializeRoutingTable();
    updateRoutingTable();

    for (int i = 0; i < numRouters; i++) {
        printRoutingTable(i);
    }

    return 0;
}
