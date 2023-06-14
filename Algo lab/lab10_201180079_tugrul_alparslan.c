#include <stdio.h>
#include <limits.h>

#define V 9

int find_dist(int range[], int visit[])
{
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++)
    {
        if (visit[v] == 0 && range[v] <= min)
        {
            min = range[v];
            min_index = v;
        }
    }
    
    return min_index;
}

void print(int range[])
{
    printf("Dugum:    Uzaklik:\n");
    for (int i = 1; i < V; i++)
    {
        printf("%d->\t <- %d\n", i, range[i]);
    }
}

void dijk(int gra[V][V], int src)
{
    int range[V];
    int visit[V];
    
    for (int i = 0; i < V; i++)
    {
        range[i] = INT_MAX;
        visit[i] = 0;
    }
    
    range[src] = 0;
    
    for (int count = 0; count < V - 1; count++)
    {
        int u = find_dist(range, visit);
        visit[u] = 1;
        
        for (int v = 0; v < V; v++)
        {
            if (visit[v] == 0 && gra[u][v] && range[u] != INT_MAX && range[u] + gra[u][v] < range[v])
            {
                range[v] = range[u] + gra[u][v];
            }
        }
    }
    
    print(range);
}

int main()
{
    int gra[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };
    
    dijk(gra, 0);
    
    return 0;
}
