#include<bits/stdc++.h>
using namespace std;

class graph{
    int v;
    map<string, int>name_id;
    map<int,string> id_name;
    unordered_map<int,vector<int>>adj;

    public:
    graph(){v=0;}

void addEdge(int src, int dest){
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}
    void input(){
        cout<<"Enter the total no.of cities:";
        cin>>v;
        int id=0;
        for(int i=0;i<v;i++){
            cout<<"Enter the name of the city:";
            string c1;
            cin>>c1;
            if(name_id.find(c1)==name_id.end()){
                id_name[id]=c1;
                name_id[c1]=id;
                id++;
            }
            int num;
            cout<<"Enter the no. of adjacent cities";
            cin>>num;
            for(int j=0;j<num;j++){
                cout<<"Enter the name of the adjacent city:";
                string c2;
                cin>>c2;
                if(name_id.find(c2)==name_id.end()){
                    id_name[id]=c2;
                    name_id[c2]=id;
                    id++;
                }
                int src=name_id[c1];
                int dest=name_id[c2];
                addEdge(src,dest);
            }
        }
        // for(auto cp: name_id){
        //     cout<<cp.first<<" "<<cp.second;
        // }
    }

    int find1(map<int,vector<int>>level,int node){
        for(auto row: level){
            for (auto j: row.second){
                if (j==node)
                return row.first;
            }
        }
        return -1;
    }

    void dfs_rec(int id, map<int,vector<int>>&level, vector<int>&ans, map<int,int>&visited){
        visited[id]=1;
        ans.push_back(id);
        for(auto i: adj[id]){
            if(visited.find(i)==visited.end()){
            int val=find1(level,id);
            level[val+1].push_back(i);
            cout<<"Visited node"<<id_name[i]<<"at level"<<val+1<<endl;
            dfs_rec(i, level,ans,visited);}
        }
    }

    void print_dfs(){
        cout<<"Enter the starting city:";
        string c1;
        cin>>c1;
        int id=name_id[c1];
        vector<int> ans;
        map<int, vector<int>>level;
        map<int,int> visited;
        level[0].push_back(id);
        dfs_rec(id, level,ans, visited);
        for(auto i:ans){cout<<i<<" ";}
        cout<<endl;
    }

    void bfs(){
        cout<<"Enter the starting city:";
        string c1;
        cin>>c1;
        int id=name_id[c1];
        queue<int> q;
        vector<int> ans;
        map<int,int>visited;
        map<int,vector<int>>level;
        q.push(id);
        visited[id]=1;
        level[0].push_back(id);
        bfs_rec(q,visited,ans,level);
        for(auto i:ans){cout<<i<<" ";}
        cout<<endl;
    }

    void bfs_rec(queue<int>&q, map<int,int>&visited, vector<int>&ans, map<int,vector<int>>&level){
        if(q.empty()){return;}
        int t=q.front();
        q.pop();
        ans.push_back(t);
        for(auto j: adj[t]){
            if(visited[j]==0){
                visited[j]=1;
                int val=find1(level,t);
                level[val+1].push_back(j);
                cout<<"visited"<<j<<"at level"<<val+1<<endl;
                q.push(j);
            }
        }
        bfs_rec(q,visited,ans,level);
        }
    };

int main(){
    graph g;
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
            g.bfs();
        }
        else if (choice==3) {
            g.print_dfs();
        }
        else
        break;
        cout<<"Do you want to continue :- ";
        cin>>c;
    }
    return 0;
}
