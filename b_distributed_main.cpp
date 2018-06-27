#include <iostream>
#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

typedef struct Node
{
    int weight;
    int degree;
    int index;
    vector<int> neigh;
    double priority;
} node;

int total_weight;
node Nodes[100];
int graph[100][100];

void copy_from_vector_to_array(int *from, int *des, int num)
{
    for(int i=0 ; i<num ; i++)
    {
        des[i] = from[i];
    }
}

int main()
{
    int total_vertex = 0;
    int degree_count;
    int check = 0; // check for the correct MIS array
    ifstream fin;
    ofstream fout;

    fin.open("test1.txt");
    fout.open("output2.txt");
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
        Nodes[i].neigh.resize(total_vertex);
        for(int j=0; j<total_vertex; j++)
        {
            fin >> graph[i][j];
            if(graph[i][j] == 1)
            {
                degree_count++;
                Nodes[i].degree = degree_count;
            }
            Nodes[i].neigh[j] = graph[i][j];
        }
    }

// priority set and initialize the flag
    for(int i=0; i<total_vertex; i++)
    {
        Nodes[i].priority = (double)Nodes[i].weight /((double)Nodes[i].degree + 1); //greedy selection
    }

    int max_index = 0;
    int cmp_matrix[total_vertex] = {0};
    int MIS_matrix[total_vertex] = {0};
    double tmp_pri;

    while(check ==0)
    {
        for(int i=0; i<total_vertex; i++)
        {
            tmp_pri = 0;
            for(int j=0; j<total_vertex; j++)
            {
                // find the biggest one neighbor
                if(Nodes[i].neigh[j] == 1 && Nodes[j].priority > tmp_pri)
                {
                    tmp_pri = Nodes[j].priority;
                    max_index = Nodes[j].index;
                }
            }
            // check the priority
            if(Nodes[i].priority > Nodes[max_index].priority)
            {
                // add i to MIS set
                MIS_matrix[i] = 1;
            }
            else if(Nodes[i].priority == Nodes[max_index].priority)
            {
                if(Nodes[i].index < Nodes[max_index].index)
                {
                    MIS_matrix[i] = 1;
                }
                else if(Nodes[i].index > Nodes[max_index].index && cmp_matrix[max_index] == 0)
                {
                    MIS_matrix[i] = 1;
                }
                else // other set to 0
                {
                    MIS_matrix[i] = 0;
                }
            }
            else
            {
                if(cmp_matrix[max_index] == 1) // in the set
                {
                    //cancel from the set
                    MIS_matrix[i] = 0;
                }
                else
                {
                    MIS_matrix[i] = 1;
                }
            }
            //compare the matrix to find whether to change the map
            //check for the correct array and the compare array
        }

        int count_cmp = 0;
        //if the EMIS matrix equal to the old check set to one to break
        for(int i=0; i<total_vertex; i++)
        {
            if(MIS_matrix[i] != cmp_matrix[i])
            {
                count_cmp++;// count the total match
            }
        }
        if(count_cmp == 0 )
        {
            check = 1;// time to exit the loop
        }
        //put the new matrix to the old for the next round
        copy_from_vector_to_array(MIS_matrix, cmp_matrix, total_vertex);
    }

// print out the result


    //cout << "MWIS: { ";
    fout << "MWIS: { ";
    for(int i=0; i<total_vertex; i++)
    {
        if(MIS_matrix[i] == 1)
            //cout << i << " ";
            fout << i << " ";
    }
    //cout << "}" << endl;
    fout << "}" << endl;
    total_weight = 0;
    //calculate the total weight
    for(int i=0; i<total_vertex; i++)
    {
        if(MIS_matrix[i] == 1)
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
