//prim usign adjacency list and ElogV

 int prim(vector<vector<pair<int,int>>> &adj)
    {
        int n=adj.size(),sum=0;
        int vis[n],key[n],par[n];
        for(int i=0;i<n;i++)
        {
            vis[i]=0,key[i]=INT_MAX,par[i]=-1;
        }
        key[0]=0;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        pq.push({0,0});
       while(!pq.empty())
       {
           int ind=pq.top().second;
           pq.pop();
           if(vis[ind])
               continue;
           vis[ind]=1;
           for(auto it:adj[ind])
           {
               int v=it.first;
               int wt=it.second;
               if(vis[v]==0 && wt<key[v])
               {
                   par[v]=ind;
                   key[v]=wt;
                   pq.push({wt,v});
               }
           }
       }
    }
