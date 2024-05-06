#include <bits/stdc++.h>
#define n 3
using namespace std;

class node{
    int mat[n][n];
    int level,cost;
    int x,y;
    node* parent;
    public:
    friend class Solution;
};

class Solution{
    public:
    class cmp{
        public:
        bool operator()(node* lhs,node* rhs){
            return(lhs->cost + lhs->level) > (rhs->cost + rhs->level);
        }
    };
    void printmat(int mat[n][n]){
        for(int i =0;i<n; i++){
            for(int j =0; j<n; j++){
                cout<<mat[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    void printPath(node* root){
        if(root == nullptr) return;
        printPath(root->parent);
        cout<<endl;
        cout<<"g(n) :"<<root->level<<endl;
        cout<<"h(n) :"<<root->cost<<endl;
        cout<<"f(n) :"<<(root->cost + root->level)<<endl;
        printmat(root->mat);
        cout<<endl;
    }
    bool isSafe(int r,int c){
        return (r >= 0 && r< n && c >=0 && c < n);
    }
    node* NewNode(int mat[n][n],int x, int y,int nx, int ny,int level,node* par){
        node* Node = new node;
        Node->parent = par;
        for(int i =0; i<n; i++){
            for(int j =0; j<n; j++){
                Node->mat[i][j] = mat[i][j];
            }
        }
        swap(Node->mat[x][y],Node->mat[nx][ny]);
        Node->x = nx;
        Node->y = ny;
        Node->cost = INT_MAX;
        Node->level = level;
        return Node;
    }
    int calcCost(int initial[n][n], int final[n][n]){
        int cost = 0;
        for(int i =0; i<n; i++){
            for(int j =0; j<n; j++){
                if(initial[i][j] && initial[i][j] != final[i][j]){
                    cost++;
                }
            }
        }
        return cost;
    }
    void solve(int initial[n][n], int final[n][n],int x, int y){
        priority_queue<node*,vector<node*>,cmp>pq;
        node* root;
        root = NewNode(initial,x,y,x,y,0,nullptr);
        root->cost =calcCost(initial,final);
        pq.push(root);
        int xdir[] = {1,0,-1,0};
        int ydir[] = {0,-1,0,1};

        while(!pq.empty()){
            node* curr;
            curr = pq.top();
            pq.pop();

            if(curr->cost == 0){
                printPath(curr);
                return;
            }

            int currx = curr->x;
            int curry = curr->y;

            for(int i =0;i<4; i++){
                int newx = currx + xdir[i];
                int newy = curry + ydir[i];
                if(isSafe(newx,newy)){
                    // printmat(curr->mat);
                    node* child = NewNode(curr->mat,currx,curry,newx,newy,curr->level+1,curr);
                    child->cost = calcCost(child->mat,final);
                    pq.push(child);
                }
            }
        }
    }
};

int main()
{
    int initial[n][n];
    int final[n][n];
    int xc,yc,x;
    cout<<"Initial Matrix :"<<endl;
    for(int i =0; i<n; i++){
        for(int j =0; j<n; j++){
            cin>>initial[i][j];
            if(initial[i][j] == 0){
                xc = i;
                yc = j;
            }
        }
    }
    cout<<"Final Matrix :"<<endl;
    for(int i =0; i<n; i++){
        for(int j =0; j<n; j++){
            cin>>x;
            final[i][j] = x;
        }
    }
    Solution s;
    s.solve(initial,final,xc,yc);
    return 0;
}
