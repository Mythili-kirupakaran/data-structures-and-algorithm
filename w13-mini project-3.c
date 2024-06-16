#include <stdio.h>
#include <limits.h>

#define MAX_CITIES 100
#define INF INT_MAX

typedef struct {
    char name[50];
} City;

City cities[MAX_CITIES];
int distances[MAX_CITIES][MAX_CITIES];
int numCities = 0;

int addCity(char *name) {
    if (numCities >= MAX_CITIES) {
        printf("Max cities limit reached.\n");
        return -1;
    }
    strcpy(cities[numCities].name, name);
    numCities++;
    return numCities - 1;
}

void addDistance(int city1, int city2, int distance) {
    distances[city1][city2] = distance;
    distances[city2][city1] = distance;
}

int minDistance(int dist[], int sptSet[]) {
    int min = INF, min_index;
    for (int v = 0; v < numCities; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int src, int dest) {
    int dist[MAX_CITIES];
    int sptSet[MAX_CITIES];
    int parent[MAX_CITIES];

    for (int i = 0; i < numCities; i++) {
        parent[src] = -1;
        dist[i] = INF;
        sptSet[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < numCities - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        for (int v = 0; v < numCities; v++)
            if (!sptSet[v] && distances[u][v] && dist[u] != INF && dist[u] + distances[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + distances[u][v];
            }
    }

    printf("Shortest path from %s to %s is %d\n", cities[src].name, cities[dest].name, dist[dest]);
    printf("Path: ");
    int crawl = dest;
    while (parent[crawl] != -1) {
        printf("%s <- ", cities[crawl].name);
        crawl = parent[crawl];
    }
    printf("%s\n", cities[src].name);
}

int main() {
    for (int i = 0; i < MAX_CITIES; i++)
        for (int j = 0; j < MAX_CITIES; j++)
            distances[i][j] = INF;

    int choice;
    char city1[50], city2[50];
    int dist, cityIndex1, cityIndex2;

    while (1) {
        printf("\nTravel Planner\n");
        printf("1. Add City\n");
        printf("2. Add Distance\n");
        printf("3. Find Shortest Path\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter city name: ");
                scanf("%s", city1);
                addCity(city1);
                break;

            case 2:
                printf("Enter first city name: ");
                scanf("%s", city1);
                printf("Enter second city name: ");
                scanf("%s", city2);
                printf("Enter distance between cities: ");
                scanf("%d", &dist);
                cityIndex1 = -1;
                cityIndex2 = -1;
                for (int i = 0; i < numCities; i++) {
                    if (strcmp(cities[i].name, city1) == 0)
                        cityIndex1 = i;
                    if (strcmp(cities[i].name, city2) == 0)
                        cityIndex2 = i;
                }
                if (cityIndex1 != -1 && cityIndex2 != -1)
                    addDistance(cityIndex1, cityIndex2, dist);
                else
                    printf("One or both cities not found.\n");
                break;

            case 3:
                printf("Enter source city name: ");
                scanf("%s", city1);
                printf("Enter destination city name: ");
                scanf("%s", city2);
                cityIndex1 = -1;
                cityIndex2 = -1;
                for (int i = 0; i < numCities; i++) {
                    if (strcmp(cities[i].name, city1) == 0)
                        cityIndex1 = i;
                    if (strcmp(cities[i].name, city2) == 0)
                        cityIndex2 = i;
                }
                if (cityIndex1 != -1 && cityIndex2 != -1)
                    dijkstra(cityIndex1, cityIndex2);
                else
                    printf("One or both cities not found.\n");
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
