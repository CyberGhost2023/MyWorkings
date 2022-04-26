 int find(int par[],int ind)
    {
        if(par[ind]==-1)
            return ind;
        return par[ind]=find(par,par[ind]);
    }
    
    void unite(int par[],int rank[],int x,int y){
        int s1=find(par,x);
        int s2=find(par,y);
        if(s1!=s2)
        {
            if(rank[s1]>rank[s2])
            {
                par[s2]=s1;
                rank[s1]+=s2;
            }
            else
            {
                par[s1]=s2;
                rank[s2]+=s1;
            }
        }
    }
    
    int kruskal(vector<vector<int>> &edges)
    {
        int n=edges.size(),sum=0;        
        int par[n],rank[n];
        for(int i=0;i<n;i++)
        {
            par[i]=-1;
            rank[i]=1;
        }
        sort(edges.begin(),edges.end());
        for(auto edge:edges)
        {
            int w=edge[0];
            int x=edge[1];
            int y=edge[2];
            if(find(par,x)!=find(par,y))
            {
                unite(par,rank,x,y);
                sum+=w;
            }
        }
        return sum;
    }
    
