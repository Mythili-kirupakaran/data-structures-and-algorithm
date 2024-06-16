Write a function to perform Breadth-First Search on the graph. Start the search from a specified source vertex. Print the visited vertices in BFS order.

Aim:

To implement a function in C to perform Breadth-First Search (BFS) on a graph represented using an adjacency list. The BFS function will start from a specified source vertex and print the visited vertices in BFS order.

Algorithm:
Breadth-First Search (BFS)
1.	Initialize:
•	Create a boolean array visited to keep track of visited vertices.
•	Create a queue to manage the vertices to be explored.
2.	Start BFS from the source vertex:
•	Mark the source vertex as visited and enqueue it.
3.	Process the queue:
•	While the queue is not empty:
•	Dequeue a vertex from the queue and print it.
•	Get all adjacent vertices of the dequeued vertex. If an adjacent vertex has not been visited, mark it as visited and enqueue it.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent an adjacency list node
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;
// Structure to represent an adjacency list
typedef struct AdjList {
    struct AdjListNode *head;
} AdjList;

// Structure to represent a graph
typedef struct Graph {
    int V;
    struct AdjList* array;
} Graph;

// Function to create a new adjacency list node
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}



 


// Function to create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}


// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to perform BFS starting from a given source vertex
void BFS(Graph* graph, int startVertex) {
    // Create a visited array and mark all vertices as not visited
    bool *visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++)
        visited[i] = false;

    // Create a queue for BFS
    int *queue = (int*)malloc(graph->V * sizeof(int));
    int front = 0;
    int rear = 0;
// Mark the current node as visited and enqueue it
    visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front < rear) {
        // Dequeue a vertex from queue and print it
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);
  // Get all adjacent vertices of the dequeued vertex
        AdjListNode* adjList = graph->array[currentVertex].head;
        while (adjList != NULL) {
            int adjVertex = adjList->dest;
if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            adjList = adjList->next;





 


      }
    }
    free(visited);
    free(queue);
}

// Function to print the adjacency list representation of the graph
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int main() {
    int V = 5;
    Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printf("Graph adjacency list:\n");
    printGraph(graph);

    printf("\nBreadth First Traversal starting from vertex 0:\n");
    BFS(graph, 0);

    return 0;
}

