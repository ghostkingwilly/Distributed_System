#include <iostream>
#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

typedef struct Node
{
    int weight;
    int degree;
    int index;
    vector<int> neigh;
    double priority;
} node;

typedef struct Compare
{
    int dup_time;
    vector<int> possible_list;
} compare_c;

int total_weight;
node Nodes[100];
vector<compare_c> com;
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
    int c_cmp;
    int break_flag = 0;
    ifstream fin;
    ofstream fout;

    fin.open("test2.txt");
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
        //Compare[i].possible_list.resize(total_vertex);
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
    int tmp_pri;
    srand((unsigned)time(NULL));
    int mis[total_vertex] = {0};
    int round;
    int run_time = 0;
    int num_resize = 0;
    /***
     simulate 1000 times
    ***/
    int cmp_matrix[total_vertex] = {0};
    int MIS_matrix[total_vertex] = {0};
    for(round=0; round<1000; round++)
    {
        int times = 0;
        int can_select = 0;
        check = 0;
        srand(round*10000);
        //can_select = rand()%total_vertex; // choose a man to select to the MMIS
        /***
        adding to MIS should be random
        ***/
        for(int i=0; i<total_vertex; i++)
        {
            //cmp_matrix[i] = rand()%2;
            cmp_matrix[i] = 0;
        }
        while(check ==0)
        {
            int is_in_set = 0;
            int i_old;
            //for(i_old=0; i_old<total_vertex; i_old++)
            //{
            can_select = rand()%total_vertex;
            for(int j=0; j<total_vertex; j++)
            {
                //cout << cmp_matrix[j] << " " <<endl;
                // find the biggest one neighbor
                if(Nodes[can_select].neigh[j] == 1 && Nodes[j].priority >= Nodes[can_select].priority)
                {
                    if(cmp_matrix[j] == 1) //larger neighbor in set
                    {
                        is_in_set++;
                    }
                }

            }

            //compare the matrix to find whether to change the map
            if(is_in_set != 0) // there are some neighbor in the set
            {
                MIS_matrix[can_select] = 0;
            }
            else
            {
                MIS_matrix[can_select] = 1;
            }
            //}

            int count_cmp = 0;
            //if the EMIS matrix equal to the old check set to one to break
            for(int i=0; i<total_vertex; i++)
            {
                if(MIS_matrix[i] != cmp_matrix[i])
                {
                    count_cmp++;// count the total match
                    times =0;
                }
            }
            if(count_cmp == 0 )
            {
                times++;// record the times when the arrays same
                if(times > 5000)
                {
                    check = 1;// time to exit the loop
                }
            }
            //put the new matrix to the old for the next round
            copy_from_vector_to_array(MIS_matrix, cmp_matrix, total_vertex);
            run_time++; // times of rounds
        }

        run_time -= times;

// calculate the duplicate array
        vector<int> tmp_MIS;

        for(int i=0; i<total_vertex; i++)//convert the MIS_matrix to set
        {
            if(MIS_matrix[i] == 1)
            {
                tmp_MIS.push_back(i);
            }
        }

        if(round == 0)
        {
            num_resize = round+1;
            com.resize(num_resize);
            com[num_resize-1].possible_list.resize(tmp_MIS.size());
            for(int i=0; i<tmp_MIS.size(); i++)
            {
                com[num_resize-1].possible_list[i] = tmp_MIS[i];
            }
            com[num_resize - 1].dup_time = 1;
        }
        else //from second round to end
        {
            int same =0;
            for(int i=0; i<com.size(); i++)
            {
                if(com[i].possible_list.size() == tmp_MIS.size())
                {
                    same = 0;
                    for(int j=0; j<tmp_MIS.size(); j++)
                    {
                        if(com[i].possible_list[j] == tmp_MIS[j])
                        {
                            same++;// check each element of array is equal
                        }
                    }
                    if(same == tmp_MIS.size())  // two arrays are the same
                    {
                        com[i].dup_time++;
                        break;
                    }

                }
            }
            if(same != tmp_MIS.size())
            {
                num_resize++;
                com.resize(num_resize);
                com[num_resize-1].possible_list.resize(tmp_MIS.size());
                for(int i=0; i<tmp_MIS.size(); i++)
                {
                    com[num_resize-1].possible_list[i] = tmp_MIS[i];
                }
                com[num_resize - 1].dup_time = 1;
            }
        }
    }

    // print result
    double total_prob = 0;
    for(int i=0; i<com.size(); i++)
    {
        total_prob = (double)com[i].dup_time/10.0;// percentage
        cout << "{ ";
        for(int j=0; j<com[i].possible_list.size(); j++)
        {
            cout << com[i].possible_list[j] << " ";
        }
        cout << "} ---> " << "Probability: " << total_prob << " %" << endl;

    }
    fin.close();
    fout.close();
    return 0;
}
