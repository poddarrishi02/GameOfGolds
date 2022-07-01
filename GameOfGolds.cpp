/* Data Structures And Algorithms Group Project */
 
// Problem Statement:
/*
Inside the Castle of Asymptopia there is a maze, and
along each corridor of the maze there is a bag of gold
coins. The amount of gold in each bag varies. A noble
knight, named Sir Paul, will be given the opportunity
to walk through the maze, picking up bags of gold. He may
enter the maze only through a door marked �ENTER� and
exit through another door marked �EXIT.� While in the
maze, he may not retrace his steps. Each corridor of the
maze has an arrow painted on the wall. Sir Paul may
only go down the corridor in the direction of the arrow.
There is no way to traverse a �loop� in the maze. Given a
map of the maze, including the amount of gold in and the
direction of each corridor, describe an algorithm
to help Sir Paul pick up the most gold.
*/
 
/*
Input Format
Size n, denoting number of edges
array1->weights of edges
array2->initial node for array1[i�th]
array3->final node for array1[i�th]
Integers x,y->Entry node, exit node
Constraints
array1[i]>=0
*/
 
/*
Group Members:
AKSHAT KHAITAN - 2020A7PS2055H
RISHI PODDAR - 2020A7PS1195H
ANKIT RAMESH YADAV - 2020A7PS2046H
*/
 
#include <bits/stdc++.h>
using namespace std;
 
// Class to represent the maze
class Maze
{
    // variable to keep a track of number of vertices in the maze
    int V;
    // variable to keep a track of number of corridor in the maze along with the weights of the gold in each corridor
    list<pair<int, int>> *corridor_map;
 
public:
    // Constructor
    Maze(int V);
    // function to add a corridor to the maze
    void addCorridor(int u, int v, int w);
    // function to print the path to be taken by the knight
    void gameOfGolds(int start, int end);
};
 
Maze::Maze(int V) // Constructor for the Maze class
{
    this->V = V;
    corridor_map = new list<pair<int, int>>[V + 1];
}
 
void Maze::addCorridor(int u, int v, int w)
{
    // Add v to the adjacency list of u along with it's weight w
    corridor_map[u].push_back({v, w});
}
 
void Maze::gameOfGolds(int start, int end)
{
 
    vector<pair<int, int>> ans(V + 1);
    for (int i = 1; i <= V; i++)
        ans[i] = {INT_MIN, -1};
    ans[start] = {0, -1};
    queue<int> q;
    q.push(start);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        list<pair<int, int>>::iterator i;
        for (i = corridor_map[u].begin(); i != corridor_map[u].end(); ++i)
        {
            if (ans[(*i).first].first < ans[u].first + (*i).second)
            {
                ans[(*i).first].first = ans[u].first + (*i).second;
                ans[(*i).first].second = u;
                q.push((*i).first);
            }
        }
    }
    cout << "The maximum amount of gold Sir Paul can pick is: " << endl;
    cout << ans[end].first << endl;
    vector<int> path;
    int temp = end;
    while (temp != -1)
    {
        path.push_back(temp);
        temp = ans[temp].second;
    }
    cout << "The Path to Be Followed is: " << endl;
    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (i != 0)
            cout << path[i] << " -> ";
        else
            cout << path[i];
    }
}
 
int main()
{
    cout << "Enter the number of corridors :\n";
    int n;
    cin >> n;
    int weights[n], init_node[n], final_node[n];
    set<int> s;
 
    cout << "Enter the amount of gold in each corridor :\n";
    for (int i = 0; i < n; i++)
        cin >> weights[i];
 
    cout << "Enter the initial points of corridors :\n";
    for (int i = 0; i < n; i++)
    {
        cin >> init_node[i];
        s.insert(init_node[i]);
    }
 
    cout << "Enter the final points of corridors :\n";
    for (int i = 0; i < n; i++)
    {
        cin >> final_node[i];
        s.insert(final_node[i]);
    }
 
    int no_of_vertices = s.size();
    Maze m(no_of_vertices);
    for (int i = 0; i < n; i++)
        m.addCorridor(init_node[i], final_node[i], weights[i]); // add a corridor with the bag of gold(w) from u -> v
 
    int start_node, end_node;
    cout << "Enter starting and exiting point :\n";
    cin >> start_node >> end_node;
    m.gameOfGolds(start_node, end_node);
    return 0;
}
/*
Test Cases:
 
1.
12
3 5 22 7 9 25 3 1 2 6 1 5
1 1 1 2 3 1 3 4 6 5 6 7
2 2 4 3 4 4 5 6 7 8 8 8
1 8
 
2.
6
1 2 3 4 5 6
1 2 3 4 2 5
2 3 4 6 5 4
1 6
 
3.
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
2 2 2 2 2 2 2 2 2 2
2 2 2 2 2 2 2 2 2 2
2 2 2 2 2 2 2 2 2 2
 
1 2 3 4 5 6 7 8 9 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30
 
2 3 4 5 6 7 8 9 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30 31
*/