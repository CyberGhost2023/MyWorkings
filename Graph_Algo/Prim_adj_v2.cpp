//Prim Using adjacency List but with V^2 tc

int prim(vector<vector<pair<int,int>>> &adj)
    {
        int n=adj.size(),sum=0;
        int vis[n],key[n],par[n];
        for(int i=0;i<n;i++)
        {
            vis[i]=0,key[i]=INT_MAX,par[i]=-1;
        }
        key[0]=0;
        for(int cnt=0;cnt<n-1;cnt++)
        {
            int mx=INT_MAX,ind;
            for(int j=0;j<n;j++)
            {
                if(vis[j]==0 && key[j]<=mx)
                { 
                    mx=key[j];
                    ind=j;
                }
            }
            sum+=mx;
            vis[ind]=1;
            for(auto x:adj[ind])
            {
                if(vis[x.first]==0 && x.second<key[x.first])
                {
                    key[x.first]=x.second;
                }
            }   
        }
        int mx=INT_MAX,ind;
            for(int j=0;j<n;j++)
            {
                if(vis[j]==0 && key[j]<=mx)
                { 
                    mx=key[j];
                    ind=j;
                }
            }
        sum+=mx;
        return sum;
    }
