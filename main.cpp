#include <iostream>
#include <vector>
#include <math.h>

#include "projekt.h"

// struktura grafu przechowująca dwuwymiarową tablicę zawierającą informacje o grafie oraz ilość jego wierzchołków
struct {
    // tablica dwuwymiarowa przechowująca informacje o krawędziach grafu
    int** array;
    // wymiary grafu
    int size;
} typedef graph;

// inicjalizacja struktury grafu tablicą wypełnioną zerami
graph new_graph(int size)
{
    if (size < 0) throw "Rozmiar grafu nie moze byc ujemny!\n";
    // stworzenie nowej struktury typu graf
    graph g;
    // przypisanie wymiarów grafu do struktury
    g.size = size;

    // zainicjowanie tablicy wskaźników
    g.array = new int*[size];

    int i, j;
    // dla każdego elementu tablicy
    for (int i = 0; i < size; i++) {
        // zainicjowanie pamięci dla wiersza
        g.array[i] = new int[size];
        // zapełnienie zainicjowanej pamięci zerami
        memset(g.array[i], 0, size * sizeof(int));
    }

    // zwrócenie utworzonej struktury
    return g;
}

// zwolnienie pamięci zajętej przez strukturę grafu
void free_graph(graph &g)
{
    // dla każdego elementu w tablicy
    for (int i = 0; i < g.size; i++)
    {
        // zwolnienie pamięci dla wiersza
        delete[] g.array[i];
    }
    // zwolnienie pamięci tablicy
    delete[] g.array;
    
    // wyzerowanie elementów w strukturze
    g.array = NULL;
    g.size = 0;
}

// wypisanie zawartości tablicy relacji między wierzchołkami grafu
void print_graph(const graph& g)
{
    int i, j;
    // wypisanie numerów kolumn grafu
    printf("   ");
    for (i = 0; i < g.size; i++) printf("%3d ", i);
    printf("\n\n");

    // dla każdego elementu w tablicy
    for (i = 0; i < g.size; i++)
    {
        // wypisanie numeru wiersza
        printf("%2d ", i);

        // wypisanie zawartości wiersza
        for (j = 0; j < g.size; j++)
            printf("%3d ", g.array[i][j]);
        printf("\n");
    }
}

// wypisanie sąsiadów każdego wierzchołka
void graph_print_neighbours_of_each_vertex(const graph& g)
{
    int i, j, print_count;

    // dla każdego elementu w tablicy
    for (i = 0; i < g.size; i++)
    {
        print_count = 0;
        
        // wypisanie numeru wierzchołka
        printf("%2d: ", i);

        // dla każdej kolumny w tablicy
        for (j = 0; j < g.size; j++) 
        {
            // jeżeli istnieje krawędź w grafie od wierzchołka i do j
            if (g.array[i][j] == 1)
            {
                // wypisanie numeru wierzchołka j
                printf("%s%2d", print_count++ ? ", " : "", j);
            }
        }
        // wypisanie informacji o braku elementów jeżeli licznik wypisań jest równy 0
        if (print_count == 0) printf(" brak");
        printf("\n");
    }
}

// wypisanie każdego wierzchołka, który jest sąsiadem każdego wierzchołka
void graph_print_each_vertex_that_is_neighbour(const graph& g)
{
    int i, j, print_count;

    // dla każdego elementu w tablicy
    for (i = 0; i < g.size; i++)
    {
        print_count = 0;

        // wypisanie numeru wierzchołka
        printf("%2d: ", i);

        // dla każdej kolumny w tablicy
        for (j = 0; j < g.size; j++)
        {
            // jeżeli istnieje krawędź w grafie od wierzchołka j do i
            if (g.array[j][i] == 1)
            {
                // wypisanie numeru wierzchołka j
                printf("%s%2d", print_count++ ? ", " : "", j);
            }
        }
        // wypisanie informacji o braku elementów jeżeli licznik wypisań jest równy 0
        if (print_count == 0) printf(" brak");
        printf("\n");
    }
}

// wypisanie stopni wychodzących każdego z wierzchołków
void graph_print_vertex_outdegrees(const graph& g)
{
    int i, j, count;
    // dla każdego elementu w tablicy
    for (i = 0; i < g.size; i++)
    {
        // wypisanie numeru wierzchołka
        printf("%2d: ", i);
        // zerowanie licznika
        count = 0;

        // dla każdej kolumny w tablicy
        for (j = 0; j < g.size; j++)
        {
            // jeżeli istnieje krawędź w grafie od wierzchołka i do j
            if (g.array[i][j] == 1)
                // zwiększenie licznika krawędzi wychodzących z wierzchołka i
                count++;
        }
        // wypisanie licznika
        printf("%d\n", count);
    }
}

// wypisanie stopni wchodzących każdego z wierzchołków
void graph_print_vertex_indegrees(const graph& g)
{
    int i, j, count;
    // dla każdego elementu w tablicy
    for (i = 0; i < g.size; i++)
    {
        // wypisanie numeru wierzchołka
        printf("%2d: ", i);
        // zerowanie licznika
        count = 0;

        // dla każdej kolumny w tablicy
        for (j = 0; j < g.size; j++)
        {
            // jeżeli istnieje krawędź w grafie od wierzchołka j do i
            if (g.array[j][i] == 1)
                // zwiększenie licznika krawędzi wchodzących do wierzchołka i
                count++;
        }
        // wypisanie licznika
        printf("%d\n", count);
    }
}

// wypisanie wszystkich izolowanych wierzchołków
void graph_print_isolated_vertexes(const graph& g)
{
    int i, j, count, print_count = 0;
    // dla każdego elementu w tablicy
    for (i = 0; i < g.size; i++)
    {
        // zerowanie licznika
        count = 0;

        // dla każdej kolumny w tablicy
        for (j = 0; j < g.size; j++)
        {
            // jeżeli istnieje krawędź w grafie między wierzchołkami i oraz j
            if (g.array[j][i] == 1 || g.array[i][j] == 1)
                // zwiększenie licznika krawędzi wchodzących lub wychodzących z wierzchołka i
                count++;
        }
        // jeżeli licznik jest równy 0 to dany wierzchołek nie posiada żadnych krawędzi i jest izolowany
        if (count == 0) printf("%s%2d", print_count++ ? ", " : "", i);
    }
    printf("\n");
}

// wypisanie wszystkich pętli w grafie
void graph_print_loops(const graph& g)
{
    int i, print_count = 0;
    // dla każdego elementu w tablicy
    for (i = 0; i < g.size; i++)
    {
        // jeżeli wierzchołek i łączy się z krawędzią z samym sobą to jest to pętla
        if (g.array[i][i] == 1) printf("%s%2d", print_count++ ? ", " : "", i);
    }
    printf("\n");
}

// wypisanie wszystkich krawędzi dwukierunkowych w grafie
void graph_print_multi_edges(const graph& g)
{
    int i, j, print_count = 0;
    // dla każdego elementu w tablicy
    for (i = 0; i < g.size; i++)
    {
        // dla każdej kolumny w tablicy pomijając elementy już sprawdzone przez poprzednie iteracje oraz wierzchołek i
        for (j = i + 1; j < g.size; j++)
        {
            // jeżeli istnieją krawędzie w obu kierunkach między wierzchołkami i oraz j
            if (g.array[i][j] == 1 && g.array[j][i] == 1)
                // wypisanie tej pary wierzchołków
                printf("%s%2d<->%2d", print_count++ ? ", " : "", i, j);
        }
    }
    printf("\n");
}

// dodanie krawędzi między wierzchołkami a i b do grafu
void graph_add_edge(graph& g, int a, int b)
{
    // jeżeli podane wierzchołki znajduja się w zakresie grafu
    if (a < 0 || a >= g.size || b < 0 || b >= g.size) throw "Podane wierzcholki nie znajduja sie w grafie!";
    // wpisanie istnienia krawędzi do macierzy sąsiedztwa
    g.array[a][b] = 1;
}

// przeciążenie funkcji graph_add_edge przyjmujące tablicę par numerów wierzchołków tworzących krawędzie
void graph_add_edge(graph& g, const std::vector<std::pair<int, int>>& edges)
{
    // dla każdej pary wierzchołków
    for (const std::pair<int, int>& edge : edges)
    {
        // utworzenie krawędzi między nimi
        graph_add_edge(g, edge.first, edge.second);
    }
}

int main()
{
    // utworzenie grafu zawierającego 6 wierzchołków
    graph g = new_graph(6);

    // wpisanie krawędzi do grafu
    graph_add_edge(g, {
        {0, 1},
        {1, 2},
        {2, 2},
        {1, 3},
        {3, 1},
        {2, 4},
        {4, 0},
        {4, 3}
        });

    // wypisanie macierzy sąsiedztwa znajdującej się w grafie
    print_graph(g);

    // 1) wypisanie wszystkich sąsiadów dla każdego wierzchołka grafu.
    std::cout << "Sasiedzi dla kazdego wierzcholka grafu: \n";
    graph_print_neighbours_of_each_vertex(g);

    // 2) wypisanie wszyskich wierzchołków, które są sąsiadami każdego wierzchołka
    std::cout << "Wierzcholki, ktore sa sasiadami kazdego wierzcholka: \n";
    graph_print_each_vertex_that_is_neighbour(g);

    // 3) wypisanie stopni wychodzących wszystkich wierzchołków
    std::cout << "Stopnie wychodzace: \n";
    graph_print_vertex_outdegrees(g);

    // 4) wypisanie stopni wchodzących wszystkich wierzchołków
    std::cout << "Stopnie wchodzace:\n";
    graph_print_vertex_indegrees(g);

    // wypisanie wszystkich wierzchołków izolowanych
    std::cout << "Wierzcholki izolowane: \n";
    graph_print_isolated_vertexes(g);

    // wypisanie wysztkich pętli
    std::cout << "Petle: \n";
    graph_print_loops(g);

    // wypisanie wszystkich krawędzi dwukierunkowych
    std::cout << "Krawedzie dwukierunkowe: \n";
    graph_print_multi_edges(g);

    // zwolnienie pamięci struktury grafu
    free_graph(g);
    return 0;
}