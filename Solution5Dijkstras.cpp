#include<bits/stdc++.h>
using namespace std;
class graph {
    map<string,int>name_id;
    map<int,string>id_name;
    map<int,vector<pair<int,int>>>adj;
    int v;
    public:

    void addedge(int a,int b,int y) {
        adj[a].push_back({b,y});
        adj[b].push_back({a,y});

    }

    void input() {
        int id=0;
        cout<<"Enter the no. of cities:";
        cin>>v;
        for (int i=0;i<v;i++) {
            string a,b;
            int c;
            cout<<"Enter a name of city :- ";
            cin>>a;
            cout<<endl;
            if (name_id.find(a)==name_id.end()) {
                id_name[id]=a;
                name_id[a]=id++;
            }
            else {
                int e=name_id[a];
                id_name[e]=a;
            }
            int k;
            cout<<"Enter number of adjacent cities:- ";
            cin>>k;

            for (int j=0;j<k;j++) {
                string t;
                int g;
                cout<<"Enter a adjacent city name :- ";
                cin>>t;
                cout<<"Enter its distance :- ";
                cin>>g;
                cout<<endl;
                if (name_id.find(t)==name_id.end()) {
                    id_name[id]=t;
                    name_id[t]=id++;
                }
                else {
                    int e=name_id[t];
                    id_name[e]=t;
                }
                int src=name_id[a];
                int dest=name_id[t];
                addedge(src,dest,g);          
            }
        }
    }
   
    void path(int dest,int src,map<int,int>parent) {
        vector<int>ans;
        ans.push_back(dest);
        int node=dest;
        while (parent[node]!=node) {
            ans.push_back(parent[node]);
            node=parent[node];
        }
        reverse(ans.begin(),ans.end());
        for (auto i:ans) {
            cout<<id_name[i]<<" -> ";
        }
        cout<<endl;
    }
   
    void plan() {
        string h,de;
        cout<<"Enter a source city :- ";
        cin>>h;
        cout<<endl;
       
        cout<<"Enter a destination city :- ";
        cin>>de;
        cout<<endl;
       
        map<int,int>parent;
        int id=name_id[h];
        int de_id=name_id[de];
       
        vector<int>dist(v,INT_MAX);
       
        dist[id]=0;
        set<pair<int,int>>se;
       
        se.insert({0,id});

        while (!se.empty()) {

            auto top=*(se.begin());
            se.erase(se.begin());

            int d=top.first;
            int n=top.second;

            for (auto ng:adj[n]) {
                if (d+ng.second<dist[ng.first]) {
                    auto rec=se.find(make_pair(dist[ng.first],ng.first));
                    parent[ng.first]=n;        
                    if (rec!=se.end()) {
                        se.erase(rec);
                    }
                    dist[ng.first]=d+ng.second;
                    se.insert({dist[ng.first],ng.first});
                }
            }       
        }    
        for (int i=0;i<v;i++) {
            cout<<id_name[i]<<" "<<dist[i]<<endl;
        }       
        path(de_id,id,parent);       
    }
};

int main() {
    graph g;
    g.input();
    g.plan();
    return 0;
}
