#include<bits/stdc++.h>
using namespace std;

class Prim{
    private:
    int V;
    map<string, int>name_id;
    map<int,string>id_name;
    vector<vector<int>>graph;
    public:

    void getInput() {
        int e;
        cout << "Enter the number of cities: ";
        cin >> V;

        graph.assign(V, vector<int>(V, 0));

        cout << "Enter the city names:" << endl;
        for (int i = 0; i < V; i++) {
            string temp;
            cout << "Enter City " << i + 1 << ": ";
            cin >> temp;
            name_id[temp]=i;
            id_name[i]=temp;
        }

        cout << "Enter the number of routes: ";
        cin >> e;

        for (int i = 0; i < e; i++) {
            cout << "Route " << i + 1 << endl;
            string c1, c2;
            int wt;
            cout << "Enter City 1: ";
            cin >> c1;
            cout << "Enter City 2: ";
            cin >> c2;
            cout << "Enter the Travel Cost: ";
            cin >> wt;
            graph[name_id[c1]][name_id[c2]] = wt;
            graph[name_id[c2]][name_id[c1]] = wt;
        }
    }

    int minKey(vector<int> key, vector<bool> mstSet){
    int min = INT_MAX, min_index;
     for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
    }

    void primMST(){
        vector<int> parent(V);
        vector<bool> visited(V);
        vector<int> key(V);
        for(int i=0;i<V;i++){
            key[i]=INT_MAX;
            visited[i]=false;
        }
        cout<<"\nEnter the Source City:";
        string c;
        cin>>c;
        key[name_id[c]]=0;
        parent[name_id[c]]=-1;
        for(int cnt=0;cnt<V-1; cnt++){
            int u=minKey(key,visited);
            visited[u]=true;
            for(int v=0;v<V;v++){
                if(graph[u][v] && visited[v]==false && graph[u][v]<key[v])
                {parent[v]=u;
                key[v]=graph[u][v];}
            }
        }
        printMST(parent,graph);
    }

    void printMST(vector<int> parent, vector<vector<int>> graph)
    {
        cout << "Edge \tWeight\n";
        int sum=0;
        for (int i = 0; i < V; i++)
            {if(parent[i]==-1){continue;}
                cout << id_name[parent[i]] << " - " << id_name[i] << " \t"
             << graph[i][parent[i]] << " \n";
            sum+=graph[i][parent[i]];}
            cout<<"Total cost of Routes:"<<sum;
    }
};

int main(){
    Prim p;
    p.getInput();
    p.primMST();
}
