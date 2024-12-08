#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ROUTERS 10
#define INFINITY 9999

typedef struct {
    int cost[MAX_ROUTERS];
    int nextHop[MAX_ROUTERS];
} Router;

Router routers[MAX_ROUTERS];
int numRouters;

void initializeRouter(int routerId) {
    for (int i = 0; i < numRouters; i++) {
        if (i == routerId) {
            routers[routerId].cost[i] = 0;
            routers[routerId].nextHop[i] = i;
        } else {
            routers[routerId].cost[i] = INFINITY;
            routers[routerId].nextHop[i] = -1;
        }
    }
}

void printRoutingTable(int routerId) {
    printf("Routing table for Router %d:\n", routerId);
    for (int i = 0; i < numRouters; i++) {
        if (routers[routerId].cost[i] != INFINITY) {
            printf("Destination: %d, Cost: %d, Next Hop: %d\n", i, routers[routerId].cost[i], routers[routerId].nextHop[i]);
        } else {
            printf("Destination: %d, Cost: INFINITY\n", i);
        }
    }
}

void updateRoutingTable(int routerId) {
    for (int i = 0; i < numRouters; i++) {
        if (i != routerId) {
            for (int j = 0; j < numRouters; j++) {
                if (routers[routerId].cost[j] + routers[j].cost[i] < routers[routerId].cost[i]) {
                    routers[routerId].cost[i] = routers[routerId].cost[j] + routers[j].cost[i];
                    routers[routerId].nextHop[i] = routers[routerId].nextHop[j];
                }
            }
        }
    }
}

void simulateRouting() {
    for (int i = 0; i < numRouters; i++) {
        updateRoutingTable(i);
    }
}

int main() {
    printf("Enter the number of routers: ");
    scanf("%d", &numRouters);
    
    int costs[MAX_ROUTERS][MAX_ROUTERS];
    printf("Enter the cost matrix (use %d for INFINITY):\n", INFINITY);
    for (int i = 0; i < numRouters; i++) {
        for (int j = 0; j < numRouters; j++) {
            scanf("%d", &costs[i][j]);
        }
    }

    for (int i = 0; i < numRouters; i++) {
        initializeRouter(i);
        for (int j = 0; j < numRouters; j++) {
            if (costs[i][j] < INFINITY) {
                routers[i].cost[j] = costs[i][j];
                routers[i].nextHop[j] = j;
            }
        }
    }

    for (int i = 0; i < numRouters; i++) {
        printRoutingTable(i);
    }

    simulateRouting();

    printf("\nUpdated Routing Tables:\n");
    for (int i = 0; i < numRouters; i++) {
        printRoutingTable(i);
    }

    return 0;
}

