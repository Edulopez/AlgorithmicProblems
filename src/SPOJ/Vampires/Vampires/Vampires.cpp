// Vampires.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<vector>
#include<string>
#include<set>
#include <queue>
#include <cmath>
using namespace std;

#define INF  100000000000


struct state
{
    int u,sun,dist;
    state(int _u=0,int _sun=0,int _dist=0):u(_u),sun(_sun),dist(_dist){}

    bool operator<(const state &S)const{
        return sun != S.sun ? (sun > S.sun) : (dist > S.dist);
    }
};
struct GRAPH
{
    int N; // number of nodes
    vector< vector<int> > G; // adjacency list
    vector< vector<int> > D; // adjacency distance
    vector< vector<int> > H; // adjacency sun

    GRAPH(int n)
    {
        N = n;
        G = vector< vector<int> >(n);
        D = vector< vector<int> >(n);
        H = vector< vector<int> >(n);
    }
    void add_edge(int u,int v,int distance,int sun,bool undirected = true)
    {
        G[u].push_back(v);
        D[u].push_back(distance);
        H[u].push_back(sun);
        if(undirected)
        {
            G[v].push_back(u);
            D[v].push_back(distance);
            H[v].push_back(sun);
        }
    }
    state distra(int source, int sink)
    {
        priority_queue<state>  PQsun;

        state Dist[10005];
        for(int i=0 ; i<N ; ++i){
            Dist[i]=state(i,INF,INF);
        }
        
        Dist[source] = state(source,0,0);
        PQsun.push(state(source,0,0));

        while(!PQsun.empty())
        {
            state opt = PQsun.top();          
            PQsun.pop();          
            if( opt < Dist[opt.u] )continue;
            
            if (opt.u == sink)
            {
                return  state(opt.u,opt.sun,opt.dist);
            }
            for(int j=0 ; j< G[opt.u].size() ; ++j)
            {
                state near (G[opt.u][j] , H[opt.u][j]+opt.sun,D[opt.u][j]+opt.dist );
                if( Dist[near.u] < near )
                {
                    Dist[near.u]= near;
                    PQsun.push(near);
                }
            }
        }
        return state(-1,-1,-1);
    }
};
int main()
{
    int A,B,C,D , E , S, T, N;
    cin >> N>> E>> S>> T;
    GRAPH G(N+5);

    while(E-->0)
    { 
        int dist;

        cin >> A >> B >> C >>D;
        G.add_edge(A,B,C , C-D);
    }
    state Res = G.distra(S,T);

    cout<<Res.dist<<" "<<Res.sun;
    return 0;
}

