#include <iostream>
#include <vector>
#include <math.h>

#include "projekt.h"

struct {
    int** array;
    int size;
} typedef graph;

graph new_graph(int size)
{
    graph g;
    g.size = size;
    g.array = new int*[size];
    int i, j;
    for (int i = 0; i < size; i++) {
        g.array[i] = new int[size];
        memset(g.array[i], 0, size * sizeof(int));
    }
    return g;
}

void free_graph(graph &g)
{
    for (int i = 0; i < g.size; i++) delete[] g.array[i];
    delete[] g.array;
    g.array = NULL;
    g.size = 0;
}

void print_graph(const graph& g)
{
    int i, j;
    printf("   ");
    for (i = 0; i < g.size; i++) printf("%3d ", i);
    printf("\n\n");
    for (i = 0; i < g.size; i++)
    {
        printf("%2d ", i);
        for (j = 0; j < g.size; j++)
        {
            printf("%3d ", g.array[i][j]);
        }
        printf("\n");
    }
}

void graph_print_neighbours_of_each_vertex(const graph& g)
{
    int i, j, print_count;

    for (i = 0; i < g.size; i++)
    {
        print_count = 0;
        printf("%2d: ", i);
        for (j = 0; j < g.size; j++) 
        {
            if (g.array[i][j] == 1)
                printf("%s%2d", print_count++ ? ", " : "", j);
        }
        printf("\n");
    }
}

void graph_print_each_vertex_that_is_neighbour(const graph& g)
{
    int i, j, print_count;

    for (i = 0; i < g.size; i++)
    {
        print_count = 0;
        printf("%2d: ", i);
        for (j = 0; j < g.size; j++)
        {
            if (g.array[j][i] == 1)
                printf("%s%2d", print_count++ ? ", " : "", j);
        }
        printf("\n");
    }
}

void graph_print_vertex_outdegrees(const graph& g)
{
    int i, j, count;
    for (i = 0; i < g.size; i++)
    {
        printf("%2d: ", i);
        count = 0;
        for (j = 0; j < g.size; j++)
        {
            if (g.array[i][j] == 1)
                count++;
        }
        printf("%d\n", count);
    }
}

void graph_print_vertex_indegrees(const graph& g)
{
    int i, j, count;
    for (i = 0; i < g.size; i++)
    {
        printf("%2d: ", i);
        count = 0;
        for (j = 0; j < g.size; j++)
        {
            if (g.array[j][i] == 1)
                count++;
        }
        printf("%d\n", count);
    }
}

void graph_print_isolated_vertexes(const graph& g)
{
    int i, j, count, print_count = 0;
    for (i = 0; i < g.size; i++)
    {
        count = 0;
        for (j = 0; j < g.size; j++)
        {
            if (g.array[j][i] == 1 || g.array[i][j] == 1)
                count++;
        }
        if (count == 0) printf("%s%2d", print_count++ ? ", " : "", i);
    }
    printf("\n");
}

void graph_print_loops(const graph& g)
{
    int i, print_count = 0;
    for (i = 0; i < g.size; i++)
    {
        if (g.array[i][i] == 1) printf("%s%2d", print_count++ ? ", " : "", i);
    }
    printf("\n");
}

void graph_print_multi_edges(const graph& g)
{
    int i, j, print_count = 0;
    for (i = 0; i < g.size; i++)
    {
        for (j = i + 1; j < g.size; j++)
        {
            if (g.array[i][j] == 1 && g.array[j][i] == 1)
                printf("%s%2d<->%2d", print_count++ ? ", " : "", i, j);
        }
    }
    printf("\n");
}

void graph_add_edge(graph& g, int a, int b)
{
    if (a >= g.size || b >= g.size) throw std::string("Provided graph edge vertex pair is incorrect!");

    g.array[a][b] = 1;
}

int main()
{
    graph g = new_graph(6);

    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 2, 2);
    graph_add_edge(g, 1, 3);
    graph_add_edge(g, 3, 1);
    graph_add_edge(g, 2, 4);
    graph_add_edge(g, 4, 0);
    graph_add_edge(g, 4, 3);


    print_graph(g);

    std::cout << "Sasiedzi dla kazdego wierzcholka grafu: \n";
    graph_print_neighbours_of_each_vertex(g);

    std::cout << "Wierzcholki, ktore sa sasiadami kazdego wierzcholka: \n";
    graph_print_each_vertex_that_is_neighbour(g);

    std::cout << "Stopnie wychodzace: \n";
    graph_print_vertex_outdegrees(g);

    std::cout << "Stopnie wchodzace:\n";
    graph_print_vertex_indegrees(g);

    std::cout << "Wierzcholki izolowane: \n";
    graph_print_isolated_vertexes(g);

    std::cout << "Petle: \n";
    graph_print_loops(g);

    std::cout << "Krawedzie dwukierunkowe: \n";
    graph_print_multi_edges(g);

    free_graph(g);
    return 0;
}