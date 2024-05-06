#include<bits/stdc++.h>
using namespace std;

class Graph{
    int vertices;
    int n;
    unordered_map<int,vector<int>>adjlist;
    public:
    graph() 
    {
        vertices=0;
    }
    void addedge(int i,int j) 
    {
        adjlist[i].push_back(j);
        adjlist[j].push_back(i);
    }

    void input() 
    {
        cout<<"Enter a number of vertices :- ";
        cin>>n;
        vertices=n;
        cout<<"Input"<<endl;
        for (int i=0;i<vertices;i++) 
        {
            int v1;
            cout<<"Enter a vertex :- ";
            cin>>v1;
            cout<<endl;
            int cnt;
            cout<<"Enter number of adjacent vertices :- ";
            cin>>cnt;
            cout<<endl;
            for (int j=0;j<cnt;j++) {
                int v2;
                cout<<"Enter a adjacent vertex:- ";
                cin>>v2;
                addedge(v1,v2);
                addedge(v2,v1);
                cout<<endl;
            }
        }
    }

    int find(map<int,vector<int>>&level,int id) 
    {
        for (auto i:level) {
            for (auto j:i.second) {
                if (j==id) {
                    return i.first;
                }
            }
        }
        return -1;
    }

    void dfs(int st,vector<int>&ans,map<int,int>&visited,map<int,vector<int>>&level) 
    {
        visited[st]=1;
        ans.push_back(st);
        for (auto u:adjlist[st]) {
            if (visited.find(u)==visited.end()) {
                int val=find(level,st);
                level[val+1].push_back(u);
                cout<<"Node visited :-"<<u<<", Level :-"<<val+1<<endl;
                dfs(u,ans,visited,level);
            }
        }
    }
    
    void dfs_print(int v) {
        cout<<endl;
        map<int,int>visited;
        vector<int>ans;
        map<int,vector<int>>level;
        level[0].push_back(v);
        dfs(v,ans,visited,level);
        for (auto i:ans) {
            cout<<i<<" ";
        }
        cout<<endl;
        cout<<"Level wise:- "<<endl;
        for (auto i:level) {
            cout<<"level "<<i.first<<" -> ";
            for (auto j:i.second) {
                cout<<j<<" ";
            }
            cout<<endl;
        }
    }

    void bfs(int start) {
        queue<int> q;
        map<int,int> visited;
        map<int,vector<int>> level;
        vector<int>ans;
        q.push(start);
        visited[start] = 1;
        level[0].push_back(start);
        BFSRec(q, visited, level);
        for(auto i:ans){
            {cout<<i<<" ";}
        }
        for(auto i:level){
            cout<<"Level"<<i.first<<"->";
            for(auto j:i.second){
                cout<<j<<" ";
            }
            cout<<endl;
        }
    }

    void bfs_rec(queue<int> &q,map<int,int>&visited,map<int,vector<int>>&level,vector<int>&ans){
        if (q.empty())
            return;

        int current = q.front();
        q.pop();
        ans.push_back(current); // Store the current node in traversal order

        for (auto j : adjlist[current]) {
            if (visited.find(j)==visited.end()) {
                visited[j] = 1;
                int val=find(level,current);
                cout<<"Visited node is:-"<<j<<"at a level"<<val+1<<endl;
                level[val+1].push_back(j);
                q.push(j);
            }
        }
        BFSRec(q, visited, level, ans);
    }
};

int main(){
     Graph g;

    int choice;

    char c='y';

    while (c=='y') {
        cout<<"========MENU==========\n1.Create\n2.BFS\n3.DFS\n4.Exit."<<endl;
        cout<<"Enter a choice :- ";
        cin>>choice;

        if (choice==1) {
            g.input();
        }

        else if (choice==2) {
            int st;
            cout<<"Enter a start node :- ";
            cin>>st;
            g.bfs(st);
        }

        else if (choice==3) {
            int st;
            cout<<"Enter a start node :- ";
            cin>>st;
            g.dfs_print(st);
        }

        else
        break;

        cout<<"Do you want to continue :- ";
        cin>>c;
    }

    return 0;
}