#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

#define N 5
#define INF 10e7
#define min(a,b) ((a>b)?b:a)

static const int M = 1 << (N-1);
// Store the distance between cities
int g[N][N] = {{0,3,INF,8,9},
               {3,0,3,10,5},
               {INF,3,0,4,3},
               {8,10,4,0,20},
               {9,5,3,20,0}};
// Save the minimum distance from vertex i to the starting point in state s
int dp[N][M] ;
// Save the path
vector<int> path;

// Core function, calculate the dp array in dynamic programming
void TSP(){
    // Initialize dp[i][0]
    for(int i = 0 ; i < N ;i++){
        dp[i][0] = g[i][0];
    }
    // Calculate dp[i][j], update the column before updating the row
    for(int j = 1 ; j < M ;j++){
        for(int i = 0 ; i < N ;i++ ){
            dp[i][j] = INF;
            // If node i is included in set j (or state j), it does not meet the condition and exit
            if( ((j >> (i-1)) & 1) == 1){
                continue;
            }
            for(int k = 1 ; k < N ; k++){
                if( ((j >> (k-1)) & 1) == 0){
                    continue;
                }
                if( dp[i][j] > g[i][k] + dp[k][j^(1<<(k-1))]){
                    dp[i][j] = g[i][k] + dp[k][j^(1<<(k-1))];
                }
            }
        }
    }
}

// Check if all nodes have been visited, excluding node 0
bool isVisited(bool visited[]){
    for(int i = 1 ; i<N ;i++){
        if(visited[i] == false){
            return false;
        }
    }
    return true;
}

// Get the optimal path and save it in path, and find the shortest path nodes based on the dynamic programming formula in reverse order
void getPath(){
    // Visited node array
    bool visited[N] = {false};
    // Predecessor node number
    int pioneer = 0 ,min = INF, S = M - 1,temp ;
    // Add the starting node number to the container
    path.push_back(0);

    while(!isVisited(visited)){
        for(int i=1; i<N;i++){
            if(visited[i] == false && (S&(1<<(i-1))) != 0){
                if(min > g[i][pioneer] + dp[i][(S^(1<<(i-1)))]){
                    min = g[i][pioneer] + dp[i][(S^(1<<(i-1)))] ;
                    temp = i;
                }
            }
        }
        pioneer = temp;
        path.push_back(pioneer);
        visited[pioneer] = true;
        S = S ^ (1<<(pioneer - 1));
        min = INF;
    }
}

// Output the path
void printPath(){
    cout<<"The minimum path is: ";
    vector<int>::iterator  it = path.begin();
    for(it ; it != path.end();it++){
        cout<<*it<<"--->";
    }
    // Output the starting point number separately
    cout<<0;
}

int main()
{
    TSP(); // Function call to TSP
    cout<<"The minimum value is: "<<dp[0][M-1]<<endl; // Output the minimum value
    getPath(); // Function call to getPath
    printPath(); // Function call to printPath
    return 0;
}
