#include <iostream>
#include <vector>
using namespace std;

class NQueens{
    int N;
    vector<vector<int>>back_tracking;
    vector<vector<int>>branch_bound;
    vector<vector<int>>slash_diag;
    vector<vector<int>>backslash_diag;
    int num_diags;
    vector<bool>slash_lookup;
    vector<bool>backslash_lookup;
    vector<bool>row_lookup;
public:
    NQueens(int n): N(n), back_tracking(n, vector<int>(n,0)),
     branch_bound(n, vector<int>(n,0)),num_diags(2*n-1),
     slash_diag(n,vector<int>(n,0)),backslash_diag(n,vector<int>(n,0)),
     row_lookup(n,false),slash_lookup(2*n-1, false),backslash_lookup(2*n-1,false)
    {
        initMatrices();
    }

    void initMatrices(){
        for (int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                slash_diag[i][j]=i+j;
                backslash_diag[i][j]=i-j+N-1;
            }
        }
    }

    bool checkOverlap(int i, int j){
        for(int k=0;k<N;k++){
            if(back_tracking[i][k]==1 || back_tracking[k][j]==1 || back_tracking[i][j]==1)
            return true;
        }

        for(int k=0; k<N; k++){
            for(int l=0;l<N;l++){
                if((i+j==k+l) || (i-j==k-l)){
                    if(back_tracking[k][l]==1)
                    return true;
                }
            }
        }
        return false;
    }

    bool backTracking(int n){
        if(n==0)
        return true;
        for(int i=0;i<N;i++){
            for(int j=0; j<n; j++){
                if((!checkOverlap(i,j)) && (back_tracking[i][j]==0)){
                    back_tracking[i][j]=1;
                    if(backTracking(n-1)){
                        return true;
                    }
                    back_tracking[i][j]=0;
                }
            }
        }
        return false;
    }

    bool isSafe(int r, int c){
        if(slash_lookup[slash_diag[r][c]]||backslash_lookup[backslash_diag[r][c]]|| row_lookup[r])
        return false;
        else
        return true;
    }

    bool branch_and_bound(int c){
        if(c>=N)
        return true;
        for(int i=0; i<N; i++){
            if(isSafe(i,c)){
                branch_bound[i][c]=1;
                row_lookup[i]=true;
                slash_lookup[slash_diag[i][c]]=true;
                backslash_lookup[backslash_diag[i][c]]=true;
                if(branch_and_bound(c+1))
                return true;
                branch_bound[i][c]=0;
                row_lookup[i]=false;
                slash_lookup[slash_diag[i][c]]=false;
                backslash_lookup[backslash_diag[i][c]]=false;
            }
        }
        return false;
    }

    void runner(){
        cout<<"\nSolution using Backtracking: "<<endl;
        backTracking(N);
        for (auto& row: back_tracking ){
            for (int cell:row){
                if(cell==1)
                cout<<"Q";
                else
                cout<<"-";
            }
            cout<<endl;
        }
        cout<<"\n Solution using Branch and Bound: "<<endl;
        branch_and_bound(0);
        for (auto& row: branch_bound ){
            for (int cell:row){
                if(cell==1)
                cout<<"Q";
                else
                cout<<"-";
            }
            cout<<endl;
        }
    }
};

int main(){
    cout<<"Enter the number of the queens:";
    int n;
    cin>>n;
    if(n>3){
    NQueens g(n);
    g.runner();}
    else{
        cout<<"Not possible to perform NQueens for less than 3 queens."
    }
    return 0;
}