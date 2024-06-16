#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void minCashFlowRec(int amount[], int n);

// Utility function that returns index of minimum value in arr[]
int getMin(int arr[], int n) {
    int minInd = 0;
    for (int i = 1; i < n; i++)
        if (arr[i] < arr[minInd])
            minInd = i;
    return minInd;
}

// Utility function that returns index of maximum value in arr[]
int getMax(int arr[], int n) {
    int maxInd = 0;
    for (int i = 1; i < n; i++)
        if (arr[i] > arr[maxInd])
            maxInd = i;
    return maxInd;
}

// A utility function to return minimum of 2 values
int minOf2(int x, int y) {
    return (x < y) ? x : y;
}

// amount[p] indicates the net amount to be credited/debited to person 'p'
// If amount[p] is positive, then i'th person will receive amount[p] money.
// If amount[p] is negative, then i'th person will give amount[p] money.
void minCashFlowRec(int amount[], int n) {
    // Find the indexes of minimum and maximum values in amount[]
    // amount[mxCredit] indicates the maximum amount to be given
    // amount[mxDebit] indicates the maximum amount to be taken
    int mxCredit = getMax(amount, n), mxDebit = getMin(amount, n);

    // If both amounts are 0, then all amounts are settled
    if (amount[mxCredit] == 0 && amount[mxDebit] == 0)
        return;

    // Find the minimum of two amounts
    int min = minOf2(-amount[mxDebit], amount[mxCredit]);
    amount[mxCredit] -= min;
    amount[mxDebit] += min;

    // If minimum is the maximum amount to be given, print the transaction
    printf("Person %d pays %d to Person %d\n", mxDebit, min, mxCredit);

    // Recur for the amount array. Note that it is guaranteed that
    // the recursion would terminate as either amount[mxCredit] 
    // or amount[mxDebit] becomes 0
    minCashFlowRec(amount, n);
}

// Given a set of persons as graph[] where graph[i][j] indicates
// the amount that person i needs to pay person j, this function
// finds and prints the minimum cash flow to settle all debts.
void minCashFlow(int graph[MAX][MAX], int n) {
    // Create an array amount[], initialize all value in it as 0.
    int amount[MAX] = {0};

    // Calculate the net amount to be paid to person 'p', and store it in amount[p]
    for (int p = 0; p < n; p++)
        for (int i = 0; i < n; i++)
            amount[p] += (graph[i][p] - graph[p][i]);

    minCashFlowRec(amount, n);
}

int main() {
    int graph[MAX][MAX];
    int n;
    
    printf("Enter the number of persons: ");
    scanf("%d", &n);

    printf("Enter the cash flow matrix (amount to be paid from i to j):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    minCashFlow(graph, n);
    
    return 0;
}
