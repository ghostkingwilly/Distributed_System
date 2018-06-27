#include <iostream>
#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <fstream>

using namespace std;

typedef struct Node
{
    int weight;
    int degree;
    int index;
    bool isMIS;
    bool can_do;
    double priority;
} node;

int total_weight = 0;
node Nodes[100];
int graph[100][100];

void sort_func(int vertex, node* Nodes)
{
    for (int i = vertex - 1; i > 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (Nodes[j].priority < Nodes[j + 1].priority)
            {
                swap(Nodes[j].priority, Nodes[j + 1].priority);
                swap(Nodes[j].degree, Nodes[j + 1].degree);
                swap(Nodes[j].index, Nodes[j + 1].index);
                swap(Nodes[j].isMIS, Nodes[j + 1].isMIS);
                swap(Nodes[j].weight, Nodes[j + 1].weight);
            }
            else if(Nodes[j].priority == Nodes[j].priority && Nodes[j].index < Nodes[j].index)
            {
                swap(Nodes[j].priority, Nodes[j + 1].priority);
                swap(Nodes[j].degree, Nodes[j + 1].degree);
                swap(Nodes[j].index, Nodes[j + 1].index);
                swap(Nodes[j].isMIS, Nodes[j + 1].isMIS);
                swap(Nodes[j].weight, Nodes[j + 1].weight);
            }

        }
    }
}

int Detect_toDo(int vertex)
{
    int num_no = 0;
    for(int i=0; i<vertex; i++)
    {
        num_no += Nodes[i].can_do; //initial are 1s for no neighbor
    }
    return num_no;
}

int main()
{
    int total_vertex = 0;
    int degree_count;
    int max_pri;
    ifstream fin;
    ofstream fout;

    fin.open("test2.txt");
    fout.open("output1.txt");
    fin >> total_vertex;
// read weight and add index
    for(int i=0; i<total_vertex; i++)
    {
        fin >> Nodes[i].weight;
        Nodes[i].index = i;
    }
// read map and count degree
    for(int i=0; i<total_vertex; i++)
    {
        degree_count = 0;
        for(int j=0; j<total_vertex; j++)
        {
            fin >> graph[i][j];
            if(graph[i][j] == 1)
            {
                degree_count++;
                Nodes[i].degree = degree_count;
            }
        }
    }
// priority set and initialize the flag
    for(int i=0; i<total_vertex; i++)
    {
        Nodes[i].priority = (double)Nodes[i].weight /((double)Nodes[i].degree + 1); //greedy selection
        Nodes[i].isMIS = 1; //not in MIS
        Nodes[i].can_do = 1; //no neighbor
    }

    while(Detect_toDo(total_vertex))
    {
        // sort the priority
        sort_func(total_vertex, Nodes);
        // decide to break the loop when there is no one can do.
        max_pri = 0;
        int d;
        // select the node to the set
        for(d=0; d<total_vertex; d++)
        {
            if(Nodes[d].can_do == 1)
            {
                max_pri = d;
                Nodes[d].isMIS = 0;
                Nodes[d].can_do = 0;
                break;
            }
        }
        // Matrix adjustment
        if(d!=total_vertex)
        {
            for(int j=0; j<total_vertex; j++)
            {
                if(graph[Nodes[max_pri].index][j] == 1)// Nodes[max_pri].index the real location
                {
                    for(int k=0; k<total_vertex; k++)
                    {
                        if(j == Nodes[k].index)// use the original index, to find the sorted index
                        {
                            Nodes[k].can_do = 0;
                        }
                    }
                    graph[Nodes[max_pri].index][j] = 0;
                    graph[j][Nodes[max_pri].index] = 0;
                }
            }
        }
    }
    // print out the result
    //cout << "MWIS: {";
    fout << "MWIS: {";
    for(int i=0,m=0; i<total_vertex; i++)
    {
        for (int k=0; k<total_vertex ; k++)
        {
            if(Nodes[k].index == i && Nodes[k].isMIS == 0)
            {
                if(m == 0){
                    //printf("%d", Nodes[k].index);
                    fout << Nodes[k].index;
                }
                else{
                    //printf(",%d", Nodes[k].index);
                    fout << "," << Nodes[k].index;
                }
                m++;

            }
        }
    }
    //cout << "}" << endl;
    fout << "}" << endl;
    total_weight = 0;
    //calculate the total weight
    for(int i=0; i<total_vertex; i++)
    {
        if(Nodes[i].isMIS == 0)
        {
            total_weight += Nodes[i].weight;
        }
    }
    //printf("Total Weight: %d", total_weight);
    fout << "Total Weight: " << total_weight << endl;

    fin.close();
    fout.close();
    return 0;
}

